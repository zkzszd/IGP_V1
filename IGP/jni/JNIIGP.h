#pragma once
#include <android/log.h>
#include <android/bitmap.h>
#include "../IGP.hpp"
using namespace zkzszd;
class JNIIGP
{
public:
	JNIIGP();
	~JNIIGP();

private:
	IGPBitmap _src_bitmap;						//ԭͼ
	jobject jbitmap;							//��ʾͼ����֤���в���������Ч��
};

