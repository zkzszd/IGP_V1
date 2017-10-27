//
//  AlphaModule.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/7/10.
//  Copyright Â© 2017å¹?zkzszd. All rights reserved.
//

#include "AlphaModule.hpp"
#include "../Util/UtilAllocator.hpp"

namespace zkzszd
{
    uint8 AlphaModule::coverToBg(IGPBitmap &bg_bitmap,IGPBitmap &cv_bitmap,IGPPoint& point)
    {
        uint32 cv_width = cv_bitmap.getWidth();
        uint32 bg_width = bg_bitmap.getWidth();
        uint32 cv_height = cv_bitmap.getHeight();
        uint32 bg_height = bg_bitmap.getHeight();
        uint8* bg_px = (uint8*)bg_bitmap.getPixels();
        uint8* cv_px = (uint8*)cv_bitmap.getPixels();
        uint32 end_width = 0;
        uint32 end_height = 0;
        if(point.x+cv_width > bg_width)
        {
            end_width = bg_width - point.x;
        }
        else
        {
            end_width = cv_width;
        }
        if(point.y+cv_height >  bg_height)
        {
            end_height = bg_height - point.y;
        }
        else
        {
            end_height = cv_height;
        }
        uint8 bg_one_length = bg_bitmap.getOnePixelLength();
        uint8 cv_one_length = cv_bitmap.getOnePixelLength();
#pragma omp parallel for
        for(int32 h = 0;h < end_height;h++)
        {
            for(int32 w = 0;w < end_width;w++)
            {
				uint8* bg_loc = bg_px+((point.y+h)*bg_width+point.x+w)*bg_one_length;
				uint8* cv_loc = cv_px+(h*cv_width+w)*cv_one_length;
				float ratio = *(cv_loc+3)/255.0;
                *bg_loc = (*bg_loc)*(1-ratio)+(*cv_loc)*ratio;
                *(bg_loc+1) = (*(bg_loc+1))*(1-ratio)+(*(cv_loc+1))*ratio;
                *(bg_loc+2) = (*(bg_loc+2))*(1-ratio)+(*(cv_loc+2))*ratio;
            }
        }
        return CODE_SUCESS;
    }
}
