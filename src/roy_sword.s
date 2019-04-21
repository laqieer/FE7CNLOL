@This file is made by BattleAnimation.py automatically. You can edit it.
	.include "BattleAnimationEventDef.inc"
	.section .rodata
	.align 4
	.global roy_sword_modes
	.global roy_sword_script
	.global roy_sword_oam_r
	.global roy_sword_oam_l
	.include "../include/roy_sword_oam.inc"

roy_sword_script:

	.extern roy_sword_sheet_0
	.extern roy_sword_sheet_1
	.extern roy_sword_sheet_2
	.extern roy_sword_sheet_3
	.extern roy_sword_sheet_4
	.extern roy_sword_sheet_5
	.extern roy_sword_sheet_6
	.extern roy_sword_sheet_7
	.extern roy_sword_sheet_8

roy_sword_mode_1:
	Cmd 0x03
	Cmd 0x07
	@1 p- roy_sword_000.png
	Show 1, roy_sword_sheet_0, roy_sword_frame_r_1 - roy_sword_oam_r, 1
	@3 p- roy_sword_001.png
	Show 2, roy_sword_sheet_0, roy_sword_frame_r_2 - roy_sword_oam_r, 3
	@3 p- roy_sword_002.png
	Show 3, roy_sword_sheet_0, roy_sword_frame_r_3 - roy_sword_oam_r, 3
	@3 p- roy_sword_003.png
	Show 4, roy_sword_sheet_0, roy_sword_frame_r_4 - roy_sword_oam_r, 3
	@3 p- roy_sword_004.png
	Show 5, roy_sword_sheet_0, roy_sword_frame_r_5 - roy_sword_oam_r, 3
	Cmd 0x04
	Cmd 0x24
	Cmd 0x20
	Cmd 0x1A
	@3 p- roy_sword_005.png
	Show 6, roy_sword_sheet_0, roy_sword_frame_r_6 - roy_sword_oam_r, 3
	Cmd 0x1B
	@3 p- roy_sword_006.png
	Show 8, roy_sword_sheet_0, roy_sword_frame_r_8 - roy_sword_oam_r, 3
	@5 p- roy_sword_007.png
	Show 10, roy_sword_sheet_1, roy_sword_frame_r_10 - roy_sword_oam_r, 5
	@3 p- roy_sword_008.png
	Show 11, roy_sword_sheet_1, roy_sword_frame_r_11 - roy_sword_oam_r, 3
	@3 p- roy_sword_009.png
	Show 12, roy_sword_sheet_1, roy_sword_frame_r_12 - roy_sword_oam_r, 3
	@2 p- roy_sword_010.png
	Show 13, roy_sword_sheet_1, roy_sword_frame_r_13 - roy_sword_oam_r, 2
	@1 p- roy_sword_011.png
	Show 14, roy_sword_sheet_1, roy_sword_frame_r_14 - roy_sword_oam_r, 1
	@Loop end
	Cmd 0x01
	@2 p- roy_sword_012.png
	Show 15, roy_sword_sheet_1, roy_sword_frame_r_15 - roy_sword_oam_r, 2
	@3 p- roy_sword_013.png
	Show 16, roy_sword_sheet_1, roy_sword_frame_r_16 - roy_sword_oam_r, 3
	@4 p- roy_sword_014.png
	Show 17, roy_sword_sheet_1, roy_sword_frame_r_17 - roy_sword_oam_r, 4
	@6 p- roy_sword_015.png
	Show 18, roy_sword_sheet_2, roy_sword_frame_r_18 - roy_sword_oam_r, 6
	@3 p- roy_sword_016.png
	Show 19, roy_sword_sheet_2, roy_sword_frame_r_19 - roy_sword_oam_r, 3
	@3 p- roy_sword_017.png
	Show 20, roy_sword_sheet_2, roy_sword_frame_r_20 - roy_sword_oam_r, 3
	@3 p- roy_sword_018.png
	Show 21, roy_sword_sheet_2, roy_sword_frame_r_21 - roy_sword_oam_r, 3
	@2 p- roy_sword_019.png
	Show 22, roy_sword_sheet_2, roy_sword_frame_r_22 - roy_sword_oam_r, 2
	@2 p- roy_sword_020.png
	Show 23, roy_sword_sheet_2, roy_sword_frame_r_23 - roy_sword_oam_r, 2
	@5 p- roy_sword_021.png
	Show 24, roy_sword_sheet_2, roy_sword_frame_r_24 - roy_sword_oam_r, 5
	@1 p- roy_sword_022.png
	Show 25, roy_sword_sheet_2, roy_sword_frame_r_25 - roy_sword_oam_r, 1
	@2 p- roy_sword_023.png
	Show 26, roy_sword_sheet_3, roy_sword_frame_r_26 - roy_sword_oam_r, 2
	@1 p- roy_sword_024.png
	Show 27, roy_sword_sheet_3, roy_sword_frame_r_27 - roy_sword_oam_r, 1
	@1 p- roy_sword_025.png
	Show 28, roy_sword_sheet_3, roy_sword_frame_r_28 - roy_sword_oam_r, 1
	Cmd 0x34
	@2 p- roy_sword_026.png
	Show 29, roy_sword_sheet_3, roy_sword_frame_r_29 - roy_sword_oam_r, 2
	@2 p- roy_sword_027.png
	Show 30, roy_sword_sheet_3, roy_sword_frame_r_30 - roy_sword_oam_r, 2
	@3 p- roy_sword_028.png
	Show 31, roy_sword_sheet_3, roy_sword_frame_r_31 - roy_sword_oam_r, 3
	@2 p- roy_sword_029.png
	Show 32, roy_sword_sheet_3, roy_sword_frame_r_32 - roy_sword_oam_r, 2
	Cmd 0x06
	@2 p- roy_sword_029.png
	Show 32, roy_sword_sheet_3, roy_sword_frame_r_32 - roy_sword_oam_r, 2
	@2 p- roy_sword_030.png
	Show 33, roy_sword_sheet_3, roy_sword_frame_r_33 - roy_sword_oam_r, 2
	Cmd 0x0D
	EndMode

