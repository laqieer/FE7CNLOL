-- dumpְҵ����
-- usage: lua BattleAnimationDumper.lua [args]
-- by laqieer
-- 2017/8/13

require "lz77"

-- �ر��ļ�������˳�����
--[[
function closeAllAndExit(exitCode)
--	�ر�rom
	if(rom ~= nil)
	then
		io.close(rom)
	end
--	�ر����
	if(cs ~= nil)
	then
		cs:close()
	end
	if(script ~= nil)
	then
		script:close()
	end
--	�˳�����
	os.exit(exitCode)
end
--]]

-- ���õ����ļ��б�
files = {}

-- �ر����еǼǹ����ļ����˳����򣬷���ָ�����˳���
function closeAllAndExit(exitCode)
	for key, value in pairs(files) do
		if(key ~= nil)
		then
			key:close()
		end
	end
	os.exit(exitCode)
end

-- �򿪲��Ǽǵ��ļ��б�
-- �ļ��������ļ���(���԰���·��)���򿪷�ʽ
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

-- ���ղ����������в���

-- �޲�������ʾ������Ϣ
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

-- ��ȡdumpԴROM
-- rom = io.open(arg[1],"rb")
rom = openAndRegister(arg[1],"rb")
--[[
if(rom == nil)
then
	print('Error: Cannot open '..arg[1]..'\n')
	closeAllAndExit(-1)
end
--]]

-- ְҵ����ָ����ַ��
-- �հ�������ַ��ͬ
baseTable = {}
baseTable['6'] = 0x6A0008
baseTable['7'] = 0xE00008
baseTable['8'] = 0xC00008

-- ROM�汾(Ĭ��FE7)
ver = '7'

-- �Ƿ�dump�ű����������(Ĭ�Ϸ���������ֱ��תָ�룬������dump��ROM��ԭ���ʹ��ڵĶ���)
dumpAll = false

-- Ҫdump�Ķ�����ID(Ĭ�ϵ�һ��)
index = 1

-- ���·��(Ĭ�ϵ�ǰ·��)
path = '.'

-- ������������
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
				
-- ����ʶ�Ĳ���ֱ�Ӻ��Ե�
p = 2	-- ָ��Ҫ����Ĳ���
while(arg[p] ~= nil)
do
	handler[arg[p]](arg[p+1])
	p = p + 2
end

-- dump���Ķ���������
if(name == nil)
then
	name = 'BattleAnimation_FE'..ver..'_'..string.format("0x%X",index)
end

-- ְҵ����ָ����ַ
if(base == nil)
then
	base = baseTable[ver]
end

-- Ҫdump�Ķ�����ַ
offset = base + 0x20 * (index - 1)
rom:seek("set",offset)

-- ��ȡ��ʶ��
identifier = rom:read(12)

-- ��ĩβ�ӱ�ʶ���ᵼ��ĩβ����ܶ�'\0'
-- if(identifier ~= nil)
-- then
	-- name = name..'_'..identifier
-- end

-- �ַ�ת����(���ֽ�)
-- function char2int(s)
	-- if(s == nil)
	-- then
		-- return 0
	-- else
		-- return string.byte(s)
		-- -- return tonumber(string.byte(s))
	-- end
-- end

-- ���ֽ�

function str2byte(s)
	return string.byte(s,1)
end

function readByte(file)
	return str2byte(file:read(1))
end

-- ˫�ֽ�

function str2short(s)
	return string.byte(s,1) + string.byte(s,2) * 0x100
end

function readShort(file)
	return str2short(file:read(2))
end

-- 4�ֽ�

function str2int(s)
	return string.byte(s,1) + string.byte(s,2) * 0x100 + string.byte(s,3) * 0x10000 + string.byte(s,4) * 0x1000000
end

function readInt(file)
	return str2int(file:read(4))
end

-- ���ļ���ǰλ�ö�ȡһ������
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

-- �ַ���ת����
-- function str2int(s)
	-- if(s == nil)
	-- then
		-- return 0
	-- else
		-- -- ��Ҫlua53
		-- return string.byte(s,1) + string.byte(s,2) * 0x100 + string.byte(s,3) * 0x10000 + string.byte(s,4) * 0x1000000
	-- end
-- end

-- ��ȡ������ݵ�ַ
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

-- ��ӡ
-- print(string.format("0x%X",pdata1))

-- �������C����
-- cs = io.open(path..'/'..name..'.c',"w")
cs = openAndRegister(path..'/'..name..'.c',"w")
--[[
if(cs == nil)
then
	print('Error: Cannot create output file\n')
	closeAllAndExit(-2)
end
--]]

