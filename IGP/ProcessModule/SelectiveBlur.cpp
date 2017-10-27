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

		ColHist += Radius * 256;	    	//	����ƫ�� ���ͷſռ��ʱ��ע��ָ�ƫ�ƣ�

		int32 *RowOffset, *ColOffSet;
		ColOffSet = (int32 *)(colHistogram.data) + Radius;
		RowOffset = (int32 *)(rowHistogram.data) + Radius;

		unsigned char *LinePS, *LinePD;

		for (int32 Y = 0; Y < height; Y++)
		{
			if (Y == 0)											//	��һ�е���ֱ��ͼ,Ҫ��ͷ����
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
			else															//	�����е���ֱ��ͼ�����¾Ϳ�����
			{
				LinePS = src_data + ColOffSet[Y - Radius - 1] * width;
				for (int32 X = -Radius; X < width + Radius; X++)			// ɾ���Ƴ���Χ�ڵ���һ�е�ֱ��ͼ����
				{
					ColHist[X * 256 + LinePS[RowOffset[X]]]--;
				}

				LinePS = src_data + ColOffSet[Y + Radius] * width;
				for (int32 X = -Radius; X < width + Radius; X++)		// ���ӽ��뷶Χ�ڵ���һ�е�ֱ��ͼ����
				{
					ColHist[X * 256 + LinePS[RowOffset[X]]]++;
				}
			}

			memset(Hist, 0, 256 * sizeof(uint16));						//	ÿһ��ֱ��ͼ����������

			LinePS = src_data + Y * width;
			LinePD = des_data + Y * width;

			for (int32 X = 0; X < width; X++)
			{
				if (X == 0)
				{
					for (int32 K = -Radius; K <= Radius; K++)			//	�е�һ�����أ���Ҫ���¼���	
																		//�޷��Ŷ�����ֱ��ͼ������ӣ�Y = X + Y
						HistgramAddShort(ColHist + K * 256, Hist);
				}
				else
				{
					//�޷��Ŷ�����ֱ��ͼ������Ӽ���Z = Z + Y - X
					HistgramSubAddShort(ColHist + RowOffset[X - Radius - 1] * 256, ColHist + RowOffset[X + Radius] * 256, Hist);  //	�����������أ�����ɾ�������ӾͿ�����
				}
				Calc(Hist, LinePS[0], LinePD, Threshold);
				LinePS++;
				LinePD++;
			}
		}

		ColHist -= Radius * 256;		//	�ָ�ƫ�Ʋ������ͷſռ�
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

		RowHistogram rowHistogram;			//��ӳ���
		ColHistogram colHistogram;			//��ӳ���
		// ����ָ���ı�Եģʽ������չ������������ֵ
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