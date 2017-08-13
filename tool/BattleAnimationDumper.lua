-- dump职业动画
-- usage: lua BattleAnimationDumper.lua [args]
-- by laqieer
-- 2017/8/13

-- 关闭文件句柄并退出程序
function closeAllAndExit(exitCode)
--	关闭rom
	if(rom ~= nil)
	then
		io.close(rom)
	end
--	关闭输出
	if(cs ~= nil)
	then
		cs:close()
	end
	if(script ~= nil)
	then
		script:close()
	end
--	退出程序
	os.exit(exitCode)
end

-- 接收并处理命令行参数

-- 无参数则显示帮助信息
if(arg[1] == nil)
then
	print([[Dump Battle Animation From GBA FE ROM
	
Usage:		lua BattleAnimationDumper.lua rom [options]
Main options:
	
-v			Set the version of the game (Supported: 6,7,8)
-b			If the table has been repointed, set its new offset
-a			Dump all related data (Not only scripts and sections)
-i			Set the index of the animation
-n			Set the name for the animation
-o			Set the output path
	]])
	closeAllAndExit(0);
end

-- 读取dump源ROM
rom = io.open(arg[1],"rb")
if(rom == nil)
then
	print('Error: Cannot open '..arg[1]..'\n')
	closeAllAndExit(-1)
end

-- 职业动画指针表基址表
-- 日版和美版地址相同
baseTable = {}
baseTable['6'] = 0x6A0008
baseTable['7'] = 0xE00008
baseTable['8'] = 0xC00008

-- ROM版本(默认FE7)
ver = '7'

-- 是否dump脚本以外的数据(默认否，其他数据直接转指针，适用于dump本ROM里原本就存在的动画)
dumpAll = false

-- 要dump的动画的ID(默认第一个)
index = 1

-- dump出的动画的名字
name = 'BattleAnimation_FE'..ver..'_'..index

-- 输出路径(默认当前路径)
path = '.'

-- 参数处理函数表
handler = {}

handler['-v'] = function(para)
					if(para == '6' or para == '7' or para == '8')
					then
						ver = para
					else
						print('Error: Unsupported game version\n')
						closeAllAndExit(-3)
					end
				end

handler['-b'] = function(para)
					if(para < 0 or para > 0x2000000)
					then
						print('Error: Invalid base offset\n')
						closeAllAndExit(-4)
					else
						base = para
					end
				end

handler['-a'] = function(para)
					dumpAll = true
					p = p - 1
				end

handler['-i'] = function(para)
					if(para >= 0 and para < 0x10000)
					then
						index = para
					else
						print('Error: Invalid animation index\n')
						closeAllAndExit(-5)
					end
				end

handler['-n'] = function(para)
					name = para
				end
				
handler['-o'] = function(para)
					path = para
				end
				
-- 不认识的参数直接忽略掉
p = 2	-- 指向要处理的参数
while(arg[p] ~= nil)
do
	handler[arg[p]](arg[p+1])
	p = p + 2
end

-- 职业动画指针表基址
if(base == nil)
then
	base = baseTable[ver]
end

-- 要dump的动画地址
offset = base + 0x20 * (index - 1)
rom:seek("set",offset)

-- 读取标识符
identifier = rom:read(12)

-- 在末尾加标识符会导致末尾多出很多'\0'
-- if(identifier ~= nil)
-- then
	-- name = name..'_'..identifier
-- end

-- 字符转整数(单字节)
-- function char2int(s)
	-- if(s == nil)
	-- then
		-- return 0
	-- else
		-- return string.byte(s)
		-- -- return tonumber(string.byte(s))
	-- end
-- end

-- 4字节
function str2int(s)
	return string.byte(s,1) + string.byte(s,2) * 0x100 + string.byte(s,3) * 0x10000 + string.byte(s,4) * 0x1000000
end

-- 从文件当前位置读取一个整数
-- function readInt(file)
	-- local s = char2int(file:read(1))
	-- -- s = s + 0x100 * char2int(file:read(1))
	-- -- s = s + 0x10000 * char2int(file:read(1))
	-- -- s = s + 0x1000000 * char2int(file:read(1))
	-- return s
-- end

-- function readInt(file)
	-- if(file:read(4) == nil)
	-- then
		-- return 0
	-- else
		-- return string.unpack("<I4",file:read(4))
	-- end
-- end

function readInt(file)
	return str2int(file:read(4))
end

-- 字符串转整数
-- function str2int(s)
	-- if(s == nil)
	-- then
		-- return 0
	-- else
		-- -- 需要lua53
		-- return string.byte(s,1) + string.byte(s,2) * 0x100 + string.byte(s,3) * 0x10000 + string.byte(s,4) * 0x1000000
	-- end
-- end

-- 读取相关数据地址
-- pdata1 = str2int(rom:read(4))
-- pdata2 = str2int(rom:read(4))
-- pdata3 = str2int(rom:read(4))
-- pdata4 = str2int(rom:read(4))
-- pdata5 = str2int(rom:read(4))
pdata1 = readInt(rom)
pdata2 = readInt(rom)
pdata3 = readInt(rom)
pdata4 = readInt(rom)
pdata5 = readInt(rom)

-- print(type(pdata1))

-- 打印
-- print(string.format("0x%X",pdata1))

-- 创建输出C数据
cs = io.open(path..'/'..name..'.c',"w")

if(cs == nil)
then
	print('Error: Cannot create output file\n')
	closeAllAndExit(-2)
end

-- 输出注释
cs:write([[// Generated by BattleAnimationDumper
// ]]..os.date("%Y/%m/%d %H:%M:%S")..'\n\n')

-- 输出要包含的头文件
cs:write([[#include	"FE7JBattleAnimation.h"
#include	"]]..name..[[.h"

]])

-- dump data1
cs:write('const int * const '..name..'_data1[] = {\n')
-- print(rom:seek())
rom:seek("set",pdata1 - 0x8000000)
-- print(pdata1 - 0x8000000)
-- print(rom:seek())
modeComment = {
'//Mode 1: Normal attack (Layered in front of the enemy)\n',
'//Mode 2: Normal attack (Layered behind the enemy)\n',
'//Mode 3: Critical attack (Layered in front of the enemy)\n',
'//Mode 4: Critical attack (Layered behind the enemy)\n',
'//Mode 5: Magic attack\n',
'//Mode 6: Critical magic attack\n',
'//Mode 7: Close range dodge\n',
'//Mode 8: Ranged dodge\n',
'//Mode 9: Standing animation\n',
'//Mode 10: Standing animation 2\n',
'//Mode 11: Ranged standing "animation"\n',
'//Mode 12: Dodged attack\n'
}
for mode=1,12 do
	cs:write('\t'..string.format("0x%X",readInt(rom))..',\t'..modeComment[mode])
--	cs:write('\t'..readInt(rom)..',\t')
--	cs:write('\t'..rom:read(4)..',\t')
--	rom:seek(cur,4)
end
cs:write('\t0,0,0,0,0,0,0,0,0,0,0,0\n};\n\n')

-- dump data2

-- -- 若data2压缩过
-- if()
-- -- 读取data2的大小
-- then
-- --	data2size = 
-- end

-- 程序成功退出
closeAllAndExit(1)