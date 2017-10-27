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
	IGPBitmap _src_bitmap;						//原图
	jobject jbitmap;							//显示图、保证所有操作立马看到效果
};

