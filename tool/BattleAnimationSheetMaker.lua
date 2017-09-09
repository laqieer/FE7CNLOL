-- 把战斗动画帧图切割并组合成sheet
-- by laqieer
-- 2017/9/5

require "imlua"
require "imlua_process"
require "math"
require "bit"

-- lua 除了简单类型分配内存外，table只是传递引用，所以不能用简单的"="来copy两个表，并试图修改一个表中的值
--lua table 拷贝
function table_copy_table(ori_tab)
    if (type(ori_tab) ~= "table") then
        return nil
    end
    local new_tab = {}
    for i,v in pairs(ori_tab) do
        local vtyp = type(v)
        if (vtyp == "table") then
            new_tab[i] = table_copy_table(v)
        elseif (vtyp == "thread") then
            new_tab[i] = v
        elseif (vtyp == "userdata") then
            new_tab[i] = v
        else
            new_tab[i] = v
        end
    end
    return new_tab
end

-- 从全路径中获取文件名(linux、windows通用)
function getFileName(filename)
	--[[
	fn_flag = string.find(filename, "\\")
 
	if fn_flag then
	 
	dest_filename = string.match(filename, ".+\\([^\\]*%.%w+)$")
	end
	 
	 
	 
	fn_flag = string.find(filename, "/")
	 
	if fn_flag then
	 
	dest_filename = string.match(filename, ".+/([^/]*%.%w+)$")
	end
	
	return dest_filename
	--]]
	return string.gsub(filename,".+[/\\]","")
end

if(not arg[1])
then
	print([[Cut the battle animation frames and combine them into sheets.
	
	Usage: lua BattleAnimationSheetMaker.lua AnimationName [options]
	
	Options:
		-L	The animation is at left. (Default is at right.)
		-f	Set the format for images. (Default is PNG.)
	]])
	os.exit(-1)
end

-- 动画名
name = arg[1]

_frame_L_R_ = '_frame_R_'

optHandlers = {}
-- 右侧还是左侧(默认右侧)
optHandlers['-L']=	function(para)
						isLeft = true
						_frame_L_R_ = '_frame_L_'
						opt = opt - 1
					end
-- 设置图片格式
imageFormat = 'PNG'
optHandlers['-f']=	function(para)
						imageFormat = para
					end

opt = 2					
while(arg[opt])
do
	optHandlers[arg[opt]](arg[opt+1])
	opt = opt + 2
end

-- 屏幕(240x160)中战斗动画的坐标原点
yCenter = 160 - 1 - 88
if(isLeft)
then
	xCenter = 92
else
	xCenter = 148
end

-- 帧图
frames = {}
-- sheet图
sheets = {}
-- sheet占用与空余情况
sheetMap = {}
-- 每个frame对应的OAM集合
OAM = {}
-- 帧序号
frame = 0
-- sheet序号
-- sheet = 1
sheet = 0
-- 读取所有的帧图
repeat
	--[[
	if(isLeft)
	then
		-- gif指定index读取帧测试有问题
		frames[frame] = im.FileImageLoad(name..'_frame_L_'..frame..'.'..imageFormat)
	else
		frames[frame] = im.FileImageLoad(name..'_frame_R_'..frame..'.'..imageFormat)
	end
	-]]
	frames[frame] = im.FileImageLoad(name.._frame_L_R_..frame..'.'..imageFormat)
	frame = frame + 1
until(frames[frame-1] == NULL)
frames[frame-1] = nil
frames[frame] = nil

-- 检测帧图是否为16色索引图
for k,v in pairs(frames) do
	if(v:ColorSpace() ~= im.MAP)
	then
		-- print('Error: '..name..'_frame_L_'..k..'.'..imageFormat..' is not indexed')
		print('Error: '..name.._frame_L_R_..k..'.'..imageFormat..' is not indexed')
		os.exit(-1)
	end
	if(v:GetPalette()[16] ~= im.ColorEncode(0,0,0) or v:GetPalette()[17] ~= im.ColorEncode(0,0,0))
	then
		-- print('Error: '..name..'_frame_L_'..k..'.'..imageFormat..' has over 16 colors')
		print('Error: '..name.._frame_L_R_..k..'.'..imageFormat..' has over 16 colors')
		os.exit(-1)
	end
end
pal = frames[0]:GetPalette()

-- 取一张图片最左边的不透明像素的横坐标
function getXMin(image)
	for col = 0, image:Width()-1 do
		for lin = 0, image:Height()-1 do
			if(image[0][lin][col] ~= 0)
			then
				return col
			end
		end
	end
end

-- 取一张图片最右边的不透明像素的横坐标
function getXMax(image)
	for col = image:Width()-1, 0, -1 do
		for lin = 0, image:Height()-1 do
			if(image[0][lin][col] ~= 0)
			then
				return col
			end
		end
	end
