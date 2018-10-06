// 光箭魔法动画
// by laqieer
// 2017/6/4

#include "spellArou.h"

// 光箭魔法主协程
const struct coroutine efxArou[]={
	spellStart,
	setLoopFuncAndYield(Arou),
	endofCoroutine
};

// 光箭主函数
void spellArou(void *AIS)
{
	struct context *ctx;

	sub(80507CC)();
//	sub(8050348)();
	sub(80507E4)();
	ctx = createContext(efxArou,3);
	*(void **)&ctx->userSpace[51] = AIS;
	*(u16 *)&ctx->userSpace[3] = 0;
	ctx->userSpace[0] = sub(8054E74)(sub(8054FEC)(AIS));
}

// 光箭魔法动画
void Arou(struct context *ctx)
{
	int v2,v3;
	u16 frameID;
	void* AIS;
	u8 *missOrHit;

	AIS = *(u32 *)&ctx->userSpace[51];
	v2 = sub(8054F90)(AIS);
	v3 = sub(8050F54)();
	frameID = ++*(u16 *)&ctx->userSpace[3];
  	if ( (frameID != 1 && frameID != 5 && frameID != 10 && frameID != 15 && frameID != 20 && frameID != 25 && frameID != 30 && frameID != 35 && frameID != 40 && frameID != 45)
    	|| (ScrollScreen(AIS, 0xFFFFu),
        	loadArrowOBJ(*(void **)&ctx->userSpace[51]),
        	PlaySFX(204, 256, *(u16 *)((int)AIS + 2), 1),
        	(frameID != 1 && frameID != 5 && frameID != 10 && frameID != 15 && frameID != 20 && frameID != 25 && frameID != 30 && frameID != 35 && frameID != 40 && frameID != 45)) )
  	{
    	if ( frameID != v3 + 54 && frameID == v3 + 55 )
    	{
      		sub(80507D8)();
      		breakLoop(ctx);
    	}
  	}
  	else
  	{
    	missOrHit = ctx->userSpace;
		if(frameID == 45)
		{
			*(u16 *)(v2 + 16) |= 9u;
			reduceHPBar(v2, ctx->userSpace[0]);
		}
    	if ( (s16)sub(80684B0)(v2) != 2 )
    	{
      		if ( checkIfCritical(*(void **)&ctx->userSpace[51]) == 1 )
     	 	{
        		criticalAttackEffect(v2);
      		}
      		else
      		{
        		if ( *missOrHit )
          		return;
        		normalAttackEffect(AIS);
      		}
    	}
    	if ( !*missOrHit )
    		playHitSound((void *)v2);
 	}
}

