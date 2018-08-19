@ Generated by BattleAnimationDumper
@ 2017/10/05 22:43:58

	.include	"BattleAnimationEventDef.inc"

	.include	"../include/BattleAnimation_MyrrhInvers_sheet.inc"

	.section	.rodata
	.align	4
	.global	BattleAnimation_MyrrhInvers_data1
	.global	BattleAnimation_MyrrhInvers_data2
	.global	BattleAnimation_MyrrhInvers_data3
	.global	BattleAnimation_MyrrhInvers_data4
	.include	"../include/BattleAnimation_MyrrhInvers_OAMInfo.inc"

BattleAnimation_MyrrhInvers_data2:

BattleAnimation_MyrrhInvers_Mode1:	@ Normal attack (Layered in front of the enemy)

	@ Cmd 2
	@ Cmd 0xE
	@ SetPal BattleAnimation_MyrrhDragon_pal
	SetPal BattleAnimation_MyrrhTrans_pal
	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 9
	Show 1, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_1 - BattleAnimation_MyrrhInvers_data3, 4
	Show 2, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_2 - BattleAnimation_MyrrhInvers_data3, 2
	Show 3, BattleAnimation_MyrrhInvers_sheet_2, BattleAnimation_MyrrhInvers_frame_R_3 - BattleAnimation_MyrrhInvers_data3, 2
	Show 4, BattleAnimation_MyrrhInvers_sheet_2, BattleAnimation_MyrrhInvers_frame_R_4 - BattleAnimation_MyrrhInvers_data3, 3
	Show 5, BattleAnimation_MyrrhInvers_sheet_2, BattleAnimation_MyrrhInvers_frame_R_5 - BattleAnimation_MyrrhInvers_data3, 3
	Show 6, BattleAnimation_MyrrhInvers_sheet_3, BattleAnimation_MyrrhInvers_frame_R_6 - BattleAnimation_MyrrhInvers_data3, 3
	Show 7, BattleAnimation_MyrrhInvers_sheet_3, BattleAnimation_MyrrhInvers_frame_R_7 - BattleAnimation_MyrrhInvers_data3, 2
	Show 8, BattleAnimation_MyrrhInvers_sheet_3, BattleAnimation_MyrrhInvers_frame_R_8 - BattleAnimation_MyrrhInvers_data3, 2
	@ SetPal BattleAnimation_Myrrh_pal
	Show 9, BattleAnimation_MyrrhInvers_sheet_4, BattleAnimation_MyrrhInvers_frame_R_9 - BattleAnimation_MyrrhInvers_data3, 2
	Show 10, BattleAnimation_MyrrhInvers_sheet_4, BattleAnimation_MyrrhInvers_frame_R_10 - BattleAnimation_MyrrhInvers_data3, 2
	Show 11, BattleAnimation_MyrrhInvers_sheet_4, BattleAnimation_MyrrhInvers_frame_R_11 - BattleAnimation_MyrrhInvers_data3, 2
	Show 12, BattleAnimation_MyrrhInvers_sheet_4, BattleAnimation_MyrrhInvers_frame_R_12 - BattleAnimation_MyrrhInvers_data3, 1
	Trans 4
	@ Cmd 1
	@ Cmd 0xD
	EndMode

BattleAnimation_MyrrhInvers_Mode2:	@ Normal attack (Layered behind the enemy)

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	EndMode

BattleAnimation_MyrrhInvers_Mode3:	@ Critical attack (Layered in front of the enemy)

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	EndMode

BattleAnimation_MyrrhInvers_Mode4:	@ Critical attack (Layered behind the enemy)

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	EndMode

BattleAnimation_MyrrhInvers_Mode5:	@ Magic attack

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	EndMode

BattleAnimation_MyrrhInvers_Mode6:	@ Critical magic attack

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	EndMode

BattleAnimation_MyrrhInvers_Mode7:	@ Close range dodge

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	EndMode

BattleAnimation_MyrrhInvers_Mode8:	@ Ranged dodge

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	EndMode

BattleAnimation_MyrrhInvers_Mode9:	@ Standing animation

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	@ Cmd 1
	EndMode

BattleAnimation_MyrrhInvers_Mode10:	@ Standing animation 2

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	@ Cmd 1
	EndMode

BattleAnimation_MyrrhInvers_Mode11:	@ Ranged standing "animation"

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	@ Cmd 1
	EndMode

BattleAnimation_MyrrhInvers_Mode12:	@ Dodged attack

	Show 0, BattleAnimation_MyrrhInvers_sheet_1, BattleAnimation_MyrrhInvers_frame_R_0 - BattleAnimation_MyrrhInvers_data3, 4
	EndMode

BattleAnimation_MyrrhInvers_data1:

	.word	BattleAnimation_MyrrhInvers_Mode1 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode2 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode3 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode4 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode5 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode6 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode7 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode8 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode9 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode10 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode11 - BattleAnimation_MyrrhInvers_data2
	.word	BattleAnimation_MyrrhInvers_Mode12 - BattleAnimation_MyrrhInvers_data2
	.word	0,0,0,0,0,0,0,0,0,0,0,0

	.end