roy_sword_mode_2:
	Cmd 0x03
	Cmd 0x07
	@1 p- roy_sword_000.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 1
	@3 p- roy_sword_001.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_002.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_003.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_004.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	Cmd 0x04
	Cmd 0x24
	Cmd 0x20
	Cmd 0x1A
	@3 p- roy_sword_005.png
	Show 7, roy_sword_sheet_0, roy_sword_frame_r_7 - roy_sword_oam_r, 3
	Cmd 0x1B
	@3 p- roy_sword_006.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 3
	@5 p- roy_sword_007.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 5
	@3 p- roy_sword_008.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 3
	@3 p- roy_sword_009.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 3
	@2 p- roy_sword_010.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 2
	@1 p- roy_sword_011.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 1
	@Loop end
	Cmd 0x01
	@2 p- roy_sword_012.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 2
	@3 p- roy_sword_013.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@4 p- roy_sword_014.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 4
	@6 p- roy_sword_015.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 6
	@3 p- roy_sword_016.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_017.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_018.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@2 p- roy_sword_019.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@2 p- roy_sword_020.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@5 p- roy_sword_021.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 5
	@1 p- roy_sword_022.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 1
	@2 p- roy_sword_023.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@1 p- roy_sword_024.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 1
	@1 p- roy_sword_025.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 1
	Cmd 0x34
	@2 p- roy_sword_026.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@2 p- roy_sword_027.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@3 p- roy_sword_028.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@2 p- roy_sword_029.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	Cmd 0x06
	@2 p- roy_sword_029.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@2 p- roy_sword_030.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	Cmd 0x0D
	EndMode

