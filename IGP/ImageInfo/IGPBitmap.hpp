//
//  IGPBitmap.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/25.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef IGPBitmap_hpp
#define IGPBitmap_hpp

#include <stdio.h>
#include <string>
#include "../Typedef/MyTypedef.h"

using namespace std;
namespace zkzszd
{
    /**
     * 算法处理中请用指针操作，这也是getPixels()不是const的原因
     */
    class IGPBitmap
    {
    public:
        /**
         Description 默认构造函数
         */
        IGPBitmap();
        
        /**
         通过图片构造

         @param file_path 图片文件绝对路径
         @param file_format 图片文件格式
         */
        IGPBitmap(const string &file_path,EnumFileFormat file_format = FORMAT_UNKNOW);
        /**
         Description
         @param width 大于0 如果传0 则会初始化为1
         @param height 大于0 如果传0 则会初始化为1
         @param pixel 一个像素值（其他像素全部拷贝次像素）
         @param image_format image_format description
         */
        IGPBitmap(uint32 width,uint32 height, uint32 pixel = 0,ImageFormat image_format = RGBA_8888);
//        /**
//         Description
//
//         @param copy_from copy_from description
//         */
//        IGPBitmap(IGPBitmap &copy_from);
        IGPBitmap(IGPBitmap const &copy_from,int at_x,int at_y,int width,int height);
        
        const uint32 getWidth()     {return width;}
        const uint32 getHeight()    {return height;}
        const uint32 getStride()    {return stride;}
        const ImageFormat getFormat() {return image_format;}
        void setFormat(ImageFormat format) {image_format = format;computeOnePixelAndStrideLength();}
        const uint8 getOnePixelLength() {return one_pixel_length;}
        void* getPixels()   {return pixels;}
        void  setPixels(uint8 *addr)   {pixels = addr;}
        
        void computeOnePixelAndStrideLength();
        ~IGPBitmap();

		friend class JpegTurbo;
		friend class SpaceAdapter;
		friend class ProcessBase;
		friend class GrayModule;
		friend class BlackAndWhiteModule;
    private:
        uint32 width;
        uint32 height;
        uint32 stride;              //步幅
        uint8 one_pixel_length;     //1像素占多大内存
        ImageFormat image_format;
        uint8* pixels;
        
        #define PNG_BYTES_TO_CHECK 4
    private:
		
        int8 createByPNG(const string &file_path);
        int8 createByBMP(const string &file_path);
    };
}

#endif /* IGPBitmap_hpp */
