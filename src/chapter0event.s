@by laqieer
@2017/04/24
@序章剧情事件(测试用)

	.include	"FE7JEvent.inc"
	.include	"FE7JCharacterList.inc"
	.include	"FE7JClassList.inc"
	.include	"FE7JItemList.inc"

	.section	.rodata
	.align		4
	.global		chapter0event
chapter0event:
	.word		turnEvents		@ 回合事件
	.word		talkEvents		@ 会话事件
	.word		locationEvents	@ 位置事件
	.word		miscEvents		@ 触发事件
	.word		trapDataE, trapDataH	@ 机关布置
	.word		enemiesEN, enemiesEH, enemiesHN, enemiesHH	@ 敌方配置
	.word		alliesEN,	alliesEH,	alliesHN, alliesHH	@ 我方配置
	.word		openingEvent, endingEvents	@ 章节开头和结尾

openingEvent:
@	.word		cameraOff
@	.word		loadUnits,	enemiesEN
@	.word		wait
@	.word		call,	0x807B3AC+1
@	.word		call,	0x807B448+1
	cameraOff
	loadUnits	enemiesEN
	wait
	call	0x807B3AC
	call	0x807B448
	fadeInCG
	
	

enemiesEN:
enemiesEH:
enemiesHN:
enemiesHH:
	@格式: 人物	职业	队长	等级所属和自动等级	初始位置	终点位置	携带物品1		携带物品2		携带物品3		携带物品4		AI1	AI2	AI3	AI4
	.byte	Batta,	Brigand,	0,	2*8+2*2+0,				3,2,		3,2,		IronAxe,		0,				0,				0,				3,		3,		9,		0x20	@ boss巴塔
	.byte	Bandit,Brigand,Batta,1*8+2*2+0,			2,6,		2,6,		IronAxe,		0,				0,				0,				0,		0,		9,		0		@ 杂兵山贼
	endList

turnEvents:

talkEvents:

locationEvents:

miscEvents:

trapDataE:
trapDataH:

alliesEN:
alliesEH:
alliesHN:
alliesHH:

endingEvents:
