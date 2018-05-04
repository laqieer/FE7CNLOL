// �ṹ�嶨��
// by laqieer
// 2018-04-21

#include "AgbTypes.h"

typedef		u16						TextID;	// �ı�id
typedef		u8						ClassID; // ְҵid
typedef		u8						CharacterID; // ����id
typedef		u8						ItemID;	// ��Ʒid
typedef		u16						AnimationID; // ����id
typedef		u8						IconID;	// ͼ��id
typedef		u16						PortraitID;	// ͷ��id

// װ��������������(ʹ����Ʒ���ü�����)
typedef struct WeaponStatBonusInfo
{
	
	// The HP.
	s8 hp;
	
	// The attack. ����.
	s8 atk;
	
	// The skill. ��.
	s8 skl;
	
	// The speed. �٤�.
	s8 spd;
	
	// The defense. �؂�.
	s8 def;
	
	// The magic defense. ħ��.
	s8 res;
	
	// The luck. ���\.
	s8 luk;
	
	// The movement. �Ƅ���.
	s8 mov;
	
	// The constitution. ���.
	s8 con;
	
	s8 unk_9;
	s8 unk_A;
	s8 unk_B;
}WeaponStatBonus;

// �������Զ���

// ������
#define AffinityNone	0
// ������
#define AffinityFire	1
// ������
#define AffinityThunder	2
// ������
#define AffinityWind	3
// ˮ����
#define AffinityWater	4
// �����
#define AffinityDark	5
// ������
#define AffinityLight	6
// ������
#define AffinityAnima	7

// ����֧Ԯ�趨����
typedef struct SupportDataConfig
{
	// ֧Ԯ����
	CharacterID person[7];
	// �øжȳ�ʼֵ
	u8 favorInitial[7];
	// �øж�ÿ�غ�����ֵ
	u8 favorGrowth[7];
	// ֧Ԯ��������
	u8 supportNumber;
	// ������2���ֽڣ�ƫ��0x16
	u16 pad_16;
}SupportData;