end

-- 取一张图片最下边的不透明像素的纵坐标
function getYMin(image)
	for lin = 0, image:Height()-1 do
		for col = 0, image:Width()-1 do
			if(image[0][lin][col] ~= 0)
			then
				return lin
			end
		end
	end
end

-- 取一张图片最上边的不透明像素的纵坐标
function getYMax(image)
	for lin = image:Height()-1, 0, -1 do
		for col = 0, image:Width()-1 do
			if(image[0][lin][col] ~= 0)
			then
				return lin
			end
		end
	end
end

-- 取一张图片不透明矩形区域范围
-- xmin,ymin,xmax,ymax 单位: pixel
-- frame中不要求8像素对齐
function getOpaqueArea(image)
	xmin = getXMin(image)
	ymin = getYMin(image)
	xmax = getXMax(image)
	ymax = getYMax(image)
	return xmin,ymin,xmax,ymax -- 左下角坐标 右上角坐标
end

-- 检测图片是否为空
function checkIfBlankImage(image)
	for lin = 0, image:Height() - 1 do
		for col = 0, image:Width() - 1 do
			if(image[0][lin][col] ~= 0)
			then
				return false
			end
		end
	end
	return true
end

-- 将一张图片上指定矩形区域置为透明
-- xmin,ymin,xmax,ymax 单位: pixel
function setOpaqueArea(image,xmin,ymin,xmax,ymax)
	if(xmin < 0 or ymin < 0 or xmax > image:Width()-1 or ymax > image:Height()-1 or xmin > xmax or ymin > ymax)
	then
		print('Error: Invalid rectangle area is set')
		os.exit(-1)
	end
	for lin = ymin, ymax do
		for col = xmin,xmax do
			image[0][lin][col] = 0
		end
	end
end

-- 区域拷贝
-- 参数:源图片,源位置（左下角坐标）,目标图片,目标位置（左下角坐标）,要拷贝区域的宽和高
-- xSrc, ySrc, xDst, yDst, w, h 单位: pixel
function areaCopy(imgSrc, xSrc, ySrc, imgDst, xDst, yDst, w, h)
	if(xSrc < 0 or ySrc < 0 or xSrc + w > imgSrc:Width() or ySrc + h > imgSrc:Height())
	then
		print('Error: Invalid source area to copy')
		os.exit(-1)
	end
	if(xDst < 0 or yDst < 0 or xDst + w > imgDst:Width() or yDst + h > imgDst:Height())
	then
		print('Error: Invalid destination area to copy')
		os.exit(-1)
	end
	for lin = 0, h-1 do
		for col = 0, w-1 do
			imgDst[0][yDst + lin][xDst + col] = imgSrc[0][ySrc + lin][xSrc + col]
		end
	end
end

-- 区域剪切
-- 参数:源图片,源位置（左下角坐标）,目标图片,目标位置（左下角坐标）,要剪切区域的宽和高
-- xSrc, ySrc, xDst, yDst, w, h 单位: pixel
function areaCut(imgSrc, xSrc, ySrc, imgDst, xDst, yDst, w, h)
	if(xSrc < 0 or ySrc < 0 or xSrc + w > imgSrc:Width() or ySrc + h > imgSrc:Height())
	then
		print('Error: Invalid source area to cut')
		os.exit(-1)
	end
	if(xDst < 0 or yDst < 0 or xDst + w > imgDst:Width() or yDst + h > imgDst:Height())
	then
		print('Error: Invalid destination area to cut')
		os.exit(-1)
	end
	for lin = 0, h-1 do
		for col = 0, w-1 do
			imgDst[0][yDst + lin][xDst + col] = imgSrc[0][ySrc + lin][xSrc + col]
			imgSrc[0][ySrc + lin][xSrc + col] = 0
		end
	end
end

-- 从区域创建图片
-- 也可以使用im.FileImageLoadRegion(file_name: string, index, bitmap, xmin, xmax, ymin, ymax, width, height: number, ) -> image: imImage, error: number [in Lua 5] 
-- xmin,ymin,width,height 单位: pixel
function createImageFromArea(image,xmin,ymin,width,height)
	if(xmin < 0 or ymin < 0 or xmin + width > image:Width() or ymin + height > image:Height())
	then
		print('Error: Invalid area is selected')
		os.exit(-1)
	end
	subImage = im.ImageCreate(width, height, im.MAP, im.BYTE)
	subImage:SetPalette(image:GetPalette())
	for lin = 0, height-1 do
		for col = 0, width-1 do
			subImage[0][lin][col] = image[0][ymin + lin][xmin + col]
		end
	end
	return subImage
end

