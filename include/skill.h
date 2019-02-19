// ����ϵͳ
// ��Ϊ���������������ͻظ������ü���(cd)�ķ�ʽ��������������
// by laqieer
// 2019-2-19

#pragma once

#include "AgbTypes.h"
#include "FE7JStructDef.h"

// ������cd
extern u8 skill_count_attack_player[];
extern u8 skill_count_attack_enemy[];
extern u8 skill_count_attack_npc[];
extern u8 skill_count_attack_p4[];

// ������cd
extern u8 skill_count_defend_player[];
extern u8 skill_count_defend_enemy[];
extern u8 skill_count_defend_npc[];
extern u8 skill_count_defend_p4[];

// �ظ���cd
extern u8 skill_count_heal_player[];
extern u8 skill_count_heal_enemy[];
extern u8 skill_count_heal_npc[];
extern u8 skill_count_heal_p4[];

// ����ֵ����
typedef enum PersonalDataType
{
	none = 0,
	hp,	// ���hp - ����hp
	atk, // ���� 
	def, // �ر�
	mdf, // ħ��
	skl, // ����
	spd, // �ٶ�
	luk, // ����
	con, // ���
	mov // �ƶ�
}StatType;

// ����ֵ���㷽ʽ
typedef enum PersonalDataCalcType
{
	self = 0, // �Լ���
	target, // �Է���
	diff, // �Լ��� - �Է���
	diff2 // �Է��� - �Լ���
}StatCalcType;

// �������ܶ���
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

// ���ؼ��ܶ���
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

// �ظ����ܶ���
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

