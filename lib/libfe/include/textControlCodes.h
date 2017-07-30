// by laqieer
// 2017/4/19
// 文本控制符

#pragma once

/* 几种宏定义方式比较
	#define loadFace 0x10
	#define loadFace	'\x10'
	#define loadFace	"\x10"
	*/

// 基本控制符

// 结束(字符串结尾自动添加)
#define end				"\0"
// 换行
#define endl			"\x01"
// 换2行
#define endl2			"\x02"
// A键
#define pushA			"\x03"
// 短停顿
#define	shortPause		"\x04"
// 停顿
#define pause			"\x05"
// 长停顿
#define longPause		"\x06"
// 更长停顿
#define longlongPause	"\x07"
// 打开对话框(有不同位置)
#define openLeft		"\x0a"
#define openRight		"\x0b"
#define openMidLeft		"\x09"
#define openMidRight	"\x0c"
#define openFarLeft		"\x08"
#define	openFarRight	"\x0d"
#define openFarFarLeft	"\x0e"
#define openFarFarRight	"\x0f"
// 载入头像
#define loadFace		"\x10"
// 清除头像
#define clearFace		"\x11"
// 快速关闭对话框
#define closeFast		"\x14"
// 慢速关闭对话框
#define closeSlow		"\x15"
// 开始/停止动嘴
#define toggleMouthMove	"\x16"
// 开始/停止微笑
#define toggleSmile		"\x17"
// 给出选项(默认是)
#define	yes				"\x18"
// 给出选项(默认否)
#define	no				"\x19"
// 给出选项(买/卖)
#define buySell			"\x1a"
// 把选中的人物压到下方图层显示
#define sendToBack		"\x1c"
// 短停顿(打字音效继续)
#define	shortPauseWithSFX	"\x1f"

// 扩展控制符

// 在世界地图载入头像
#define	loadOverworldFace	"\x80\x04"
// 打印金币数
#define	goldAmount			"\x80\x05"
// 移动头像
#define	movetoLeft			"\x80\x0c"
#define	movetoRight			"\x80\x0d"
#define movetoMidLeft		"\x80\x0b"
#define movetoMidRight		"\x80\x0e"
#define movetoFarLeft		"\x80\x0a"
#define movetoFarRight		"\x80\x0f"
#define movetoFarFarLeft	"\x80\x10"
#define movetoFarFarRight	"\x80\x11"
// 使能眨眼
#define enableBlinking		"\x80\x16"
// 一行结束后延时一定时间眨眼
#define delayBlinking		"\x80\x18"
// 短时间暂停眨眼
#define pauseBlinking		"\x80\x19"
// 禁止眨眼
#define disableBlinking		"\x80\x1b"
// 睁眼
#define openEyes			"\x80\x1c"
// 闭眼
#define closeEyes			"\x80\x1d"
// 半闭眼
#define halfCloseEyes		"\x80\x1e"
// 眨单侧眼(使眼色)
#define wink				"\x80\x1f"
// 打印军师名字
#define tacticianName		"\x80\x20"
// 切换文本颜色(黑色和红色)
#define toggleRed			"\x80\x21"
// 显示当前的物品名
#define itemName			"\x80\x22"
// 显示说话者名字(文本框左上的小框)(带背景CG的对话，比如琳篇序章开头)
#define setName				"\x80\x23"
// 切换对话框反色(营造恐怖气氛)
#define	toggleColorInvert	"\x80\x25"

// 谁说什么话 封装
// #define talk(portraitID,position,content)	open##position loadFace #portraitID endl content clearFace
// 配合头像宏定义
#define sbsaysth(portrait,position,content)	open##position loadFace portrait endl content clearFace

