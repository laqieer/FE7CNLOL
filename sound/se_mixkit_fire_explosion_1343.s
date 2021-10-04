	.include "MusicPlayDef.s"

	.equ	se_mixkit_fire_explosion_1343_grp, voicegroup_mixkit_fire_explosion_1343
	.equ	se_mixkit_fire_explosion_1343_pri, 10
	.equ	se_mixkit_fire_explosion_1343_rev, 0
	.equ	se_mixkit_fire_explosion_1343_mvl, 127
	.equ	se_mixkit_fire_explosion_1343_key, 0
	.equ	se_mixkit_fire_explosion_1343_tbs, 1
	.equ	se_mixkit_fire_explosion_1343_exg, 0
	.equ	se_mixkit_fire_explosion_1343_cmp, 1

	.section .rodata
	.global	se_mixkit_fire_explosion_1343
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

se_mixkit_fire_explosion_1343_1:
	.byte	KEYSH , se_mixkit_fire_explosion_1343_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 120*se_mixkit_fire_explosion_1343_tbs/2
	.byte		VOICE , 0
	.byte		VOL   , 127*se_mixkit_fire_explosion_1343_mvl/mxv
	.byte		PAN   , c_v+0
	.byte		N72   , Cn3 , v127
	.byte	W72
	.byte	FINE

@******************************************************@
	.align	2

se_mixkit_fire_explosion_1343:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	se_mixkit_fire_explosion_1343_pri	@ Priority
	.byte	se_mixkit_fire_explosion_1343_rev	@ Reverb.

	.word	se_mixkit_fire_explosion_1343_grp

	.word	se_mixkit_fire_explosion_1343_1

	.end
