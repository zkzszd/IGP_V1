//
//  BlackAndWhiteModule.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/7/17.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "BlackAndWhiteModule.hpp"

namespace zkzszd {
    
	int8 BlackAndWhiteModule::processGray(IGPBitmap &bitmap, function<float(IGPBitmap&)> threshol_method)
	{
		//if (bitmap.image_format != GRAY_ONE_CHANNEL || bitmap.image_format != GRAY_THREE_CHANNEL)
		//{
		//	return -1;
		//}

		float threshol = threshol_method(bitmap);
		if (threshol > 255)
			threshol = 255;
		if (threshol < 0)
			threshol = 0;
		uint8* px = (uint8*)bitmap.getPixels();
		uint32 width = bitmap.getWidth();
		uint32 height = bitmap.getHeight();
		uint32 oneLength = bitmap.getOnePixelLength();

		if (bitmap.getFormat() == GRAY_ONE_CHANNEL)
		{
			for (int32 h = 0; h < height; h++)
			{
				uint8 *line_px = px + h*bitmap.getStride();
				for (uint32 w = 0; w < width; w++)
				{
					if (line_px[w] > threshol)
					{
						line_px[w] = 255;
					}
					else
					{
						line_px[w] = 0;
					}
				}
			}
		}
		else
		{
#pragma omp parallel for
			for (int32 h = 0; h < height; h++)
			{
				for (uint32 w = 0; w < width; w++)
				{
					uint32 loc = (h*width + w)*oneLength;
					if (px[loc] > threshol)
					{
						px[loc] = 255;
						px[loc + 1] = 255;
						px[loc + 2] = 255;
					}
					else
					{
						px[loc] = 0;
						px[loc + 1] = 0;
						px[loc + 2] = 0;
					}
				}
			}
		}
		return CODE_SUCESS;
	}

	float BlackAndWhiteModule::ThresholAverage::operator()(IGPBitmap &bitmap)
	{
		uint32 total = 0;
		int32 width = bitmap.getWidth();
		int32 height = bitmap.getHeight();
		uint8 *px = (uint8 *)bitmap.getPixels();
		int32 onePxLength = bitmap.getOnePixelLength();
#pragma omp parallel for reduction(+:total)
		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
				int32 loc = (h*width + w)*onePxLength;
				total += px[loc];
			}
		}
		return (float)total / (width*height);
	}

	float BlackAndWhiteModule::ThresholdRockBottom::operator()(IGPBitmap &bitmap)
	{
		int32 width = bitmap.getWidth();
		int32 height = bitmap.getHeight();
		int8 *px = (int8 *)bitmap.getPixels();
		int32 onePxLength = bitmap.getOnePixelLength();
		int32 histogramArray[256] = { 0 };	        //直方图 0 - 255个值出现的个数
		int32 totalPixels = width * height;
		float densityArray[256] = { 0 };			 //密度
		int bestT = 0;

//#pragma omp parallel for
		for (int32 h = 0; h < height; h++)
		{
			for (int32 w = 0; w < width; w++)
			{
				histogramArray[px[h*width+w]]++;
			}
		}

		for (int i = 0; i < 256; i++)
		{
			densityArray[i] = histogramArray[i] / (float)totalPixels;
		}

		double u0 = 0;
		double u1 = 0;
		double w0 = 0;
		double w1 = 0;
		double bestDeviation = 0;
		double temp;

		for (int i = 0; i < 256; i++)
		{
			w0 = 0;
			w1 = 0;
			u0 = 0;
			u1 = 0;

			for (int j = 0; j <= i; j++)
			{
				w0 += densityArray[j];
				u0 += j * densityArray[j];
			}

			for (int j = i + 1; j < 256; j++)
			{
				w1 += densityArray[j];

				u1 += j * densityArray[j];
			}

			u0 = u0 / w0;
			u1 = u1 / w1;
			temp = w0 * w1 * (u0 - u1) * (u0 - u1);

			if (temp > bestDeviation)
			{
				bestT = i;
				bestDeviation = temp;
			}
		}

		if (bestT < 0)
			bestT = 0;
		if (bestT > 255)
			bestT = 255;

		return bestT;
	}

	float BlackAndWhiteModule::Otsu::operator()(IGPBitmap &bitmap)
	{
		float histogram[256] = { 0 };
		for (int i = 0; i<bitmap.height; i++) {
			unsigned char* p = (unsigned char*)bitmap.pixels + bitmap.stride*i;
			for (int j = 0; j<bitmap.width; j++) {
				histogram[*p]++;
				p += bitmap.one_pixel_length;
			}
		}
		//normalize histogram  
		int size = bitmap.height*bitmap.width;
		for (int i = 0; i<256; i++) {
			histogram[i] = histogram[i] / size;
		}

		//average pixel value  
		float avgValue = 0;
		for (int i = 0; i<256; i++) {
			avgValue += i*histogram[i];
		}

		int threshold;
		float maxVariance = 0;
		float w = 0, u = 0;
		for (int i = 0; i<256; i++) {
			w += histogram[i];
			u += i*histogram[i];

			float t = avgValue*w - u;
			float variance = t*t / (w*(1 - w));
			if (variance>maxVariance) {
				maxVariance = variance;
				threshold = i;
			}
		}
		return threshold;
	}
}