// ROM�е�����
typedef struct CharacterInfo
{
	// ��������
	TextID name;

	// ��������
	TextID description;

	// �������
	CharacterID id;

	// ְҵ(������֧Ԯ������ʾ)
	ClassID m_class;

	// ����ͷ��
	PortraitID portrait;

	// Сͷ��(��������ͷ�����Сͷ��,0-Ĭ��)
	// 0x00 Default
	// 0x01 Dragon
	// 0x02 Ostia/Caelin/Civilian
	// 0x03 Black Fang/Morph/Bandit
	u8 miniPortrait;

	// ����
	u8 affinity;

	// ���Ӳ˵�����˳��
	u8 sortID;

	// ��������ֵ

	// �ȼ�
	s8 baseLv;
	// ��/ħ��
	s8 baseStr;
	// ����
	s8 baseSkl;
	// �ٶ�
	s8 baseSpd;
	// �ر�
	s8 baseDef;
	// ħ��
	s8 baseRes;
	// ����
	s8 baseLuk;
	// ��񸽼�ֵ
	s8 baseConBonus;
	
	// ����������

	// ���ȼ�
	u8 levelSword;
	// ǹ�ȼ�
	u8 levelLance;
	// ���ȼ�
	u8 levelAxe;
	// ���ȼ�
	u8 levelBow;
	// �ȵȼ�
	u8 levelStaff;
	// ��ȼ�
	u8 levelAnima;
	// ��ȼ�
	u8 levelLight;
	// 霵ȼ�
	u8 levelDark;

	// �ɳ���

	// hp�ɳ�
	u8 growthHp;
	// ��/ħ���ɳ�
	u8 growthStr;
	// �����ɳ�
	u8 growthSkl;
	// �ٶȳɳ�
	u8 growthSpd;
	// �ر��ɳ�
	u8 growthDef;
	// ħ���ɳ�
	u8 growthRes;
	// ���˳ɳ�
	u8 growthLuk;

	// ����ս�����������ɫ����

	// ��λְҵ
	u8 paletteIdUnpromoted;
	// ��λְҵ
	u8 paletteIdPromoted;

	// ��������ս���������

	// ��λְҵ
	u8 battleAnimationIdUnpromoted;
	// ��λְҵ
	u8 battleAnimationIdPromoted;

	// ����ֽ�
	u8 pad_27;

	// ��������(����/ְҵ��ͨ)

	// Class & Character Ability 1

	// ���ϵ�ȳ�
	u8 ability_mountedAid:1;
	// ���ƶ�
	u8 ability_moveAgain:1;
	// ����
	u8 ability_steal:1;
	// ʹ�õ���Կ��
	u8 ability_theifKey:1;
	// �赸
	u8 ability_dance:1;
	// ����
	u8 ability_play:1;
	// ��ɱ�ӳ�
	u8 ability_criticalBonus:1;
	// ʹ����
	u8 ability_ballista:1;
	
	// Class & Character Ability 2

	// ��λְҵ
	u8 ability_promoted:1;
	// �����
	u8 ability_supplyDepot:1;
	// ����ͼ����ʾ
	u8 ability_mountedIcon:1;
	// ����ʿͼ����ʾ
	u8 ability_dragonKnightIcon:1;
	// ������ʿͼ����ʾ
	u8 ability_pegasusKnightIcon:1;
	// ����
	u8 ability_lord:1;
	// Ů��
	u8 ability_female:1;
	// bossͼ����ʾ
	u8 ability_boss:1;
	
	// Class & Character Ability 3

	// δʹ��������
	u8 ability_unusedWeaponLock:1;
	// ����������
	u8 ability_WoDaoWeaponLock:1;
	// ��ʯ������
	u8 ability_dragonStoneWeaponLock:1;
	// ������(������Ϊboss����ʱ��ά��)
	u8 ability_morph:1;
	// �޷�ѡ��(���絹�µ����˹)
	u8 ability_preventControl:1;
	// �������ǹ���
	u8 ability_pegasusTriangleAttack:1;
	// �ؼ����ǹ���
	u8 ability_armorTriangleAttack:1;
	// ��Ҫʹ���������λ
	u8 ability_forbidden:1;

	// Class & Character Ability 4

	// �����޾���ֵ��˲ɱ��Ч(�����ħ��).
	u8 ability_noExp:1;
	// ˲ɱ
	u8 ability_lethality:1;
	// ��ħ
	u8 ability_magicSeal:1;
	// ��Ʒ�����һ����Ʒ�ɵ���
	u8 ability_dropLastItem:1;
	// �����ڵ�������
	u8 ability_EliwoodWeaponLock:1;
	// �����ж�������
	u8 ability_HectorWeaponLock:1;
	// ��������
	u8 ability_LynWeaponLock:1;
	// ����˹������
	u8 ability_AthosWeaponLock:1;

	// ֧Ԯ�趨
	SupportData *support;

	// ���Ʋ�ͬ������ĳ��������˵��ͬ�Ļ�
	// http://feuniverse.us/t/fe7-ch25h-fort-seizing-dialogue/1446
	u8 dialogueId;

	// ����ֽڣ�ƫ��0x31
	u8 pad_31;

	// ���˫�ֽڣ�ƫ��0x32
	u16 pad_32;
}Character;

// ��Ʒ+����
typedef struct ItemDataInfo
{
	ItemID item;	// ��Ʒ����
	u8 number;		// ��Ʒ����
}ItemData;

// ְҵս��������������
typedef struct ClassBattleAnimationConfigData
{
	// ��������/ID
	union
	{
	u8 weaponType; // ��������
	ItemID weaponID; // ����ID
	};
	// ��������/ID�л�����
	u8 isWeaponID; // �Ƿ�����������ս������
	// �������
	AnimationID animation;
}ClassBattleAnimationConfig;

