//
//  RGB_HSLAdapter.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/5.
//  Copyright 漏 2017骞?zkzszd. All rights reserved.
//

#include "SpaceAdapter.hpp"
#include "../Typedef/_struct.hpp"
#include "../IGP.hpp"
#include "../Typedef/My_define.h"

namespace zkzszd
{
    int8 SpaceAdapter::getBitmapHSL(IGPBitmap &bitmap,IGPBitmapHSL &hsl_bitmap)
    {
        hsl_bitmap.init(bitmap.getWidth(), bitmap.getHeight());
        uint8 *src_px = (uint8*)bitmap.getPixels();
        void *des_px = hsl_bitmap.getPixels();
        uint32 src_stride = bitmap.getStride();
        uint32 des_stride = sizeof(IGPHSL)*hsl_bitmap.getWidth();
        float r,g,b; 
        float max,min,total,les;
        uint8* src_px_line;
        IGPHSL* des_px_line;
        IGPHSL* igp_hsl;
        uint32 bt_h = bitmap.getHeight();
        uint32 bt_w = bitmap.getWidth();
#pragma omp parallel for private(src_px_line,des_px_line,r,g,b,max,min,total,les,igp_hsl)
        for(int32 h = 0;h < bt_h;h++)
        {
			src_px_line = src_px+src_stride*h;
			des_px_line = (IGPHSL*)((uint8*)des_px+des_stride*h);
            for(uint32 w = 0;w < bt_w; w++)
            {
                igp_hsl = des_px_line+w;
                int pos = w*bitmap.getOnePixelLength();
                r = *(src_px_line+pos)/255.0;
                g = *(src_px_line+pos+1)/255.0;
                b = *(src_px_line+pos+2)/255.0;
                //姝ゅ鍙�傚悎rgb888 鍜宺gba8888
                max = zk_MAX(r,g,b);
                min = zk_MIN(r,g,b);
                total = max + min;
                les = max - min;
                if(max == 0 && min == 0)
                {
                    igp_hsl->H = 0;
                    igp_hsl->S = 0;
                    igp_hsl->L = 0;
                    continue;
                }
                if(max == min)
                {
                    igp_hsl->H = 0;
                    igp_hsl->S = 0;
                    igp_hsl->L = max;
                    continue;
                }
                igp_hsl->L = (total)/2;
                if(igp_hsl->L <= 0.5)
                {
                    igp_hsl->S = les/(2*igp_hsl->L);
                }
                else
                {
                    igp_hsl->S = les/(2-2*igp_hsl->L);
                }
                if(max == r)
                {
                    if(g>=b)
                    {
                        igp_hsl->H = 60*(g-b)/les;
                    }
                    else
                    {
                        igp_hsl->H = 60*(g-b)/les + 360;
                    }
                }
                else if(max == g)
                {
                    igp_hsl->H = 60*(b-r)/les + 120;
                }
                else
                {
                    igp_hsl->H = 60*(r-g)/les + 240;
                }
                igp_hsl->H /=360;
            }
        }
        return CODE_SUCESS;
    }
    
