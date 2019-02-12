/*	by laqieer
	2017/1/27
	Ö÷Á´½Ó½Å±¾
*/

SECTIONS
{
	. = 0x8000000;
	.rom : {*.o(.rom)}
/*	.rom (COPY): {KEEP(*.o(.rom))}	*/
	. = 0x805609C;
	.spellAnimationTableBase : {*.o(.spellAnimationTableBase)}
	. = 0x8D61A1C;
	.fireAnimationID : {*.o(.fireAnimationID)}
	. = 0x8D61ACC;
	.NosferatuAnimationID : {*.o(.NosferatuAnimationID)}
	. = 0x8007774;	
	.callBlink : {*.o(.callBlink)}
	. = 0x80077E8;
	.call_sub_80077E8 : {*.o(.call_sub_80077E8)}
	. = 0x8007824;
	.call_sub_8007824 : {*.o(.call_sub_8007824)}
	. = 0x8007860;
	.callWink : {*.o(.callWink)}
	. = 0x8006C48;
	.callChooseMainPortraitSpriteTemplate : {*.o(.callChooseMainPortraitSpriteTemplate)}
	. = 0x8007160;
	.callDrawPortraitInBox : {*.o(.callDrawPortraitInBox)}
	. = 0x800749C;
	.callMouthAnimation : {*.o(.callMouthAnimation)}
	. = 0x80069B0;
	.callGetPortrait : {*.o(.callGetPortrait)}
/*	. = 0x8D5E23C + 28 * 0x16;
	.LynPortraitH : {*.o(.LynPortraitH)}	
	. = 0x8D5E23C + 28 * 0x16;
	.LynPortraitV : {*.o(.LynPortraitV)}	
	. = 0x8D5E23C + 28 * 0x16;
	.TikiPortrait : {*.o(.TikiPortrait)}	*/
	. = 0x8D5E23C + 28 * 0x20;
	.SharonPortrait : {*.o(.SharonPortrait)}	
	. = 0x8D5E23C + 28 * 0xC;
	.TikiFPortrait : {*.o(.TikiFPortrait)}		
	. = 0x8D5E23C + 28 * 0x1B;
	.HuajiPortrait : {*.o(.HuajiPortrait)}	
	. = 0x8013318;
	.callDecodeText : {*.o(.callDecodeText)}
	. = 0x80056D8;
	.callShowFont1 : {*.o(.callShowFont1)}
	. = 0x80055DC;
	.callShowFont2 : {*.o(.callShowFont2)}
	. = 0x805480C;
	.callBattleAnimationInit : {*.o(.callBattleAnimationInit)}	
	. = 0x8C0A560;
	.ekrUnitKakudaiEx : {*.o(.ekrUnitKakudaiEx)}	
/*	. = 0x8053C3C;
	.callBattleAnimationEventHandlerEx : {*.o(.callBattleAnimationEventHandlerEx)}	*/
	. = 0x805408C;	
/*	.C0DHandlerJPTCase0_1_2_3_9 : {*.o(.C0DHandlerJPTCase0_1_2_3_9)}	*/
	.C0DHandlerJPT : {*.o(.C0DHandlerJPT)}	
/*	. = 0x8053CB4;
	.battleAnimationEventHandlerJPT : {*.o(.battleAnimationEventHandlerJPT)}	
	. = 0x8006580;
	.sub_8006518JPT : {*.o(.sub_8006518JPT)}	
	. = 0x8068050;
	.playBattleAnimationSFXJPT : {*.o(.playBattleAnimationSFXJPT)}	*/
	. = 0x8054AC0;
	.callBattleAnimationAISInit : {*.o(.callBattleAnimationAISInit)}	
	. = 0x8054D7C;
	/*	.call_sub_8054D7C : {*.o(.call_sub_8054D7C)}	*/
	.callInitAIS : {*.o(.callInitAIS)}
	. = 0x8054764;
	.call_sub_8054764 : {*.o(.call_sub_8054764)}
	. = 0x8053D6C;
	.C2E_EX : {*.o(.C2E_EX)}
	. = 0x8053D70;
	.C2F_EX : {*.o(.C2F_EX)}	
	. = 0x8006594;
	.capeFlowingAnimationEx : {*.o(.capeFlowingAnimationEx)}	
	. = 0x806810C;
	.battleAnimationSoundEx : {*.o(.battleAnimationSoundEx)}
	. = 0x80552D8;
	.callDemoBattleAnimationInit : {*.o(.callDemoBattleAnimationInit)}	
/*	. = 0x8E00008 + 0x20 * (0x5E - 1);
	.NinoSageAnimation : {*.o(.NinoSageAnimation)}	*/
	. = 0x8E00008 + 0x20 * (0x11 - 1);
	.LynBladeLordSwordAnimation : {*.o(.LynBladeLordSwordAnimation)}
	. = 0x8E00008 + 0x20 * (0x84 - 1);
	.FalconKnightSpearAnimationWithIceEffect : {*.o(.FalconKnightSpearAnimationWithIceEffect)}
	. = 0x8E00008 + 0x20 * (4 - 1);
	.LordKnightEliwoodDurandalAnimation : {*.o(.LordKnightEliwoodDurandalAnimation)}
/*	. = 0x8E00008 + 0x20 * (0x29 - 1);
	.BattleAnimation_FE7_0x29 : {*.o(.BattleAnimation_FE7_0x29)}	*/
	. = 0x8E00008 + 0x20 * (0x71 - 1);
	.PriscillaAnimationTest : {*.o(.PriscillaAnimationTest)}
	. = 0x8FD8008 + 0x10 * (0x79 - 1);
	.PriscillaTestPal : {*.o(.PriscillaTestPal)}
	. = 0x8C4C158 + 52 * (0x1B - 1) + 0x24;
	.PriscillaTestPalNo : {*.o(.PriscillaTestPalNo)}
/*	. = 0x81BD514;
	.FireRingPaletteTColor : {*.o(.FireRingPaletteTColor)}	*/
	. = 0x8E00008 + 0x20 * (0x1B - 1);
	.FireDragonTestAnimation : {*.o(.FireDragonTestAnimation)}
	. = 0x8C4C830;
	.DisableEliwoodPromotedPalette : {*.O(.DisableEliwoodPromotedPalette)}	
	. = 0x8006518;
	.callBattleAnimationScriptHandler : {*.o(.callBattleAnimationScriptHandler)}
	. = 0x804C7C4;
	.call_sub_804C7C4 : {*.o(.call_sub_804C7C4)}
	. = 0x8C4F468 + 84 * 0x41 + 52;
	.NilsBattleAnimationConf : {*.o(.NilsBattleAnimationConf)}
	. = 0x8C4F468 + 84 * 0x41 + 40;
	.BardAbility : {*.o(.BardAbility)}
	. = 0x8C4C158 + 52 * (0x26 - 1) + 35;
	.DisableNilsCharacterPalette : {*.o(.DisableNilsCharacterPalette)}
	. = 0x8C51538 + 36 * 0x8F + 25;
	.FlametongueRange : {*.o(.FlametongueRange)}
	. = 0x80A119C;
	.callSaveGameEx : {*.o(.callSaveGameEx)}
	INCLUDE build\auto.lds
	. = 0x9000000;	
	.text : {*(.text)}
	.rodata : {*(.rodata) . = ALIGN(4);}
/*	.data : {*(.data)}
	.bss : {*(.bss)}	*/
	/DISCARD/ : { *(.data) *(.bss) }	
}