roy_sword_mode_3:
	Cmd 0x03
	Cmd 0x07
	@1 p- roy_sword_000.png
	Show 1, roy_sword_sheet_0, roy_sword_frame_r_1 - roy_sword_oam_r, 1
	Cmd 0x1B
	@2 p- roy_sword_031.png
	Show 34, roy_sword_sheet_4, roy_sword_frame_r_34 - roy_sword_oam_r, 2
	@4 p- roy_sword_032.png
	Show 35, roy_sword_sheet_4, roy_sword_frame_r_35 - roy_sword_oam_r, 4
	@6 p- roy_sword_033.png
	Show 36, roy_sword_sheet_4, roy_sword_frame_r_36 - roy_sword_oam_r, 6
	@4 p- roy_sword_034.png
	Show 37, roy_sword_sheet_4, roy_sword_frame_r_37 - roy_sword_oam_r, 4
	@4 p- roy_sword_035.png
	Show 38, roy_sword_sheet_4, roy_sword_frame_r_38 - roy_sword_oam_r, 4
	@4 p- roy_sword_036.png
	Show 39, roy_sword_sheet_4, roy_sword_frame_r_39 - roy_sword_oam_r, 4
	@4 p- roy_sword_037.png
	Show 40, roy_sword_sheet_4, roy_sword_frame_r_40 - roy_sword_oam_r, 4
	Cmd 0x22
	Cmd 0x1B
	@3 p- roy_sword_038.png
	Show 41, roy_sword_sheet_4, roy_sword_frame_r_41 - roy_sword_oam_r, 3
	@3 p- roy_sword_039.png
	Show 42, roy_sword_sheet_5, roy_sword_frame_r_42 - roy_sword_oam_r, 3
	@3 p- roy_sword_040.png
	Show 43, roy_sword_sheet_5, roy_sword_frame_r_43 - roy_sword_oam_r, 3
	@3 p- roy_sword_041.png
	Show 44, roy_sword_sheet_5, roy_sword_frame_r_44 - roy_sword_oam_r, 3
	Cmd 0x23
	@2 p- roy_sword_042.png
	Show 45, roy_sword_sheet_5, roy_sword_frame_r_45 - roy_sword_oam_r, 2
	Cmd 0x1B
	@5 p- roy_sword_043.png
	Show 46, roy_sword_sheet_5, roy_sword_frame_r_46 - roy_sword_oam_r, 5
	@6 p- roy_sword_044.png
	Show 47, roy_sword_sheet_5, roy_sword_frame_r_47 - roy_sword_oam_r, 6
	@10 p- roy_sword_045.png
	Show 48, roy_sword_sheet_6, roy_sword_frame_r_48 - roy_sword_oam_r, 10
	@3 p- roy_sword_046.png
	Show 49, roy_sword_sheet_6, roy_sword_frame_r_49 - roy_sword_oam_r, 3
	@3 p- roy_sword_047.png
	Show 50, roy_sword_sheet_6, roy_sword_frame_r_50 - roy_sword_oam_r, 3
	@3 p- roy_sword_048.png
	Show 51, roy_sword_sheet_6, roy_sword_frame_r_51 - roy_sword_oam_r, 3
	Cmd 0x04
	@2 p- roy_sword_049.png
	Show 52, roy_sword_sheet_6, roy_sword_frame_r_52 - roy_sword_oam_r, 2
	Cmd 0x09
	Cmd 0x20
	Cmd 0x1B
	@3 p- roy_sword_006.png
	Show 8, roy_sword_sheet_0, roy_sword_frame_r_8 - roy_sword_oam_r, 3
	@6 p- roy_sword_007.png
	Show 10, roy_sword_sheet_1, roy_sword_frame_r_10 - roy_sword_oam_r, 6
	@3 p- roy_sword_008.png
	Show 11, roy_sword_sheet_1, roy_sword_frame_r_11 - roy_sword_oam_r, 3
	@2 p- roy_sword_009.png
	Show 12, roy_sword_sheet_1, roy_sword_frame_r_12 - roy_sword_oam_r, 2
	@2 p- roy_sword_010.png
	Show 13, roy_sword_sheet_1, roy_sword_frame_r_13 - roy_sword_oam_r, 2
	@1 p- roy_sword_011.png
	Show 14, roy_sword_sheet_1, roy_sword_frame_r_14 - roy_sword_oam_r, 1
	@Loop end
	Cmd 0x01
	@2 p- roy_sword_012.png
	Show 15, roy_sword_sheet_1, roy_sword_frame_r_15 - roy_sword_oam_r, 2
	@3 p- roy_sword_013.png
	Show 16, roy_sword_sheet_1, roy_sword_frame_r_16 - roy_sword_oam_r, 3
	@4 p- roy_sword_014.png
	Show 17, roy_sword_sheet_1, roy_sword_frame_r_17 - roy_sword_oam_r, 4
	@6 p- roy_sword_015.png
	Show 18, roy_sword_sheet_2, roy_sword_frame_r_18 - roy_sword_oam_r, 6
	@3 p- roy_sword_016.png
	Show 19, roy_sword_sheet_2, roy_sword_frame_r_19 - roy_sword_oam_r, 3
	@3 p- roy_sword_017.png
	Show 20, roy_sword_sheet_2, roy_sword_frame_r_20 - roy_sword_oam_r, 3
	@3 p- roy_sword_018.png
	Show 21, roy_sword_sheet_2, roy_sword_frame_r_21 - roy_sword_oam_r, 3
	@2 p- roy_sword_019.png
	Show 22, roy_sword_sheet_2, roy_sword_frame_r_22 - roy_sword_oam_r, 2
	@2 p- roy_sword_020.png
	Show 23, roy_sword_sheet_2, roy_sword_frame_r_23 - roy_sword_oam_r, 2
	@6 p- roy_sword_021.png
	Show 24, roy_sword_sheet_2, roy_sword_frame_r_24 - roy_sword_oam_r, 6
	@1 p- roy_sword_022.png
	Show 25, roy_sword_sheet_2, roy_sword_frame_r_25 - roy_sword_oam_r, 1
	@2 p- roy_sword_023.png
	Show 26, roy_sword_sheet_3, roy_sword_frame_r_26 - roy_sword_oam_r, 2
	@1 p- roy_sword_024.png
	Show 27, roy_sword_sheet_3, roy_sword_frame_r_27 - roy_sword_oam_r, 1
	@1 p- roy_sword_025.png
	Show 28, roy_sword_sheet_3, roy_sword_frame_r_28 - roy_sword_oam_r, 1
	Cmd 0x34
	@4 p- roy_sword_026.png
	Show 29, roy_sword_sheet_3, roy_sword_frame_r_29 - roy_sword_oam_r, 4
	@2 p- roy_sword_027.png
	Show 30, roy_sword_sheet_3, roy_sword_frame_r_30 - roy_sword_oam_r, 2
	@3 p- roy_sword_028.png
	Show 31, roy_sword_sheet_3, roy_sword_frame_r_31 - roy_sword_oam_r, 3
	@2 p- roy_sword_029.png
	Show 32, roy_sword_sheet_3, roy_sword_frame_r_32 - roy_sword_oam_r, 2
	Cmd 0x06
	@2 p- roy_sword_029.png
	Show 32, roy_sword_sheet_3, roy_sword_frame_r_32 - roy_sword_oam_r, 2
	@2 p- roy_sword_030.png
	Show 33, roy_sword_sheet_3, roy_sword_frame_r_33 - roy_sword_oam_r, 2
	Cmd 0x0D
	EndMode