// ROM�е�ְҵ
typedef struct ClassInfo
{
	// ְҵ����
	TextID name;

	// ְҵ����
	TextID description;

	// ְҵID
	ClassID id;

	// תְ����ְҵID
	ClassID promote;

	// ��ְ̬ҵ����
	u8 mapSprite;

	// �����ٶ�
	// 0-���� 1-��
	u8 walkingSpeed;

	// ְҵ��
	PortraitID classCard;

	// ��֪����ʲô�õģ��������ã�ƫ��0xA
	u8 unk_A;

	// ְҵ����ֵ

	// HP
	s8 baseHp;
	// ��/ħ
	s8 baseStr;
	// ��
	s8 baseSkl;
	// ��
	s8 baseSpd;
	// �ر�
	s8 baseDef;
	// ħ��
	s8 baseRes;
	// ���
	s8 baseCon;
	// �ƶ�
	s8 baseMov;

	// ְҵ��������

	// HP
	s8 maxHp;
	// ��/ħ
	s8 maxStr;
	// ��
	s8 maxSkl;
	// ��
	s8 maxSpd;
	// �ر�
	s8 maxDef;
	// ħ��
	s8 maxRes;
	// ���
	s8 maxCon;

	// ְҵǿ��ϵ��(�������ƾ���ֵ)
	u8 relativePower;

	// ְҵ�ɳ���(��Ҫ�ǵз��ӱ���)

	// HP
	s8 growthHp;
	// ��/ħ
	s8 growthStr;
	// ��
	s8 growthSkl;
	// ��
	s8 growthSpd;
	// �ر�
	s8 growthDef;
	// ħ��
	s8 growthRes;
	// ����
	s8 growthCon;

	// תְ�ӳ�

	// HP
	s8 CCBonusHp;
	// ��/ħ
	s8 CCBonusStr;
	// ��
	s8 CCBonusSkl;
	// ��
	s8 CCBonusSpd;
	// �ر�
	s8 CCBonusDef;
	// ħ��
	s8 CCBonusRes;

	// ��������(����/ְҵ��ͨ)

	// Class & Character Ability 1

	// ���ϵ�ȳ�
	u8 ability_mountedAid:1;
	// ���ƶ�
	u8 ability_moveAgain:1;
	// ����
	u8 ability_steal:1;
	// ʹ�õ���Կ��
	u8 ability_theifKey:1;
	// �赸
	u8 ability_dance:1;
	// ����
	u8 ability_play:1;
	// ��ɱ�ӳ�
	u8 ability_criticalBonus:1;
	// ʹ����
	u8 ability_ballista:1;

	// Class & Character Ability 2

	// ��λְҵ
	u8 ability_promoted:1;
	// �����
	u8 ability_supplyDepot:1;
	// ����ͼ����ʾ
	u8 ability_mountedIcon:1;
	// ����ʿͼ����ʾ
	u8 ability_dragonKnightIcon:1;
	// ������ʿͼ����ʾ
	u8 ability_pegasusKnightIcon:1;
	// ����
	u8 ability_lord:1;
	// Ů��
	u8 ability_female:1;
	// bossͼ����ʾ
	u8 ability_boss:1;

	// Class & Character Ability 3

	// δʹ��������
	u8 ability_unusedWeaponLock:1;
	// ����������
	u8 ability_WoDaoWeaponLock:1;
	// ��ʯ������
	u8 ability_dragonStoneWeaponLock:1;
	// ������(������Ϊboss����ʱ��ά��)
	u8 ability_morph:1;
	// �޷�ѡ��(���絹�µ����˹)
	u8 ability_preventControl:1;
	// �������ǹ���
	u8 ability_pegasusTriangleAttack:1;
	// �ؼ����ǹ���
	u8 ability_armorTriangleAttack:1;
	// ��Ҫʹ���������λ
	u8 ability_forbidden:1;

	// Class & Character Ability 4

	// �����޾���ֵ��˲ɱ��Ч(�����ħ��).
	u8 ability_noExp:1;
	// ˲ɱ
	u8 ability_lethality:1;
	// ��ħ
	u8 ability_magicSeal:1;
	// ��Ʒ�����һ����Ʒ�ɵ���
	u8 ability_dropLastItem:1;
	// �����ڵ�������
	u8 ability_EliwoodWeaponLock:1;
	// �����ж�������
	u8 ability_HectorWeaponLock:1;
	// ��������
	u8 ability_LynWeaponLock:1;
	// ����˹������
	u8 ability_AthosWeaponLock:1;

	// ���������Ȼ���ֵ

	// ���ȼ�
	u8 levelSword;
	// ǹ�ȼ�
	u8 levelLance;
	// ���ȼ�
	u8 levelAxe;
	// ���ȼ�
	u8 levelBow;
	// �ȵȼ�
	u8 levelStaff;
	// ��ȼ�
	u8 levelAnima;
	// ��ȼ�
	u8 levelLight;
	// 霵ȼ�
	u8 levelDark;

	// ְҵս�������趨
	ClassBattleAnimationConfig *battleAnimationConf;

	// �����ƶ�������(ÿ������ÿ������ÿ��ְҵһ�ű����ְҵ����һ�ű�)

	// ����
	u8 *movementCost;
	// ����
	u8 *movementCostRain;
	// ѩ��
	u8 *movementCostSnow;

	// ���μӳ�(ÿ������ÿ��Ч��ÿ��ְҵһ�ű����ְҵ����һ�ű�)

	// �ر�
	u8 *terrainBonusDef;
	// �ر�
	u8 *terrainBonusAvoid;
	// ħ��
	u8 *terrainBonusRes;
	// δָ֪�룬ƫ��0x50
	/* ������ְҵ�б��õ�:
		0x1C Monk
		0x1D Cleric
		0x1E Bishop
		0x1F Bishop(F)
		0x39 Brigand
		0x3A Pirate
		0x3B Berserker
		0x50 Corsair
		���޵�ʿ����Ů��˾����ɽ������������������սʿ
	*/
	u8 *unk_ptr_50;
	
}Class;

