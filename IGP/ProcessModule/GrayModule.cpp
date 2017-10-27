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
	uint8 GrayModule::GrayToOneChannel(IGPBitmap &fr_bitmap, IGPBitmap &to_bitmap,EnumGrayMode mode)
	{
		int32 width = fr_bitmap.getWidth();
		int32 height = fr_bitmap.getHeight();
		uint8* fr_px = (uint8*)fr_bitmap.getPixels();
		uint8* to_px = (uint8*)to_bitmap.getPixels();
		if (to_px != NULL)
		{
			free(to_px);
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