roy_sword_mode_4:
	Cmd 0x03
	Cmd 0x07
	@1 p- roy_sword_000.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 1
	Cmd 0x1B
	@2 p- roy_sword_031.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@4 p- roy_sword_032.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 4
	@6 p- roy_sword_033.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 6
	@4 p- roy_sword_034.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 4
	@4 p- roy_sword_035.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 4
	@4 p- roy_sword_036.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 4
	@4 p- roy_sword_037.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 4
	Cmd 0x22
	Cmd 0x1B
	@3 p- roy_sword_038.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_039.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_040.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_041.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	Cmd 0x23
	@2 p- roy_sword_042.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	Cmd 0x1B
	@5 p- roy_sword_043.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 5
	@6 p- roy_sword_044.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 6
	@10 p- roy_sword_045.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 10
	@3 p- roy_sword_046.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_047.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_048.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	Cmd 0x04
	@2 p- roy_sword_049.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	Cmd 0x09
	Cmd 0x20
	Cmd 0x1B
	@3 p- roy_sword_006.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 3
	@6 p- roy_sword_007.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 6
	@3 p- roy_sword_008.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 3
	@2 p- roy_sword_009.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 2
	@2 p- roy_sword_010.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 2
	@1 p- roy_sword_011.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 1
	@Loop end
	Cmd 0x01
	@2 p- roy_sword_012.png
	Show 9, roy_sword_sheet_0, roy_sword_frame_r_9 - roy_sword_oam_r, 2
	@3 p- roy_sword_013.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@4 p- roy_sword_014.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 4
	@6 p- roy_sword_015.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 6
	@3 p- roy_sword_016.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_017.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@3 p- roy_sword_018.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@2 p- roy_sword_019.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@2 p- roy_sword_020.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@6 p- roy_sword_021.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 6
	@1 p- roy_sword_022.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 1
	@2 p- roy_sword_023.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@1 p- roy_sword_024.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 1
	@1 p- roy_sword_025.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 1
	Cmd 0x34
	@4 p- roy_sword_026.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 4
	@2 p- roy_sword_027.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@3 p- roy_sword_028.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 3
	@2 p- roy_sword_029.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	Cmd 0x06
	@2 p- roy_sword_029.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	@2 p- roy_sword_030.png
	Show 0, roy_sword_sheet_0, roy_sword_frame_r_0 - roy_sword_oam_r, 2
	Cmd 0x0D
	EndMode

