//
//  _struct.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/12.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef _struct_hpp
#define _struct_hpp

#include <stdio.h>
#include <stdlib.h>
#include "./MyTypedef.h"
#include "../Util/UtilMath.hpp"
#include <math.h>
#include <iostream>

using namespace std;

namespace zkzszd
{
    //因为很多头像头都是固定长度，且非内存对其
#pragma pack(push) //保存对齐状态
#pragma pack(1)

	struct IGP_RGB
	{
		uint8 R;
		uint8 G;
		uint8 B;
	};

	struct IGP_RGBA:public IGP_RGB
	{
		uint8 A;
	};

    struct IGPHSL
    {
        float H;
        float S;
        float L;
        IGPHSL()
        {
            H=0;
            S=0;
            L=0;
        }
        IGPHSL(float h,float s,float l)
        {
            H = h;
            S = s;
            L = l;
        }
    };

	struct RowHistogram				//行统计直方图
	{
		uint32 width;
		int32 *data;
		~RowHistogram()
		{
			if (data != nullptr)
			{
				free(data);
			}
		}
		friend ostream& operator << (ostream& output, RowHistogram& row);//定义运算符“<<”重载函数
	};

	struct ColHistogram
	{
		uint32 heigth;				//列高
		int32 *data;
		~ColHistogram()
		{
			if (data != nullptr)
			{
				free(data);
			}
		}
		friend ostream& operator << (ostream& output, ColHistogram& col);//定义运算符“<<”重载函数
	};

	struct Color_RGB
	{
		uint8 R;
		uint8 G;
		uint8 B;
		Color_RGB():R(0), B(0), G(0) {}
		Color_RGB(uint8 p_R, uint8 p_G, uint8 p_B) :R(p_R), G(p_G), B(p_B) {}
		Color_RGB(COLOR_RGB color);
	};

	//注意大小端，不要和int型做强转
	struct Color_ARGB : public Color_RGB
	{
		uint8 A;
		Color_ARGB() :Color_RGB(), A(0) {}
		Color_ARGB(uint8 p_A, uint8 p_R, uint8 p_G, uint8 p_B) :Color_RGB(p_R, p_G, p_B), A(p_A) {}
		Color_ARGB(COLOR_ARGB color);
	};

	//灰度化图像的积分图
	//int类型最大容纳2800*3000图像的积分图
	//如果是积分图的平方，int类型最大容纳256*256
	struct GrayIntegral
	{
		int32 width;
		int32 height;
		uint32* data = nullptr;

		GrayIntegral(int32 width, int32 height)
		{
			this->width = width;
			this->height = height;
			data = (uint32*)malloc(width*height*sizeof(uint32));
			//目前算法，所有积分图点都会被更新到，不用重置
			//memset(data, 0, width*height * sizeof(uint32));
		}
		~GrayIntegral()
		{
			if (data != nullptr)
			{
				free(data);
			}
		}
	};
   
#pragma pack(pop)//恢复对齐状态
}
#endif /* _struct_hpp */
