#include "SelectiveBlur.hpp"
#include "../Typedef/MyTypedef.h"
#include "../Util/IGPUtility.h"
#include <iostream>

using namespace std;

namespace zkzszd
{

	void Calc(unsigned short *Hist, int Intensity, unsigned char *&Pixel, int Threshold)
	{
		int K, Low, High, Sum = 0, Weight = 0;
		Low = Intensity - Threshold; High = Intensity + Threshold;
		if (Low < 0) Low = 0;
		if (High > 255) High = 255;
		for (K = Low; K <= High; K++)
		{
			Weight += Hist[K];
			Sum += Hist[K] * K;
		}
		if (Weight != 0) *Pixel = Sum / Weight;
	}

	RET_CODE selectBlurOneChannel(uint8* src_data, uint8* des_data, int32 width, int32 height, RowHistogram& rowHistogram,
		ColHistogram& colHistogram, int32 Radius, int32 Threshold)
	{
		uint16 *ColHist = (uint16 *)malloc(256 * (width + 2 * Radius) * sizeof(uint16));
		if (ColHist == NULL)
		{
			return RET_ERR_OUTOFMEMORY;
		}
		memset(ColHist, 0, 256 * (width + 2 * Radius) * sizeof(uint16));

		uint16 *Hist = (uint16 *)malloc(256 * sizeof(uint16));
		if (Hist == NULL) { return RET_ERR_OUTOFMEMORY; }

		ColHist += Radius * 256;	    	//	进行偏移 （释放空间的时候注意恢复偏移）

		int32 *RowOffset, *ColOffSet;
		ColOffSet = (int32 *)(colHistogram.data) + Radius;
		RowOffset = (int32 *)(rowHistogram.data) + Radius;

		unsigned char *LinePS, *LinePD;

		for (int32 Y = 0; Y < height; Y++)
		{
			if (Y == 0)											//	第一行的列直方图,要重头计算
			{
				for (int32 K = -Radius; K <= Radius; K++)
				{
					LinePS = src_data + ColOffSet[K] * width;
					for (int32 X = -Radius; X < width + Radius; X++)
					{
						ColHist[X * 256 + LinePS[RowOffset[X]]]++;
					}
				}
			}
			else															//	其他行的列直方图，更新就可以了
			{
				LinePS = src_data + ColOffSet[Y - Radius - 1] * width;
				for (int32 X = -Radius; X < width + Radius; X++)			// 删除移出范围内的那一行的直方图数据
				{
					ColHist[X * 256 + LinePS[RowOffset[X]]]--;
				}

				LinePS = src_data + ColOffSet[Y + Radius] * width;
				for (int32 X = -Radius; X < width + Radius; X++)		// 增加进入范围内的那一行的直方图数据
				{
					ColHist[X * 256 + LinePS[RowOffset[X]]]++;
				}
			}

			memset(Hist, 0, 256 * sizeof(uint16));						//	每一行直方图数据清零先

			LinePS = src_data + Y * width;
			LinePD = des_data + Y * width;

			for (int32 X = 0; X < width; X++)
			{
				if (X == 0)
				{
					for (int32 K = -Radius; K <= Radius; K++)			//	行第一个像素，需要重新计算	
																		//无符号短整形直方图数据相加，Y = X + Y
						HistgramAddShort(ColHist + K * 256, Hist);
				}
				else
				{
					//无符号短整形直方图数据相加减，Z = Z + Y - X
					HistgramSubAddShort(ColHist + RowOffset[X - Radius - 1] * 256, ColHist + RowOffset[X + Radius] * 256, Hist);  //	行内其他像素，依次删除和增加就可以了
				}
				Calc(Hist, LinePS[0], LinePD, Threshold);
				LinePS++;
				LinePD++;
			}
		}

		ColHist -= Radius * 256;		//	恢复偏移操作后释放空间
		free(ColHist);
		free(Hist);

		return RET_OK;
	}

	int32 SelectiveBlur::selectBlur(IGPBitmapChannel &bitmapChannel, IGPBitmapChannel &des_btChannel, int32 Radius, int32 Threshold, EdgeMode Edge)
	{
		if (Radius >= 127)
			Radius = 126;
		if (Threshold < 2)
			Threshold = 2;
		else if (Threshold > 255)
			Threshold = 255;

		RowHistogram rowHistogram;			//行映射表
		ColHistogram colHistogram;			//列映射表
		// 按照指定的边缘模式计算扩展后各坐标的有理值
		IGPUtility::ValidCoordinateRow(rowHistogram,bitmapChannel._width,Radius,Radius, Edge);
		IGPUtility::ValidCoordinateCol(colHistogram,bitmapChannel._height,Radius,Radius, Edge);

		selectBlurOneChannel(bitmapChannel._R_channel, des_btChannel._R_channel, bitmapChannel._width, bitmapChannel._height, rowHistogram,colHistogram,Radius,Threshold);
		selectBlurOneChannel(bitmapChannel._G_channel, des_btChannel._G_channel, bitmapChannel._width, bitmapChannel._height, rowHistogram, colHistogram, Radius, Threshold);
		selectBlurOneChannel(bitmapChannel._B_channel, des_btChannel._B_channel, bitmapChannel._width, bitmapChannel._height, rowHistogram, colHistogram, Radius, Threshold);

		return RET_OK;
	}

	SelectiveBlur::SelectiveBlur()
	{

	}


	SelectiveBlur::~SelectiveBlur()
	{
	}
}