roy_sword_mode_5:
	Cmd 0x03
	Cmd 0x07
	@1 p- roy_sword_000.png
	Show 1, roy_sword_sheet_0, roy_sword_frame_r_1 - roy_sword_oam_r, 1
	Cmd 0x22
	@2 p- roy_sword_050.png
	Show 53, roy_sword_sheet_6, roy_sword_frame_r_53 - roy_sword_oam_r, 2
	@3 p- roy_sword_051.png
	Show 54, roy_sword_sheet_6, roy_sword_frame_r_54 - roy_sword_oam_r, 3
	Cmd 0x05
	@1 p- roy_sword_052.png
	Show 55, roy_sword_sheet_7, roy_sword_frame_r_55 - roy_sword_oam_r, 1
	@Loop end
	Cmd 0x01
	Cmd 0x23
	@3 p- roy_sword_053.png
	Show 56, roy_sword_sheet_7, roy_sword_frame_r_56 - roy_sword_oam_r, 3
	Cmd 0x06
	@2 p- roy_sword_054.png
	Show 57, roy_sword_sheet_7, roy_sword_frame_r_57 - roy_sword_oam_r, 2
	@3 p- roy_sword_055.png
	Show 58, roy_sword_sheet_7, roy_sword_frame_r_58 - roy_sword_oam_r, 3
	Cmd 0x0D
	EndMode

roy_sword_mode_6:
	Cmd 0x03
	Cmd 0x07
	@1 p- roy_sword_000.png
	Show 1, roy_sword_sheet_0, roy_sword_frame_r_1 - roy_sword_oam_r, 1
	Cmd 0x22
	@2 p- roy_sword_050.png
	Show 53, roy_sword_sheet_6, roy_sword_frame_r_53 - roy_sword_oam_r, 2
	@3 p- roy_sword_051.png
	Show 54, roy_sword_sheet_6, roy_sword_frame_r_54 - roy_sword_oam_r, 3
	@2 p- roy_sword_052.png
	Show 55, roy_sword_sheet_7, roy_sword_frame_r_55 - roy_sword_oam_r, 2
	@4 p- roy_sword_056.png
	Show 59, roy_sword_sheet_7, roy_sword_frame_r_59 - roy_sword_oam_r, 4
	@2 p- roy_sword_052.png
	Show 55, roy_sword_sheet_7, roy_sword_frame_r_55 - roy_sword_oam_r, 2
	@3 p- roy_sword_056.png
	Show 59, roy_sword_sheet_7, roy_sword_frame_r_59 - roy_sword_oam_r, 3
	@2 p- roy_sword_052.png
	Show 55, roy_sword_sheet_7, roy_sword_frame_r_55 - roy_sword_oam_r, 2
	@4 p- roy_sword_056.png
	Show 59, roy_sword_sheet_7, roy_sword_frame_r_59 - roy_sword_oam_r, 4
	Cmd 0x05
	@1 p- roy_sword_052.png
	Show 55, roy_sword_sheet_7, roy_sword_frame_r_55 - roy_sword_oam_r, 1
	@Loop end
	Cmd 0x01
	Cmd 0x23
	@3 p- roy_sword_053.png
	Show 56, roy_sword_sheet_7, roy_sword_frame_r_56 - roy_sword_oam_r, 3
	Cmd 0x06
	@2 p- roy_sword_054.png
	Show 57, roy_sword_sheet_7, roy_sword_frame_r_57 - roy_sword_oam_r, 2
	@3 p- roy_sword_055.png
	Show 58, roy_sword_sheet_7, roy_sword_frame_r_58 - roy_sword_oam_r, 3
	Cmd 0x0D
	EndMode

