#pragma once

namespace zkzszd
{
#define div255_f(x) (x * 0.003921F)								// 1/255 	//目前没有测试两种效率
#define div255_fast(x)    (((x) + (((x) + 257) >> 8)) >> 8)		//1/255		（目测该方法更快）
#define ABS(a) ((a)<(0)?(-a):(a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

#define zk_MAX(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))
#define zk_MIN(a,b,c) (a<b?(a<c?a:c):(b<c?b:c))
}