-- 比较相同尺寸的两幅图是否相同(不考虑调色板)(其实后者可以比前者尺寸大)
function compareImage(img1,img2)
	for lin = 0, img1:Height()-1 do
		for col = 0, img1:Width()-1 do
			if(img1[0][lin][col] == img2[0][lin][col])
			then
				return false
			end
		end
	end
	return true
end

-- 标记占用块
-- x,y,w,h单位:tile
function markOccupiedArea(map,x,y,w,h)
	if(x < 0 or y < 0 or x + w > map.Width or y + h > map.Height)
	-- if(x < 0 or y < 0 or x + 8 * w > map.Width or y + 8 * h > map.Height)
	then
		print('Error: Invalid area to marked as occupied')
		os.exit(-1)
	end
	for lin = 0, h-1 do
		for col = 0, w-1 do
			map[y + lin][x + col] = 1
		end
	end
	map.Tiles = map.Tiles + w * h	-- 为了提高效率，增加这个成员(已经被占用的tile数)
	if(map.Tiles > map.Width * map.Height)
	then
		print('Error: too many tiles are allocated to the this sheet')
		os.exit(-1)
	end
	if(map.Tiles == map.Width * map.Height)
	then
		map.isFull = true	-- 标记该sheet是否已满
	end
end

-- 寻找空闲块
-- x,y,w,h单位:tile
-- sheet中要求8像素对齐
function seekIdleArea(map,w,h)
	if(w < 0 or h < 0 or w > map.Width or h > map.Height)
	then
		print('Error: area to seek is over the size of sheet')
		os.exit(-1)
	end
	if(map.isFull)
	then
		return
	end
	if(map.Tiles + w * h > map.Width * map.Height)
	then
		return
	end
	-- for y = 0, map.Height-1, 8 do
	for y = 0, map.Height - h do	-- 按像素标记不如按tile标记
		-- for x = 0, map.Width-1, 8 do
		for x = 0, map.Width - w do	-- 按像素标记不如按tile标记
			for lin = 0, h - 1 do
				for col = 0, w - 1 do
					if(map[y + lin][x + col] == 1)
					then
						isNotEnough = true
						break
					end
				end
				if(isNotEnough)
				then
					break
				end
			end
			if(not isNotEnough)
			then
				return x,y
			end
			isNotEnough = false
		end
	end
end

-- 新建一张sheet
-- w,h单位:pixel
function createNewSheet(w,h)
	sheet = sheet + 1
	if(w % 8 ~= 0 or h % 8 ~= 0)
	then
		print('Error: the dimension of sheet cannot be divided by 8')
		os.exit(-1)
	end
	sheets[sheet] = im.ImageCreate(w,h,im.MAP,im.BYTE)
	sheets[sheet]:SetPalette(pal)
	sheetMap[sheet] = {}
	sheetMap[sheet].Width = w/8
	sheetMap[sheet].Height = h/8
	sheetMap[sheet].Tiles = 0
	for lin = 0, h/8-1 do
		sheetMap[sheet][lin] = {}
		for col = 0, w/8-1 do
			sheetMap[sheet][lin][col] = 0
		end
	end
end

-- 可能的尺寸(x8)
OBJSize = {}
-- 向上取
OBJSize.width = {1,2,4,4,8,8,8,8}
-- 每个宽度对应的可能的高度
OBJSize[1] = {1,2,4,4,4,4,4,4}	-- 8x8,8x16,8x32
OBJSize[2] = {1,2,4,4,4,4,4,4}	-- 16x8,16x16,16x32
OBJSize[4] = {1,2,4,4,8,8,8,8}	-- 32x8,32x16,32x32,32x64
OBJSize[8] = {4,4,4,4,8,8,8,8}	-- 64x32,64x64
-- 尺寸到OBJAttribute的映射表
-- w/8,h/8=>shape,size
shape_size = {}
shape_size[1] = {}
shape_size[2] = {}
shape_size[4] = {}
shape_size[8] = {}
shape_size[1][1] = {0,0}	-- 8x8
shape_size[2][2] = {0,1}	-- 16x16
shape_size[4][4] = {0,2}	-- 32x32
shape_size[8][8] = {0,3}	-- 64x64
shape_size[2][1] = {1,0}	-- 16x8
shape_size[4][1] = {1,1}	-- 32x8
shape_size[4][2] = {1,2}	-- 32x16
shape_size[8][4] = {1,3}	-- 64x32
shape_size[1][2] = {2,0}	-- 8x16
shape_size[1][4] = {2,1}	-- 8x32
shape_size[2][4] = {2,2}	-- 16x32
shape_size[4][8] = {2,3}	-- 32x64
-- 各尺寸拼图的历史记录(为了重复利用)
-- 这种方式可能导致同一帧的不同部分来自于不同的sheet,故不可行
--[[
history = {}
history[1] = {}
history[2] = {}
history[4] = {}
history[8] = {}
history[1][1] = {}	-- 8x8
history[2][2] = {}	-- 16x16
history[4][4] = {}	-- 32x32
history[8][8] = {}	-- 64x64
history[2][1] = {}	-- 16x8
history[4][1] = {}	-- 32x8
history[4][2] = {}	-- 32x16
history[8][4] = {}	-- 64x32
history[1][2] = {}	-- 8x16
history[1][4] = {}	-- 8x32
history[2][4] = {}	-- 16x32
history[4][8] = {}	-- 32x64
-]]

