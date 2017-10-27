//
//  AlphaModule.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/7/10.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef AlphaModule_hpp
#define AlphaModule_hpp

/**
 *用来处理图片透明通道
 */

#include <stdio.h>
#include "../ImageInfo/IGPBitmap.hpp"
#include "../Typedef/MyTypedef.h"
#include "../Typedef/_struct.hpp"
#include "../Functor/ShadeFunctor.h"
#include "../Util/UtilAllocator.hpp"
#include "../Shape/BaseRect.h"
#include "../Shape/IGPPoint.h"

namespace zkzszd {
    
class AlphaModule
{
public:
	/*****************************************************************************
	* @function name :  贴图
	* @author : zkzszd
	* @date : 2017/8/8 15:58
	* @inparam : 
	* @outparam : 
	* @last change : 
	*****************************************************************************/
    static uint8 coverToBg(IGPBitmap &bg_bitmap,IGPBitmap &cv_bitmap,IGPPoint& point);
    
    /**
     <#Description#>
     
     @param bitmap <#bitmap description#>
     @param rect rect description
     @param rect_alpha rect区域内部透明度
     @param edge_alpha 边缘透明度
     @param nexus_type <#nexus_type description#>
     @param shade_width 渐变半径
     @return return value description
     */
    template <class Nexus_type>
    static uint8 shade(IGPBitmap &bitmap,BaseRect& rect,Nexus_type& nexus_type,uint8 rect_alpha = 255, uint8 edge_alpha = 0,uint32 shade_width = 0)
    {
        if(bitmap.getFormat() == RGB_888)
        {
            return __shadeRGB(bitmap, rect, rect_alpha, edge_alpha, nexus_type, shade_width);
        }
        else if(bitmap.getFormat() == RGBA_8888)
        {
            return __shadeRGBA(bitmap, rect, rect_alpha, edge_alpha, nexus_type, shade_width);
        }
        return CODE_FAIL;
    }
private:
    template <class Nexus_type>
    static uint8 __shadeRGBA(IGPBitmap &bitmap,BaseRect& rect,uint8 rect_alpha,uint8 edge_alpha,Nexus_type nexus_type,uint32 shade_width)
    {
        IGPPoint point;
        int32 alpha_range = rect_alpha - edge_alpha;
        float shade_num;
        float distance;             //区域内点到边缘距离
        float rat;                  //比例
        uint8* px = (uint8*)bitmap.getPixels();
        uint32 width = bitmap.getWidth();
        uint32 one_length = bitmap.getOnePixelLength();
        for(uint32 h = rect.min_y;h <= rect.max_y;h++)
        {
            for(uint32 w = rect.min_x;w <= rect.max_x;w++)
            {
                point.set(w, h);
                //在区域内
                if(rect.isContain(point))
                {
                    if(shade_width > 0)
                    {
                        distance = rect.dis_border(point);
                        //渐变半径内
                        if(distance<shade_width)
                        {
							rat = nexus_type(distance / shade_width);
							shade_num = rat * alpha_range;
							//此处没有四舍五入，直接取整
							*(px + (h*width + w)*one_length) = edge_alpha + (int8)(shade_num);
							continue;
                        }
                    }
                    *(px+(h*width+w)*one_length+3) = rect_alpha;
                }
                else
                {
                    *(px+(h*width+w)*one_length+3) = edge_alpha;
                }
            }
        }
        return CODE_SUCESS;
    }
    
    template <class Nexus_type>
    static uint8 __shadeRGB(IGPBitmap &bitmap,BaseRect& rect,uint8 rect_alpha,uint8 edge_alpha,Nexus_type nexus_type,uint32 shade_width)
    {
        uint32 width = bitmap.getWidth();
        uint32 height = bitmap.getHeight();
        uint8* fr_px = (uint8*)bitmap.getPixels();
        uint32 loc;
        float shade_num;             //渐变数值
        uint8* to_loc_px;            //新点位置
        uint8* fr_loc_px;            //旧点位置
        IGPPoint point;
        int32 alpha_range = rect_alpha - edge_alpha;
        float distance = 0;         //区域内点到边缘距离
        float rat;                  //比例
        uint8* to_px = (uint8*)UtilAllocator::alloc_malloc(width*height*4);

		for (int32 h = 0; h < height; h++)
		{
			for (int32 w = 0; w < width; w++)
			{
				loc = h*width + w;
				to_loc_px = to_px + loc * 4;
				fr_loc_px = fr_px + loc * 3;
				*to_loc_px = *fr_loc_px;
				*(to_loc_px + 1) = *(fr_loc_px + 1);
				*(to_loc_px + 2) = *(fr_loc_px + 2);

				point.set(w, h);
				if (rect.isContain(point))
				{
					if (shade_width > 0)
					{
						distance = rect.dis_border(point);
						if (distance < shade_width)
						{
							rat = nexus_type(distance / shade_width);
							shade_num = rat * alpha_range;
							//此处没有四舍五入，直接取整
							*(to_loc_px + 3) = edge_alpha + (int8)(shade_num);
							continue;
						}
					}
					*(to_loc_px + 3) = rect_alpha;
				}
				else
				{
					*(to_loc_px + 3) = edge_alpha;
				}
			}
		}

        bitmap.setPixels(to_px);
        bitmap.setFormat(RGBA_8888);
        free(fr_px);
        return CODE_SUCESS;
    }
};
    
}
#endif /* AlphaModule_hpp */
