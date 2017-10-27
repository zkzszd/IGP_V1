//
//  SpaceAdapter.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/5.
//  Copyright 漏 2017骞?zkzszd. All rights reserved.
//

#ifndef SpaceAdapter_hpp
#define SpaceAdapter_hpp

#include <stdio.h>
#include "../ImageInfo/IGPBitmap.hpp"
#include "../ImageInfo/IGPBitmapHSL.hpp"
#include "../ImageInfo/IGPBitmapChannel.h"

#define LOP_BLOCK_SIZE 8			//循环展开8次，用来加速
namespace zkzszd
{
    extern class IGPBitmapHSL;
    /**
     * 涓や釜棰滆壊绌洪棿杞寲閫傞厤鍣?     */
    class SpaceAdapter
    {
    public:
        
		/*****************************************************************************
		* @function name :  getBitmapHSL  获取bitmap的hsl颜色空间
		* @author : zkzszd
		* @date : 2017/8/7 15:55
		* @bitmap : 原图
		* @IGPBitmapHSL : 原图的hsl模式
		* @outparam : 
		* @last change : 
		*****************************************************************************/
		static int8 getBitmapHSL(IGPBitmap &bitmap, IGPBitmapHSL &hsl_bitmap);

		/*****************************************************************************
		* @function name :  applyHSLToBitmap  把hsl处理结果应用到原图
		* @author : zkzszd
		* @date : 2017/8/7 15:55
		* @bitmap : 原图
		* @IGPBitmapHSL : 原图的hsl模式
		* @outparam :
		* @last change :
		*****************************************************************************/
		static int8 applyHSLToBitmap(IGPBitmapHSL &hsl_bitmap, IGPBitmap &bitmap);

		/*****************************************************************************
		* @function name :  RGBToRGBA rgb 转rgba
		* @author : zkzszd
		* @date : 2017/8/4 18:05
		* @alpha : 透明通道透明值
		* @uint8 : 
		* @last change : 
		*****************************************************************************/
		static uint8 RGBToRGBA(IGPBitmap &bitmap, uint8 alpha = 255);

		/*****************************************************************************
		* @function name :  将bitmap分离出个个通道	(支持RGBA8888 和RGB888)
		* @author : zkzszd
		* @date : 2017/8/4 18:05
		* @RET_CODE :
		* @last change :
		*****************************************************************************/
		static RET_CODE BitmapSplit(IGPBitmap &bitmap,IGPBitmapChannel &bitmap_channel);

		/*****************************************************************************
		* @function name :  将分离的各个通道合成bitmap
		* @author : zkzszd
		* @date : 2017/8/4 18:05
		* @RET_CODE :
		* @last change :
		*****************************************************************************/
		static RET_CODE CombineBitmap(IGPBitmapChannel &bitmap_channel,IGPBitmap &bitmap);
    private:
		
        SpaceAdapter(){}
    };
}

#endif /* RGB_HSLAdapter_hpp */
