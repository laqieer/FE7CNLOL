-- ROM解包工具
-- 输入参数: ROM文件名(包含路径,不包含扩展名)
-- by laqieer
-- 2017/12/22

require "fileList"

require "lz77"

if(arg[1] == nil)
then
	print("No rom is specified. Exit.")
	os.exit(-1)
end
-- 默认扩展名为'.gba'
rom = io.open(arg[1]..'.gba',"rb")
if(rom == nil)
then
	print("Specified rom is not accessible. Exit.")
	os.exit(-1)
end

-- 解包出的内容存放在这个目录下
baseDir = arg[1]
os.execute('md "'..baseDir..'"')

-- 解压函数表
decompFunc = {}
decompFunc.lz77 = function(k,v)
	decodedData,dataSize = lz77:decode(rom,k)
	for i = 1, dataSize do
		file:write(decodedData[i])
	end
end

for k,v in pairs(fileList) do
	file = io.open(baseDir..'/'..v[1],"wb")
	if(decompFunc[v[2]] ~= nil)
	then
		decompFunc[v[2]](k,v)
	else
		rom:seek("set",k)
		file:write(rom:read(v[2]))
	end
	file:close()
end

rom:close()

print("Finished.")
