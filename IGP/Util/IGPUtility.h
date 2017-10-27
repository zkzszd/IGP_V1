#ifndef __IGPUTILITY__H__
#define __IGPUTILITY__H__
#include "../Typedef/MyTypedef.h"
#include "../Typedef/_struct.hpp"
#include <emmintrin.h>

namespace zkzszd
{
	#define WIDTHBYTES(bytes) (((bytes * 8) + 31) / 32 * 4)
	unsigned char ClampToByte(int Value);
	/// �޷��Ŷ�����ֱ��ͼ������ӣ�Y = X + Y ʹ�õ���SSE�Ż�����׿��Ӧ��ָ�Ϊ	
	//����֧��Ŀ��ƽ̨ΪARM CPU�ı�����������֧��NEONָ�����ͨ���ڴ�����Ƕ��NEON�����ʹ��NEON�����Ǹ��ӳ����ķ�ʽ��ͨ������C������NEON Instrinsic����дNEON���롣����ͬNEON hello worldһ����NEON Instrinsic�Ǳ�����֧�ֵ�һ��buildin���ͺͺ����ļ��ϣ���������NEON������ָ�ͨ����ЩInstrinsic������arm_neon.hͷ�ļ��С� NEONֻ�е����ȸ���������� http://www.cnblogs.com/xylc/p/5410517.html
	void HistgramAddShort(unsigned short *X, unsigned short *Y);
	//�޷��Ŷ�����ֱ��ͼ���������Y = Y + X
	void HistgramSubShort(unsigned short *X, unsigned short *Y);
	//�޷��Ŷ�����ֱ��ͼ������Ӽ���Z = Z + Y - X
	void HistgramSubAddShort(unsigned short *X, unsigned short *Y, unsigned short *Z);

class IGPUtility
{
public:
	//������ӳ���(������ڴ桢����Ҫ�����ͷ�)
	static RET_CODE ValidCoordinateRow(RowHistogram& rowHistogram,int32 width, int32 left, int32 right, EdgeMode edgeMode);
	//������ӳ���(������ڴ桢����Ҫ�����ͷ�)
	static RET_CODE ValidCoordinateCol(ColHistogram& colHistogram,int32 heigth, int32 top, int32 bottom, EdgeMode edgeMode);
private:
	IGPUtility() {}
};
};

#endif
