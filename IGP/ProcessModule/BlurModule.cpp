//
//  BlurModule.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/17.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "BlurModule.hpp"
#include <stdlib.h>
#include "../Typedef/_struct.hpp"

namespace zkzszd
{
    uint8 BlurModule::BlurOwn(IGPBitmap &bitmap,int32 radius)
    {
        uint32 w = bitmap.getWidth();
        uint32 h = bitmap.getHeight();
		Color_RGB* pix = (Color_RGB*)bitmap.getPixels();
        int wm = w - 1;
        int hm = h - 1;
        int wh = w * h;
        int div = radius + radius + 1;
        
        short *r = (short *) malloc(wh * sizeof(short));
        short *g = (short *) malloc(wh * sizeof(short));
        short *b = (short *) malloc(wh * sizeof(short));
        int *vmin = (int *) malloc(MAX(w, h) * sizeof(int));
        
        int divsum = (div + 1) >> 1;
        divsum *= divsum;
        short *dv = (short *) malloc(256 * divsum * sizeof(short));
        for (int i = 0; i < 256 * divsum; i++) {
            dv[i] = (short) (i / divsum);
        }
        
		int yp, yi, yw;
        yw = yi = 0;
        
        int(*stack)[3] = (int (*)[3]) malloc(div * 3 * sizeof(int));
        int r1 = radius + 1;

		//暂时没有找到优化方法
//#pragma omp parallel for private(yp, yi, yw)
        for (int y = 0; y < h; y++)
        {
			int routsum = 0, goutsum = 0, boutsum = 0;
			int rinsum = 0, ginsum = 0, binsum = 0;
			int rsum = 0, gsum = 0, bsum = 0;
			int *sir;
			struct Color_RGB *p;
			int rbs;
			int stackpointer, stackstart;
            for (int i = -radius; i <= radius; i++)
            {
                p = pix+(yi + (MIN(wm, MAX(i, 0))));
                sir = stack[i + radius];
                sir[0] = p->R;
                sir[1] = p->G;
                sir[2] = p->B;
                
                rbs = r1 - ABS(i);
                rsum += sir[0] * rbs;
                gsum += sir[1] * rbs;
                bsum += sir[2] * rbs;
                if (i > 0) {
                    rinsum += sir[0];
                    ginsum += sir[1];
                    binsum += sir[2];
                }
                else {
                    routsum += sir[0];
                    goutsum += sir[1];
                    boutsum += sir[2];
                }
            }
            stackpointer = radius;
            
            for (int x = 0; x < w; x++)
            {
                r[yi] = dv[rsum];
                g[yi] = dv[gsum];
                b[yi] = dv[bsum];
                
                rsum -= routsum;
                gsum -= goutsum;
                bsum -= boutsum;
                
                stackstart = stackpointer - radius + div;
                sir = stack[stackstart % div];
                
                routsum -= sir[0];
                goutsum -= sir[1];
                boutsum -= sir[2];
                
                if (y == 0) {
                    vmin[x] = MIN(x + radius + 1, wm);
                }
                p = pix+(yw + vmin[x]);
                
                sir[0] = p->R;
                sir[1] = p->G;
                sir[2] = p->B;
                
                rinsum += sir[0];
                ginsum += sir[1];
                binsum += sir[2];
                
                rsum += rinsum;
                gsum += ginsum;
                bsum += binsum;
                
                stackpointer = (stackpointer + 1) % div;
                sir = stack[(stackpointer) % div];
                
                routsum += sir[0];
                goutsum += sir[1];
                boutsum += sir[2];
                
                rinsum -= sir[0];
                ginsum -= sir[1];
                binsum -= sir[2];
                
                yi++;
            }
            yw += w;
        }
        
        for (int x = 0; x < w; x++)
        {
			int rinsum = 0, ginsum = 0, binsum = 0;
			int routsum = 0, goutsum = 0, boutsum = 0;
			int rsum = 0, gsum = 0, bsum = 0;
			int *sir;
			int rbs, loc;
			int stackpointer, stackstart;
            yp = -radius * w;
            for (int i = -radius; i <= radius; i++)
            {
                yi = MAX(0, yp) + x;
                
                sir = stack[i + radius];
                
                sir[0] = r[yi];
                sir[1] = g[yi];
                sir[2] = b[yi];
                
                rbs = r1 - ABS(i);
                
                rsum += r[yi] * rbs;
                gsum += g[yi] * rbs;
                bsum += b[yi] * rbs;
                
                if (i > 0) {
                    rinsum += sir[0];
                    ginsum += sir[1];
                    binsum += sir[2];
                }
                else {
                    routsum += sir[0];
                    goutsum += sir[1];
                    boutsum += sir[2];
                }
                
                if (i < hm) {
                    yp += w;
                }
            }
            yi = x;
            stackpointer = radius;
            for (int y = 0; y < h; y++)
            {
                // Preserve alpha channel: ( 0xff000000 & pix[yi] )
                //pix[yi] = (0xff000000 & pix[yi]) | (dv[rsum] << 16) | (dv[gsum] << 8) | dv[bsum];
                
                pix[yi].R = dv[rsum];
                pix[yi].G = dv[gsum];
                pix[yi].B = dv[bsum];
                
                rsum -= routsum;
                gsum -= goutsum;
                bsum -= boutsum;
                
                stackstart = stackpointer - radius + div;
                sir = stack[stackstart % div];
                
                routsum -= sir[0];
                goutsum -= sir[1];
                boutsum -= sir[2];
                
                if (x == 0) {
                    vmin[y] = MIN(y + r1, hm) * w;
                }
                loc = x + vmin[y];
                
                sir[0] = r[loc];
                sir[1] = g[loc];
                sir[2] = b[loc];
                
                rinsum += sir[0];
                ginsum += sir[1];
                binsum += sir[2];
                
                rsum += rinsum;
                gsum += ginsum;
                bsum += binsum;
                
                stackpointer = (stackpointer + 1) % div;
                sir = stack[stackpointer];
                
                routsum += sir[0];
                goutsum += sir[1];
                boutsum += sir[2];
                
                rinsum -= sir[0];
                ginsum -= sir[1];
                binsum -= sir[2];
                
                yi += w;
            }
        }
        
        free(r);
        free(g);
        free(b);
        free(vmin);
        free(dv);
        free(stack);
        
        return CODE_SUCESS;
    }

