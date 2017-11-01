//
//  GrayModule.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/26.
//  Copyright © 2017年 zkzszd. All rights reserved.
//  灰度处理图片
//  会将三通道的图片转成一通道
//  C++标准提倡将模板的所有实现都放在头文件中以便编译器可以当场实现模板实例，这样能够避免产生跨目标文件链接

#ifndef GrayModule_hpp
#define GrayModule_hpp

#include <stdio.h>
#include <math.h>
#include <functional>
#include "../Shape/IGPPoint.h"
#include "../Adapter/SpaceAdapter.hpp"
#include "../Typedef/_struct.hpp"
#include "../ImageInfo/IGPBitmapHSL.hpp"
#include "../Typedef/MyTypedef.h"
#include "../Functor/ShadeFunctor.h"
#include "../Shape/BaseRect.h"
#include "../Shape/IGPLineSegment.h"

using namespace std;

namespace zkzszd
{

    class GrayModule
    {
    public:
        typedef enum _GrayProcessMode
        {
            GRAY_MODE_AVERAGE,  //rgb 平均值
            GRAY_MODE_VISION,   //视觉敏感度根据重要性及其它指标，将三个分量以不同的权值进行加权平均。由于人眼对绿色的敏感最高，对蓝色敏感最低，因此，按下式对RGB三分量进行加权平均能得到较合理的灰度图像。r*0.299 + g*0.578 + b*0.114
            GRAY_MODE_YUV      //YUV空间的亮度Y
        }EnumGrayMode;
        
		/*****************************************************************************
		* @function name :  GrayToOneChannel 灰度化原图到目标图
		* @author : zkzszd
		* @date : 2017/8/23 17:26
		* @fr_bitmap : 原图  
		* @to_bitmap : 一通道灰度化后图片
		* @outparam : 
		* @last change : 
		*****************************************************************************/
		static uint8 GrayToOneChannel(IGPBitmap &fr_bitmap,IGPBitmap &to_bitmap, EnumGrayMode mode = GRAY_MODE_AVERAGE);

		/*****************************************************************************
		* @function name : GrayOwnToOneChannel
		* @warning : 二值化或者灰度化过的不能再灰度化 会把3通道变为1通道
		* @author : zkzszd
		* @date : 2017/8/24 16:27
		* @inparam : 
		* @outparam : 
		* @last change : 
		*****************************************************************************/
        static uint8 GrayOwnToOneChannel(IGPBitmap &bitmap,EnumGrayMode mode = GRAY_MODE_AVERAGE);
        
        static uint8 GrayOwn(IGPBitmap &bitmap,EnumGrayMode mode = GRAY_MODE_AVERAGE);

		/*****************************************************************************
		* @function name : GrayOwn 灰度化原图
		* @warning : 
		* @author : zkzszd
		* @date : 2017/8/24 16:27
		* @inparam :
		* @outparam :
		* @last change :
		*****************************************************************************/
        template <class Nexus_type>
        static uint8 GrayOwn(IGPBitmap &igp_bitmap,BaseRect& rect_type,Nexus_type nexus_type=IGP_linear(),uint16 shade_width = 0)
        {
            IGPBitmapHSL hsl_bitmap;
            SpaceAdapter::RGB2HSL(igp_bitmap, hsl_bitmap);
            uint32 igp_w = hsl_bitmap.getWidth();
            uint32 igp_h = hsl_bitmap.getHeight();
            IGPHSL* igp_px = (IGPHSL*)hsl_bitmap.getPixels();
            IGPHSL* igp_px_line;
            IGPHSL* igp_point;
            float distance,rat;
            IGPPoint point;
        
            for(int h = 0;h < igp_h;h++)
            {
                igp_px_line = igp_px+h*igp_w;
                for(int w = 0;w < igp_w;w++)
                {
                    igp_point = igp_px_line+w;
                    point.set(w, h);
                    //在边外部
                    if(!rect_type.isContain(point))
                    {
                        igp_point->S = 0;
                        continue;
                    }
                    else
                    {
                        //当有渐变时，才求点到边界距离
                        if(shade_width > 0)
                        {
                            distance = rect_type.dis_border(point);
                            //在渐变效果内
                            if(distance < shade_width)
                            {
                                rat = nexus_type(distance/shade_width);
                                igp_point->S *= rat;
                            }
                        }
                    }
                }
            }
            SpaceAdapter::HSL2RGB(hsl_bitmap, igp_bitmap);
            
            return CODE_SUCESS;
        }

        
        template <class Nexus_type>
        static uint8 GrayShade(IGPBitmap &bitmap,IGPLineSegment &igpLine,Nexus_type nexus_type)
        {
            IGPBitmapHSL hsl_bitmap;
            SpaceAdapter::RGB2HSL(bitmap, hsl_bitmap);uint32 igp_w = hsl_bitmap.getWidth();
            uint32 igp_h = hsl_bitmap.getHeight();
            IGPHSL* igp_px = (IGPHSL*)hsl_bitmap.getPixels();
            IGPHSL* igp_px_line;
            IGPHSL* igp_point;
            IGPPoint point;
            float ratio;
            
            for(int h = 0;h < igp_h;h++)
            {
                igp_px_line = igp_px+h*igp_w;
                for(int w = 0;w < igp_w;w++)
                {
                    igp_point = igp_px_line+w;
                    point.set(w, h);
                    ratio = igpLine.getPointRatio(point);
                    if(ratio>0)
                    {
                        igp_point->S*=nexus_type(ratio);
                    }
                }
            }
            SpaceAdapter::HSL2RGB(hsl_bitmap, bitmap);
            return CODE_SUCESS;
        }
        
    private:
        GrayModule(){}
    };
}

#endif /* GrayModule_hpp */
