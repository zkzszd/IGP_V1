//
//  FilletModule.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/23.
//  Copyright © 2017年 zkzszd. All rights reserved.
//


#include "FilletModule.hpp"
#include "../Util/UtilMath.hpp"
#include "../Shape/IGPPoint.h"
#include <iostream>

using namespace std;

namespace zkzszd
{
	int8 FilletModule::FilletOwn(IGPBitmap & bitmap, uint32 radius, const COLOR_ARGB& fillColor)
	{
		int8 ret_code = CODE_FAIL;
		if (bitmap.getFormat() == RGBA_8888)
		{
			ret_code = FilletOwnRGBA(bitmap,
				radius, fillColor,
				radius, fillColor,
				radius, fillColor,
				radius, fillColor);
		}
		else if (bitmap.getFormat() == RGB_888)
		{
			ret_code = FilletOwnRGB(bitmap,
				radius, fillColor,
				radius, fillColor,
				radius, fillColor,
				radius, fillColor);
		}
		return ret_code;
	}

	int8 FilletModule::FilletOwn(IGPBitmap & bitmap, 
		const uint32 & topLeft, const COLOR_ARGB & topLeftColor, 
		const uint32 & topRight, const COLOR_ARGB & topRightColor, 
		const uint32 & bottomLeft, const COLOR_ARGB & bottomLeftColor, 
		const uint32 & bottomRight, const COLOR_ARGB & bottomRightColor)
	{
		int8 ret_code = CODE_FAIL;
		if (bitmap.getFormat() == RGBA_8888)
		{
			ret_code = FilletOwnRGBA(bitmap,
				topLeft, topLeftColor,
				topRight, topRightColor,
				bottomLeft, bottomLeftColor,
				bottomRight, bottomRightColor);
		}
		else if (bitmap.getFormat() == RGB_888)
		{
			ret_code = FilletOwnRGB(bitmap,
				topLeft, topLeftColor,
				topRight, topRightColor,
				bottomLeft, bottomLeftColor,
				bottomRight, bottomRightColor);
		}
		return ret_code;
	}

