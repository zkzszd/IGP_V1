#ifndef __IGPUTILITY__H__
#define __IGPUTILITY__H__
#include "../Typedef/MyTypedef.h"
#include "../Typedef/_struct.hpp"
#include <emmintrin.h>

namespace zkzszd
{
	#define WIDTHBYTES(bytes) (((bytes * 8) + 31) / 32 * 4)
	unsigned char ClampToByte(int Value);
	/// 无符号短整形直方图数据相加，Y = X + Y 使用的是SSE优化，安卓对应的指令集为	
	//主流支持目标平台为ARM CPU的编译器基本都支持NEON指令。可以通过在代码中嵌入NEON汇编来使用NEON，但是更加常见的方式是通过类似C函数的NEON Instrinsic来编写NEON代码。就如同NEON hello world一样。NEON Instrinsic是编译器支持的一种buildin类型和函数的集合，基本涵盖NEON的所有指令，通常这些Instrinsic包含在arm_neon.h头文件中。 NEON只有单精度浮点计算能力 http://www.cnblogs.com/xylc/p/5410517.html
	void HistgramAddShort(unsigned short *X, unsigned short *Y);
	//无符号短整形直方图数据相减，Y = Y + X
	void HistgramSubShort(unsigned short *X, unsigned short *Y);
	//无符号短整形直方图数据相加减，Z = Z + Y - X
	void HistgramSubAddShort(unsigned short *X, unsigned short *Y, unsigned short *Z);

class IGPUtility
{
public:
	//扩充行映射表(会分配内存、不需要主动释放)
	static RET_CODE ValidCoordinateRow(RowHistogram& rowHistogram,int32 width, int32 left, int32 right, EdgeMode edgeMode);
	//扩充列映射表(会分配内存、不需要主动释放)
	static RET_CODE ValidCoordinateCol(ColHistogram& colHistogram,int32 heigth, int32 top, int32 bottom, EdgeMode edgeMode);
private:
	IGPUtility() {}
};
};

#endif
