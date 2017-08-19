-- dump职业动画
-- usage: lua BattleAnimationDumper.lua [args]
-- by laqieer
-- 2017/8/13

require "lz77"

-- 关闭文件句柄并退出程序
--[[
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
--]]

-- 会用到的文件列表
files = {}

-- 关闭所有登记过的文件并退出程序，返回指定的退出码
function closeAllAndExit(exitCode)
	for key, value in pairs(files) do
		if(key ~= nil)
		then
			key:close()
		end
	end
	os.exit(exitCode)
end

-- 打开并登记到文件列表
-- 文件变量，文件名(可以包含路径)，打开方式
function openAndRegister(filename,mode)
	file = io.open(filename,mode)
	if(file == nil)
	then
		print('Error: Cannot open file '..filename..'\n')
		closeAllAndExit(-1)
	end
	files[file] = filename
	return file
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
-s			Enable the section name output (for linker script)
-d			Preserve temporary files for debugging
	]])
	closeAllAndExit(0);
end

-- 读取dump源ROM
-- rom = io.open(arg[1],"rb")
rom = openAndRegister(arg[1],"rb")
--[[
if(rom == nil)
then
	print('Error: Cannot open '..arg[1]..'\n')
	closeAllAndExit(-1)
end
--]]

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
					-- Fix: attempt to compare number with string
					para = tonumber(para)
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
				
handler['-s'] = function(para)
					enableSectonName = true
					p = p - 1;
				end
				
handler['-d'] = function(para)
					preserveTempFiles = true
					p = p - 1;
				end
				
-- 不认识的参数直接忽略掉
p = 2	-- 指向要处理的参数
while(arg[p] ~= nil)
do
	handler[arg[p]](arg[p+1])
	p = p + 2
end

-- dump出的动画的名字
if(name == nil)
then
	name = 'BattleAnimation_FE'..ver..'_'..string.format("0x%X",index)
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

-- 单字节

function str2byte(s)
	return string.byte(s,1)
end

function readByte(file)
	return str2byte(file:read(1))
end

-- 双字节

function str2short(s)
	return string.byte(s,1) + string.byte(s,2) * 0x100
end

function readShort(file)
	return str2short(file:read(2))
end

-- 4字节

function str2int(s)
	return string.byte(s,1) + string.byte(s,2) * 0x100 + string.byte(s,3) * 0x10000 + string.byte(s,4) * 0x1000000
end

function readInt(file)
	return str2int(file:read(4))
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
-- cs = io.open(path..'/'..name..'.c',"w")
cs = openAndRegister(path..'/'..name..'.c',"w")
--[[
if(cs == nil)
then
	print('Error: Cannot create output file\n')
	closeAllAndExit(-2)
end
--]]