-- 建第一张sheet
createNewSheet(256,64)

-- 主体
-- print(#frames)
--[[
for frame = 0, #frames do
	OAM[frame] = {}
	OBJ = 1
	while(not checkIfBlankImage(frames[frame]))
	do
		x1,y1,x2,y2 = getOpaqueArea(frames[frame])
		-- print(x1,y1,x2,y2)
		--[
			x1		x2
		y2	
			
		y1	
		--]
		-- dx = x2 - x1
		-- dy = y2 - y1
		-- 比如只有一个像素点的情形
		dx = x2 - x1 + 1
		dy = y2 - y1 + 1
		-- print(dx,dy)
		-- 切块尺寸
		w = math.ceil(dx/8)
		-- w = math.floor(dx/8)
		-- print(w)
		if(w > 8)
		then
			w = 8
		else
			-- print(w)
			w = OBJSize.width[w]
		end
		-- print(w)
		h = math.ceil(dy/8)
		if(h > 8)
		then
			h = OBJSize[w][8]
		else
			-- print(w,h)
			h = OBJSize[w][h]
		end
		-- 防止超出屏幕
		if(x1 + 8 * w > frames[frame]:Width())
		then
			x1 = frames[frame]:Width() - 8 * w
		end
		if(y1 + 8 * h > frames[frame]:Height())
		then
			y1 = frames[frame]:Height() - 8 * h
		end
		-- print('L407')
		-- 记录OAM信息
		OAM[frame][OBJ] = {}
		-- print('L410',8*w,8*h)
		OAM[frame][OBJ].shape = shape_size[w][h][1]
		OAM[frame][OBJ].size = shape_size[w][h][2]
		-- print(OAM[frame][OBJ].shape,OAM[frame][OBJ].size)
		if(OAM[frame][OBJ].shape == nil or OAM[frame][OBJ].size == nil)
		then
			print{'Error: Invalid dimension of OBJ'}
			os.exit(-1)
		end
		OAM[frame][OBJ].XOffset = x1 - xCenter
		OAM[frame][OBJ].YOffset = y1 + 8 * h -1 - yCenter
		OAM[frame][OBJ].XOffsetMirror = - 8 * w
		if(isLeft)
		then
			OAM[frame][OBJ].XOffsetMirror = - OAM[frame][OBJ].XOffsetMirror
		end
		OAM[frame][OBJ].XOffsetMirror = OAM[frame][OBJ].XOffsetMirror - OAM[frame][OBJ].XOffset
		-- print('L418')
		--[
		-- 查询历史记录
		objImg = createImageFromArea(frames[frame], x1, y1, 8 * w, 8 * h)
		-- print('L420')
		for k,v in pairs(history[w][h]) do
			if(compareImage(objImg,v.img))
			then	-- 原图
				OAM[frame][OBJ].sheetID = v.sheetID
				OAM[frame][OBJ].tileID = v.tileID
				-- 删除区域内容
				-- setOpaqueArea(frames[frame], x1, y1, x1 + 8 * w - 1, y1 + 8 * h - 1)
				OBJ = OBJ + 1
				break
			else
				if(compareImage(objImg,im.ProcessMirrorNew(v.img)))
				then	-- 水平翻转
					OAM[frame][OBJ].sheetID = v.sheetID
					OAM[frame][OBJ].tileID = v.tileID
					OAM[frame][OBJ].HFlip = true
					-- 删除区域内容
					-- setOpaqueArea(frames[frame], x1, y1, x1 + 8 * w - 1, y1 + 8 * h - 1)
					OBJ = OBJ + 1
					break
				else
					if(compareImage(objImg,im.ProcessFlipNew(v.img)))
					then	-- 垂直翻转
						OAM[frame][OBJ].sheetID = v.sheetID
						OAM[frame][OBJ].tileID = v.tileID
						OAM[frame][OBJ].VFlip = true
						-- 删除区域内容
						-- setOpaqueArea(frames[frame], x1, y1, x1 + 8 * w - 1, y1 + 8 * h - 1)
						OBJ = OBJ + 1
						break
					else
						if(compareImage(objImg,im.ProcessFlipNew(im.ProcessMirrorNew(v.img))))
						then	-- 水平翻转+垂直翻转
							OAM[frame][OBJ].sheetID = v.sheetID
							OAM[frame][OBJ].tileID = v.tileID
							OAM[frame][OBJ].HFlip = true
							OAM[frame][OBJ].VFlip = true
							-- 删除区域内容
							-- setOpaqueArea(frames[frame], x1, y1, x1 + 8 * w - 1, y1 + 8 * h - 1)
							OBJ = OBJ + 1
							break
						-- else	-- 新图
						end
					end
				end
			end
		end
		if(OAM[frame][OBJ] ~= nil)
		then
		--]
			-- 在现有的sheet里找空位塞
			-- 这种方式可能会导致同一帧里的各个部分去了不同的sheet
			for sheetID = 1, sheet do
				-- print(sheetID,sheet,sheetMap,sheetMap[sheetID])
				x,y = seekIdleArea(sheetMap[sheetID],w,h)
				if(x ~= nil)
				then
					OAM[frame][OBJ].sheetID = sheetID
					break
				end
				--[
				if(sheetID == sheet)
				then
					createNewSheet(256,64)
				end
				--]
				-- for的三个表达式在循环开始前一次性求值，以后不再进行求值
			end
			-- 找不到就新建一张sheet
			if(x == nil)
			then
				createNewSheet(256,64)
				OAM[frame][OBJ].sheetID = sheet
				x = 0
				y = 0
			end
			OAM[frame][OBJ].tileID = x + 0x20 * y
			-- 标记已占用
			-- print(sheetID)
			-- markOccupiedArea(sheetMap[sheetID],x,y,w,h)
			markOccupiedArea(sheetMap[OAM[frame][OBJ].sheetID],x,y,w,h)
			-- 做记录以便之后重复利用
			table.insert(history[w][h],{['sheetID'] = OAM[frame][OBJ].sheetID, ['tileID'] = OAM[frame][OBJ].tileID, ['img'] = createImageFromArea(frames[frame], x1, y1, 8 * w, 8 * h)})
			OBJ = OBJ + 1
			-- 把区域内容从frame剪切到sheet
			-- print(x,y,w,h)
			areaCut(frames[frame], x1, y1, sheets[sheet], 8 * x, 8 * y, 8 * w, 8 * h)
			-- print('L513')
		--[
		else
			setOpaqueArea(frames[frame], x1, y1, x1 + 8 * w - 1, y1 + 8 * h - 1)
		end
		--]
	end
	-- print('L504')
end
--]]

-- 在母图上找子图
-- 单位: tile
-- 返回x,y,HFlip,VFlip
function seekSamePart(image,subImage)
	-- 要搜索的子图比大图还大
	if(subImage:Width() > image:Width() or subImage:Height() > image:Height())
	then
		return
	end
	
	for lin = 0, image:Height() - subImage:Height(), 8 do
		for col = 0, image:Width() - subImage:Width(), 8 do
			-- print(col,lin,subImage:Width(),subImage:Height())
			local img = createImageFromArea(image,col,lin,subImage:Width(),subImage:Height())
			if(compareImage(subImage,img))
			then
				return col,lin
			end
			local img = im.ProcessMirrorNew(img)
			if(compareImage(subImage,img))
			then
				return col,lin, true
			end
			local img = im.ProcessFlipNew(img)
			if(compareImage(subImage,img))
			then
				return col,lin, true, true
			end
			local img = im.ProcessFlipNew(createImageFromArea(image,col,lin,subImage:Width(),subImage:Height()))
			if(compareImage(subImage,img))
			then
				return col,lin, false, true
			end
		end
	end
end

-- 返回指定sheet已经被标记占用的tile数
function getOccupiedTilesNum(map)
	local tiles = 0
	for lin = 0, map.Height - 1 do
		for col = 0, map.Width - 1 do
			if(map[lin][col] == 1)
			then
				tiles = tiles + 1
			end
		end
	end
	return tiles
end

-- 改进切割算法
for frame = 0, #frames do
	print('Handling the frame '..frame..'/'..#frames)
	-- thisFrame = frames[frame]
	-- print(thisFrame,frames[frame])
	-- 复杂数据类型赋值都只是在传地址
	thisFrame = im.ImageCreate(frames[frame]:Width(),frames[frame]:Height(),frames[frame]:ColorSpace(),frames[frame]:DataType())
	frames[frame]:Copy(thisFrame)
	OAM[frame] = {}
	OBJ = 1
	-- 1, 分块
	while(not checkIfBlankImage(thisFrame))
	do
		x1,y1,x2,y2 = getOpaqueArea(thisFrame)
		dx = x2 - x1 + 1
		dy = y2 - y1 + 1
		w = math.ceil(dx/8)
		if(w > 8)
		then
			w = 8
		else
			w = OBJSize.width[w]
		end
		h = math.ceil(dy/8)
		if(h > 8)
		then
			h = OBJSize[w][8]
		else
			h = OBJSize[w][h]
		end
		if(x1 + 8 * w > thisFrame:Width())
		then
			x1 = thisFrame:Width() - 8 * w
		end
		if(y1 + 8 * h > thisFrame:Height())
		then
			y1 = thisFrame:Height() - 8 * h
		end
		OAM[frame][OBJ] = {}
		OAM[frame][OBJ].w = w
		OAM[frame][OBJ].h = h
		OAM[frame][OBJ].x1 = x1
		OAM[frame][OBJ].y1 = y1
		OAM[frame][OBJ].shape = shape_size[w][h][1]
		OAM[frame][OBJ].size = shape_size[w][h][2]
		if(OAM[frame][OBJ].shape == nil or OAM[frame][OBJ].size == nil)
		then
			print{'Error: Invalid dimension of OBJ'}
			os.exit(-1)
		end
		OAM[frame][OBJ].XOffset = x1 - xCenter
		OAM[frame][OBJ].YOffset = y1 + 8 * h -1 - yCenter
		OAM[frame][OBJ].XOffsetMirror = - 8 * w
		if(isLeft)
		then
			OAM[frame][OBJ].XOffsetMirror = - OAM[frame][OBJ].XOffsetMirror
		end
		-- print(x1,y1,w,h)
		OAM[frame][OBJ].image = createImageFromArea(thisFrame,x1,y1,8 * w,8 * h)
		OAM[frame][OBJ].XOffsetMirror = OAM[frame][OBJ].XOffsetMirror - OAM[frame][OBJ].XOffset
		setOpaqueArea(thisFrame, x1, y1, x1 + 8 * w - 1, y1 + 8 * h - 1)
		OBJ = OBJ + 1
	end
	-- 2, 寻找合适的sheet
	
	candidate = {}	-- 候选sheet编号(按优先级排序)
	priority = {}	-- 每个sheet的优先级,与candidate的关系:键值互换(值越小优先级越高)
	
	-- (1) 优先找重复(有重复的可利用就不必在sheet中为这个部分分配剩余空间)
	for objID, object in ipairs(OAM[frame]) do
		for sheetID, sheetImg in ipairs(sheets) do
			x,y,HFlip,VFlip = seekSamePart(sheetImg,object.image)
			if(x ~= nil and priority[sheetID] == nil)
			then
				table.insert(candidate,sheetID)
				priority[sheetID] = #candidate
			end
		end
	end
	-- (2) 次优先找剩余空间小的(为了尽量充分利用每一张sheet的空间)
	occupiedTilesNum = {}	-- 记录sheet的id和已经标记占用的tile数
	for sheetID, map in ipairs(sheetMap) do
		if(priority[sheetID] == nil)
		then
			-- table.insert(occupiedTilesNum, {['id'] = sheetID, ['OccupiedTiles'] = getOccupiedTilesNum(map)})
			table.insert(occupiedTilesNum, {['id'] = sheetID, ['OccupiedTiles'] = map.Tiles})
		end
	end
	table.sort(occupiedTilesNum, function(a,b)
		-- return	a.OccupiedTiles < b.OccupiedTiles or
				-- a.OccupiedTiles == b.OccupiedTiles and a.id > b.id
			return	a.OccupiedTiles > b.OccupiedTiles or
		a.OccupiedTiles == b.OccupiedTiles and a.id < b.id
	end)
	for pri, v in ipairs(occupiedTilesNum) do
		table.insert(candidate,v.id)
		priority[v.id] = #candidate
	end
	
	-- print(sheet)
	-- for k,v in ipairs(candidate) do
		-- print(k,v, sheetMap[v].Tiles)
	-- end
	
	-- for k,v in pairs(priority) do
		-- print(k,v)
	-- end
	
	-- (3) 依次检查找到的sheet的剩余空间能否容纳所有的部分(考虑重复)
	for pri, sheetID in ipairs(candidate) do
		-- local thisMap = sheetMap[sheetID]
		-- print(thisMap,sheetMap[sheetID])
		-- 给表赋值只是在赋值引用
		thisMap = table_copy_table(sheetMap[sheetID])
		for objID, object in ipairs(OAM[frame]) do
			-- x,y,HFlip,VFlip = seekSamePart(sheets[sheetID],object.image)
			object.x,object.y,object.HFlip,object.VFlip = seekSamePart(sheets[sheetID],object.image)
			-- 避免重复计算，提高效率
			-- if(x == nil)
			if(object.x == nil)
			then
				-- x, y = seekIdleArea(thisMap, object.w, object.h)
				object.x, object.y = seekIdleArea(thisMap, object.w, object.h)
				-- print(x,y)
				if(object.x == nil)
				then
					break
				end
				-- markOccupiedArea(thisMap, x, y, object.w, object.h)
				object.ifNew = true
				markOccupiedArea(thisMap, object.x, object.y, object.w, object.h)
			end
		end
		--[[
		if(x ~= nil)
		then
			OAM[frame].sheetID = sheetID
			break
		end
		--]]
		OAM[frame].sheetID = sheetID
		for objID, object in ipairs(OAM[frame]) do
			if(object.x == nil)
			then
				OAM[frame].sheetID = nil
				break
			end
		end
	end
	-- (4) 找到了合适的sheet
	if(OAM[frame].sheetID ~= nil)
	then
		for objID, object in ipairs(OAM[frame]) do
			object.tileID = object.x + 0x20 * object.y
			if(object.ifNew)
			then
				markOccupiedArea(sheetMap[OAM[frame].sheetID], object.x, object.y, object.w, object.h)
				areaCopy(frames[frame], object.x1, object.y1, sheets[OAM[frame].sheetID], 8 * object.x, 8 * object.y, 8 * object.w, 8 * object.h)
			end
			--[[
			x,y,HFlip,VFlip = seekSamePart(sheets[OAM[frame].sheetID],object.image)
			if(x ~= nil)
			then
				object.tileID = x + 0x20 * y
				object.HFlip = HFlip
				object.VFlip = VFlip
			else
				x, y = seekIdleArea(sheetMap[OAM[frame].sheetID], object.w, object.h)
				print(x,y)
				object.tileID = x + 0x20 * y
				markOccupiedArea(sheetMap[OAM[frame].sheetID], x, y, object.w, object.h)
				areaCopy(frames[frame], object.x1, object.y1, sheets[OAM[frame].sheetID], 8 * x, 8 * y, 8 * object.w, 8 * object.h)	-- 也可以把object.image作为图片源
			end
			-]]
			-- 避免重复计算,提高效率
		end
	-- end
	-- (5) 现有的sheet都不符合要求就新建一张sheet
	-- if(OAM[frame].sheetID == nil)
	-- then
	else
		createNewSheet(256,64)
		OAM[frame].sheetID = sheet
		for objID, object in ipairs(OAM[frame]) do
			x, y = seekIdleArea(sheetMap[sheet], object.w, object.h)
			object.tileID = x + 0x20 * y
			markOccupiedArea(sheetMap[sheet], x, y, object.w, object.h)
			areaCopy(frames[frame], object.x1, object.y1, sheets[sheet], 8 * x, 8 * y, 8 * object.w, 8 * object.h)	-- 也可以把object.image作为图片源
		end
	end
end

-- 输出

-- sheet图片
for k,v in pairs(sheets) do
	v:Save(name..'_sheet_'..k..'.'..imageFormat,imageFormat)
end

-- OAM信息
OAMInfo = io.open(name..'_OAMInfo.inc','w')
if(OAMInfo == nil)
then
	print('Error: cannot create file '..name..'_OAMInfo.inc')
	os.exit(-1)
end
OAMInfo:write([[@ Generated by BattleAnimationSheetMaker
@ ]]..os.date("%Y/%m/%d %H:%M:%S")..'\n\n\t.align\t4\n\n')
-- 自身
if(isLeft)
then
	-- OAMInfo:write(string.match(name,".+/([^/]*%w+)$")..'_data4:\n\n')
	OAMInfo:write(getFileName(name)..'_data4:\n\n')
else
	-- OAMInfo:write(string.match(name,".+/([^/]*%w+)$")..'_data3:\n\n')
	OAMInfo:write(getFileName(name)..'_data3:\n\n')
end
for k,v in pairs(OAM) do
	-- OAMInfo:write(string.match(name,".+/([^/]*%w+)$").._frame_L_R_..k..':\n')
	-- OAMInfo:write(string.match(name,".+/([^/]*%w+)$").._frame_L_R_..k..':\t@ '..string.match(name,".+/([^/]*%w+)$")..'_sheet_'..v.sheetID..'\n')
	OAMInfo:write(getFileName(name).._frame_L_R_..k..':\t@ '..getFileName(name)..'_sheet_'..v.sheetID..'\n')
	for key,value in ipairs(v) do
		OAMAttr0 = bit.lshift(value.shape,14)
		OAMAttr1 = bit.lshift(value.size,14)
		if(value.HFlip)
		then
			OAMAttr1 = OAMAttr1 + bit.lshift(1,12)
		end
		if(value.VFlip)
		then
			OAMAttr1 = OAMAttr1 + bit.lshift(1,13)
		end
		OAMAttr2 = bit.band(value.tileID,1023)
		-- OAMInfo:write(string.format('\tOBJ\t0x%X, 0x%X, 0x%X, %d, %d\t@ %s_sheet_%d\n',OAMAttr0,OAMAttr1,OAMAttr2,value.XOffset,value.YOffset,string.match(name,".+/([^/]*%w+)$"),value.sheetID))
		OAMInfo:write(string.format('\tOBJ\t0x%X, 0x%X, 0x%X, %d, %d\n',OAMAttr0,OAMAttr1,OAMAttr2,value.XOffset,value.YOffset))
	end
	OAMInfo:write('\tEndFrame\n\n')
end
OAMInfo:write('\tEndOAMInfo\n\n')
-- 对面
if(isLeft)
then
	-- OAMInfo:write(string.match(name,".+/([^/]*%w+)$")..'_data3:\n\n')
	OAMInfo:write(getFileName(name)..'_data3:\n\n')
	_frame_L_R_ = '_frame_R_'
else
	-- OAMInfo:write(string.match(name,".+/([^/]*%w+)$")..'_data4:\n\n')
	OAMInfo:write(getFileName(name)..'_data4:\n\n')
	_frame_L_R_ = '_frame_L_'
end
for k,v in pairs(OAM) do
	-- OAMInfo:write(string.match(name,".+/([^/]*%w+)$").._frame_L_R_..k..':\n')
	-- OAMInfo:write(string.match(name,".+/([^/]*%w+)$").._frame_L_R_..k..':\t@ '..string.match(name,".+/([^/]*%w+)$")..'_sheet_'..v.sheetID..'\n')
	OAMInfo:write(getFileName(name).._frame_L_R_..k..':\t@ '..getFileName(name)..'_sheet_'..v.sheetID..'\n')
	for key,value in ipairs(v) do
		OAMAttr0 = bit.lshift(value.shape,14)
		OAMAttr1 = bit.lshift(value.size,14)
		if(not value.HFlip)
		then
			OAMAttr1 = OAMAttr1 + bit.lshift(1,12)
		end
		if(value.VFlip)
		then
			OAMAttr1 = OAMAttr1 + bit.lshift(1,13)
		end
		OAMAttr2 = bit.band(value.tileID,1023)
		-- OAMInfo:write(string.format('\tOBJ\t0x%X, 0x%X, 0x%X, %d, %d\t@ %s_sheet_%d\n',OAMAttr0,OAMAttr1,OAMAttr2,value.XOffsetMirror,value.YOffset,string.match(name,".+/([^/]*%w+)$"),value.sheetID))
		OAMInfo:write(string.format('\tOBJ\t0x%X, 0x%X, 0x%X, %d, %d\n',OAMAttr0,OAMAttr1,OAMAttr2,value.XOffsetMirror,value.YOffset))
	end
	OAMInfo:write('\tEndFrame\n\n')
end
OAMInfo:write('\tEndOAMInfo\n\n')
OAMInfo:close()

-- sheet raw data
sheetData = io.open(name..'_sheet.inc','w')
if(sheetData == nil)
then
	print('Error: cannot create file '..name..'_sheet.inc')
	os.exit(-1)
end
sheetData:write([[@ Generated by BattleAnimationSheetMaker
@ ]]..os.date("%Y/%m/%d %H:%M:%S")..'\n\n\t.align\t4\n\n')
for k,v in ipairs(sheets) do
	-- sheetData:write(string.match(name,".+/([^/]*%w+)$")..'_sheet_'..k..':\n')
	sheetData:write(getFileName(name)..'_sheet_'..k..':\n')
	-- 注意:Y轴方向的不同
	-- 注意:以tile为单位输出(而不是像素)
	-- 注意:1字节=2像素,低半字节对应左边像素,高半字节对应右边像素
	for lin = v:Height() - 1, 0, -8 do
		for col = 0, v:Width() - 1, 8 do
			sheetData:write('\t.byte\t')
			for y0 = 0, 8 - 1 do
				for x0 = 0, 8 / 2 - 1 do
					sheetData:write(string.format('0x%02X, ',v[0][lin - y0][col + 2 * x0] + v[0][lin - y0][col + 2 * x0 + 1] * 0x10))
				end
				-- sheetData:write(string.format('0x%02X',v[0][lin - y0][6] + v[0][lin - y0][7] * 0x100))
			end
			-- sheetData:write('\n')
			sheetData:write(' @ tile ('..col..','..v:Height() - 1 - lin..')\n')
		end
	end
end
sheetData:close()