	void BlurModule::gaussian(IGPBitmap& inBitmap, IGPBitmap& outBitmap, BaseRect& rect, uint32 radius, function<float(float)> nexus_type, uint32 shade_width)
	{
		uint8_t* outPixels = (uint8_t*)outBitmap.getPixels();
		uint8_t* inPixels = (uint8_t*)inBitmap.getPixels();
		uint32_t x, y;
		uint8_t *tInPixel, *tOutPixel;
		float tR = 0.0, tG = 0.0, tB = 0.0, tCount = 0.0;
		float dif, gauss;
		int startx, endx, starty, endy;
		int m;
		uint32_t top, left, right, bottom;
		top = rect.min_y;
		bottom = rect.max_y;
		left = rect.min_x;
		right = rect.max_x;
		if (top < 0)
		{
			top = 0;
		}
		if (bottom > inBitmap.getHeight() - 1) {
			bottom = inBitmap.getHeight() - 1;
		}
		if (left < 0) {
			left = 0;
		}
		if (right > inBitmap.getWidth() - 1) {
			right = inBitmap.getWidth() - 1;
		}
		//The dimension of X
		int32 temp = (bottom - top + 1) * (right - left + 1);
		IGPPoint *tDo = new IGPPoint[temp]();
		uint32_t tDoLen = 0;
		IGPPoint point;
		float distance;                 //边缘距离
		uint32 range = radius;          //新的模糊半径

		for (y = top; y <= bottom; y++)
		{
			for (x = left; x <= right; x++)
			{
				point.set(x, y);
				if (!rect.isContain(point))
				{
					continue;
				}

				//                    if(shade_width > 0)
				//                    {
				//                        distance = rect.dis_border(point);
				//                        //在渐变效果内
				//                        if(distance < shade_width)
				//                        {
				//                            range = radius*nexus_type(distance/shade_width);
				//                            printf("range = %d \t %f\n",range,nexus_type(distance/shade_width));
				//                        }
				//                    }

				tDo[tDoLen].set(x, y);
				tDoLen++;

				tOutPixel = outPixels + (y*outBitmap.getStride() + x*outBitmap.getOnePixelLength());
				startx = (x < range ? -x : -range);
				endx = ((inBitmap.getWidth() <= x + range) ? (inBitmap.getWidth() - x - 1) : range);

				//x dimension
				tR = tG = tB = tCount = 0.0;
				for (m = startx; m <= endx; m++)
				{
					tInPixel = inPixels + (y*inBitmap.getStride() + (x + m)*inBitmap.getOnePixelLength());
					dif = m*m;
					gauss = exp(-dif / (2 * range));
					tR += gauss * *(tInPixel + 0);
					tG += gauss * *(tInPixel + 1);
					tB += gauss * *(tInPixel + 2);
					tCount += gauss;
				}
				*(tOutPixel + 0) = tR / tCount;
				*(tOutPixel + 1) = tG / tCount;
				*(tOutPixel + 2) = tB / tCount;
			}
		}

		//y dimension
		uint32_t ind = 0;
		for (ind = 0; ind < tDoLen; ind++)
		{
			point = tDo[ind];
			tOutPixel = outPixels + (point.y*outBitmap.getStride() + point.x*outBitmap.getOnePixelLength());
			//tOutPixel = (uint8_t* )*outPixels + (p.y * bitmapInfo.width + p.x) * 4;
			starty = (point.y < range ? -point.y : -range);

			endy = ((inBitmap.getHeight() <= point.y + range) ? (inBitmap.getHeight() - point.y - 1) : range);
			tR = tG = tB = tCount = 0.0;
			for (m = starty; m <= endy; m++)
			{
				tInPixel = inPixels + ((point.y + m)*inBitmap.getStride() + point.x*inBitmap.getOnePixelLength());
				//tInPixel = (uint8_t* )*outPixels + ((p.y + m) * bitmapInfo.width + p.x) * 4;
				dif = m*m;
				gauss = exp(-dif / (2 * range));
				tR += gauss * *(tInPixel + 0);
				tG += gauss * *(tInPixel + 1);
				tB += gauss * *(tInPixel + 2);
				tCount += gauss;
			}
			*(tOutPixel + 0) = tR / tCount;
			*(tOutPixel + 1) = tG / tCount;
			*(tOutPixel + 2) = tB / tCount;
		}
		delete[]tDo;
	}
}
