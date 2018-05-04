// 结构体定义
// by laqieer
// 2018-04-21

#include "AgbTypes.h"

typedef		u16						TextID;	// 文本id
typedef		u8						ClassID; // 职业id
typedef		u8						CharacterID; // 人物id
typedef		u8						ItemID;	// 物品id
typedef		u16						AnimationID; // 动画id
typedef		u8						IconID;	// 图标id
typedef		u16						PortraitID;	// 头像id

// 装备武器附加能力(使用物品永久加能力)
typedef struct WeaponStatBonusInfo
{
	
	// The HP.
	s8 hp;
	
	// The attack. 攻撃.
	s8 atk;
	
	// The skill. 技.
	s8 skl;
	
	// The speed. 速さ.
	s8 spd;
	
	// The defense. 守備.
	s8 def;
	
	// The magic defense. 魔防.
	s8 res;
	
	// The luck. 幸運.
	s8 luk;
	
	// The movement. 移動力.
	s8 mov;
	
	// The constitution. 体格.
	s8 con;
	
	s8 unk_9;
	s8 unk_A;
	s8 unk_B;
}WeaponStatBonus;

// 人物属性定义

// 无属性
#define AffinityNone	0
// 炎属性
#define AffinityFire	1
// 雷属性
#define AffinityThunder	2
// 风属性
#define AffinityWind	3
// 水属性
#define AffinityWater	4
// 闇属性
#define AffinityDark	5
// 光属性
#define AffinityLight	6
// 理属性
#define AffinityAnima	7

// 人物支援设定数据
typedef struct SupportDataConfig
{
	// 支援对象
	CharacterID person[7];
	// 好感度初始值
	u8 favorInitial[7];
	// 好感度每回合增加值
	u8 favorGrowth[7];
	// 支援对象人数
	u8 supportNumber;
	// 最后填充2个字节，偏移0x16
	u16 pad_16;
}SupportData;

// ROM中的人物
typedef struct CharacterInfo
{
	// 人物名字
	TextID name;

	// 人物描述
	TextID description;

	// 人物序号
	CharacterID id;

	// 职业(用于在支援界面显示)
	ClassID m_class;

	// 人物头像
	PortraitID portrait;

	// 小头像(覆盖人物头像里的小头像,0-默认)
	// 0x00 Default
	// 0x01 Dragon
	// 0x02 Ostia/Caelin/Civilian
	// 0x03 Black Fang/Morph/Bandit
	u8 miniPortrait;

	// 属性
	u8 affinity;

	// 部队菜单排序顺序
	u8 sortID;

	// 能力基础值

	// 等级
	s8 baseLv;
	// 力/魔力
	s8 baseStr;
	// 技术
	s8 baseSkl;
	// 速度
	s8 baseSpd;
	// 守备
	s8 baseDef;
	// 魔防
	s8 baseRes;
	// 幸运
	s8 baseLuk;
	// 体格附加值
	s8 baseConBonus;
	
	// 武器熟练度

	// 剑等级
	u8 levelSword;
	// 枪等级
	u8 levelLance;
	// 斧等级
	u8 levelAxe;
	// 弓等级
	u8 levelBow;
	// 杖等级
	u8 levelStaff;
	// 理等级
	u8 levelAnima;
	// 光等级
	u8 levelLight;
	// 闇等级
	u8 levelDark;

	// 成长率

	// hp成长
	u8 growthHp;
	// 力/魔力成长
	u8 growthStr;
	// 技术成长
	u8 growthSkl;
	// 速度成长
	u8 growthSpd;
	// 守备成长
	u8 growthDef;
	// 魔防成长
	u8 growthRes;
	// 幸运成长
	u8 growthLuk;

	// 人物战斗动画特殊调色板编号

	// 低位职业
	u8 paletteIdUnpromoted;
	// 高位职业
	u8 paletteIdPromoted;

	// 人物特殊战斗动画编号

	// 低位职业
	u8 battleAnimationIdUnpromoted;
	// 高位职业
	u8 battleAnimationIdPromoted;

	// 填充字节
	u8 pad_27;

	// 特殊能力(人物/职业共通)

	// Class & Character Ability 1

	// 骑乘系救出
	u8 ability_mountedAid:1;
	// 再移动
	u8 ability_moveAgain:1;
	// 盗窃
	u8 ability_steal:1;
	// 使用盗贼钥匙
	u8 ability_theifKey:1;
	// 舞蹈
	u8 ability_dance:1;
	// 吹奏
	u8 ability_play:1;
	// 必杀加成
	u8 ability_criticalBonus:1;
	// 使用弩车
	u8 ability_ballista:1;
	
	// Class & Character Ability 2

	// 上位职业
	u8 ability_promoted:1;
	// 运输队
	u8 ability_supplyDepot:1;
	// 骑马图标显示
	u8 ability_mountedIcon:1;
	// 龙骑士图标显示
	u8 ability_dragonKnightIcon:1;
	// 天马骑士图标显示
	u8 ability_pegasusKnightIcon:1;
	// 领主
	u8 ability_lord:1;
	// 女性
	u8 ability_female:1;
	// boss图标显示
	u8 ability_boss:1;
	
	// Class & Character Ability 3

	// 未使用武器锁
	u8 ability_unusedWeaponLock:1;
	// 倭刀武器锁
	u8 ability_WoDaoWeaponLock:1;
	// 龙石武器锁
	u8 ability_dragonStoneWeaponLock:1;
	// 人造人(包括作为boss出现时的维达)
	u8 ability_morph:1;
	// 无法选中(例如倒下的尼尔斯)
	u8 ability_preventControl:1;
	// 天马三角攻击
	u8 ability_pegasusTriangleAttack:1;
	// 重甲三角攻击
	u8 ability_armorTriangleAttack:1;
	// 不要使用这个能力位
	u8 ability_forbidden:1;

	// Class & Character Ability 4

	// 击破无经验值，瞬杀无效(例如封魔者).
	u8 ability_noExp:1;
	// 瞬杀
	u8 ability_lethality:1;
	// 封魔
	u8 ability_magicSeal:1;
	// 物品栏最后一个物品可掉落
	u8 ability_dropLastItem:1;
	// 艾利乌德武器锁
	u8 ability_EliwoodWeaponLock:1;
	// 海克托尔武器锁
	u8 ability_HectorWeaponLock:1;
	// 琳武器锁
	u8 ability_LynWeaponLock:1;
	// 阿特斯武器锁
	u8 ability_AthosWeaponLock:1;

	// 支援设定
	SupportData *support;

	// 控制不同人物在某个场景下说不同的话
	// http://feuniverse.us/t/fe7-ch25h-fort-seizing-dialogue/1446
	u8 dialogueId;

	// 填充字节，偏移0x31
	u8 pad_31;

	// 填充双字节，偏移0x32
	u16 pad_32;
}Character;