roy_sword_mode_7:
	Cmd 0x18
	@1 p- roy_sword_000.png
	Show 1, roy_sword_sheet_0, roy_sword_frame_r_1 - roy_sword_oam_r, 1
	Cmd 0x0E
	@3 p- roy_sword_057.png
	Show 60, roy_sword_sheet_7, roy_sword_frame_r_60 - roy_sword_oam_r, 3
	@1 p- roy_sword_058.png
	Show 61, roy_sword_sheet_5, roy_sword_frame_r_61 - roy_sword_oam_r, 1
	@Loop end
	Cmd 0x01
	@3 p- roy_sword_057.png
	Show 60, roy_sword_sheet_7, roy_sword_frame_r_60 - roy_sword_oam_r, 3
	Cmd 0x0D
	EndMode

roy_sword_mode_8:
	Cmd 0x18
	@1 p- roy_sword_000.png
	Show 1, roy_sword_sheet_0, roy_sword_frame_r_1 - roy_sword_oam_r, 1
	Cmd 0x0E
	@3 p- roy_sword_057.png
	Show 60, roy_sword_sheet_7, roy_sword_frame_r_60 - roy_sword_oam_r, 3
	@1 p- roy_sword_058.png
	Show 61, roy_sword_sheet_5, roy_sword_frame_r_61 - roy_sword_oam_r, 1
	@Loop end
	Cmd 0x01
	@3 p- roy_sword_057.png
	Show 60, roy_sword_sheet_7, roy_sword_frame_r_60 - roy_sword_oam_r, 3
	Cmd 0x0D
	EndMode

roy_sword_mode_9:
	@4 p- roy_sword_000.png
	Show 1, roy_sword_sheet_0, roy_sword_frame_r_1 - roy_sword_oam_r, 4
	@Loop end
	Cmd 0x01
	EndMode

roy_sword_mode_10:
	@4 p- roy_sword_000.png
	Show 1, roy_sword_sheet_0, roy_sword_frame_r_1 - roy_sword_oam_r, 4
	@Loop end
	Cmd 0x01
	EndMode

roy_sword_mode_11:
	@4 p- roy_sword_000.png
	Show 1, roy_sword_sheet_0, roy_sword_frame_r_1 - roy_sword_oam_r, 4
	@Loop end
	Cmd 0x01
	EndMode

