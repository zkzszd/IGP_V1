#include "ProcessBase.hpp"
#include "../Util/UtilMath.hpp"
#include <math.h>

namespace zkzszd
{

	RET_CODE ProcessBase::ProcessWithLayer(IGPBitmap& bitmap, Color_RGB &layer_color_rgb)
	{
		int32 height = bitmap.getHeight();
		int32 width = bitmap.getWidth();
		uint8* px = (uint8*)bitmap.getPixels();
		int32 onePxLength = bitmap.getOnePixelLength();
		int32 stride = bitmap.getStride();

		for (int32 h = 0; h < height; h++)
		{
			for (int32 w = 0; w < width; w++)
			{
				int32 loc = h*stride + w*onePxLength;
				int16 temp_r, temp_g, temp_b;
				temp_r = px[loc] + layer_color_rgb.R ;
				temp_g = px[loc + 1] + layer_color_rgb.G;
				temp_b = px[loc + 2] + layer_color_rgb.B;

				//防止增加分量后出现大于255情况
				temp_r = temp_r > 255 ? 255 : temp_r;
				temp_g = temp_g > 255 ? 255 : temp_g;
				temp_b = temp_b > 255 ? 255 : temp_b;

				px[loc] = temp_r;
				px[loc + 1] = temp_g;
				px[loc + 2] = temp_b;
			}
		}

		return RET_OK;
	}

	RET_CODE ProcessBase::getFaceAreaByRGB(IGPBitmap &bitmap, IGPBitmap &area_bitmap)
	{
		if (area_bitmap.pixels != nullptr)
		{
			free(area_bitmap.pixels);
		}
		area_bitmap.width = bitmap.width;
		area_bitmap.height = bitmap.height;
		area_bitmap.stride = bitmap.width;
		area_bitmap.image_format = GRAY_ONE_CHANNEL;
		area_bitmap.pixels = (uint8*)malloc(area_bitmap.height*area_bitmap.width*sizeof(uint8));
		memset(area_bitmap.pixels, 0, area_bitmap.height*area_bitmap.width);

		for (int32 h = 0; h < bitmap.height; h++)
		{
			for (int32 w = 0; w < bitmap.width; w++)
			{
				int32 loc = h*bitmap.stride + w*bitmap.one_pixel_length;
				uint8 r, b, g;
				r = bitmap.pixels[loc];
				g = bitmap.pixels[loc + 1];
				b = bitmap.pixels[loc + 2];

				if (r > 95 && g > 40 && b > 20 && UtilMath::Max(r, g, b) - UtilMath::Min(r, g, b) > 15
					&& abs(r - g) > 15 && r > g && r > b)
				{
					area_bitmap.pixels[h*area_bitmap.stride + w] = 255;
				}
			}
		}
		return RET_OK;
	}

	RET_CODE ProcessBase::getGrayIntegral(IGPBitmap &gray_bitmap, GrayIntegral &integral)
	{
		if (gray_bitmap.image_format != GRAY_ONE_CHANNEL)
		{
			return RET_ERR_PARAMISMATCH;
		}
		if (integral.width != gray_bitmap.width || integral.height != gray_bitmap.height)
		{
			integral.width = gray_bitmap.width;
			integral.height = gray_bitmap.height;
			integral.data = (uint32*)malloc(integral.width*integral.height*sizeof(uint32));
		}

		integral.data[0] = gray_bitmap.pixels[0];
		for (int32 w = 1; w < gray_bitmap.width; w++)				//第一行分开单独处理
		{
			integral.data[w] = integral.data[w - 1] + gray_bitmap.pixels[w];
		}

		for (int32 h = 1; h < gray_bitmap.height; h++)
		{
			uint8* linePS = gray_bitmap.pixels + h*gray_bitmap.stride;
			uint32* line_up_PL = integral.data + (h-1) * integral.width;
			uint32* linePD = line_up_PL + integral.width;
			//linePD[0] = line_up_PL[0] + linePS[0];	//没一行的第一个像素

			for (int32 w = 0,sum = 0; w < gray_bitmap.width; w++)
			{
				sum += linePS[w];
				linePD[w] = line_up_PL[w] + sum;
			}
		}
		return RET_OK;
	}
}