//
//  GrayModule.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/26.
//  Copyright © 2017年 zkzszd. All rights reserved.
//  灰度处理图片

#include "GrayModule.hpp"

namespace zkzszd
{
	uint8 GrayModule::GrayToOneChannel(IGPBitmap &fr_bitmap, IGPBitmap &to_bitmap,EnumGrayMode gray_mode)
	{
		if (fr_bitmap.width != to_bitmap.width || fr_bitmap.height != to_bitmap.height)
		{
			if (to_bitmap.pixels != nullptr)
			{
				free(to_bitmap.pixels);
			}
			to_bitmap.width = fr_bitmap.width;
			to_bitmap.height = fr_bitmap.height;
			to_bitmap.image_format = GRAY_ONE_CHANNEL;
			to_bitmap.stride = to_bitmap.width;
			to_bitmap.one_pixel_length = 1;
			to_bitmap.pixels = (uint8*)malloc(to_bitmap.width*to_bitmap.height*sizeof(uint8*));
		}
		switch (gray_mode)
		{
		case GRAY_MODE_AVERAGE:
			for (int32 h = 0; h < fr_bitmap.height; h++)
			{
				uint8* line_fr_px = fr_bitmap.pixels + h*fr_bitmap.stride;
				uint8* line_to_px = to_bitmap.pixels + h*to_bitmap.stride;
				for (int32 w = 0; w < fr_bitmap.width; w++)
				{
					int32 fr_loc = w*fr_bitmap.one_pixel_length;
					line_to_px[w] = (line_fr_px[fr_loc] + line_fr_px[fr_loc + 1] + line_fr_px[fr_loc + 2]) / 3;
				}
			}
			break;
		case GRAY_MODE_VISION:
			for (int32 h = 0; h < fr_bitmap.height; h++)
			{
				uint8* line_fr_px = fr_bitmap.pixels + h*fr_bitmap.stride;
				uint8* line_to_px = to_bitmap.pixels + h*to_bitmap.stride;
				for (int32 w = 0; w < fr_bitmap.width; w++)
				{
					int32 fr_loc = w*fr_bitmap.one_pixel_length;
					line_to_px[w] = line_fr_px[fr_loc] * 0.299 + line_fr_px[fr_loc + 1] * 0.578 + line_fr_px[fr_loc + 2] * 0.114;
				}
			}
			break;
		case GRAY_MODE_YUV:
			for (int32 h = 0; h < fr_bitmap.height; h++)
			{
				uint8* line_fr_px = fr_bitmap.pixels + h*fr_bitmap.stride;
				uint8* line_to_px = to_bitmap.pixels + h*to_bitmap.stride;
				for (int32 w = 0; w < fr_bitmap.width; w++)
				{
					int32 fr_loc = w*fr_bitmap.one_pixel_length;
					line_to_px[w] = line_fr_px[fr_loc] * 0.3 + line_fr_px[fr_loc + 1] * 0.59 + line_fr_px[fr_loc + 2] * 0.11;
				}
			}
			break;
		default:
			break;
		}

		return 0;
	}

    uint8 GrayModule::GrayOwnToOneChannel(IGPBitmap &bitmap,EnumGrayMode gray_mode)
    {
        //只有rgb888 565 8888 4444 支持
        //二值化或者灰度化过的不能再灰度化
        uint32 total_pixel = bitmap.getWidth()*bitmap.getHeight();
        int8 *p_bt_pix = (int8*)bitmap.getPixels();
        uint8 *p_addr = (uint8*)UtilAllocator::alloc_malloc(total_pixel);
        switch (bitmap.getFormat()) {
            case RGB_888:
                for(int i = 0; i < total_pixel;i++)
                {
                    if(gray_mode == GRAY_MODE_AVERAGE)
                    {
                        p_addr[i] = (p_bt_pix[i*3] + p_bt_pix[i*3 +1] + p_bt_pix[i*3 +2])/3;
                    }
                    else if(gray_mode == GRAY_MODE_VISION)
                    {
                        p_addr[i] = p_bt_pix[i*3]*0.299 + p_bt_pix[i*3 +1]*0.578 + p_bt_pix[i*3 +2]*0.114;
                    }
                    else
                    {
                        p_addr[i] = p_bt_pix[i*3]*0.3 + p_bt_pix[i*3 +1]*0.59 + p_bt_pix[i*3 +2]*0.11;
                    }
                }
                break;
                
            default:
                break;
        }
        bitmap.setFormat(GRAY_ONE_CHANNEL);
        bitmap.computeOnePixelAndStrideLength();
        bitmap.setPixels(p_addr);
        free(p_bt_pix);
        return CODE_SUCESS;
    }
    
    uint8 GrayModule::GrayOwn(IGPBitmap &bitmap,EnumGrayMode gray_mode)
    {
        uint8* px = (uint8*)bitmap.getPixels();
        uint32 widht = bitmap.getWidth();
        uint32 height = bitmap.getHeight();
        uint32 onePxlength = bitmap.getOnePixelLength();
        
#pragma omp parallel for
        for(int32 h = 0; h<height; h++)
        {
            for(int32 w = 0;w < widht; w++)
            {
				uint32 loc = (h*widht+w)*onePxlength;
                if(gray_mode == GRAY_MODE_AVERAGE)
                {
                    px[loc+2] = px[loc+1] = px[loc] = (px[loc] + px[loc+1] + px[loc+2])/3;
                }
                else if(gray_mode == GRAY_MODE_VISION)
                {
                    px[loc+2] = px[loc+1] = px[loc] = px[loc]*0.299 + px[loc+1]*0.578 + px[loc+2]*0.114;
                }
                else
                {
                    px[loc+2] = px[loc+1] = px[loc] = px[loc]*0.3 + px[loc+1]*0.59 + px[loc+2]*0.11;
                }
            }
        }
        
        return CODE_SUCESS;
    }
}