// 物品+个数
typedef struct ItemDataInfo
{
	ItemID item;	// 物品种类
	u8 number;		// 物品数量
}ItemData;

// 职业战斗动画配置数据
typedef struct ClassBattleAnimationConfigData
{
	// 武器类型/ID
	union
	{
	u8 weaponType; // 武器类型
	ItemID weaponID; // 武器ID
	};
	// 武器类型/ID切换控制
	u8 isWeaponID; // 是否是武器特殊战斗动画
	// 动画编号
	AnimationID animation;
}ClassBattleAnimationConfig;

// ROM中的职业
typedef struct ClassInfo
{
	// 职业名称
	TextID name;

	// 职业描述
	TextID description;

	// 职业ID
	ClassID id;

	// 转职关联职业ID
	ClassID promote;

	// 静态职业形象
	u8 mapSprite;

	// 行走速度
	// 0-正常 1-慢
	u8 walkingSpeed;

	// 职业卡
	PortraitID classCard;

	// 不知道做什么用的，但是有用，偏移0xA
	u8 unk_A;

	// 职业基础值

	// HP
	s8 baseHp;
	// 力/魔
	s8 baseStr;
	// 技
	s8 baseSkl;
	// 速
	s8 baseSpd;
	// 守备
	s8 baseDef;
	// 魔防
	s8 baseRes;
	// 体格
	s8 baseCon;
	// 移动
	s8 baseMov;

	// 职业能力上限

	// HP
	s8 maxHp;
	// 力/魔
	s8 maxStr;
	// 技
	s8 maxSkl;
	// 速
	s8 maxSpd;
	// 守备
	s8 maxDef;
	// 魔防
	s8 maxRes;
	// 体格
	s8 maxCon;

	// 职业强度系数(决定击破经验值)
	u8 relativePower;

	// 职业成长率(主要是敌方杂兵用)

	// HP
	s8 growthHp;
	// 力/魔
	s8 growthStr;
	// 技
	s8 growthSkl;
	// 速
	s8 growthSpd;
	// 守备
	s8 growthDef;
	// 魔防
	s8 growthRes;
	// 幸运
	s8 growthCon;

	// 转职加成

	// HP
	s8 CCBonusHp;
	// 力/魔
	s8 CCBonusStr;
	// 技
	s8 CCBonusSkl;
	// 速
	s8 CCBonusSpd;
	// 守备
	s8 CCBonusDef;
	// 魔防
	s8 CCBonusRes;

	// 特殊能力(人物/职业共通)

	// Class & Character Ability 1

	// 骑乘系救出
	u8 ability_mountedAid:1;
	// 再移动
	u8 ability_moveAgain:1;
	// 盗窃
	u8 ability_steal:1;
	// 使用盗贼钥匙
	u8 ability_theifKey:1;
	// 舞蹈
	u8 ability_dance:1;
	// 吹奏
	u8 ability_play:1;
	// 必杀加成
	u8 ability_criticalBonus:1;
	// 使用弩车
	u8 ability_ballista:1;

	// Class & Character Ability 2

	// 上位职业
	u8 ability_promoted:1;
	// 运输队
	u8 ability_supplyDepot:1;
	// 骑马图标显示
	u8 ability_mountedIcon:1;
	// 龙骑士图标显示
	u8 ability_dragonKnightIcon:1;
	// 天马骑士图标显示
	u8 ability_pegasusKnightIcon:1;
	// 领主
	u8 ability_lord:1;
	// 女性
	u8 ability_female:1;
	// boss图标显示
	u8 ability_boss:1;

	// Class & Character Ability 3

	// 未使用武器锁
	u8 ability_unusedWeaponLock:1;
	// 倭刀武器锁
	u8 ability_WoDaoWeaponLock:1;
	// 龙石武器锁
	u8 ability_dragonStoneWeaponLock:1;
	// 人造人(包括作为boss出现时的维达)
	u8 ability_morph:1;
	// 无法选中(例如倒下的尼尔斯)
	u8 ability_preventControl:1;
	// 天马三角攻击
	u8 ability_pegasusTriangleAttack:1;
	// 重甲三角攻击
	u8 ability_armorTriangleAttack:1;
	// 不要使用这个能力位
	u8 ability_forbidden:1;

	// Class & Character Ability 4

	// 击破无经验值，瞬杀无效(例如封魔者).
	u8 ability_noExp:1;
	// 瞬杀
	u8 ability_lethality:1;
	// 封魔
	u8 ability_magicSeal:1;
	// 物品栏最后一个物品可掉落
	u8 ability_dropLastItem:1;
	// 艾利乌德武器锁
	u8 ability_EliwoodWeaponLock:1;
	// 海克托尔武器锁
	u8 ability_HectorWeaponLock:1;
	// 琳武器锁
	u8 ability_LynWeaponLock:1;
	// 阿特斯武器锁
	u8 ability_AthosWeaponLock:1;

	// 武器熟练度基础值

	// 剑等级
	u8 levelSword;
	// 枪等级
	u8 levelLance;
	// 斧等级
	u8 levelAxe;
	// 弓等级
	u8 levelBow;
	// 杖等级
	u8 levelStaff;
	// 理等级
	u8 levelAnima;
	// 光等级
	u8 levelLight;
	// 闇等级
	u8 levelDark;

	// 职业战斗动画设定
	ClassBattleAnimationConfig *battleAnimationConf;

	// 地形移动力消耗(每个地形每种天气每种职业一张表，多个职业共享一张表)

	// 晴天
	u8 *movementCost;
	// 雨天
	u8 *movementCostRain;
	// 雪天
	u8 *movementCostSnow;

	// 地形加成(每个地形每种效果每种职业一张表，多个职业共享一张表)

	// 守备
	u8 *terrainBonusDef;
	// 回避
	u8 *terrainBonusAvoid;
	// 魔防
	u8 *terrainBonusRes;
	// 未知指针，偏移0x50
	/* 在下列职业中被用到:
		0x1C Monk
		0x1D Cleric
		0x1E Bishop
		0x1F Bishop(F)
		0x39 Brigand
		0x3A Pirate
		0x3B Berserker
		0x50 Corsair
		即修道士、修女、司祭、山贼、海贼、湖贼、狂战士
	*/
	u8 *unk_ptr_50;
	
}Class;

