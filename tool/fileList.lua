-- 解包rom所需要的文件信息
-- 格式: fileList[offset] = {fileName, fileSize/compType}
-- by laqieer
-- 2017/12/22

fileList = {}

fileList[0] = {"GBA ROM Header", 0xC0}

-- 数据库
fileList[0xC4C158] = {"data/Character Database", 52 * 253}
fileList[0xC4F468] = {"data/Class Database", 84 * 100}
fileList[0xC51538] = {"data/Item Database", 36 * 159}

return fileList