	int8 FilletModule::FilletOwnRGB(IGPBitmap& bitmap,
		const uint32 &topLeft, const COLOR_RGB &topLeftColor,
		const uint32 &topRight, const COLOR_RGB &topRightColor,
		const uint32 &bottomLeft, const COLOR_RGB &bottomLeftColor,
		const uint32 &bottomRight, const COLOR_RGB &bottomRightColor)
	{
		uint32 width = bitmap.getWidth();
		uint32 height = bitmap.getHeight();
		//处理圆角半径大于宽高特殊情况
		uint32 lop_topLeft_h = MIN(height, topLeft);
		uint32 lop_topLeft_w = MIN(width, topLeft);
		uint32 lop_topRight_h = MIN(height, topRight);
		uint32 lop_topRight_w = MIN(width, topRight);
		uint32 lop_bottomLeft_h = MIN(height, bottomLeft);
		uint32 lop_bottomLeft_w = MIN(width, bottomLeft);
		uint32 lop_bottomRight_h = MIN(height, bottomRight);
		uint32 lop_bottomRight_w = MIN(width, bottomRight);

		uint32 tl_loc, tr_loc, bl_loc, br_loc;
		float tl_dis, tr_dis, bl_dis, br_dis;
		uint8 onePxlen = bitmap.getOnePixelLength();
		uint32 stride = bitmap.getStride();
		uint8 *px = (uint8*)bitmap.getPixels();

#if USE_OPENMP
#pragma omp parallel num_threads(4)  
		{
#pragma omp sections
			{
#pragma omp section
				{  //printf("section 1 id: %d\n", omp_get_thread_num());
#endif
				   //top_left
					for (int h = 0; h < lop_topLeft_h; h++)
					{
						for (int w = 0; w < lop_topLeft_w; w++)
						{
							tl_dis = UtilMath::distance(IGPPoint(w, h), IGPPoint(topLeft, topLeft));//四舍五入
							if (tl_dis > topLeft)
							{
								tl_loc = h*stride + w*onePxlen;
								px[tl_loc] = (topLeftColor & 0x00ff0000) >> 16;
								px[tl_loc + 1] = (topLeftColor & 0x0000ff00) >> 8;
								px[tl_loc + 2] = (topLeftColor & 0x000000ff);
							}
						}
					}
#if USE_OPENMP
				}
#pragma omp section
				{ //printf("section 2 id: %d\n", omp_get_thread_num());
#endif
					for (int h = 0; h < lop_topRight_h; h++)
					{
						for (int w = width - lop_topRight_w; w < width; w++)
						{
							tr_dis = UtilMath::distance(IGPPoint(w, h), IGPPoint(width - topRight, topRight));
							if (tr_dis > topRight)
							{
								tr_loc = h*stride + w*onePxlen;
								px[tr_loc] = (topRightColor & 0x00ff0000) >> 16;
								px[tr_loc + 1] = (topRightColor & 0x0000ff00) >> 8;
								px[tr_loc + 2] = (topRightColor & 0x000000ff);
							}
						}
					}
#if USE_OPENMP
				}
#pragma omp section
				{ //printf("section 3 id: %d\n", omp_get_thread_num());
#endif
					for (int h = height - lop_bottomLeft_h; h < height; h++)
					{
						for (int w = 0; w < lop_bottomLeft_w; w++)
						{
							bl_dis = UtilMath::distance(IGPPoint(w, h), IGPPoint(bottomLeft, height - bottomLeft));//四舍五入
							if (bl_dis > bottomLeft)
							{
								bl_loc = h*stride + w*onePxlen;
								px[bl_loc] = (bottomLeftColor & 0x00ff0000) >> 16;
								px[bl_loc + 1] = (bottomLeftColor & 0x0000ff00) >> 8;
								px[bl_loc + 2] = (bottomLeftColor & 0x000000ff);
							}
						}
					}

#if USE_OPENMP
				}
#pragma omp section
				{ //printf("section 4 id: %d\n", omp_get_thread_num());
#endif
					for (int h = height - lop_bottomRight_h; h < height; h++)
					{
						for (int w = width - lop_bottomRight_w; w < width; w++)
						{
							br_dis = UtilMath::distance(IGPPoint(w, h), IGPPoint(width - bottomRight, height - bottomRight));//四舍五入
							if (br_dis > bottomRight)
							{
								br_loc = h*stride + w*onePxlen;
								px[br_loc] = (bottomRightColor & 0x00ff0000) >> 16;
								px[br_loc + 1] = (bottomRightColor & 0x0000ff00) >> 8;
								px[br_loc + 2] = (bottomRightColor & 0x000000ff);
							}
						}
					}
#if USE_OPENMP
				}
			}
		}
#endif
		return CODE_SUCESS;
	}

