//
//  BlackAndWhiteModule.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/7/17.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef BlackAndWhiteModule_hpp
#define BlackAndWhiteModule_hpp
#include <functional>
#include <stdio.h>
#include "../ImageInfo/IGPBitmap.hpp"
#include "../Typedef/MyTypedef.h"

using namespace std;

namespace zkzszd  {
class BlackAndWhiteModule
{
public:
    struct ThresholdConstant
    {
		float threshol = 127;
		//ThresholdConstant() { threshol = 127; }
		ThresholdConstant(float threshol) { this->threshol = threshol; }
        /**
         中直求图片二值化墒值

         @param bitmap <#bitmap description#>
         @return <#return value description#>
         */
        float operator()(const IGPBitmap &bitmap)
        {
            return threshol;
        }
    };
    
	/*****************************************************************************
	* @function name : 图像所有像素点的平均值做为二值化墒值
	* @author : zkzszd
	* @date : 2017/8/28 15:05
	*****************************************************************************/
    struct ThresholAverage
    {
        float operator()(IGPBitmap &bitmap);
    };
    
	/*****************************************************************************
	* @function name : 图像像素统计中最大波动处做为二值化墒值
	* @author : zkzszd
	* @date : 2017/8/28 15:05
	*****************************************************************************/
    struct ThresholdRockBottom
    {
        float operator()(IGPBitmap &bitmap);
    };
    
    /**
     二值化(黑白化)灰度化过的图像

     @param bitmap 灰度化过的照片 RGB 或者RGBA格式
     @return <#return value description#>
     */
	static int8 processGray(IGPBitmap &bitmap, function<float(IGPBitmap&)> threshol_method);
    
private:
    
};
}


#endif /* BlackAndWhiteModule_hpp */
