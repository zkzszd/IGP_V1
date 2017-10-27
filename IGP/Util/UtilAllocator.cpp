//
//  UtilAllocator.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/25.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "UtilAllocator.hpp"

namespace zkzszd
{
    int8* UtilAllocator::alloc_malloc(uint32 length,uint32 pixel,uint8 item_length)
    {
        //int8* p_return = new int8(length);
        int8* p_return = (int8*)malloc(length);
        if(p_return == nullptr)
        {
            return p_return;
        }
        if(pixel == 0)
        {
            memset(p_return,0,length);
        }
        else
        {
            uint8 *p_pixel = (uint8 *)&pixel;
            int lop = length / item_length;
#pragma omp parallel for
            for(int i = 0; i < lop; i++)
            {
                for(int j = 0;j < item_length; j++)
                {
                    p_return[i*item_length+j] = ((uint8*)p_pixel)[j];
                }
            }
        }
        return p_return;
    }
    
    int8* UtilAllocator::alloc_malloc(uint32 alloc_length,void *copy_addr)
    {
        //int8* p_return = new int8(alloc_length);
        int8 *p_return = (int8*)malloc(alloc_length);
        if(p_return == nullptr)
        {
            return p_return;
        }
        memcpy(p_return, copy_addr, alloc_length);
        return p_return;
    }
}