// WRAM中的人物
typedef struct UnitDataInWRAM
{
	// 角色指针
	Character *character;
	// 职业指针
	Class *m_class;
	// 等级
	u8 lv;
	// 经验值
	u8 exp;
	// 未知,偏移0xA
	u8 unk_A;
	// 编号(我军:1-0x3E(62人) 敌军:0x81-0xB2(50人) NPC:0x41-0x54(20人) 通信斗技场第4军:0xC1-0xC5(5人))
	u8 deployNumber;
	// 行动状态(0-行动前)
	u8 actionState;
	// 未知标识位,偏移0xD,bit0-3
	u8 unk_flags_D_0_3:4;
	// 物品掉落
	u8 dropItem:1;
	// 成长率上升(亚法水滴使用效果)
	u8 growthPlus:1;
	// 未知标识位,偏移0xD,bit6-7
	u8 unk_flags_D_6_7:2;
	// 未知，偏移0xE
	u8 unk_E;
	// 未知，偏移0xF
	u8 unk_F;
	// X坐标
	u8 PositionX;
	// Y坐标
	u8 PositionY;
	// 最大HP
	s8 maxHp;
	// 现在HP
	s8 hp;
	// 力/魔
	s8 str;
	// 技
	s8 skl;
	// 速
	s8 spd;
	// 守备
	s8 def;
	// 魔防
	s8 res;
	// 幸运
	s8 luk;
	// 体格附加值
	s8 conBonus;
	// 同行人物编号(救出/被救出)
	u8 aidUnitNumber;
	// 未知，偏移0x1C
	u8 unk_1C;
	// 移动附加值
	s8 movBonus;

	// 携带物品栏
	ItemData items[5];

	// 武器熟练度

	// 剑等级
	u8 levelSword;
	// 枪等级
	u8 levelLance;
	// 斧等级
	u8 levelAxe;
	// 弓等级
	u8 levelBow;
	// 杖等级
	u8 levelStaff;
	// 理等级
	u8 levelAnima;
	// 光等级
	u8 levelLight;
	// 闇等级
	u8 levelDark;

	// buff/异常状态种类
	u8 stateType:4;
	// buff/异常状态持续回合数
	u8 stateTurn:4;

	// 火把/照明杖剩余回合数(视野附加值)
	u8 sightBonus:4;
	// 圣水/魔防杖剩余回合数(魔防附加值)
	u8 resBonus:4;

	// 支援等级
	u8 levelSupport[7];

	// 支援解锁flag

	// 第1人
	u8 unlockSupport1:1;
	// 第2人
	u8 unlockSupport2:1;
	// 第3人
	u8 unlockSupport3:1;
	// 第4人
	u8 unlockSupport4:1;
	// 第5人
	u8 unlockSupport5:1;
	// 第6人
	u8 unlockSupport6:1;
	// 第7人
	u8 unlockSupport7:1;
	// 填充位
	u8 unlockSupport8:1;
		
	// 未知，偏移0x3A
	u8 unk_3A[6];

	// AI(电脑控制下的任务行为规则)

	// 回血
	u8 AI_healing:3;
	// 目标选择
	u8 AI_targeting:5;
	// 撤退
	u8 AI_retreat;
	// 行动
	u8 AI_action;
	u8 AI_action_counter;
	// 移动
	u8 AI_movement;
	u8 AI_movement_counter;

	// 未知，偏移0x46
	u8 unk_46[2];
}Unit;