-- ���ע��
cs:write([[// Generated by BattleAnimationDumper
// ]]..os.date("%Y/%m/%d %H:%M:%S")..'\n\n')

-- ���Ҫ������ͷ�ļ�
-- cs:write([[#include	"FE7JBattleAnimation.h"
-- #include	"]]..name..[[_event.h"

-- ]])

cs:write([[#include	"FE7JBattleAnimation.h"

]])

-- �ӻ��ű�������
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
-- �Ա�����ô������ֵ
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
	-- �Ա�����ô������ֵ
	-- cs:write('\t&&'..name..'_Mode'..mode..',\t// '..modeComment[mode])
	-- error: field name not in record or union initializer
	-- error: label 'XXX_Mode1' referenced outside of any function
	-- �����У���ΪC�����б��ֻ�ܶ��������ǰ�����û��

	-- error: initializer element is not constant
	-- cs:write('\t&'..name..'_Mode'..mode..' - &'..name..'_data2,\t// '..modeComment[mode])
	-- ����ƫ�Ƹĵ������
	
--	cs:write('\t'..readInt(rom)..',\t')
--	cs:write('\t'..rom:read(4)..',\t')
--	rom:seek(cur,4)
end
--]]

-- cs:write('\t0,0,0,0,0,0,0,0,0,0,0,0\n};\n\n')

-- dump�����ṹ��

-- ��Ӷ����Ա��������ӽű���ָ���öε�λ��(��ѡ)
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
	frameSection = {}	-- �ֶ�ƫ�Ʊ�,�Ա㷭��data2�е�86
	-- frame = 1
	-- Ϊ����ٷ��ļ���ͳһ���ĳɴ�0��ʼ����
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

-- ��Ȼtonc����������ݷ���ͷ�ļ���...
-- script = io.open(path..'/'..name..'_event.h',"w")
-- script = openAndRegister(path..'/'..name..'_event.h',"w")
-- ���û��д�ű�
script = openAndRegister(path..'/'..name..'_event.s',"w")
rom:seek("set",pdata2 - 0x8000000)
-- ��data2ѹ����
if(readByte(rom) == 0x10)
-- ��ȡdata2�Ĵ�С
then
	--[[
	-- �������ѹ�������ݴ�С������ѹ��ǰ��
	data2size = readShort(rom)
	rom:seek("set",pdata2 - 0x8000000)
	compressedScript = rom:read(data2size)
	-- data2lz = io.open(path..'/'..name..'_data2.lz',"wb")
	data2lz = openAndRegister(path..'/'..name..'_data2.lz',"wb")
	data2lz:write(compressedScript)
	-- ����ʱ�ر�����ļ���Ӱ��gbalzss�����ķ���
	data2lz:close()
	-- �ر��ļ��󲻼�ʱ�ӷ����ļ��б���ɾ����Ӧ�ı���ᵼ�¹ر������ļ����˳������ʱ����Ȼ����ȥ�ر�����Ѿ����رյ��ļ�
	-- data2lz = nil
	-- table.remove(files,data2lz)
	files[data2lz] = nil
	-- Ҫ��: ��gbalzss����·����ӵ���������
	os.execute("gbalzss d "..path..'/'..name..'_data2.lz'..' '..path..'/'..name..'_data2.bin')
	-- ����: �����Ϊ����ԭ���޷��õ���ѹ����data2�������ļ�������������ѭ���ȴ�
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
	-- ��rom�ڵ�data2�����û��ѹ��
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

-- ���ע��
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
-- ��ӱ���Ա�data1����
-- script:write(name..'_Mode1:\t// '..modeComment[1])
script:write(name..'_data2:\n\n'..name..'_Mode1:'..'\t@ '..modeComment[1])

mode = 1

-- Ϊ�ű���ע�͵ĺ�����
ScriptComment = {}

-- ģʽ�ָ�
--[[
function EndMode()
	script:write('\t// End of Mode '..mode..' : '..modeComment[mode])
	-- �ӱ���Ա���data1������
	if(mode < 12)
	then
		script:write('\n'..name..'_Mode'..mode+1..':\t// '..modeComment[mode+1])
	end
	mode = mode + 1
end
--]]
function EndMode()
	mode = mode + 1
	-- �ӱ���Ա���data1������
	if(mode <= 12)
	then
		script:write('\n\n'..name..'_Mode'..mode..':\t@ '..modeComment[mode])
	end
end

ScriptComment[0x80000000] = EndMode

-- ָ��ǰһ��4�ֽ�
p0 = 0

-- ֱ�����raw
--[[
for i=1,data2size,4 do
    p = readInt(data2bin)
	script:write('\t'..string.format("0x%X",p)..',')
	
	-- ����0x86��ͷ�������������8�ֽ������ͬһ��
	if((p < 0x86000000 or p >= 0x87000000) and (p0 < 0x86000000 or p0 >= 0x87000000))
	then
		script:write('\n')
	end
	
	-- ��ע��
	if(ScriptComment[p] ~= nil)
	then
		ScriptComment[p]()
	end
	
	p0 = p
end
--]]

-- C80 �ָ���
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

-- ָ�������
CmdHandler = {}
CmdHandler[0] = C80H
CmdHandler[5] = C85H
CmdHandler[6] = C86H

-- ���û��ű�
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
	
		-- ��ע��
		if(ScriptComment[p] ~= nil)
		then
			ScriptComment[p]()
		end
	
		-- ����0x86��ͷ�������������8�ֽ������ͬһ��
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
-- ɾ�����һ��Ԫ�غ�Ķ���
-- script:seek("cur",-1)
-- ��ɾҲû��

-- �û������data1
script:write('\n'..name..'_data1:\n\n')
for mode=1,12 do
	script:write('\t'..'.word\t'..name..'_Mode'..mode..' - '..name..'_data2\n')
end
script:write('\t.word\t0,0,0,0,0,0,0,0,0,0,0,0\n')

-- script:write('};\n')
-- ���û��
script:write('\n\t.end\n')

-- Ϊ��ɾ����ʱ�򲻻����Permission denied
data2bin:close()
-- files[data2bin] = nil

---[[
-- ɾ����ʱ�ļ�
if(preserveTempFiles == nil)
then
	-- os.execute('rm '..path..'/'..name..'_data2.bin'..' '..path..'/'..name..'_data2.lz')
	os.execute('rm '..path..'/'..name..'_data2.bin')
end
--]]

-- ����ɹ��˳�
closeAllAndExit(1)
