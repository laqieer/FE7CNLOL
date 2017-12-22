-- 解包rom所需要的文件信息
-- 格式: fileList[offset] = {fileName, fileSize/compType}
-- by laqieer
-- 2017/12/22

fileList = {}

fileList[0] = {"GBA ROM Header", 0xC0}

return fileList