// 人物内存池
#define units			((Unit *)0x202BD4C)
#define playerNum		62
#define enemyNum		50
#define npcNum			20
#define p4Num			5
#define units_player	((Unit *)0x202BD4C)
#define units_enemy		((Unit *)0x202BD4C + playerNum)
#define units_npc		((Unit *)0x202BD4C + playerNum + enemyNum)
#define units_p4		((Unit *)0x202BD4C + playerNum + enemyNum + npcNum)
#define units_end		((Unit *)0x202BD4C + playerNum + enemyNum + npcNum + p4Num)

// 人物buff/异常状态种类定义

// 正常
#define unitState_none		0
// 中毒
#define	unitState_poison	1
// 睡眠
#define	unitState_sleep		2
// 沉默
#define	unitState_silence	3
// 狂乱
#define	unitState_berserker	4
// 攻击上升
#define	unitState_attack	5
// 防御上升
#define	unitState_defense	6
// 必杀上升
#define	unitState_critical	7
// 回避上升
#define	unitState_avoid		8
// 生病
#define	unitState_ill		9
// 石化(圣魔里有，烈火里没有)
#define unitState_stone		0

// 武器类型定义

// 剑
#define weaponType_sword				0
// 枪
#define weaponType_lance				1
// 斧
#define weaponType_axe					2
// 弓
#define weaponType_bow					3
// 杖
#define weaponType_staff				4
// 理
#define weaponType_anima				5
// 光
#define weaponType_light				6
// 闇
#define weaponType_dark					7
// 道具
#define weaponType_item					9
// 龙石/魔物专用
#define weaponType_dragonStone			0xB
// 戒指
#define weaponType_ring					0xC
// 火龙石
#define weaponType_flameDragonStone		0x11
// 舞蹈戒指?
#define weaponType_dancingRing			0x12

