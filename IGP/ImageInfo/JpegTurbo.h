#pragma once

#include <stdio.h>
/*
* <setjmp.h> is used for the optional error recovery mechanism shown in
* the second part of the example.
*/

#include <setjmp.h>    //跳转功能头文件
#include <string>

#include "../ThirdLib/include/jpeglib.h"
#include "../Typedef/MyTypedef.h"
#include "./IGPBitmap.hpp"

using namespace std;

namespace zkzszd
{
	extern class IGPBitmap;
	//jpeg 解码类
	class JpegTurbo
	{
	public:
		JpegTurbo();
		~JpegTurbo();
		/*********************************
		* 解码指定路径文件到bitmap
		/********************************/
		int8 decode(string jpeg_path);
		/*********************************
		* 解码内存中的数据
		/********************************/
		int8 decode(void *buffer, uint32 buf_length);
		/*********************************
		* 得到的是一个引用，请用引用来接收，防止被提前释放
		/********************************/
		IGPBitmap& getBitamp() { return _bitmap; }
		/*********************************
		* 编码图像数据到文件
		/********************************/
		int8 encode(string jpeg_path);
	private:
		/* This struct contains the JPEG decompression parameters and pointers to
		* working space (which is allocated as needed by the JPEG library).
		*/
		struct jpeg_decompress_struct _jpeg_dec_info;
		struct jpeg_compress_struct _jpeg_enc_info;
		IGPBitmap _bitmap;
	};

}

