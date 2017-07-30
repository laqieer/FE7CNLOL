//======================================================
//    math.h                                           
//    Utilities
//======================================================

#ifndef	__SHARE__
#define	__SHARE__




#undef	NULL
#define	NULL	((void *)0)

#define ROUND(a)	((int)(a+0.5))	//四舍五入


//求小值
#define MIN(a,b)	({						\
					typedef _ta=(a);		\
					typedef _tb=(b);		\
					_ta=(a);				\
					_tb=(b);				\
					_a < _b ? _a : _b;		\
					})


//求大值
#define MAX(a,b)	({						\
					typedef _ta=(a);		\
					typedef _tb=(b);		\
					_ta=(a);				\
					_tb=(b);				\
					_a > _b ? _a : _b;		\
					})




#define ABS(a) (((a)<0) ? -(a) : (a))

//-------------------- Fixed decimal point ----------------------
extern const u16 sin_cos_table[256+64];
#define	_Sin( a ) (s16)(sin_cos_table[(a)])
#define	_Cos( a ) (s16)(sin_cos_table[(a)+64])
s16 fix_mul( s16 a , s16 b );
s16 fix_div( s16 a , s16 b );
s16 fix_inverse( s16 b );

extern const float sin_data[91];
extern float GtSin(int deg);
extern float GtCos(int deg);
extern u32 GtSqurt(u32 n);

#endif	//  __math__
