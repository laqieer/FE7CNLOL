@ Generated by BattleAnimationDumper
@ 2017/10/06 23:24:35

	.include	"BattleAnimationEventDef.inc"

	.include	"../include/BattleAnimation_Fa_sheet.inc"

	.section	.rodata
	.align	4
	.global	BattleAnimation_Fa_data1
	.global	BattleAnimation_Fa_data2
	.global	BattleAnimation_Fa_data3
	.global	BattleAnimation_Fa_data4
	.include	"../include/BattleAnimation_Fa_OAMInfo.inc"

BattleAnimation_Fa_data2:

BattleAnimation_Fa_Mode1:	@ Normal attack (Layered in front of the enemy)

	Trans 1,0
	Cmd 0x2 @ Start of dodge
	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 1
	Cmd 0xE @ Start of dodging frames (should go after standing frame and before dodging animation)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0x25 @ Play wing flap SFE
	Show 6, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_6 - BattleAnimation_Fa_data3, 1
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0xD @ End of dodge animation (should have an 0x01 command before it and after a preceding 0x0E)
	EndMode

BattleAnimation_Fa_Mode2:	@ Normal attack (Layered behind the enemy)

	Trans 1,0
	Cmd 0x2 @ Start of dodge
	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 1
	Cmd 0xE @ Start of dodging frames (should go after standing frame and before dodging animation)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0x25 @ Play wing flap SFE
	Show 6, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_6 - BattleAnimation_Fa_data3, 1
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0xD @ End of dodge animation (should have an 0x01 command before it and after a preceding 0x0E)
	EndMode

BattleAnimation_Fa_Mode3:	@ Critical attack (Layered in front of the enemy)

	Trans 1,1
	Cmd 0x2 @ Start of dodge
	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 1
	Cmd 0xE @ Start of dodging frames (should go after standing frame and before dodging animation)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0x25 @ Play wing flap SFE
	Show 6, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_6 - BattleAnimation_Fa_data3, 1
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0xD @ End of dodge animation (should have an 0x01 command before it and after a preceding 0x0E)
	EndMode

BattleAnimation_Fa_Mode4:	@ Critical attack (Layered behind the enemy)

	Trans 1,1
	Cmd 0x2 @ Start of dodge
	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 1
	Cmd 0xE @ Start of dodging frames (should go after standing frame and before dodging animation)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0x25 @ Play wing flap SFE
	Show 6, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_6 - BattleAnimation_Fa_data3, 1
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0xD @ End of dodge animation (should have an 0x01 command before it and after a preceding 0x0E)
	EndMode

BattleAnimation_Fa_Mode5:	@ Magic attack

	Trans 1,2
	Cmd 0x2 @ Start of dodge
	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 1
	Cmd 0xE @ Start of dodging frames (should go after standing frame and before dodging animation)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0x25 @ Play wing flap SFE
	Show 6, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_6 - BattleAnimation_Fa_data3, 1
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0xD @ End of dodge animation (should have an 0x01 command before it and after a preceding 0x0E)
	EndMode

BattleAnimation_Fa_Mode6:	@ Critical magic attack

	Trans 1,3
	Cmd 0x2 @ Start of dodge
	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 1
	Cmd 0xE @ Start of dodging frames (should go after standing frame and before dodging animation)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0x25 @ Play wing flap SFE
	Show 6, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_6 - BattleAnimation_Fa_data3, 1
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0xD @ End of dodge animation (should have an 0x01 command before it and after a preceding 0x0E)
	EndMode

BattleAnimation_Fa_Mode7:	@ Close range dodge

	Trans 1,4
	Cmd 0x2 @ Start of dodge
	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 1
	Cmd 0xE @ Start of dodging frames (should go after standing frame and before dodging animation)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0x25 @ Play wing flap SFE
	Show 6, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_6 - BattleAnimation_Fa_data3, 1
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0xD @ End of dodge animation (should have an 0x01 command before it and after a preceding 0x0E)
	EndMode

BattleAnimation_Fa_Mode8:	@ Ranged dodge

	Trans 1,5
	Cmd 0x2 @ Start of dodge
	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 1
	Cmd 0xE @ Start of dodging frames (should go after standing frame and before dodging animation)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0x25 @ Play wing flap SFE
	Show 6, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_6 - BattleAnimation_Fa_data3, 1
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0xD @ End of dodge animation (should have an 0x01 command before it and after a preceding 0x0E)
	EndMode

BattleAnimation_Fa_Mode9:	@ Standing animation

	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 8
	Show 1, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_1 - BattleAnimation_Fa_data3, 4
	Show 2, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_2 - BattleAnimation_Fa_data3, 4
	Show 3, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_3 - BattleAnimation_Fa_data3, 4
	Show 4, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_4 - BattleAnimation_Fa_data3, 9
	Show 3, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_3 - BattleAnimation_Fa_data3, 4
	Show 2, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_2 - BattleAnimation_Fa_data3, 4
	Show 1, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_1 - BattleAnimation_Fa_data3, 4
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	EndMode

BattleAnimation_Fa_Mode10:	@ Standing animation 2

	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 8
	Show 1, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_1 - BattleAnimation_Fa_data3, 4
	Show 2, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_2 - BattleAnimation_Fa_data3, 4
	Show 3, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_3 - BattleAnimation_Fa_data3, 4
	Show 4, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_4 - BattleAnimation_Fa_data3, 9
	Show 3, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_3 - BattleAnimation_Fa_data3, 4
	Show 2, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_2 - BattleAnimation_Fa_data3, 4
	Show 1, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_1 - BattleAnimation_Fa_data3, 4
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	EndMode

BattleAnimation_Fa_Mode11:	@ Ranged standing "animation"

	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 8
	Show 1, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_1 - BattleAnimation_Fa_data3, 4
	Show 2, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_2 - BattleAnimation_Fa_data3, 4
	Show 3, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_3 - BattleAnimation_Fa_data3, 4
	Show 4, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_4 - BattleAnimation_Fa_data3, 9
	Show 3, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_3 - BattleAnimation_Fa_data3, 4
	Show 2, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_2 - BattleAnimation_Fa_data3, 4
	Show 1, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_1 - BattleAnimation_Fa_data3, 4
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	EndMode

BattleAnimation_Fa_Mode12:	@ Dodged attack

	Trans 1,9
	Cmd 0x2 @ Start of dodge
	Show 0, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_0 - BattleAnimation_Fa_data3, 1
	Cmd 0xE @ Start of dodging frames (should go after standing frame and before dodging animation)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0x25 @ Play wing flap SFE
	Show 6, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_6 - BattleAnimation_Fa_data3, 1
	Cmd 0x1 @ Wait for HP to deplete (freezes if no HP depletion is occurring/has occurred)
	Show 5, BattleAnimation_Fa_sheet_1, BattleAnimation_Fa_frame_R_5 - BattleAnimation_Fa_data3, 3
	Cmd 0xD @ End of dodge animation (should have an 0x01 command before it and after a preceding 0x0E)
	EndMode

BattleAnimation_Fa_data1:

	.word	BattleAnimation_Fa_Mode1 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode2 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode3 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode4 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode5 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode6 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode7 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode8 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode9 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode10 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode11 - BattleAnimation_Fa_data2
	.word	BattleAnimation_Fa_Mode12 - BattleAnimation_Fa_data2
	.word	0,0,0,0,0,0,0,0,0,0,0,0

	.end