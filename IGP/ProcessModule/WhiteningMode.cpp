#include "./WhiteningMode.hpp"
#include <math.h>
#include "../Typedef/My_define.h"

namespace zkzszd
{
	//new_px = 255*log(px*(b-1)+1)/log(b)
	RET_CODE WhiteningMode::WhiteningWithLog(IGPBitmap& bitmap, float bata)
	{
		//1.0 < bata < 10  log(1) = 0 log(10) = 1
		if (bata <= 1.0 || bata >= 10.0)
		{
			return RET_ERR_PARAMISMATCH;
		}
		float divisor = logf(bata);  //函数的除数  log(bata)
		uint8 bata_1 = bata - 1;
		int32 width = bitmap.getWidth();
		int32 height = bitmap.getHeight();
		int32 stride = bitmap.getStride();
		int32 onePxLength = bitmap.getOnePixelLength();
		uint8* px = (uint8*)bitmap.getPixels();

		for (int32 h = 0; h < height; h++)
		{
			for (int32 w = 0; w < width; w++)
			{
				int32 loc = h*stride + w*onePxLength;
				////log求出来的是小数，精确的话需要进行四舍五入取整

				px[loc] = (uint8)((255 * logf(div255_f(px[loc]) * bata_1 + 1)) / divisor);
				px[loc + 1] = (uint8)((255 * logf(div255_f(px[loc + 1]) * bata_1 + 1)) / divisor);
				px[loc + 2] = (uint8)(255 * (logf(div255_f(px[loc + 2]) * bata_1 + 1)) / divisor);
			}
		}
		return RET_OK;
	}

	RET_CODE WhiteningMode::WhiteningWithLog(IGPBitmap& bitmap, float bata, IGPBitmap& map_bitmap)
	{
		//1.0 < bata < 10  log(1) = 0 log(10) = 1
		if (bata <= 1.0 || bata >= 10.0)
		{
			return RET_ERR_PARAMISMATCH;
		}
		if (map_bitmap.getFormat() != GRAY_ONE_CHANNEL)
		{
			return RET_ERR_PARAMISMATCH;
		}
		float divisor = logf(bata);  //函数的除数  log(bata)
		uint8 bata_1 = bata - 1;
		int32 width = bitmap.getWidth();
		int32 height = bitmap.getHeight();
		int32 stride = bitmap.getStride();
		int32 onePxLength = bitmap.getOnePixelLength();
		uint8* px = (uint8*)bitmap.getPixels();

		for (int32 h = 0; h < height; h++)
		{
			uint8* map_px = (uint8*)map_bitmap.getPixels() + h*map_bitmap.getStride();
			for (int32 w = 0; w < width; w++)
			{
				int32 loc = h*stride + w*onePxLength;
				if (map_px[w] != 0)
				{
					////log求出来的是小数，精确的话需要进行四舍五入取整

					//float f_r, f_g, f_b;
					//f_r = ((255 * logf(div255_f(px[loc]) * bata_1 + 1)) / divisor);
					//f_g = ((255 * logf(div255_f(px[loc + 1]) * bata_1 + 1)) / divisor);
					//f_b = (255 * (logf(div255_f(px[loc + 2]) * bata_1 + 1)) / divisor);
					//px[loc] = f_r > 255 ? 255 : f_r;
					//px[loc + 1] = f_g > 255 ? 255 : f_g;
					//px[loc + 2] = f_b > 255 ? 255 : f_b;

					px[loc] = (uint8)((255 * logf(div255_f(px[loc]) * bata_1 + 1)) / divisor);
					px[loc + 1] = (uint8)((255 * logf(div255_f(px[loc + 1]) * bata_1 + 1)) / divisor);
					px[loc + 2] = (uint8)(255 * (logf(div255_f(px[loc + 2]) * bata_1 + 1)) / divisor);
				}
			}
		}
		return RET_OK;
	}
}