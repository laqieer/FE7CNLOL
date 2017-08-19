-- GBA的lz77压缩解压缩库
-- by laqieer
-- 2017/8/19

require "bit"

lz77 = {header = 0x10}

-- 解压缩
-- encodedFile -> rb
-- 返回解压后的字符数组和长度
function lz77:decode(encodedFile,offset)
	-- 保存当前文件指针位置
	current = encodedFile:seek()
	-- 转到指定偏移处解压
	encodedFile:seek("set",offset)
	-- 处理lz77压缩头
	if(string.byte(encodedFile:read(1)) ~= self.header)
	then
		print('Error: the data at '..string.format("0x%X",offset)..' is not lz77 compressed\n')
		return
	end
	-- 获取数据压缩前的大小
	dataSize = string.byte(encodedFile:read(1)) + string.byte(encodedFile:read(1)) * 0x100 + string.byte(encodedFile:read(1)) * 0x10000
	if(dataSize == 0)
	then
		print('Error: the data at '..string.format("0x%X",offset)..' is not lz77 compressed\n')
		return
	end
	-- 当前解压大小
	p = 0
	-- 解压
	decodedData = {}
	repeat
		flags = string.byte(encodedFile:read(1))
		mask = 0x80
		-- 1个flags(8个flag,MSB 1st)后面跟8个block
		for i=1,8 do
			flag = bit.band(flags,mask)
--			print(flag,mask)
			mask = mask / 2
			if(flag == 0)
			then
				-- 无压缩直接拷贝一个字节
				table.insert(decodedData,encodedFile:read(1))
				p = p + 1
			else
				-- 从Dest-Disp-1拷贝N+3个字节到Dest
				q = string.byte(encodedFile:read(1))
				N = bit.rshift(q,4)
				Disp = bit.band(q,0xF) * 0x100 + string.byte(encodedFile:read(1))
				for j=1,N+3 do
					table.insert(decodedData,decodedData[p - Disp - 1 + j])
				end
				p = p + N + 3
			end
		end
	until(p >= dataSize)
	-- 恢复调用前的文件指针位置
	encodedFile:seek("set",current)
	return decodedData,dataSize
end
