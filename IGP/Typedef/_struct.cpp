//
//  _struct.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/12.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "_struct.hpp"
#include "../IGP.hpp"

namespace zkzszd
{
	ostream& operator << (ostream& output, RowHistogram& row)//定义运算符“<<”重载函数
	{
		output << "---------------------------------------" << endl;
		output << "RowHistogram.width" << row.width << endl;
		for (uint32 i = 0; i<row.width; i++)
		{
			output << row.data[i] << "    ";
		}
		output << endl << "---------------------------------------" << endl;
		return output;
	}

	ostream& operator << (ostream& output, ColHistogram& col)//定义运算符“<<”重载函数
	{
		output << "---------------------------------------" << endl;
		output << "ColHistogram.heigth" << col.heigth << endl;
		for (uint32 i = 0; i< col.heigth; i++)
		{
			output << col.data[i] << "    ";
		}
		output << endl << "---------------------------------------" << endl;
		return output;
	}

	Color_RGB::Color_RGB(COLOR_RGB color)
	{
		B = (color & 0xFF);
		G = (color >> 8) & 0xFF;
		R = (color >> 16) & 0xFF;
	}

	Color_ARGB::Color_ARGB(COLOR_ARGB color):Color_RGB(color)
	{
		A = (color >> 24) & 0xFF;
	}
}
