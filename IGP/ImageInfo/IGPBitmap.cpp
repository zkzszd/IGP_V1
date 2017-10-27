//
//  IGPBitmap.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/25.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "IGPBitmap.hpp"
#include "../Util/UtilAllocator.hpp"
#include "../buildConfig.h"
#if USE_LIBPNG
#include "../ThirdLib/include/png.h"
#endif

namespace zkzszd
{
    IGPBitmap::IGPBitmap()
    {
        width = 0;
        height = 0;
        stride = 0;
        one_pixel_length = 0;
        image_format = ImageFormat_unknow;
        pixels = nullptr;
    }
    
//    IGPBitmap::IGPBitmap(IGPBitmap &copy_from)
//    {
//        this->width = copy_from.getWidth();
//        this->height = copy_from.getHeight();
//        stride = copy_from.getStride();
//        one_pixel_length = copy_from.getOnePixelLength();
//        image_format = copy_from.getFormat();
//        pixels = UtilAllocator::alloc_new(height*stride, copy_from.getPixels());
//    }
    
    IGPBitmap::~IGPBitmap()
    {
        if(pixels != nullptr)
        {
            free(pixels);
        }
    }
    
    IGPBitmap::IGPBitmap(uint32 width,uint32 height,uint32 pixel,ImageFormat image_format)
    {
        this->width = width != 0 ? width : 1;
        this->height = height != 0 ? height : 1;
        this->image_format = image_format;
        computeOnePixelAndStrideLength();
        pixels = (uint8*)UtilAllocator::alloc_malloc(stride * this->height,pixel,one_pixel_length);
        
    }
    
    IGPBitmap::IGPBitmap(const string &file_path,EnumFileFormat file_format)
    {
        IGPBitmap();
        switch (file_format) {
            case FORMAT_PIC_PNG:
                createByPNG(file_path);
                break;
            case FORMAT_PIC_BMP:
                createByBMP(file_path);
                break;
                
            default:
                break;
        }
    }
    
    void IGPBitmap::computeOnePixelAndStrideLength()
    {
        switch (image_format) {
            case RGBA_4444:
                one_pixel_length = 2;
                break;
            case RGBA_8888:
                one_pixel_length = 4;
                break;
            case RGB_888:
                one_pixel_length = 3;
                break;
            case RGB_565:
                one_pixel_length = 2;
                break;
            case GRAY_ONE_CHANNEL:
                 one_pixel_length = 1;
                break;
            default:
                break;
        }
        stride = one_pixel_length * this->width;
    }
    
    int8 IGPBitmap::createByBMP(const string &file_path)
    {
        
        return CODE_SUCESS;
    }
    
    int8 IGPBitmap::createByPNG(const string &file_path)
    {
#if USE_LIBPNG
        FILE *fp;
        png_structp png_ptr;
        png_infop info_ptr;
        png_bytep* row_pointers;
        char buf[PNG_BYTES_TO_CHECK];
        int w, h, x, y, temp, color_type;
        
        fp = fopen( file_path.c_str(), "rb" );

        if( fp == NULL ) {
            return CODE_FILE_OPEN_FILE;
        }
        png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );
        info_ptr = png_create_info_struct( png_ptr );
        
        setjmp( png_jmpbuf(png_ptr) );
        /* 读取PNG_BYTES_TO_CHECK个字节的数据 */
        temp = fread( buf, 1, PNG_BYTES_TO_CHECK, fp );
        /* 若读到的数据并没有PNG_BYTES_TO_CHECK个字节 */
        if( temp < PNG_BYTES_TO_CHECK ) {
            fclose(fp);
            png_destroy_read_struct( &png_ptr, &info_ptr, 0);
            return CODE_FAIL;
        }
        /* 检测数据是否为PNG的签名 */
        temp = png_sig_cmp( (png_bytep)buf, (png_size_t)0, PNG_BYTES_TO_CHECK );
        /* 如果不是PNG的签名，则说明该文件不是PNG文件 */
        if( temp != 0 ) {
            fclose(fp);
            png_destroy_read_struct( &png_ptr, &info_ptr, 0);
            return CODE_FAIL;
        }
        
        /* 复位文件指针 */
        rewind( fp );
        /* 开始读文件 */
        png_init_io( png_ptr, fp );
        /* 读取PNG图片信息和像素数据 */
        png_read_png( png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0 );
        /* 获取图像的色彩类型 */
        color_type = png_get_color_type( png_ptr, info_ptr );
        /* 获取图像的宽高 */
        width = w = png_get_image_width( png_ptr, info_ptr );
        height = h = png_get_image_height( png_ptr, info_ptr );
        /* 获取图像的所有行像素数据，row_pointers里边就是rgba数据 */
        row_pointers = png_get_rows( png_ptr, info_ptr );
        /* 根据不同的色彩类型进行相应处理 */
        switch( color_type )
        {
            case PNG_COLOR_TYPE_RGB_ALPHA:
                image_format = RGBA_8888;
                one_pixel_length = 4;
                stride = one_pixel_length * width;
                pixels = (uint8*)UtilAllocator::alloc_malloc(stride * height);
                for( y=0; y<h; ++y ) {
                    for( x=0; x<w*4; ) {
                        /* 以下是RGBA数据，需要自己补充代码，保存RGBA数据 */
                        
                        ((char*)pixels)[y*stride + x] = row_pointers[y][x]; // red
                        ++x;
                        ((char*)pixels)[y*stride + x] = row_pointers[y][x]; // green
                        ++x;
                        ((char*)pixels)[y*stride + x] = row_pointers[y][x]; // blue
                        ++x;
                        ((char*)pixels)[y*stride + x] = row_pointers[y][x]; // alpha
                        ++x;
                    }
                }
                break;
                
            case PNG_COLOR_TYPE_RGB:
                image_format = RGB_888;
                one_pixel_length = 3;
                stride = one_pixel_length * width;
                pixels = (uint8*)UtilAllocator::alloc_malloc(stride * height);
                for( y=0; y<h; ++y ) {
                    for( x=0; x<w*3; ) {
                        /* 以下是RGBA数据，需要自己补充代码，保存RGBA数据 */
                        ((char*)pixels)[y*stride + x] = row_pointers[y][x]; // red
                        ++x;
                        ((char*)pixels)[y*stride + x] = row_pointers[y][x]; // green
                        ++x;
                        ((char*)pixels)[y*stride + x] = row_pointers[y][x]; // blue
                        ++x;
                    }
                }
                break;
                /* 其它色彩类型的图像就不读了 */
            default:
                fclose(fp);
                png_destroy_read_struct( &png_ptr, &info_ptr, 0);
                return CODE_FAIL;
        }
        png_destroy_read_struct( &png_ptr, &info_ptr, 0);
#endif
        return (uint8)CODE_SUCESS;
    }
}
