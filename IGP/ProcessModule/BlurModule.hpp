//
//  BlurModule.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/17.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef BlurModule_hpp
#define BlurModule_hpp

#include <stdio.h>
#include <stdlib.h>
#include "../ImageInfo/IGPBitmap.hpp"
#include "../Typedef/MyTypedef.h"
#include "../Typedef/_struct.hpp"
#include "../Functor/ShadeFunctor.h"
#include "../Shape/BaseRect.h"
#include "../Shape/IGPPoint.h"
#include <functional>

using namespace std;

namespace zkzszd
{
    class BlurModule
    {
    public:
        static uint8 BlurOwn(IGPBitmap &bitmap,int32 radius);

		static void gaussian(IGPBitmap& inBitmap, IGPBitmap& outBitmap, BaseRect& rect, uint32 radius, function<float(float)> nexus_type = IGP_linear(), uint32 shade_width = 0);
        
        template <class Nexus_type>
        static void gaussianWhole(IGPBitmap& inBitmap,IGPBitmap& outBitmap,BaseRect& rect,uint32 radius,Nexus_type nexus_type=IGP_linear(),uint32 shade_width = 0)
        {
            uint8_t* outPixels = (uint8_t*)outBitmap.getPixels();
            uint8_t* inPixels = (uint8_t*)inBitmap.getPixels();
            uint32_t x,y;
            uint8_t *tInPixel, *tOutPixel;
            double tR = 0.0,tG = 0.0,tB = 0.0,tCount = 0.0;
            double dif,gauss;
            int startx,endx,starty,endy;
            int m;
            uint32_t top,left,right,bottom;
            top = rect.min_y;
            bottom = rect.max_y;
            left = rect.min_x;
            right = rect.max_x;
            if(top < 0)
            {
                top = 0;
            }
            if(bottom > inBitmap.getHeight() - 1){
                bottom = inBitmap.getHeight() - 1;
            }
            if(left < 0){
                left = 0;
            }
            if(right > inBitmap.getWidth() - 1){
                right = inBitmap.getWidth() - 1;
            }
            //The dimension of X
            IGPPoint tDo[(inBitmap.getWidth()) * (inBitmap.getHeight() )];
            uint32_t tDoLen = 0;
            IGPPoint point;
            float distance;                 //边缘距离
            uint32 range = radius;          //新的模糊半径
            
            for(y = 0; y <= inBitmap.getHeight(); y ++)
            {
                for(x = 0; x <= inBitmap.getWidth(); x ++)
                {
                    point.set(x, y);
                    if(rect.isContain(point))
                    {
                        continue;
                    }
                    
                    //                    if(shade_width > 0)
                    //                    {
                    //                        distance = rect.dis_border(point);
                    //                        //在渐变效果内
                    //                        if(distance < shade_width)
                    //                        {
                    //                            range = radius*nexus_type(distance/shade_width);
                    //                            printf("range = %d \t %f\n",range,nexus_type(distance/shade_width));
                    //                        }
                    //                    }
                    
                    tDo[tDoLen].set(x, y);
                    tDoLen ++;
                    
                    tOutPixel = outPixels + (y*outBitmap.getStride()+x*outBitmap.getOnePixelLength());
                    startx = (x < range ? -x : -range);
                    endx = ((inBitmap.getWidth() <= x + range) ? (inBitmap.getWidth() - x - 1) : range);
                    
                    //x dimension
                    tR = tG = tB = tCount = 0.0;
                    for(m = startx; m <= endx; m ++)
                    {
                        tInPixel = inPixels + (y*inBitmap.getStride()+(x+m)*inBitmap.getOnePixelLength());
                        dif = m*m;
                        gauss = exp(-dif/(2*range));
                        tR += gauss * *(tInPixel + 0);
                        tG += gauss * *(tInPixel + 1);
                        tB += gauss * *(tInPixel + 2);
                        tCount += gauss;
                    }
                    *(tOutPixel + 0) = tR / tCount;
                    *(tOutPixel + 1) = tG / tCount;
                    *(tOutPixel + 2) = tB / tCount;
                }
            }
            
            //y dimension
            uint32_t ind = 0;
            for(ind = 0; ind < tDoLen; ind ++)
            {
                point = tDo[ind];
                tOutPixel = outPixels + (point.y*outBitmap.getStride()+point.x*outBitmap.getOnePixelLength());
                //tOutPixel = (uint8_t* )*outPixels + (p.y * bitmapInfo.width + p.x) * 4;
                starty = (point.y < range ? -point.y : -range);
                
                endy = ((inBitmap.getHeight() <= point.y + range) ? (inBitmap.getHeight() - point.y - 1) : range);
                tR = tG = tB = tCount = 0.0;
                for(m = starty; m <= endy; m ++)
                {
                    tInPixel = inPixels + ((point.y+m)*inBitmap.getStride()+point.x*inBitmap.getOnePixelLength());
                    //tInPixel = (uint8_t* )*outPixels + ((p.y + m) * bitmapInfo.width + p.x) * 4;
                    dif = m*m;
                    gauss = exp(-dif/(2*range));
                    tR += gauss * *(tInPixel + 0);
                    tG += gauss * *(tInPixel + 1);
                    tB += gauss * *(tInPixel + 2);
                    tCount += gauss;
                }
                *(tOutPixel + 0) = tR / tCount;
                *(tOutPixel + 1) = tG / tCount;
                *(tOutPixel + 2) = tB / tCount;
            }
        }

    private:
		BlurModule();
    };
}

#endif /* BlurModule_hpp */