// ROM中的武器道具
typedef struct ItemInfo
{
	
	// The name
	TextID name;
	
	// The description
	TextID description;
	
	// The use description
	TextID useDescription;
	
	// The identifier
	ItemID id;
	
	// The category
	u8 category;

	//Weapon Ability 1
	
	// weapon? equippable? 物理?
	u8 isWeapon : 1;
	
	// magic? 魔法?
	u8 isMagic : 1;
	
	// staff? 杖?
	u8 isStaff : 1;
	
	// --/--? 耐久無限?
	u8 isIndestructible : 1;
	
	// unsellable? 売却不可?
	u8 isUnsellable : 1;
	
	// brave weapon? double attack? 二回攻撃?
	u8 isBrave : 1;
	
	// magic damage? 間接固定? 魔法剣?
	u8 isSpell : 1;
	
	// uncounterable? 双方反撃不可?
	u8 isUncounterable : 1;

	//Weapon Ability 2
	
	// reverse weapon triangle? 属性逆転?
	u8 isReverse : 1;
	
	// unrepairable? 修理不可?
	u8 isUnrepairable : 1;
	
	// The dragon stone weapon lock. 竜石専用.
	u8 dragonStoneWPLock : 1;
	
	// The unused weapon lock
	u8 unusedWPLock : 1;
	
	// The sword weapon lock. Swordfighter/Swordmaster/Lyn. 剣士系専用.
	u8 swordWPLock : 1;
	
	// 専用マークのみ
	u8 unknownAbility2 : 1;
	
	// The flier talisman. Negate Flying Effectiveness. 飛行特効無効.
	u8 flierTalisman : 1;
	
	// The critical talisman. Negate Critical attacks. 必殺無効.
	u8 CRTTalisman : 1;

	//Weapon Ability 3
	
	// Weapon Unusable? 使用不可?
	u8 isUnusable : 1;
	
	// Negate Target Defenses? 防御無視?
	u8 isLunar : 1;
	
	// Locked to Eliwood/Eirika. エリウッド専用.
	u8 EliwoodWPLock : 1;
	
	// Locked to Hector/Ephraim. ヘクトル専用.
	u8 HectorWPLock : 1;
	
	// Locked to Lyn. リン専用.
	u8 LynWPLock : 1;
	
	// Locked to Athos. アトス専用.
	u8 AthosWPLock : 1;
	
	// The unknown ability4
	u8 unknownAbility4 : 1;
	
	// The unknown ability5
	u8 unknownAbility5 : 1;

	//Weapon Ability 4
	
	// The unknown ability6
	u8 unknownAbility6 : 1;
	
	// The unknown ability7
	u8 unknownAbility7 : 1;
	
	// The unknown ability8
	u8 unknownAbility8 : 1;
	
	// The unknown ability9
	u8 unknownAbility9 : 1;
	
	// The unknown ability10
	u8 unknownAbility10 : 1;
	
	// The unknown ability11
	u8 unknownAbility11 : 1;
	
	// The unknown ability12
	u8 unknownAbility12 : 1;
	
	// The unknown ability13
	u8 unknownAbility13 : 1;

	
	// Stat Bonuses Pointer. 能力修正アドレス. 指向装备武器附加能力值和使用道具增长能力值的指针.
	WeaponStatBonus *pStatBonus;
	
	// 指向武器特效职业列表的指针. 对哪些职业有特效. 特効指定アドレス.
	ClassID *pEffectivenessClassList;

	
	// The durability. 耐久.
	u8 durability;
	
	// The power. 攻撃.
	u8 power;
	
	// The hit rate. 命中.
	u8 hit;
	
	// The weight. 重さ.
	u8 WT;
	
	// The critical rate. 必殺.
	u8 CRT;
	
	// The minimum range. 射程下限.
	u8 minRange : 4;
	
	// The maximum range. 射程上限.
	u8 maxRange : 4;
	
	// Cost Per Use (0 = Unsellable). 単価.
	u16 cost;
	
	// The rank. レベル.
	u8 rank;
	
	// The icon #. アイコン. 图标.
	IconID icon;
	
	// Staff/Use Effect. 使った場合効果. 杖和物品的使用效果.
	u8 useEffect;
	
	// Weapon Effect. ダメージ追加効果. 武器追加效果.
	u8 WPEffect;
	
	// Weapon Experience. 武器Lv熟練度. 使用一次该武器所获得的武器熟练度.
	u8 WPEXP;
	
	u8 unk_21;
	u8 unk_22;
	u8 unk_23;
}Item;

