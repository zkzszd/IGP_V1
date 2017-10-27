//
//  IGPBitmapSHL.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/5.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "IGPBitmapHSL.hpp"
#include "../Typedef/_struct.hpp"

namespace zkzszd
{
    void IGPBitmapHSL::init(uint32 width,uint32 height)
    {
        if(width == getWidth() && height == getHeight())
        {
            return;
        }
		IGPHSL* p_pixel = getPixels();
        if (p_pixel != nullptr)
        {
            free(p_pixel);
        }
        setWidth(width);
        setHeight(height);
        p_pixel = (IGPHSL*)UtilAllocator::alloc_malloc(sizeof(IGPHSL)*width*height);
        setPixels(p_pixel);
    }
    
    void IGPBitmapHSL::updateOnePXLenAndStride()
    {}
}
