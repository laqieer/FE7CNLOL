//This file is made by BattleAnimation.py automatically.
//You can set the abbr for the animation.
//It is required to add &roy_sword_animation into BattleAnimationPointerBank[].
#include "FE7JBattleAnimation.h"
#include "roy_sword_animation.h"
// LZ77 compressed
const char roy_sword_pal[53] __attribute__((aligned(4)))= {
    0x10, 0x80, 0x00, 0x00, 0x00, 0x34, 0x4f, 0xde, 0x7b, 0xde, 0x67, 0xfe, 
    0x4a, 0x00, 0x91, 0x25, 0x59, 0x00, 0x1e, 0x20, 0x52, 0x00, 0x00, 0x77, 
    0x73, 0xd2, 0x6a, 0x2d, 0x52, 0xb2, 0x7b, 0x00, 0xce, 0x7a, 0xa9, 0x75, 
    0x65, 0x54, 0xa5, 0x14, 0xfc, 0xf0, 0x1f, 0xf0, 0x1f, 0xf0, 0x1f, 0xf0, 
    0x1f, 0xf0, 0x1f, 0x30, 0x1f
};
const BattleAnimation roy_sword_animation __attribute__((aligned(4)))= {"lorm_sw1",&roy_sword_modes,&roy_sword_script,&roy_sword_oam_r,&roy_sword_oam_l,&roy_sword_pal};