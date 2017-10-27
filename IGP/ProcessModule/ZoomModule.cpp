//
//  ZoomModule.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/27.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "ZoomModule.hpp"

namespace zkzszd
{
    int8 ZoomModule::Zoom(IGPBitmap &src, IGPBitmap &des,EnumZoomMode mode)
    {
        int8 ret_code = CODE_FAIL;
        if(src.getWidth() <= 0 || src.getHeight() <= 0 || des.getWidth() <= 0 || des.getHeight() <= 0)
        {
            return ret_code;
        }
        switch (mode) {
            case ZOOM_MODE_4_weighted_average:
               ret_code = Zoom4weightedAverage(src,des);
                break;
                
            default:
                break;
        }
        
        
        
        return ret_code;
    }
    
    /**
     * 双线性 改进为周围四像素均值 用于高斯模糊
     */
    int ZoomModule::BMP32_resize(unsigned char * SrcBuf, int srcW,int srcH,unsigned char* DstBuf, int dstW, int dstH)
    {
        if(!DstBuf || !SrcBuf)
            return -1;
        if(srcW <=0 || srcH <=0 || dstW <=0 || dstH <=0)
            return -1;
        
        int nSrcWidthStep = srcW * 4;  //源图像每行所占字节数
        int nDstWidthStep = dstW * 4;  //目标图像每行所占字节数
        int i,j,k;
        for(i =0; i < dstH; ++i)
        {
            //原图中对应纵坐标（i+0.5 如果加的是一，就会出现内存访问溢出情况）dstH 如果不减去1会出现白边情况
            float y = (float)(((double)i+0.5)*(double)srcH/(double)dstH -1);
            //指向目标图像的行数据
            unsigned char * pDstLine = DstBuf + i * nDstWidthStep;
            for(j =0; j <dstW; ++j)
            {
                //原图中对应横坐标
                float x = (float)(((double)j+0.5)*(double)srcW/(double)dstW-1);
                //u和v为x,y的小数部分,并放大2048倍以规避浮点运算
                //            int u = (int)(y-(int)y*2048);
                //            int v = (int)(x-(int)x*2048);
                
                //            int u = (int)(y-(int)y)>>11;
                //            int v = (int)(x-(double)x)>>11;
                
                //ix,iy分别存储x,y的整数部分
                int ix = (int)x;
                int iy = (int)y;
                for(k=0; k<4; k++)
                {
                    pDstLine[j*4 +k] = (char)(SrcBuf[iy*nSrcWidthStep + ix*4 +k]*(x-ix)*(y-iy)+SrcBuf[iy*nSrcWidthStep + (ix+1)*4 +k]*(x-ix)*(1-(y-iy))+SrcBuf[(iy+1)*nSrcWidthStep + ix*4 +k]*(1-(x-ix))*(y-iy)+SrcBuf[(iy+1)*nSrcWidthStep + (ix+1)*4 +k]*(1-(x-ix))*(1-(y-iy)));
                    //               pDstLine[j*4 +k] = (SrcBuf[iy*nSrcWidthStep + ix*4 +k]*(2048 -u)*(2048 -v)
                    //                                   +SrcBuf[iy*nSrcWidthStep + (ix+1)*4 +k]*(2048 -u)*v
                    //                                   +SrcBuf[(iy+1)*nSrcWidthStep + ix*4 +k]*u*(2048 -v)
                    //                                   +SrcBuf[(iy+1)*nSrcWidthStep + (ix+1)*4 +k]*u*v)>>22;
                }
            }
        }
        return 0;
    }
    
    int8 ZoomModule::Zoom4weightedAverage(IGPBitmap &src,IGPBitmap &des)
    {
        int8 ret_code = CODE_FAIL;
        
//        BMP32_resize((uint8*)src.getPixels(), src.getWidth(), src.getHeight(), (uint8*)des.getPixels(), des.getWidth(), des.getHeight());
//        return CODE_SUCESS;
        
        
        float f_src_h, f_src_w;     //目标坐标映射到原图的坐标
        float f_h, f_w;             //映射原图坐标的小数部分
        uint32 int_src_h, int_src_w;//映射原图坐标的整数
        int8 *px_line;              //目标图每行的起始位置
        
        int8 *des_pixel = (int8*)des.getPixels();
        int8 *src_pixel = (int8*)src.getPixels();
        int32 des_stride = des.getStride();
        int32 src_stride = src.getStride();    //
        int8 one_pix_lop = 0;
        int8 one_pix_len = src.getOnePixelLength();
        if(src.getFormat() == RGB_888)
        {
            one_pix_lop = 3;
        }
        else if(src.getFormat() == RGBA_8888)
        {
            one_pix_lop = 4;
        }
        //des_w 如果不减1就会出现白边情况
        float fw = (float)(src.getWidth())/(des.getWidth());
        float fh = (float)(src.getHeight())/(des.getHeight());
        
        for(uint32 h = 0;h < des.getHeight(); h++)
        {
            px_line = des_pixel + des_stride*h;
            f_src_h = h * fh;
            for(int w = 0;w < des.getWidth(); w++)
            {
                f_src_w = w * fw;
                int_src_w = (uint32)f_src_w;
                int_src_h = (uint32)f_src_h;
                //此处可以放大2048倍 规避浮点数操作
                f_w = f_src_w - int_src_w;
                f_h = f_src_h = int_src_h;
                float _1_f_w = (1.0f - f_w);
                float _1_f_h = 1.0f - f_h;
                
                for(uint32 i = 0;i < one_pix_lop;i++)
                {
                    int32 src_loc = int_src_h*src_stride + int_src_w*one_pix_len + i;
//                    px_line[w*one_pix_lop+i] =
//                    (src_pixel[src_loc]
//                    + src_pixel[src_loc+one_pix_len]
//                    + src_pixel[src_loc+src_stride]
//                    + src_pixel[src_loc+src_stride+one_pix_len])/4;
                    
//                    px_line[w*one_pix_lop+i] =
//                    src_pixel[src_loc]*_1_f_w*_1_f_h
//                    + src_pixel[src_loc+one_pix_len]*f_w*_1_f_h
//                    + src_pixel[src_loc+src_stride]*_1_f_w*f_h
//                    + src_pixel[src_loc+src_stride+one_pix_len]*f_w*f_h;
                        px_line[w*one_pix_lop+i] =
                        (uint8)(src_pixel[src_loc]*_1_f_w*_1_f_h
                        + src_pixel[src_loc+one_pix_len]*f_w*_1_f_h
                        + src_pixel[src_loc+src_stride]*_1_f_w*f_h
                        + src_pixel[src_loc+src_stride+one_pix_len]*f_w*f_h);
                    
                }
                
                //printf("%d_%d(%d,%d)  ",w,h,int_src_w,int_src_h);
            }
        }

        return ret_code;
    }
}
