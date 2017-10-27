#pragma once

namespace zkzszd
{
#define div255_f(x) (x * 0.003921F)								// 1/255 	//Ŀǰû�в�������Ч��
#define div255_fast(x)    (((x) + (((x) + 257) >> 8)) >> 8)		//1/255		��Ŀ��÷������죩
#define ABS(a) ((a)<(0)?(-a):(a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))

#define zk_MAX(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))
#define zk_MIN(a,b,c) (a<b?(a<c?a:c):(b<c?b:c))
}


