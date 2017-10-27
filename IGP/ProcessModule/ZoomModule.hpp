//
//  ZoomModule.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/27.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef ZoomModule_hpp
#define ZoomModule_hpp

#include <stdio.h>
#include "../IGP.hpp"

namespace zkzszd
{
    class ZoomModule
    {
    public:
        typedef enum _ZoomMode
        {
            ZOOM_MODE_fast,                 //快速缩放
            ZOOM_MODE_4_average,            //4邻域
            ZOOM_MODE_4_weighted_average,   //
        }EnumZoomMode;
    
        static int8 Zoom(IGPBitmap &src,IGPBitmap &des,EnumZoomMode mode = ZOOM_MODE_4_weighted_average);
    private:
        static int8 Zoom4weightedAverage(IGPBitmap &src,IGPBitmap &des);
        static int BMP32_resize(unsigned char * SrcBuf, int srcW,int srcH,unsigned char* DstBuf, int dstW, int dstH);
        ZoomModule(){}
    };
}

#endif /* ZoomModule_hpp */
