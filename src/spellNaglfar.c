// 纳格尔法尔魔法动画
// by laqieer
// 2017/6/2

#include "spellNaglfar.h"

// 纳格尔法尔魔法主协程
struct coroutine efxNaglfar[]={
	spellStart,
	setLoopFuncAndYield(Naglfar),
	endofCoroutine
};

// 纳格尔法尔主函数
void spellNaglfar(void *AIS)
{
	struct context *ctx;

	sub(80507CC)();
	sub(8050348)();
	sub(80507E4)();
	ctx = createContext(efxNaglfar,3);
	*(void **)&ctx->userSpace[51] = AIS;
	*(u16 *)&ctx->userSpace[3] = 0;
	ctx->userSpace[0] = sub(8054E74)(sub(8054FEC)(AIS));
}

// 纳格尔法尔魔法动画
void Naglfar(struct context *ctx)
{
	
}