	int8 FilletModule::FilletOwnRGBA(IGPBitmap& bitmap,
		const uint32 &topLeft, const COLOR_ARGB &topLeftColor,
		const uint32 &topRight, const COLOR_ARGB &topRightColor,
		const uint32 &bottomLeft, const COLOR_ARGB &bottomLeftColor,
		const uint32 &bottomRight, const COLOR_ARGB &bottomRightColor)
	{
		uint32 width = bitmap.getWidth();
		uint32 height = bitmap.getHeight();
		//处理圆角半径大于宽高特殊情况
		uint32 lop_topLeft_h = MIN(height, topLeft);
		uint32 lop_topLeft_w = MIN(width, topLeft);
		uint32 lop_topRight_h = MIN(height, topRight);
		uint32 lop_topRight_w = MIN(width, topRight);
		uint32 lop_bottomLeft_h = MIN(height, bottomLeft);
		uint32 lop_bottomLeft_w = MIN(width, bottomLeft);
		uint32 lop_bottomRight_h = MIN(height, bottomRight);
		uint32 lop_bottomRight_w = MIN(width, bottomRight);

		uint32 tl_loc, tr_loc, bl_loc, br_loc;
		float tl_dis, tr_dis, bl_dis, br_dis;
		uint8 onePxlen = bitmap.getOnePixelLength();
		uint32 stride = bitmap.getStride();
		uint8 *px = (uint8*)bitmap.getPixels();

#if USE_OPENMP
#pragma omp parallel num_threads(4)  
		{
#pragma omp sections
			{
#pragma omp section
				{  //printf("section 1 id: %d\n", omp_get_thread_num());
#endif
				   //top_left
					for (int h = 0; h < lop_topLeft_h; h++)
					{
						for (int w = 0; w < lop_topLeft_w; w++)
						{
							tl_dis = UtilMath::distance(IGPPoint(w, h), IGPPoint(topLeft, topLeft));//四舍五入
							if (tl_dis > topLeft)
							{
								tl_loc = h*stride + w*onePxlen;
								px[tl_loc] = (topLeftColor & 0x00ff0000) >> 16;
								px[tl_loc + 1] = (topLeftColor & 0x0000ff00) >> 8;
								px[tl_loc + 2] = (topLeftColor & 0x000000ff);
								px[tl_loc + 3] = (topLeftColor & 0xff000000) >> 24;
							}
						}
					}
#if USE_OPENMP
				}
#pragma omp section
				{ //printf("section 2 id: %d\n", omp_get_thread_num());
#endif
					for (int h = 0; h < lop_topRight_h; h++)
					{
						for (int w = width - lop_topRight_w; w < width; w++)
						{
							tr_dis = UtilMath::distance(IGPPoint(w, h), IGPPoint(width - topRight, topRight));
							if (tr_dis > topRight)
							{
								tr_loc = h*stride + w*onePxlen;
								px[tr_loc] = (topRightColor & 0x00ff0000) >> 16;
								px[tr_loc + 1] = (topRightColor & 0x0000ff00) >> 8;
								px[tr_loc + 2] = (topRightColor & 0x000000ff);
								px[tr_loc + 3] = (topRightColor & 0xff000000) >> 24;
							}
						}
					}
#if USE_OPENMP
				}
#pragma omp section
				{ //printf("section 3 id: %d\n", omp_get_thread_num());
#endif
					for (int h = height - lop_bottomLeft_h; h < height; h++)
					{
						for (int w = 0; w < lop_bottomLeft_w; w++)
						{
							bl_dis = UtilMath::distance(IGPPoint(w, h), IGPPoint(bottomLeft, height - bottomLeft));//四舍五入
							if (bl_dis > bottomLeft)
							{
								bl_loc = h*stride + w*onePxlen;
								px[bl_loc] = (bottomLeftColor & 0x00ff0000) >> 16;
								px[bl_loc + 1] = (bottomLeftColor & 0x0000ff00) >> 8;
								px[bl_loc + 2] = (bottomLeftColor & 0x000000ff);
								px[bl_loc + 3] = (bottomLeftColor & 0xff000000) >> 24;
							}
						}
					}

#if USE_OPENMP
				}
#pragma omp section
				{ //printf("section 4 id: %d\n", omp_get_thread_num());
#endif
					for (int h = height - lop_bottomRight_h; h < height; h++)
					{
						for (int w = width - lop_bottomRight_w; w < width; w++)
						{
							br_dis = UtilMath::distance(IGPPoint(w, h), IGPPoint(width - bottomRight, height - bottomRight));//四舍五入
							if (br_dis > bottomRight)
							{
								br_loc = h*stride + w*onePxlen;
								px[br_loc] = (bottomRightColor & 0x00ff0000) >> 16;
								px[br_loc + 1] = (bottomRightColor & 0x0000ff00) >> 8;
								px[br_loc + 2] = (bottomRightColor & 0x000000ff);
								px[br_loc + 3] = (bottomRightColor & 0xff000000) >> 24;
							}
						}
					}
#if USE_OPENMP
				}
			}
		}
#endif
		return CODE_SUCESS;
	}
}