// WRAM�е�����
typedef struct UnitDataInWRAM
{
	// ��ɫָ��
	Character *character;
	// ְҵָ��
	Class *m_class;
	// �ȼ�
	u8 lv;
	// ����ֵ
	u8 exp;
	// δ֪,ƫ��0xA
	u8 unk_A;
	// ���(�Ҿ�:1-0x3E(62��) �о�:0x81-0xB2(50��) NPC:0x41-0x54(20��) ͨ�Ŷ�������4��:0xC1-0xC5(5��))
	u8 deployNumber;
	// �ж�״̬(0-�ж�ǰ)
	u8 actionState;
	// δ֪��ʶλ,ƫ��0xD,bit0-3
	u8 unk_flags_D_0_3:4;
	// ��Ʒ����
	u8 dropItem:1;
	// �ɳ�������(�Ƿ�ˮ��ʹ��Ч��)
	u8 growthPlus:1;
	// δ֪��ʶλ,ƫ��0xD,bit6-7
	u8 unk_flags_D_6_7:2;
	// δ֪��ƫ��0xE
	u8 unk_E;
	// δ֪��ƫ��0xF
	u8 unk_F;
	// X����
	u8 PositionX;
	// Y����
	u8 PositionY;
	// ���HP
	s8 maxHp;
	// ����HP
	s8 hp;
	// ��/ħ
	s8 str;
	// ��
	s8 skl;
	// ��
	s8 spd;
	// �ر�
	s8 def;
	// ħ��
	s8 res;
	// ����
	s8 luk;
	// ��񸽼�ֵ
	s8 conBonus;
	// ͬ��������(�ȳ�/���ȳ�)
	u8 aidUnitNumber;
	// δ֪��ƫ��0x1C
	u8 unk_1C;
	// �ƶ�����ֵ
	s8 movBonus;

	// Я����Ʒ��
	ItemData items[5];

	// ����������

	// ���ȼ�
	u8 levelSword;
	// ǹ�ȼ�
	u8 levelLance;
	// ���ȼ�
	u8 levelAxe;
	// ���ȼ�
	u8 levelBow;
	// �ȵȼ�
	u8 levelStaff;
	// ��ȼ�
	u8 levelAnima;
	// ��ȼ�
	u8 levelLight;
	// 霵ȼ�
	u8 levelDark;

	// buff/�쳣״̬����
	u8 stateType:4;
	// buff/�쳣״̬�����غ���
	u8 stateTurn:4;

	// ���/������ʣ��غ���(��Ұ����ֵ)
	u8 sightBonus:4;
	// ʥˮ/ħ����ʣ��غ���(ħ������ֵ)
	u8 resBonus:4;

	// ֧Ԯ�ȼ�
	u8 levelSupport[7];

	// ֧Ԯ����flag

	// ��1��
	u8 unlockSupport1:1;
	// ��2��
	u8 unlockSupport2:1;
	// ��3��
	u8 unlockSupport3:1;
	// ��4��
	u8 unlockSupport4:1;
	// ��5��
	u8 unlockSupport5:1;
	// ��6��
	u8 unlockSupport6:1;
	// ��7��
	u8 unlockSupport7:1;
	// ���λ
	u8 unlockSupport8:1;
		
	// δ֪��ƫ��0x3A
	u8 unk_3A[6];

	// AI(���Կ����µ�������Ϊ����)

	// ��Ѫ
	u8 AI_healing:3;
	// Ŀ��ѡ��
	u8 AI_targeting:5;
	// ����
	u8 AI_retreat;
	// �ж�
	u8 AI_action;
	u8 AI_action_counter;
	// �ƶ�
	u8 AI_movement;
	u8 AI_movement_counter;

	// δ֪��ƫ��0x46
	u8 unk_46[2];
}Unit;

// �����ڴ��
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

// ����buff/�쳣״̬���ඨ��

// ����
#define unitState_none		0
// �ж�
#define	unitState_poison	1
// ˯��
#define	unitState_sleep		2
// ��Ĭ
#define	unitState_silence	3
// ����
#define	unitState_berserker	4
// ��������
#define	unitState_attack	5
// ��������
#define	unitState_defense	6
// ��ɱ����
#define	unitState_critical	7
// �ر�����
#define	unitState_avoid		8
// ����
#define	unitState_ill		9
// ʯ��(ʥħ���У��һ���û��)
#define unitState_stone		0