-- 输出注释
cs:write([[// Generated by BattleAnimationDumper
// ]]..os.date("%Y/%m/%d %H:%M:%S")..'\n\n')

-- 输出要包含的头文件
-- cs:write([[#include	"FE7JBattleAnimation.h"
-- #include	"]]..name..[[_event.h"

-- ]])

cs:write([[#include	"FE7JBattleAnimation.h"

]])

-- 从汇编脚本引入标号
cs:write('extern const int '..name..'_data1;\n')
cs:write('extern const int '..name..'_data2;\n')
cs:write('extern const int '..name..'_data3;\n')
cs:write('extern const int '..name..'_data4;\n\n')
--[[
for mode=1,12 do
	cs:write('extern const int '..name..'_Mode'..mode..';\n')
end
cs:write('\n')
--]]

-- dump data1
-- cs:write('const int * const '..name..'_data1[] = {\n')
-- cs:write('const int const '..name..'_data1[] = {\n')
-- cs:write('const int '..name..'_data1[] = {\n')
-- 以标号引用代替绝对值
-- cs:write('const void *'..name..'_data1[] = {\n')
-- print(rom:seek())
-- rom:seek("set",pdata1 - 0x8000000)
-- print(pdata1 - 0x8000000)
-- print(rom:seek())
--[[
modeComment = {
'// Mode 1: Normal attack (Layered in front of the enemy)\n',
'// Mode 2: Normal attack (Layered behind the enemy)\n',
'// Mode 3: Critical attack (Layered in front of the enemy)\n',
'// Mode 4: Critical attack (Layered behind the enemy)\n',
'// Mode 5: Magic attack\n',
'// Mode 6: Critical magic attack\n',
'// Mode 7: Close range dodge\n',
'// Mode 8: Ranged dodge\n',
'// Mode 9: Standing animation\n',
'// Mode 10: Standing animation 2\n',
'// Mode 11: Ranged standing "animation"\n',
'// Mode 12: Dodged attack\n'
}
--]]
modeComment = {
'Normal attack (Layered in front of the enemy)\n',		-- Mode 1
'Normal attack (Layered behind the enemy)\n',			-- Mode 2
'Critical attack (Layered in front of the enemy)\n',	-- Mode 3
'Critical attack (Layered behind the enemy)\n',			-- Mode 4
'Magic attack\n',										-- Mode 5
'Critical magic attack\n',								-- Mode 6
'Close range dodge\n',									-- Mode 7
'Ranged dodge\n',										-- Mode 8
'Standing animation\n',									-- Mode 9
'Standing animation 2\n',								-- Mode 10
'Ranged standing "animation"\n',						-- Mode 11
'Dodged attack\n'										-- Mode 12
}
--[[
for mode=1,12 do
	-- cs:write('\t'..string.format("0x%X",readInt(rom))..',\t'..modeComment[mode])
	-- cs:write('\t'..string.format("0x%X",readInt(rom))..',\t// Mode '..mode..' : '..modeComment[mode])
	-- 以标号引用代替绝对值
	-- cs:write('\t&&'..name..'_Mode'..mode..',\t// '..modeComment[mode])
	-- error: field name not in record or union initializer
	-- error: label 'XXX_Mode1' referenced outside of any function
	-- 不可行，因为C语言中标号只能定义在语句前，改用汇编

	-- error: initializer element is not constant
	-- cs:write('\t&'..name..'_Mode'..mode..' - &'..name..'_data2,\t// '..modeComment[mode])
	-- 计算偏移改到汇编中
	
--	cs:write('\t'..readInt(rom)..',\t')
--	cs:write('\t'..rom:read(4)..',\t')
--	rom:seek(cur,4)
end
--]]

-- cs:write('\t0,0,0,0,0,0,0,0,0,0,0,0\n};\n\n')

-- dump动画结构体

-- 添加段名以便于在链接脚本中指定该段的位置(可选)
if(enableSectonName == true)
then
	cs:write([[__attribute__((section(".]]..name..[[")))
]])
end 

cs:write('const BattleAnimation '..name..' = {\n')
cs:write('\t'..'\"'..identifier..'\",\t// Identifier\n')
-- cs:write('\t'..string.format("0x%X",pdata1)..',\t// Mode divider\n')
-- cs:write('\t'..name..'_data1,\t// Mode divider\t// '..string.format("0x%X",pdata1)..'\n')
-- cs:write('\t'..name..'_data1,\t// Mode divider\n')
cs:write('\t&'..name..'_data1,\t// Mode divider\n')
-- cs:write('\t'..string.format("0x%X",pdata2)..',\t// Script\n')
-- cs:write('\t'..name..'_data2,\t// Script\t// '..string.format("0x%X",pdata2)..'\n')
-- cs:write('\t'..name..'_data2,\t// Script\n')
cs:write('\t&'..name..'_data2,\t// Script\n')
if(dumpAll == true)
then
	cs:write('\t&'..name..'_data3,\t// Right X Y Position\n')
	cs:write('\t&'..name..'_data4,\t// Left X Y Position\n')
	cs:write('\t&'..name..'_data5,\t// Palette Group\n')
else
	cs:write('\t'..string.format("0x%X",pdata3)..',\t// Right X Y Position\n')
	cs:write('\t'..string.format("0x%X",pdata4)..',\t// Left X Y Position\n')
	cs:write('\t'..string.format("0x%X",pdata5)..'\t// Palette Group\n')
end
cs:write('};\n')

if(dumpAll == true)
then
	-- dump data5
	data5,data5size = lz77:decode(rom,pdata5 - 0x8000000)
	paletteComment = {'Player','Enemy','NPC','4th(arena)'}
	cs:write('\nconst u16 '..name..'_data5[] = {\n')
	for i=1,data5size,2 do
		cs:write(string.format("0x%04X,",string.byte(data5[i]) + string.byte(data5[i+1]) * 0x100))
		if((i+0x11)%0x20 == 0)
		then
			cs:write('\t// '..paletteComment[(i+0x11)/0x20])
		end
		if((i+1)%0x10 == 0)
		then
			cs:write('\n')
		end
	end
	cs:write('};\n')
	-- dump data3&4
	data3,data3size = lz77:decode(rom,pdata3 - 0x8000000)
	data4,data4size = lz77:decode(rom,pdata4 - 0x8000000)
	oam = openAndRegister(path..'/'..name..'_OAMInfo.s','w')
	oamInc = openAndRegister(path..'/'..name..'_OAMInfo.inc','w')
	scriptInc = openAndRegister(path..'/'..name..'_event.inc','w')
	oam:write([[@ Generated by BattleAnimationDumper
@ ]]..os.date("%Y/%m/%d %H:%M:%S")..'\n\n')
	oamInc:write([[@ Generated by BattleAnimationDumper
@ ]]..os.date("%Y/%m/%d %H:%M:%S")..'\n\n')
	scriptInc:write([[@ Generated by BattleAnimationDumper
@ ]]..os.date("%Y/%m/%d %H:%M:%S")..'\n\n')
	oamInc:write('\t.global\t'..name..'_data3\n')
	oamInc:write('\t.global\t'..name..'_data4\n')
	scriptInc:write('\t.extern\t'..name..'_data3\n')
	scriptInc:write('\t.extern\t'..name..'_data4\n')
	oam:write("\t.include\t"..path..'/'..name..'_event.inc\n\n')
	-- data3
	oam:write('\t.section\t.rodata\n\t.align\t4\n\n')
	oam:write(name..'_data3:\n\n')
	frameSection = {}	-- 分段偏移表,以便翻译data2中的86
	-- frame = 1
	-- 为了与官方的计数统一，改成从0开始计数
	frame = 0
	frameSection[0] = frame
	oam:write(name..'_frame_R_'..frame..':\n')
	for i=0,data3size-1,2 do
		if(i%12 == 0)
		then
			oam:write('\n\t.hword')
		end
		oam:write(string.format('\t0x%04X,',string.byte(data3[i+1]) + string.byte(data3[i+1+1]) * 0x100))
		if(i>9)
		then
			if(string.byte(data3[i+1+2-12]) == 1 and (i+2)%12 == 0)
			then
				frame = frame + 1
				frameSection[i+2] = frame
				oam:write('\n\n'..name..'_frame_R_'..frame..':\n')
			end
		end
	end
	oam:write('\n')
	for i=0,frame-1 do
		oamInc:write('\t.global\t'..name..'_frame_R_'..i..'\n')
		scriptInc:write('\t.extern\t'..name..'_frame_R_'..i..'\n')
	end
	-- data4
	oam:write('\t.section\t.rodata\n\t.align\t4\n\n')
	oam:write(name..'_data4:\n\n')
	-- frame = 1
	frame = 0
	oam:write(name..'_frame_L_'..frame..':\n')
	for i=0,data4size-1,2 do
		if(i%12 == 0)
		then
			oam:write('\n\t.hword')
		end
		oam:write(string.format('\t0x%04X,',string.byte(data4[i+1]) + string.byte(data4[i+1+1]) * 0x100))
		if(i>9)
		then
			if(string.byte(data4[i+1+2-12]) == 1 and (i+2)%12 == 0)
			then
				frame = frame + 1
				oam:write('\n\n'..name..'_frame_L_'..frame..':\n')
			end
		end
	end
	oam:write('\n')
	for i=0,frame-1 do
		oamInc:write('\t.global\t'..name..'_frame_L_'..i..'\n')
		scriptInc:write('\t.extern\t'..name..'_frame_L_'..i..'\n')
	end
end

-- dump data2

-- 虽然tonc不建议把数据放在头文件中...
-- script = io.open(path..'/'..name..'_event.h',"w")
-- script = openAndRegister(path..'/'..name..'_event.h',"w")
-- 改用汇编写脚本
script = openAndRegister(path..'/'..name..'_event.s',"w")
rom:seek("set",pdata2 - 0x8000000)
-- 若data2压缩过
if(readByte(rom) == 0x10)
-- 读取data2的大小
then
	--[[
	-- 这里假设压缩后数据大小不超过压缩前的
	data2size = readShort(rom)
	rom:seek("set",pdata2 - 0x8000000)
	compressedScript = rom:read(data2size)
	-- data2lz = io.open(path..'/'..name..'_data2.lz',"wb")
	data2lz = openAndRegister(path..'/'..name..'_data2.lz',"wb")
	data2lz:write(compressedScript)
	-- 不及时关闭这个文件会影响gbalzss对它的访问
	data2lz:close()
	-- 关闭文件后不及时从访问文件列表里删除对应的表项会导致关闭所有文件并退出程序的时候仍然尝试去关闭这个已经被关闭的文件
	-- data2lz = nil
	-- table.remove(files,data2lz)
	files[data2lz] = nil
	-- 要求: 把gbalzss所在路径添加到环境变量
	os.execute("gbalzss d "..path..'/'..name..'_data2.lz'..' '..path..'/'..name..'_data2.bin')
	-- 隐患: 如果因为种种原因无法得到无压缩的data2二进制文件，会陷入无限循环等待
	repeat
		data2bin = io.open(path..'/'..name..'_data2.bin','rb')
	until(data2bin ~= nil)
	files[data2bin] = path..'/'..name..'_data2.bin'
	--]]
	data2bin = io.open(path..'/'..name..'_data2.bin','wb')
	decompressedData2,data2size = lz77:decode(rom,pdata2 - 0x8000000)
	for k,v in ipairs(decompressedData2) do
		data2bin:write(v)
	end
	data2bin:close()
	data2bin = io.open(path..'/'..name..'_data2.bin','rb')
else
	-- 若rom内的data2本身就没有压缩
	--[[
	print('Error: Uncompressed data2 has not been supported yet\n')
	closeAllAndExit(-5)
	--]]
	data2bin = io.open(path..'/'..name..'_data2.bin','wb')
	rom:seek("cur",-1)
	mode = 0
	repeat
		p = rom:read(4)
		data2bin:write(p)
		if(str2int(p) == 0x80000000)
		then
			mode = mode + 1
		end
	until(mode == 12)
	data2size = data2bin:seek()
	data2bin:close()
	data2bin = openAndRegister(path..'/'..name..'_data2.bin','rb')
	decompressedData2 = {}
	for i=1,data2size do
		decompressedData2[i] = data2bin:read(1)
	end
	data2bin:seek("set")
end

-- 输出注释
-- script:write([[// Generated by BattleAnimationDumper
-- // ]]..os.date("%Y/%m/%d %H:%M:%S")..'\n\n')

script:write([[@ Generated by BattleAnimationDumper
@ ]]..os.date("%Y/%m/%d %H:%M:%S")..'\n\n')
script:write('\t.include\tBattleAnimationEventDef.inc\n\n')
-- script:write('#pragma once\n')
-- script:write('const unsigned int '..name..'_data2[] = {\n')
script:write('\t.section\t.rodata\n\t.align\t4\n\t.global\t'..name..'_data2\n')
script:write('\t.global\t'..name..'_data1\n\n')
--[[
for mode=1,12 do
	script:write('\t.global\t'..name..'_Mode'..mode..'\n')
end
--]]
-- 添加标号以便data1引用
-- script:write(name..'_Mode1:\t// '..modeComment[1])
script:write(name..'_data2:\n\n'..name..'_Mode1:'..'\t@ '..modeComment[1])

mode = 1

-- 为脚本加注释的函数表
ScriptComment = {}

-- 模式分隔
--[[
function EndMode()
	script:write('\t// End of Mode '..mode..' : '..modeComment[mode])
	-- 加标号以便在data1中引用
	if(mode < 12)
	then
		script:write('\n'..name..'_Mode'..mode+1..':\t// '..modeComment[mode+1])
	end
	mode = mode + 1
end
--]]
function EndMode()
	mode = mode + 1
	-- 加标号以便在data1中引用
	if(mode <= 12)
	then
		script:write('\n\n'..name..'_Mode'..mode..':\t@ '..modeComment[mode])
	end
end

ScriptComment[0x80000000] = EndMode

-- 指向前一个4字节
p0 = 0

-- 直接输出raw
--[[
for i=1,data2size,4 do
    p = readInt(data2bin)
	script:write('\t'..string.format("0x%X",p)..',')
	
	-- 若以0x86开头，则与接下来的8字节输出在同一行
	if((p < 0x86000000 or p >= 0x87000000) and (p0 < 0x86000000 or p0 >= 0x87000000))
	then
		script:write('\n')
	end
	
	-- 加注释
	if(ScriptComment[p] ~= nil)
	then
		ScriptComment[p]()
	end
	
	p0 = p
end
--]]

-- C80 分隔符
function C80H()
	script:write('EndMode')
	EndMode()
end

-- C85 
function C85H()
	script:write(string.format('Cmd 0x%X',string.byte(decompressedData2[i])))
end

-- C86 
function C86H()
	-- script:write(string.format('ShowFrame %d, %d, 0x%X, 0x%X',string.byte(decompressedData2[i]),string.byte(decompressedData2[i+2]),string.byte(decompressedData2[i+4])+string.byte(decompressedData2[i+5])*0x100+string.byte(decompressedData2[i+6])*0x10000+string.byte(decompressedData2[i+7])*0x1000000,string.byte(decompressedData2[i+8])+string.byte(decompressedData2[i+9])*0x100))
	script:write(string.format('ShowFrame %d, %d, 0x%X, %s',string.byte(decompressedData2[i]),string.byte(decompressedData2[i+2]),string.byte(decompressedData2[i+4])+string.byte(decompressedData2[i+5])*0x100+string.byte(decompressedData2[i+6])*0x10000+string.byte(decompressedData2[i+7])*0x1000000,name..'_frame_R_'..frameSection[string.byte(decompressedData2[i+8])+string.byte(decompressedData2[i+9])*0x100]..' - '..name..'_data3'))
	i = i + 8
end

-- 指令处理函数表
CmdHandler = {}
CmdHandler[0] = C80H
CmdHandler[5] = C85H
CmdHandler[6] = C86H

-- 改用汇编脚本
if(dumpAll ~= true)
then
	for i=1,data2size,4 do
		p = readInt(data2bin)
		-- script:write('\t.word\t'..string.format("0x%X",p))
		---[[
		if(not C86)
		then
			script:write('\t.word\t')
		end
		script:write(string.format("0x%X",p))
		--]]
	
		-- 加注释
		if(ScriptComment[p] ~= nil)
		then
			ScriptComment[p]()
		end
	
		-- 若以0x86开头，则与接下来的8字节输出在同一行
		if((p < 0x86000000 or p >= 0x87000000) and (p0 < 0x86000000 or p0 >= 0x87000000))
		then
			script:write('\n')
			C86 = false
		else
			script:write(', ')
			C86 = true
		end
		
		p0 = p
	end
else
	i = 1	
	while(i<data2size)
	do
		script:write('\n\t')
		CmdH = CmdHandler[string.byte(decompressedData2[i+3]) - 0x80]
		if( CmdH ~= nil)
		then
			CmdH()
		else
			script:write(string.format('.word\t0x%08X',string.byte(decompressedData2[i]) + string.byte(decompressedData2[i+1]) * 0x100 + string.byte(decompressedData2[i+2]) * 0x10000 + string.byte(decompressedData2[i+3]) * 0x1000000))
		end
		i = i + 4
	end
	script:write('\n')
end
-- 删除最后一个元素后的逗号
-- script:seek("cur",-1)
-- 不删也没事

-- 用汇编生成data1
script:write('\n'..name..'_data1:\n\n')
for mode=1,12 do
	script:write('\t'..'.word\t'..name..'_Mode'..mode..' - '..name..'_data2\n')
end
script:write('\t.word\t0,0,0,0,0,0,0,0,0,0,0,0\n')

-- script:write('};\n')
-- 改用汇编
script:write('\n\t.end\n')

-- 为了删除的时候不会出现Permission denied
data2bin:close()
-- files[data2bin] = nil

---[[
-- 删除临时文件
if(preserveTempFiles == nil)
then
	-- os.execute('rm '..path..'/'..name..'_data2.bin'..' '..path..'/'..name..'_data2.lz')
	os.execute('rm '..path..'/'..name..'_data2.bin')
end
--]]

-- 程序成功退出
closeAllAndExit(1)
