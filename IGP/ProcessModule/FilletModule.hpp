//
//  FilletModule.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/23.
//  Copyright © 2017年 zkzszd. All rights reserved.
//
//  抠图方式实现圆角  还有另一个贴图方式实现圆角

#ifndef FilletModule_hpp
#define FilletModule_hpp

#include "../buildConfig.h"
#include <stdio.h>
#include "../Typedef/_struct.hpp"
#include "../ImageInfo/IGPBitmap.hpp"

namespace zkzszd
{
    class FilletModule
    {
    public:
		//radius 圆角半径 四个角共用此半径
		//如果是RGBA图片，圆角支持透明通道
        static int8 FilletOwn(IGPBitmap& bitmap,uint32 radius, const COLOR_ARGB &fillColor = 0xffffffff);
        
        //如果是RGBA图片，圆角支持透明通道
        static int8 FilletOwn(IGPBitmap& bitmap,
                              const uint32 &topLeft,const COLOR_ARGB &topLeftColor,
                              const uint32 &topRight,const COLOR_ARGB &topRightColor,
                              const uint32 &bottomLeft,const COLOR_ARGB &bottomLeftColor,
                              const uint32 &bottomRight,const COLOR_ARGB &bottomRightColor);
    private:
        FilletModule(){}
		static int8 FilletOwnRGB(IGPBitmap& bitmap,
			const uint32 &topLeft, const COLOR_RGB &topLeftColor,
			const uint32 &topRight, const COLOR_RGB &topRightColor,
			const uint32 &bottomLeft, const COLOR_RGB &bottomLeftColor,
			const uint32 &bottomRight, const COLOR_RGB &bottomRightColor);
		//RGBA图片圆角区域支持透明通道
		static int8 FilletOwnRGBA(IGPBitmap& bitmap,
			const uint32 &topLeft, const COLOR_ARGB &topLeftColor,
			const uint32 &topRight, const COLOR_ARGB &topRightColor,
			const uint32 &bottomLeft, const COLOR_ARGB &bottomLeftColor,
			const uint32 &bottomRight, const COLOR_ARGB &bottomRightColor);
    };
}

#endif /* FilletModule_hpp */