    int8 SpaceAdapter::applyHSLToBitmap(IGPBitmapHSL &hsl_bitmap,IGPBitmap &bitmap)
    {
        void* src_px = hsl_bitmap.getPixels();
        void* des_px = bitmap.getPixels();
        uint32 src_stride = sizeof(IGPHSL)*hsl_bitmap.getWidth();
        uint32 des_stride = bitmap.getStride();
        IGPHSL* src_line = 0;
        uint8* des_line = 0;
        IGPHSL* igp_hsl;
        uint32 des_line_pos;
        float q,p;
		float T[3];
        uint8 one_length = bitmap.getOnePixelLength();
        uint32 hsl_w = hsl_bitmap.getWidth();
        uint32 hsl_h = hsl_bitmap.getHeight();
#pragma omp parallel for private(src_line,des_line,des_line_pos,igp_hsl,q,p,T)
        for(int32 h = 0;h<hsl_h;h++)
        {
            src_line = (IGPHSL*)((uint8*)src_px+h*src_stride);
            des_line = (uint8*)des_px+h*des_stride;
            for(uint32 w = 0;w<hsl_w;w++)
            {
                des_line_pos = w*one_length;
                igp_hsl = src_line+w;
                if(igp_hsl->S == 0)
                {
                    des_line[des_line_pos] = des_line[des_line_pos+1] = des_line[des_line_pos+2] = (uint8)(igp_hsl->L*255);
                    continue;
                }
                if(igp_hsl->L < 0.5)
                {
                    q = igp_hsl->L*(1.0+igp_hsl->S);
                }
                else
                {
                    q = igp_hsl->L + igp_hsl->S - igp_hsl->L*igp_hsl->S;
                }
                p = 2.0*igp_hsl->L - q;
                T[0] = igp_hsl->H + 0.3333333f;
                T[1] = igp_hsl->H;
                T[2] = igp_hsl->H - 0.3333333f;
                for (int i = 0; i < 3; i++)
                {
                    if (T[i] < 0) T[i] += 1.0f;
                    if (T[i] > 1) T[i] -= 1.0f;
                    if ((T[i] * 6) < 1)
                    {
                        T[i] = p + ((q - p)*6.0f*T[i]);
                    }
                    else if ((T[i] * 2.0f) < 1)
                    {
                        T[i] = q;
                    }
                    else if ((T[i] * 3.0f) < 2)
                    {
                        T[i] = p + (q - p) * ((2.0f / 3.0f) - T[i]) * 6.0f;
                    }
                    else T[i] = p;
                }
                des_line[des_line_pos] = ((T[0] > 1) ? 1 : ((T[0] < 0) ? 0 : T[0]))*255;
                des_line[des_line_pos+1] = ((T[1] > 1) ? 1 : ((T[1] < 0) ? 0 : T[1]))*255;
                des_line[des_line_pos+2] = ((T[2] > 1) ? 1 : ((T[2] < 0) ? 0 : T[2]))*255;
            }
        }
   
        return CODE_SUCESS;
    }

	uint8 SpaceAdapter::RGBToRGBA(IGPBitmap &bitmap, uint8 alpha)
	{
		if (bitmap.getFormat() == RGBA_8888)
		{
			return CODE_SUCESS;
		}
		else if (bitmap.getFormat() != RGB_888)
		{
			return CODE_FAIL;
		}
		uint32 width = bitmap.getWidth();
		uint32 height = bitmap.getHeight();
		uint8* fr_px = (uint8*)bitmap.getPixels();
		uint8* to_px = (uint8*)UtilAllocator::alloc_malloc(width*height*4);

#pragma omp parallel for
		for (int32 h = 0; h < height; h++)
		{
			for (uint32 w = 0; w < width; w++)
			{
				uint32 loc = h*width + w;
				uint8* to_loc_px = to_px + loc * 4;
				uint8* fr_loc_px = fr_px + loc * 3;
				*to_loc_px = *fr_loc_px;
				*(to_loc_px + 1) = *(fr_loc_px + 1);
				*(to_loc_px + 2) = *(fr_loc_px + 2);
				*(to_loc_px + 3) = alpha;
			}
		}
		bitmap.setFormat(RGBA_8888);
		bitmap.setPixels(to_px);
		free(fr_px);

		return CODE_SUCESS;
	}

