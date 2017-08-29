-- GBA图片处理
-- by laqieer
-- 2017/8/29

require "bit"
require "imlua"

GBAImage = {}

-- gba颜色转换为imColor
function GBAImage:gba2color(color)
	r = bit.band(color,31) * 256 / 32
	g = bit.band(bit.rshift(color,5),31) * 256 / 32
	b = bit.band(bit.rshift(color,10),31) * 256 / 32
	-- return r * 0x10000 + g * 0x100 + b
	return im.ColorEncode(r,g,b)
end

-- imColor转换为gba颜色
function GBAImage:color2gba(color)
	-- r = bit.rshift(bit.band(bit.rshift(color,16),255),3)
	-- g = bit.rshift(bit.band(bit.rshift(color,8),255),3)
	-- b = bit.rshift(bit.band(color,255),3)
	r,g,b = im.ColorDecode(color)
	-- return r + bit.lshift(g,5) + bit.lshift(b,10)
	return bit.rshift(r + bit.lshift(g,5) + bit.lshift(b,10),3)
end

-- gba调色板转换为imPalette
function GBAImage:gba2pal(pal)
	palette = im.PaletteCreate(#pal)
	for k,v in pairs(pal) do
		palette[k-1] = GBAImage:gba2color(v)
	end
	return palette
end

-- imPalette转换为gba调色板
function GBAImage:pal2gba(pal)
	palette = {}
	for k,v in pairs(pal) do
		palette[k] = GBAImage:color2gba(v)
	end
	return palette
end

-- gba图片转索引图
function GBAImage:gba2Image(img,width,height,pal,depth)
	image = im.ImageCreate(width,height,im.MAP,im.BYTE)
	image:SetPalette(GBAImage:gba2pal(pal))
	if(depth == 8)
	then		
		-- image:SetPixels(img)
		-- attempt to call method 'SetPixels' (a nil value)
		for lin = 0, image:Height() - 1, 1 do
			for col = 0, image:Width() - 1, 1 do
				image[0][height-1-lin][col] = img[1+ lin * width + col]
			end
		end
	end
	if(depth == 4)	-- 宽必须是偶数
	then
		for lin = 0, image:Height() - 1, 1 do
			for col = 0, image:Width() - 2, 2 do
				image[0][height-1-lin][col] = bit.rshift(img[1+ lin * width / 2 + col / 2],4)
				image[0][height-1-lin][col+1] = bit.band(img[1+ lin * width / 2 + col / 2],15)
			end
		end		
	end
	return image
end

--[[
-- 16色测试
pal = {0x5355, 0x2CF1, 0x599B, 0x72BD, 0x7FBD, 0x66D5, 0x3CE2, 0x30C2, 0x5585, 0x6E4C, 0x4E0E, 0x3146, 0x27FF, 0x2EBD, 0x35DD, 0x14A5}
img = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF}
image = GBAImage:gba2Image(img,8,2,pal,4)
image:Save("test16.png","PNG")
--]]

--[[
-- 256色测试
pal = {0x5355, 0x2CF1, 0x599B, 0x72BD, 0x7FBD, 0x66D5, 0x3CE2, 0x30C2, 0x5585, 0x6E4C, 0x4E0E, 0x3146, 0x27FF, 0x2EBD, 0x35DD, 0x14A5, 0x5355, 0x4106, 0x7733, 0x51C3, 0x7FFA, 0x2F01, 0x1140, 0x474D, 0x0DE2, 0x5FDF, 0x3ADD, 0x1D50, 0x00B4, 0x14FC, 0x7FFF, 0x14A5}
img = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}
image = GBAImage:gba2Image(img,16,2,pal,8)
image:Save("test256.png","PNG")
--]]
