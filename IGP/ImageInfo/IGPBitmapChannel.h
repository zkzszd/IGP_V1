#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../Typedef/MyTypedef.h"

namespace zkzszd
{ 

class IGPBitmapChannel
{
public:
	IGPBitmapChannel();
	IGPBitmapChannel(uint32 width,uint32 height, ImageFormat imageFormat);
	/*ÊÍ·ÅÄÚ´æ*/
	~IGPBitmapChannel();
public:
	uint32 getWidth() { return _width; }
	uint32 getHeight() { return _height; }
	uint8* getRChannel() { return _R_channel; }
	uint8* getGChannel() { return _G_channel; }
	uint8* getBChannel() { return _B_channel; }
	uint8* getAChannel() { return _A_channel; }

private:
	ImageFormat imageFormat;
	uint8 *_R_channel = nullptr;
	uint8 *_G_channel = nullptr;
	uint8 *_B_channel = nullptr;
	uint8 *_A_channel = nullptr;
	int32 _width;
	int32 _height;

	friend class SpaceAdapter;
	friend class SelectiveBlur;
};

}