	RET_CODE SpaceAdapter::BitmapSplit(IGPBitmap &bitmap, IGPBitmapChannel &bitmap_channel)
	{
		bitmap_channel._width = bitmap.width;
		bitmap_channel._height = bitmap.height;
		if (bitmap_channel._R_channel != nullptr)
		{
			free(bitmap_channel._R_channel);
		}
		if (bitmap_channel._G_channel != nullptr)
		{
			free(bitmap_channel._G_channel);
		}
		if (bitmap_channel._B_channel != nullptr)
		{
			free(bitmap_channel._B_channel);
		}
		if (bitmap_channel._A_channel != nullptr)
		{
			free(bitmap_channel._A_channel);
		}
		uint32 total_px = bitmap_channel._width*bitmap_channel._height;
		bitmap_channel._R_channel = (uint8*)malloc(total_px*sizeof(uint8));
		bitmap_channel._G_channel = (uint8*)malloc(total_px * sizeof(uint8));
		bitmap_channel._B_channel = (uint8*)malloc(total_px * sizeof(uint8));
		uint32 block = bitmap.width / LOP_BLOCK_SIZE;

		if (bitmap.image_format == RGBA_8888)
		{
			bitmap_channel.imageFormat = RGBA_8888;
			//如果是4通道才分配A通道内存
			bitmap_channel._A_channel = (uint8*)malloc(total_px * sizeof(uint8));
#pragma omp parallel for	//此处用opm并行并没有获得加速效果  （猜测for循环展开编译器优化成并行）
			for (int32 y = 0; y < bitmap.height; y++)
			{
				uint8* loc_src = bitmap.pixels + y*bitmap.stride;
				uint8* loc_des_R = bitmap_channel._R_channel + y*bitmap.width;
				uint8* loc_des_G = bitmap_channel._G_channel + y*bitmap.width;
				uint8* loc_des_B = bitmap_channel._B_channel + y*bitmap.width;
				uint8* loc_des_A = bitmap_channel._A_channel + y*bitmap.width;
				uint32 x;
				for (x = 0; x < bitmap.width; x += LOP_BLOCK_SIZE)
				{
					loc_des_R[0] = loc_src[0];		loc_des_G[0] = loc_src[1];		loc_des_B[0] = loc_src[2];		loc_des_A[0] = loc_src[3];
					loc_des_R[1] = loc_src[4];		loc_des_G[1] = loc_src[5];		loc_des_B[1] = loc_src[6];		loc_des_A[1] = loc_src[7];
					loc_des_R[2] = loc_src[8];		loc_des_G[2] = loc_src[9];		loc_des_B[2] = loc_src[10];		loc_des_A[2] = loc_src[11];
					loc_des_R[3] = loc_src[12];		loc_des_G[3] = loc_src[13];		loc_des_B[3] = loc_src[14];		loc_des_A[3] = loc_src[15];
					loc_des_R[4] = loc_src[16];		loc_des_G[4] = loc_src[17];		loc_des_B[4] = loc_src[18];		loc_des_A[4] = loc_src[19];
					loc_des_R[5] = loc_src[20];		loc_des_G[5] = loc_src[21];		loc_des_B[5] = loc_src[22];		loc_des_A[5] = loc_src[23];
					loc_des_R[6] = loc_src[24];		loc_des_G[6] = loc_src[25];		loc_des_B[6] = loc_src[26];		loc_des_A[6] = loc_src[27];
					loc_des_R[7] = loc_src[28];		loc_des_G[7] = loc_src[29];		loc_des_B[7] = loc_src[30];		loc_des_A[7] = loc_src[31];
					loc_des_R += 8;				loc_des_G += 8;				loc_des_B += 8;				loc_des_A += 8;				loc_src += 32;
				}
				//处理宽度不能被8整除部分
				while (x < bitmap.width)
				{
					loc_des_R[0] = loc_src[0];		loc_des_G[0] = loc_src[1];		loc_des_B[0] = loc_src[2];		loc_des_A[0] = loc_src[3];
					loc_des_R++;					loc_des_G++;					loc_des_B++;					loc_des_A++;		loc_src += 4;
					x++;
				}
			}
		}
		else if (bitmap.image_format == RGB_888)
		{ 
			bitmap_channel.imageFormat = RGB_888;
			//此处用opm并行并没有获得加速效果  （猜测for循环展开编译器优化成并行）
#pragma omp parallel for 
			for (int32 y = 0; y < bitmap.height; y++)
			{
				uint8* loc_src = bitmap.pixels + y*bitmap.stride;
				uint8* loc_des_R = bitmap_channel._R_channel + y*bitmap.width;
				uint8* loc_des_G = bitmap_channel._G_channel + y*bitmap.width;
				uint8* loc_des_B = bitmap_channel._B_channel + y*bitmap.width;
				uint32 x;
				//////测试代码
				//for (uint32 x = 0; x < bitmap.width; x++)
				//{
				//	loc_des_R[x] = loc_src[x*bitmap.one_pixel_length];
				//	loc_des_G[x] = loc_src[x*bitmap.one_pixel_length+1]; 
				//	loc_des_B[x] = loc_src[x*bitmap.one_pixel_length + 2];
				//}

				for (x = 0; x < bitmap.width; x += LOP_BLOCK_SIZE)
				{
					loc_des_R[0] = loc_src[0];		loc_des_G[0] = loc_src[1];		loc_des_B[0] = loc_src[2];
					loc_des_R[1] = loc_src[3];		loc_des_G[1] = loc_src[4];		loc_des_B[1] = loc_src[5];
					loc_des_R[2] = loc_src[6];		loc_des_G[2] = loc_src[7];		loc_des_B[2] = loc_src[8];
					loc_des_R[3] = loc_src[9];		loc_des_G[3] = loc_src[10];		loc_des_B[3] = loc_src[11];
					loc_des_R[4] = loc_src[12];		loc_des_G[4] = loc_src[13];		loc_des_B[4] = loc_src[14];
					loc_des_R[5] = loc_src[15];		loc_des_G[5] = loc_src[16];		loc_des_B[5] = loc_src[17];
					loc_des_R[6] = loc_src[18];		loc_des_G[6] = loc_src[19];		loc_des_B[6] = loc_src[20];
					loc_des_R[7] = loc_src[21];		loc_des_G[7] = loc_src[22];		loc_des_B[7] = loc_src[23];
					loc_des_R += 8;				loc_des_G += 8;				loc_des_B += 8;				loc_src += 24;
				}
				//处理宽度不能被8整除部分
				//while (x < bitmap.width)
				{
					loc_des_R[0] = loc_src[0];		loc_des_G[0] = loc_src[1];		loc_des_B[0] = loc_src[2];		
					loc_des_R++;					loc_des_G++;					loc_des_B++;		loc_src += 3;
					x++;
				}
			}
		}
		else
		{
			return  RET_ERR_NOT_SUPPORT;
		}

		return RET_OK;
	}

