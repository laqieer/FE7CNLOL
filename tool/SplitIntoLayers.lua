-- 把一张超16色图片分成若干张16色图片
-- by laqieer
-- 2017/9/3

require "imlua"
require "bit"

-- 读取photoshop生成的ACT格式调色板
function loadACTPal(filename)
	local ACT = io.read(filename)
	if(ACT == nil)
	then
		print('Error: Cannot open file '..filename)
		return
	end
	-- local palLen = ACT:seek("end")
	-- ACT:seek("set")
	-- Default count is 256
	pal = im.PaletteCreate()
	for i = 1,#pal do
		r = string.byte(ACT:read(1))
		g = string.byte(ACT:read(1))
		b = string.byte(ACT:read(1))
		pal[i-1] = im.ColorEncode(r,g,b)
	end
	return pal
end

if(arg[1] == nil)
then
	print([[Split one 32-color image into 2 16-color images
	
Usage: lua SplitIntoLayers.lua image [options]
Main options:

-p		Set the palette (Photoshop ACT file)
-T		Set the transparent color (the common color among all images) (RRGGBB)
-f		Set the format of new images (Default: PNG)

]])
	os.exit(-1)
end

srcImg = im.FileImageLoad(arg[1])
if(srcImg == NULL)
then
	print('Error: Cannot open source image '..arg[1])
	os.exit(-1)
end

ImageFormat = 'PNG'

optionHandler = {}

optionHandler['-p'] = 	function(para)
						pal = loadACTPal(para)
						if(pal == nil)
						then
							print('Error: Fail to create palette from '..para)
						end
					end

optionHandler['-T'] = 	function(para)
						para = tonumber(para,16)
						r = bit.rshift(para,16)
						g = bit.rshift(bit.band(para,bit.lshift(255,8)),8)
						b = bit.band(para,255)
						TColor = im.ColorEncode(r,g,b)
					end

optionHandler['-f'] = 	function(para)
						ImageFormat = para
					end					
opt = 2
while(arg[opt] ~= nil)
do
	optionHandler[arg[opt]](arg[opt+1])
	opt = opt + 2
end

if(srcImg:ColorSpace() ~= im.MAP)
then
	print('Error: the source image '..arg[1]..' is not indexed')
	os.exit(-1)
end

if(pal == nil)
then
	pal = srcImg:GetPalette()
end

w = srcImg:Width()
h = srcImg:Height()

-- 划分子调色板
pal16 = {}
toSubPal = {}	-- 旧颜色索引到新颜色索引的映射表
local colorIndex = 0
if(TColor == nil)
then
	TColor = pal[1]
	-- toSubPal[1] = 1
	TColorIndex = 0
end
for i=1,16 do
	pal16[i] = im.PaletteCreate(16)
	pal16[i][0] = TColor
	for j=1,15 do
		if(pal[colorIndex] ~= TColor)
		then
			-- print(colorIndex,pal[colorIndex-1])
			pal16[i][j] = pal[colorIndex]
			toSubPal[colorIndex] = {i,j}
		else
			-- toSubPal[colorIndex] = 1
			-- print('L116')
			TColorIndex = colorIndex
		end
		colorIndex = colorIndex + 1
		if(pal[colorIndex] == im.ColorEncode(0,0,0))
		then
			if(pal[colorIndex+1] == im.ColorEncode(0,0,0))
			then
				palEnd = true
				break
			end
		end
	end
	-- print(j)
	if(palEnd)
	then
		break
	end
end

-- 划分子图
subImages = {}
for i=1,#pal16 do
	subImages[i] = im.ImageCreate(w,h,im.MAP,im.BYTE)
	subImages[i]:SetPalette(pal16[i])
end
for lin=0,h-1 do
	for col=0,w-1 do
		if(srcImg[0][lin][col] ~= TColorIndex)
		then
			-- print(colorIndex,TColor,TColorIndex,lin,col,srcImg[0][lin][col],pal[srcImg[0][lin][col]],toSubPal[srcImg[0][lin][col]])
			subImages[toSubPal[srcImg[0][lin][col]][1]][0][lin][col] = toSubPal[srcImg[0][lin][col]][2]
		end
	end
end
for i=1,#pal16 do
	subImages[i]:Save(arg[1]..'_'..i..'.'..ImageFormat,ImageFormat)
end
