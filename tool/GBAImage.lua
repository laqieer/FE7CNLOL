-- GBA图片处理
-- by laqieer
-- 2017/8/29

require "bit"
require "math"
require "imlua"
require "imlua_process"

GBAImage = {}

GBAImage.wh = {}
GBAImage.shape = {}
GBAImage.shape[0] = 'square'
GBAImage.shape[1] = 'horizontal'
GBAImage.shape[2] = 'vertical'
GBAImage.wh.square = {{8,8},{16,16},{32,32},{64,64}}
GBAImage.wh.horizontal = {{16,8},{32,8},{32,16},{64,32}}
GBAImage.wh.vertical = {{8,16},{8,32},{16,32},{32,64}}

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
function GBAImage:gba2image(img,width,height,pal,depth)
	if(depth ~= 4 and depth ~=8)
	then
		print('Error: Unsupported image depth\n')
		return
	end
	image = im.ImageCreate(width,height,im.MAP,im.BYTE)
	image:SetPalette(GBAImage:gba2pal(pal))
	--[[
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
	--]]
	-- 以tile为单位绘图
	if(width % 8 ~= 0 or height % 8 ~= 0)
	then
		print('Error: Invalid width or height\n')
		return
	end
	local i = 1
	for lin = 0, height/8 - 1 do
		for col = 0, width/8 - 1 do
			for tileY = 0,8-1 do
				if(depth == 8)
				then
					for tileX = 0,8-1 do
						image[0][height - 1 - 8 * lin - tileY][8 * col + tileX] = img[i]
						i = i + 1
					end
				end
				if(depth == 4)
				then
					for tileX = 0,8/2-1 do
						image[0][height - 1 - 8 * lin - tileY][8 * col + 2 * tileX + 1] = bit.rshift(img[i],4)
						image[0][height - 1 - 8 * lin - tileY][8 * col + 2 * tileX] = bit.band(img[i],15)
						i = i + 1
					end
				end
			end
		end
	end
	return image
end

--[[
-- 16色测试
pal = {0x5355, 0x2CF1, 0x599B, 0x72BD, 0x7FBD, 0x66D5, 0x3CE2, 0x30C2, 0x5585, 0x6E4C, 0x4E0E, 0x3146, 0x27FF, 0x2EBD, 0x35DD, 0x14A5}
img = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF}
image = GBAImage:gba2image(img,8,2,pal,4)
image:Save("test16.png","PNG")
--]]

--[[
-- 256色测试
pal = {0x5355, 0x2CF1, 0x599B, 0x72BD, 0x7FBD, 0x66D5, 0x3CE2, 0x30C2, 0x5585, 0x6E4C, 0x4E0E, 0x3146, 0x27FF, 0x2EBD, 0x35DD, 0x14A5, 0x5355, 0x4106, 0x7733, 0x51C3, 0x7FFA, 0x2F01, 0x1140, 0x474D, 0x0DE2, 0x5FDF, 0x3ADD, 0x1D50, 0x00B4, 0x14FC, 0x7FFF, 0x14A5}
img = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}
image = GBAImage:gba2image(img,16,2,pal,8)
image:Save("test256.png","PNG")
--]]