	RET_CODE SpaceAdapter::CombineBitmap(IGPBitmapChannel &bitmap_channel, IGPBitmap &bitmap)
	{
		if (bitmap_channel._B_channel == nullptr || bitmap_channel._G_channel == nullptr 
			|| bitmap_channel._R_channel == nullptr || bitmap_channel.imageFormat == ImageFormat_unknow)
		{
			return RET_ERR_BITMAP_INFO_DEFECT;
		}
		if (bitmap_channel.imageFormat == RGBA_8888 && bitmap_channel._A_channel == nullptr)
		{
			return RET_ERR_BITMAP_INFO_DEFECT;
		}
		//如果可能,不需要再分配内存
		if (bitmap_channel._width == bitmap.width && bitmap_channel._height == bitmap.height
			&& bitmap_channel.imageFormat == bitmap.image_format && bitmap.pixels != nullptr)
		{
			//不需要分配内存
		}
		else
		{
			uint32 total_px = bitmap_channel._width*bitmap_channel._height;
			if (bitmap_channel.imageFormat == RGB_888)
			{
				total_px *= 3;
				bitmap.one_pixel_length = 3;
				bitmap.stride = bitmap_channel._width * 3;
				if (bitmap.pixels != nullptr)
				{
					free(bitmap.pixels);
				}
				bitmap.pixels = (uint8*)malloc(sizeof(uint8)*total_px);
				if (bitmap.pixels == NULL)
				{
					return RET_ERR_OUTOFMEMORY;
				}
#pragma omp parallel for //此处用opm并行并没有获得加速效果  （猜测for循环展开编译器优化成并行）
				for (int32 h = 0; h < bitmap_channel._height; h++)
				{
					uint8* src_loc_R = bitmap_channel._R_channel + h*bitmap_channel._width;
					uint8* src_loc_G = bitmap_channel._G_channel + h*bitmap_channel._width;
					uint8* src_loc_B = bitmap_channel._B_channel + h*bitmap_channel._width;
					uint8* des_loc = bitmap.pixels + h*bitmap.stride;
					uint32 w;
					for (w = 0; w < bitmap_channel._width; w += LOP_BLOCK_SIZE)
					{
						des_loc[0] = src_loc_R[0];		des_loc[1] = src_loc_G[0];		des_loc[2] = src_loc_B[0];
						des_loc[3] = src_loc_R[1];		des_loc[4] = src_loc_G[1];		des_loc[5] = src_loc_B[1];
						des_loc[6] = src_loc_R[2];		des_loc[7] = src_loc_G[2];		des_loc[8] = src_loc_B[2];
						des_loc[9] = src_loc_R[3];		des_loc[10] = src_loc_G[3];		des_loc[11] = src_loc_B[3];
						des_loc[12] = src_loc_R[4];		des_loc[13] = src_loc_G[4];		des_loc[14] = src_loc_B[4];
						des_loc[15] = src_loc_R[5];		des_loc[16] = src_loc_G[5];		des_loc[17] = src_loc_B[5];
						des_loc[18] = src_loc_R[6];		des_loc[19] = src_loc_G[6];		des_loc[20] = src_loc_B[6];
						des_loc[21] = src_loc_R[7];		des_loc[22] = src_loc_G[7];		des_loc[23] = src_loc_B[7];
						src_loc_R += 8;				src_loc_G += 8;				src_loc_B += 8;				des_loc += 24;
					}
					//处理宽度不能被LOP_BLOCK_SIZE整除剩余部分
					while (w < bitmap_channel._width)
					{
						des_loc[0] = src_loc_R[0];		des_loc[1] = src_loc_G[0];		des_loc[2] = src_loc_B[0];
						src_loc_R++;					src_loc_G++;					src_loc_B++;					des_loc += 3;
						w++;
					}
				}
			}
			else if (bitmap_channel.imageFormat == RGBA_8888)
			{
				total_px *= 4;
				bitmap.one_pixel_length = 4;
				bitmap.stride = bitmap_channel._width * 4;
				if (bitmap.pixels != nullptr)
				{
					free(bitmap.pixels);

				}
				bitmap.pixels = (uint8*)malloc(sizeof(uint8)*total_px);
				if (bitmap.pixels == NULL)
				{
					return RET_ERR_OUTOFMEMORY;
				}
#pragma omp parallel for//此处用opm并行并没有获得加速效果  （猜测for循环展开编译器优化成并行） 
				for (int32 h = 0; h < bitmap_channel._height; h++)
				{
					uint8* src_loc_R = bitmap_channel._R_channel + h*bitmap_channel._width;
					uint8* src_loc_G = bitmap_channel._G_channel + h*bitmap_channel._width;
					uint8* src_loc_B = bitmap_channel._B_channel + h*bitmap_channel._width;
					uint8* src_loc_A = bitmap_channel._A_channel + h*bitmap_channel._width;
					uint8* des_loc = bitmap.pixels + h*bitmap.stride;
					uint32 w;
					for (w = 0; w < bitmap_channel._width; w += LOP_BLOCK_SIZE)
					{
						des_loc[0] = src_loc_R[0];		des_loc[1] = src_loc_G[0];		des_loc[2] = src_loc_B[0];		des_loc[3] = src_loc_A[0];
						des_loc[4] = src_loc_R[1];		des_loc[5] = src_loc_G[1];		des_loc[6] = src_loc_B[1];		des_loc[7] = src_loc_A[1];
						des_loc[8] = src_loc_R[2];		des_loc[9] = src_loc_G[2];		des_loc[10] = src_loc_B[2];		des_loc[11] = src_loc_A[2];
						des_loc[12] = src_loc_R[3];		des_loc[13] = src_loc_G[3];		des_loc[14] = src_loc_B[3];		des_loc[15] = src_loc_A[3];
						des_loc[16] = src_loc_R[4];		des_loc[17] = src_loc_G[4];		des_loc[18] = src_loc_B[4];		des_loc[19] = src_loc_A[4];
						des_loc[20] = src_loc_R[5];		des_loc[21] = src_loc_G[5];		des_loc[22] = src_loc_B[5];		des_loc[23] = src_loc_A[5];
						des_loc[24] = src_loc_R[6];		des_loc[25] = src_loc_G[6];		des_loc[26] = src_loc_B[6];		des_loc[27] = src_loc_A[6];
						des_loc[28] = src_loc_R[7];		des_loc[29] = src_loc_G[7];		des_loc[30] = src_loc_B[7];		des_loc[31] = src_loc_A[7];
						src_loc_R += 8;				src_loc_G += 8;				src_loc_B += 8;				src_loc_A += 8;				des_loc += 32;
					}
					while (w < bitmap_channel._width)
					{
						des_loc[0] = src_loc_R[0];		des_loc[1] = src_loc_G[0];		des_loc[2] = src_loc_B[0];		des_loc[3] = src_loc_A[0];
						src_loc_R++;					src_loc_G++;					src_loc_B++;					src_loc_A++;					des_loc += 4;
						w++;
					}
				}
			}
			else
			{
				return RET_ERR_NOT_SUPPORT;
			}
			bitmap.width = bitmap_channel._width;
			bitmap.height = bitmap_channel._height;
			bitmap.image_format = bitmap_channel.imageFormat;
		}

		return RET_OK;
	}
}