// �������Ͷ���

// ��
#define weaponType_sword				0
// ǹ
#define weaponType_lance				1
// ��
#define weaponType_axe					2
// ��
#define weaponType_bow					3
// ��
#define weaponType_staff				4
// ��
#define weaponType_anima				5
// ��
#define weaponType_light				6
// �
#define weaponType_dark					7
// ����
#define weaponType_item					9
// ��ʯ/ħ��ר��
#define weaponType_dragonStone			0xB
// ��ָ
#define weaponType_ring					0xC
// ����ʯ
#define weaponType_flameDragonStone		0x11
// �赸��ָ?
#define weaponType_dancingRing			0x12

// ROM�е���������
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
	
	// weapon? equippable? ����?
	u8 isWeapon : 1;
	
	// magic? ħ��?
	u8 isMagic : 1;
	
	// staff? ��?
	u8 isStaff : 1;
	
	// --/--? �;ßo��?
	u8 isIndestructible : 1;
	
	// unsellable? ��ȴ����?
	u8 isUnsellable : 1;
	
	// brave weapon? double attack? ���ع���?
	u8 isBrave : 1;
	
	// magic damage? �g�ӹ̶�? ħ����?
	u8 isSpell : 1;
	
	// uncounterable? ˫�����Ĳ���?
	u8 isUncounterable : 1;

	//Weapon Ability 2
	
	// reverse weapon triangle? ������ܞ?
	u8 isReverse : 1;
	
	// unrepairable? ������?
	u8 isUnrepairable : 1;
	
	// The dragon stone weapon lock. �oʯ����.
	u8 dragonStoneWPLock : 1;
	
	// The unused weapon lock
	u8 unusedWPLock : 1;
	
	// The sword weapon lock. Swordfighter/Swordmaster/Lyn. ��ʿϵ����.
	u8 swordWPLock : 1;
	
	// ���åީ`���Τ�
	u8 unknownAbility2 : 1;
	
	// The flier talisman. Negate Flying Effectiveness. �w���؄��o��.
	u8 flierTalisman : 1;
	
	// The critical talisman. Negate Critical attacks. �ؚ��o��.
	u8 CRTTalisman : 1;

	//Weapon Ability 3
	
	// Weapon Unusable? ʹ�ò���?
	u8 isUnusable : 1;
	
	// Negate Target Defenses? �����oҕ?
	u8 isLunar : 1;
	
	// Locked to Eliwood/Eirika. ���ꥦ�åɌ���.
	u8 EliwoodWPLock : 1;
	
	// Locked to Hector/Ephraim. �إ��ȥ댟��.
	u8 HectorWPLock : 1;
	
	// Locked to Lyn. �����.
	u8 LynWPLock : 1;
	
	// Locked to Athos. ���ȥ�����.
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

	
	// Stat Bonuses Pointer. �����������ɥ쥹. ָ��װ��������������ֵ��ʹ�õ�����������ֵ��ָ��.
	WeaponStatBonus *pStatBonus;
	
	// ָ��������Чְҵ�б��ָ��. ����Щְҵ����Ч. �؄�ָ�����ɥ쥹.
	ClassID *pEffectivenessClassList;

	
	// The durability. �;�.
	u8 durability;
	
	// The power. ����.
	u8 power;
	
	// The hit rate. ����.
	u8 hit;
	
	// The weight. �ؤ�.
	u8 WT;
	
	// The critical rate. �ؚ�.
	u8 CRT;
	
	// The minimum range. �������.
	u8 minRange : 4;
	
	// The maximum range. �������.
	u8 maxRange : 4;
	
	// Cost Per Use (0 = Unsellable). �g��.
	u16 cost;
	
	// The rank. ��٥�.
	u8 rank;
	
	// The icon #. ��������. ͼ��.
	IconID icon;
	
	// Staff/Use Effect. ʹ�ä����τ���. �Ⱥ���Ʒ��ʹ��Ч��.
	u8 useEffect;
	
	// Weapon Effect. ����`��׷�ӄ���. ����׷��Ч��.
	u8 WPEffect;
	
	// Weapon Experience. ����Lv�쾚��. ʹ��һ�θ���������õ�����������.
	u8 WPEXP;
	
	u8 unk_21;
	u8 unk_22;
	u8 unk_23;
}Item;