-- 绘制精灵
function GBAImage:drawSprite(img,pal,depth,OAM)
	if(OAM == nil)
	then
		return
	end
	if(depth ~= 8 and depth ~= 4)
	then
		print('Error: Unsupported image depth\n')
		return
	end
	palette = GBAImage:gba2pal(pal)
	tiles = {}
	objects = {}
	screen = im.ImageCreate(240,160,im.MAP,im.BYTE)
	screen:SetPalette(palette)
	local p = 1
	local tile = 0
	repeat
		tiles[tile] = {}
		if(depth == 8)
		then
			for i1=0,8-1 do
				tiles[tile][i1] = {}
				for j1=0,8-1 do
					tiles[tile][i1][j1] = img[p]
					p = p + 1
				end
			end
		else
			for i1=0,8-1 do
				tiles[tile][i1] = {}
				for j1=0,8/2-1 do
					-- print(img[p])
					tiles[tile][i1][2*j1] = bit.band(img[p],15)
					tiles[tile][i1][2*j1+1] = bit.rshift(img[p],4)
					p = p + 1
				end
			end
		end
		tile = tile + 1
	until(p >= #(img))
	for i1=#(OAM.OBJAttr),1,-1 do
		-- w,h = GBAImage.wh[OAM.OBJAttr[i1].shape][OAM.OBJAttr[i1].size]
		w = GBAImage.wh[GBAImage.shape[OAM.OBJAttr[i1].shape]][OAM.OBJAttr[i1].size+1][1]
		h = GBAImage.wh[GBAImage.shape[OAM.OBJAttr[i1].shape]][OAM.OBJAttr[i1].size+1][2]
		objects[i1] =  im.ImageCreate(w,h,im.MAP,im.BYTE)
		objects[i1]:SetPalette(palette)
		tile = OAM.OBJAttr[i1].tileNo
		for y=0,h/8-1 do
			for x=0,w/8-1 do
				for y0=0,8-1 do
					for x0=0,8-1 do
						-- objects[i1][0][h-1-(8*y+y0)][8*x+x0] = tiles[tile][y0][x0] + 16 * OAM.OBJAttr[i1].paletteNo
						-- objects[i1][0][8*y+y0][8*x+x0] = tiles[tile][y0][x0] + 16 * OAM.OBJAttr[i1].paletteNo
						objects[i1][0][8*y+y0][8*x+x0] = tiles[tile][y0][x0]
					end
				end
				tile = tile+1
			end
			tile = tile + 256/8 - w/8
		end
		if(OAM.OBJAttr[i1].affineFlag == 1)
		then
			-- PA,PB,PC,PD = OAM.affinePara[OAM.OBJAttr[i].RSPara+1]
			--[[
			PA = OAM.affinePara[OAM.OBJAttr[i1].RSPara+1][1]
			PB = OAM.affinePara[OAM.OBJAttr[i1].RSPara+1][2]
			PC = OAM.affinePara[OAM.OBJAttr[i1].RSPara+1][3]
			PD = OAM.affinePara[OAM.OBJAttr[i1].RSPara+1][4]
			--]]
			PA = OAM.affinePara[OAM.OBJAttr[i1].RSPara+1][1] / 256
			PB = OAM.affinePara[OAM.OBJAttr[i1].RSPara+1][2] / 256
			PC = OAM.affinePara[OAM.OBJAttr[i1].RSPara+1][3] / 256
			PD = OAM.affinePara[OAM.OBJAttr[i1].RSPara+1][4] / 256
			-- alpha = math.atan(PC/PD)
			-- sy = PC * PD / math.sqrt(PC^2 + PD^2)
			-- sx = -PA * PB / math.sqrt(PA^2 + PB^2)
			sy = 1 / math.sqrt(PC^2 + PD^2)
			sx = 1 / math.sqrt(PA^2 + PB^2)
			sin0 = PC * sy
			cos0 = PD * sy
			-- sin0 = PC * sy / (256^2)
			-- cos0 = PD * sy / (256^2)
			-- print(w,h,sx,sy)
			-- print(objects[i1])
			-- c,objects[i1] = im.ProcessResizeNew(objects[i1], math.modf(w*sx/256), math.modf(h*sy/256))
			c,objects[i1] = im.ProcessResizeNew(objects[i1], math.modf(w*sx), math.modf(h*sy))
			-- print(objects[i1])
			-- print(PA,PB,PC,PD,sx,sy,cos0,sin0)
			c,objects[i1] = im.ProcessRotateNew(objects[i1], cos0, sin0, 0)
		else
			if(OAM.OBJAttr[i1].HFlip == 1)
			then
				objects[i1] = im.ProcessMirrorNew(objects[i1])
				-- im.ProcessMirror(objects[i1],objects[i1])
			end
			if(OAM.OBJAttr[i1].VFlip == 1)
			then
				objects[i1] = im.ProcessFlipNew(objects[i1])
			end
		end
		for lin=0,objects[i1]:Height()-1 do
			for col=0,objects[i1]:Width()-1 do
				if(objects[i1][0][lin][col] ~= 0)
				then
					screen[0][160-1-(OAM.OBJAttr[i1].YCoordinate+lin)][OAM.OBJAttr[i1].XCoordinate+col] = objects[i1][0][lin][col]
				end
			end
		end
	end
	return screen
end
