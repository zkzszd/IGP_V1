#include "IGPBitmapChannel.h"


namespace zkzszd
{
	IGPBitmapChannel::IGPBitmapChannel()
	{
	}

	IGPBitmapChannel::IGPBitmapChannel(uint32 width, uint32 height, ImageFormat imageFormat)
	{
		if (width <= 0)
			width = 1;
		if (height <= 0)
			height = 1;
		_width = width;
		_height = height;
		this->imageFormat = imageFormat;
		uint32 total_px = _width * _height;
		_R_channel = (uint8*)malloc(total_px * sizeof(uint8));
		_G_channel = (uint8*)malloc(total_px * sizeof(uint8));
		_B_channel = (uint8*)malloc(total_px * sizeof(uint8));
		if(imageFormat == RGBA_8888)
			_A_channel = (uint8*)malloc(total_px * sizeof(uint8));
	}


	IGPBitmapChannel::~IGPBitmapChannel()
	{
		if (_R_channel != nullptr)
		{
			free(_R_channel);
		}
		if (_G_channel != nullptr)
		{
			free(_G_channel);
		}
		if (_B_channel != nullptr)
		{
			free(_B_channel);
		}
		if (_A_channel != nullptr)
		{
			free(_A_channel);
		}
	}
}