roy_sword_mode_12:
	Cmd 0x03
	Cmd 0x07
	@1 p- roy_sword_000.png
	Show 1, roy_sword_sheet_0, roy_sword_frame_r_1 - roy_sword_oam_r, 1
	@3 p- roy_sword_001.png
	Show 2, roy_sword_sheet_0, roy_sword_frame_r_2 - roy_sword_oam_r, 3
	@3 p- roy_sword_002.png
	Show 3, roy_sword_sheet_0, roy_sword_frame_r_3 - roy_sword_oam_r, 3
	@3 p- roy_sword_003.png
	Show 4, roy_sword_sheet_0, roy_sword_frame_r_4 - roy_sword_oam_r, 3
	@3 p- roy_sword_004.png
	Show 5, roy_sword_sheet_0, roy_sword_frame_r_5 - roy_sword_oam_r, 3
	Cmd 0x04
	Cmd 0x25
	@3 p- roy_sword_059.png
	Show 62, roy_sword_sheet_0, roy_sword_frame_r_62 - roy_sword_oam_r, 3
	Cmd 0x1B
	@3 p- roy_sword_060.png
	Show 63, roy_sword_sheet_0, roy_sword_frame_r_63 - roy_sword_oam_r, 3
	@5 p- roy_sword_061.png
	Show 64, roy_sword_sheet_7, roy_sword_frame_r_64 - roy_sword_oam_r, 5
	@3 p- roy_sword_062.png
	Show 65, roy_sword_sheet_8, roy_sword_frame_r_65 - roy_sword_oam_r, 3
	@3 p- roy_sword_063.png
	Show 66, roy_sword_sheet_8, roy_sword_frame_r_66 - roy_sword_oam_r, 3
	@2 p- roy_sword_064.png
	Show 67, roy_sword_sheet_8, roy_sword_frame_r_67 - roy_sword_oam_r, 2
	@1 p- roy_sword_065.png
	Show 68, roy_sword_sheet_8, roy_sword_frame_r_68 - roy_sword_oam_r, 1
	@Loop end
	Cmd 0x01
	@2 p- roy_sword_066.png
	Show 69, roy_sword_sheet_8, roy_sword_frame_r_69 - roy_sword_oam_r, 2
	@3 p- roy_sword_013.png
	Show 16, roy_sword_sheet_1, roy_sword_frame_r_16 - roy_sword_oam_r, 3
	@4 p- roy_sword_014.png
	Show 17, roy_sword_sheet_1, roy_sword_frame_r_17 - roy_sword_oam_r, 4
	@6 p- roy_sword_015.png
	Show 18, roy_sword_sheet_2, roy_sword_frame_r_18 - roy_sword_oam_r, 6
	@3 p- roy_sword_016.png
	Show 19, roy_sword_sheet_2, roy_sword_frame_r_19 - roy_sword_oam_r, 3
	@3 p- roy_sword_017.png
	Show 20, roy_sword_sheet_2, roy_sword_frame_r_20 - roy_sword_oam_r, 3
	@3 p- roy_sword_018.png
	Show 21, roy_sword_sheet_2, roy_sword_frame_r_21 - roy_sword_oam_r, 3
	@2 p- roy_sword_019.png
	Show 22, roy_sword_sheet_2, roy_sword_frame_r_22 - roy_sword_oam_r, 2
	@2 p- roy_sword_020.png
	Show 23, roy_sword_sheet_2, roy_sword_frame_r_23 - roy_sword_oam_r, 2
	@5 p- roy_sword_021.png
	Show 24, roy_sword_sheet_2, roy_sword_frame_r_24 - roy_sword_oam_r, 5
	@1 p- roy_sword_022.png
	Show 25, roy_sword_sheet_2, roy_sword_frame_r_25 - roy_sword_oam_r, 1
	@2 p- roy_sword_023.png
	Show 26, roy_sword_sheet_3, roy_sword_frame_r_26 - roy_sword_oam_r, 2
	@1 p- roy_sword_024.png
	Show 27, roy_sword_sheet_3, roy_sword_frame_r_27 - roy_sword_oam_r, 1
	@1 p- roy_sword_025.png
	Show 28, roy_sword_sheet_3, roy_sword_frame_r_28 - roy_sword_oam_r, 1
	Cmd 0x34
	@2 p- roy_sword_026.png
	Show 29, roy_sword_sheet_3, roy_sword_frame_r_29 - roy_sword_oam_r, 2
	@2 p- roy_sword_027.png
	Show 30, roy_sword_sheet_3, roy_sword_frame_r_30 - roy_sword_oam_r, 2
	@3 p- roy_sword_028.png
	Show 31, roy_sword_sheet_3, roy_sword_frame_r_31 - roy_sword_oam_r, 3
	@2 p- roy_sword_029.png
	Show 32, roy_sword_sheet_3, roy_sword_frame_r_32 - roy_sword_oam_r, 2
	Cmd 0x06
	@2 p- roy_sword_029.png
	Show 32, roy_sword_sheet_3, roy_sword_frame_r_32 - roy_sword_oam_r, 2
	@2 p- roy_sword_030.png
	Show 33, roy_sword_sheet_3, roy_sword_frame_r_33 - roy_sword_oam_r, 2
	Cmd 0x0D
	EndMode

roy_sword_modes:
	.word roy_sword_mode_1 - roy_sword_script
	.word roy_sword_mode_2 - roy_sword_script
	.word roy_sword_mode_3 - roy_sword_script
	.word roy_sword_mode_4 - roy_sword_script
	.word roy_sword_mode_5 - roy_sword_script
	.word roy_sword_mode_6 - roy_sword_script
	.word roy_sword_mode_7 - roy_sword_script
	.word roy_sword_mode_8 - roy_sword_script
	.word roy_sword_mode_9 - roy_sword_script
	.word roy_sword_mode_10 - roy_sword_script
	.word roy_sword_mode_11 - roy_sword_script
	.word roy_sword_mode_12 - roy_sword_script
	.word 0,0,0,0,0,0,0,0,0,0,0,0
	.end
