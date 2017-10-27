//
//  ProjectionModule.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/7/24.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "ProjectionModule.hpp"
#include "../ImageInfo/IGPBitmap.hpp"
#include "../Typedef/MyTypedef.h"
#include "../Typedef/_struct.hpp"
#include "../Functor/ShadeFunctor.h"
#include "../Util/UtilAllocator.hpp"

namespace zkzszd
{
    int8 ProjectionModule::projection(IGPBitmap &bitmap,IGPBitmap &to_bitmap,BaseRect &rect,LineCommonly &line)
    {
        IGPPoint point,reverse_point;
        uint8* px = (uint8*)bitmap.getPixels();
        uint8* to_px = (uint8*)to_bitmap.getPixels();
        int32 min_x = rect.min_x;
        int32 min_y = rect.min_y;
        int32 max_x = rect.max_x;
        int32 max_y = rect.max_y;
        int32 width = bitmap.getWidth();
        int32 height = bitmap.getHeight();
        int32 onePxLength = bitmap.getOnePixelLength();
        int32 toOnePxLength = to_bitmap.getOnePixelLength();
        int32 des,loc;
        if(min_x < 0)
            min_x = 0;
        if(min_y < 0)
            min_y = 0;
        if(max_x > width)
            max_x = width;
        if(max_y > height)
            max_y = height;
        for(int h = min_y; h < max_y;h++)
        {
            for(int w = min_x;w < max_x;w++)
            {
                
                point.set(w, h);
                reverse_point = line.getSymmetry(point);
                if(reverse_point.x < 0 || reverse_point.x > width)
                {
                    continue;
                }
                if(reverse_point.y < 0 || reverse_point.y > height)
                {
                    continue;
                }
                loc = (h*width+w)*onePxLength;
                des = (reverse_point.y*width+reverse_point.x)*toOnePxLength;
                to_px[des] = px[loc];
                to_px[des+1] = px[loc+1];
                to_px[des+2] = px[loc+2];
            }
        }
        
        return CODE_SUCESS;
    }
}
