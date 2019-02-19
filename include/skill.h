// 技能系统
// 分为攻击技、防御技和回复技，用计数(cd)的方式发动，类似手游
// by laqieer
// 2019-2-19

#pragma once

#include "AgbTypes.h"
#include "FE7JStructDef.h"

// 攻击技cd
extern u8 skill_count_attack_player[];
extern u8 skill_count_attack_enemy[];
extern u8 skill_count_attack_npc[];
extern u8 skill_count_attack_p4[];

// 防御技cd
extern u8 skill_count_defend_player[];
extern u8 skill_count_defend_enemy[];
extern u8 skill_count_defend_npc[];
extern u8 skill_count_defend_p4[];

// 回复技cd
extern u8 skill_count_heal_player[];
extern u8 skill_count_heal_enemy[];
extern u8 skill_count_heal_npc[];
extern u8 skill_count_heal_p4[];

// 能力值类型
typedef enum PersonalDataType
{
	none = 0,
	hp,	// 最大hp - 现在hp
	atk, // 攻击 
	def, // 守备
	mdf, // 魔防
	skl, // 技术
	spd, // 速度
	luk, // 幸运
	con, // 体格
	mov // 移动
}StatType;

// 能力值计算方式
typedef enum PersonalDataCalcType
{
	self = 0, // 自己的
	target, // 对方的
	diff, // 自己的 - 对方的
	diff2 // 对方的 - 自己的
}StatCalcType;

// 攻击技能定义
// damage = (damage + stat * stat_calc_coefficient) * damage_plus_coefficient + damage_plus_fixed
typedef struct SkillAttack
{
	const char * name;
	const char * description;
	int count; // cd
	StatType stat_type;
	StatCalcType stat_calc_type;
	int stat_calc_coefficient;
	int damage_plus_coefficient;
	int damage_plus_fixed;
}SKL_ATK;

// 防守技能定义
// if (weapon type is in weapon_type_list)
//     damage = max(min_hp, damage * damage_cut_coefficient - damage_cut_fixed)
typedef struct SkillDefend
{
	const char * name;
	const char * description;
	int count; // cd
	const u8 *weapon_type_list;
	int damage_cut_coefficient;
	int damage_cut_fixed;
	int min_hp;
}SKL_DEF;

// 回复技能定义
// hp_heal_target = hp_heal_target * hp_heal_coefficient_target + hp_heal_fixed_target
// hp_heal_self = hp_heal_self * hp_heal_coefficient_self + hp_heal_fixed_self
typedef struct SkillHeal
{
	const char * name;
	const char * description;
	int count; // cd
	int hp_heal_coefficient_target;
	int hp_heal_fixed_target;
	int hp_heal_coefficient_self;
	int hp_heal_fixed_self;
}SKL_HEAL;

