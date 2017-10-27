#include "JpegTurbo.h"
#include "../ShowImage/OpencvShow.hpp"
#include "../Util/UtilAllocator.hpp"
#include "../Typedef/MyTypedef.h"

namespace zkzszd
{

	struct my_error_mgr {
		struct jpeg_error_mgr pub;    /* "public" fields */

		jmp_buf setjmp_buffer;        /* for return to caller */
	};

	typedef struct my_error_mgr *my_error_ptr;

	/*
	* Here's the routine that will replace the standard error_exit method:
	*/

	METHODDEF(void)
		my_error_exit(j_common_ptr cinfo)
	{
		/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
		my_error_ptr myerr = (my_error_ptr)cinfo->err;

		/* Always display the message. */
		/* We could postpone this until after returning, if we chose. */
		(*cinfo->err->output_message) (cinfo);

		/* Return control to the setjmp point */
		longjmp(myerr->setjmp_buffer, 1);
	}

	JpegTurbo::JpegTurbo()
	{
		/* Now we can initialize the JPEG decompression object. */
		jpeg_create_decompress(&_jpeg_dec_info);

		jpeg_create_compress(&_jpeg_enc_info);
	}

	JpegTurbo::~JpegTurbo()
	{
		jpeg_destroy_decompress(&_jpeg_dec_info);

		jpeg_destroy_compress(&_jpeg_enc_info);
	}

	int8 JpegTurbo::decode(string jpeg_path)
	{
		/* We use our private extension JPEG error handler.
		* Note that this struct must live as long as the main JPEG parameter
		* struct, to avoid dangling-pointer problems.
		*/
		struct my_error_mgr jerr;

		/* We set up the normal JPEG error routines, then override error_exit. */
		_jpeg_dec_info.err = jpeg_std_error(&jerr.pub);
		jerr.pub.error_exit = my_error_exit;
		/* Establish the setjmp return context for my_error_exit to use. */
		if (setjmp(jerr.setjmp_buffer)) {
			/* If we get here, the JPEG code has signaled an error.
			* We need to clean up the JPEG object, close the input file, and return.
			*/
			jpeg_destroy_decompress(&_jpeg_dec_info);
			return 0;
		}

		FILE * infile = fopen(jpeg_path.c_str(), "rb");
		if (infile == NULL) {
			fprintf(stderr, "can't open %s\n", jpeg_path.c_str());
			return 0;
		}

		/* Step 2: specify data source (eg, a file) */
		jpeg_stdio_src(&_jpeg_dec_info, infile);

		/* Step 3: read file parameters with jpeg_read_header() */

		(void)jpeg_read_header(&_jpeg_dec_info, TRUE);

		///* Step 4: set parameters for decompression */
		///* In this example, we don't need to change any of the defaults set by
		//* jpeg_read_header(), so we do nothing here.
		//*/
		//printf("enter scale M/N:\n");
		////scanf("%d/%d", &cinfo.scale_num, &cinfo.scale_denom);  
		//cinfo.scale_num = 2;
		//cinfo.scale_denom = 4;
		//printf("scale to : %d/%d\n", cinfo.scale_num, cinfo.scale_denom);

		/* Step 5: Start decompressor */
		jpeg_start_decompress(&_jpeg_dec_info);

		int row_stride;               /* physical row width in output buffer */
		/* JSAMPLEs per row in output buffer */
		row_stride = _jpeg_dec_info.output_width * _jpeg_dec_info.output_components;

		JSAMPARRAY buffer;            /* Output row buffer */
		buffer = (*_jpeg_dec_info.mem->alloc_sarray)
			((j_common_ptr)&_jpeg_dec_info, JPOOL_IMAGE, row_stride, 1);

		_bitmap.pixels = (uint8*)UtilAllocator::alloc_malloc(row_stride*_jpeg_dec_info.output_height);

		//bitmap.pixels = (*_jpeg_info.mem->alloc_sarray)
		//	((j_common_ptr)&_jpeg_info, JPOOL_IMAGE, row_stride*_jpeg_info.output_height, _jpeg_info.output_height);

		/* Step 6: while (scan lines remain to be read) */
		/*           jpeg_read_scanlines(...); */

		/* Here we use the library's state variable cinfo.output_scanline as the
		* loop counter, so that we don't have to keep track ourselves.
		*/
		JSAMPROW row_pointer[1];
		//此处不能使用并行优化
		while (_jpeg_dec_info.output_scanline < _jpeg_dec_info.output_height) {
			row_pointer[0] = _bitmap.pixels + _jpeg_dec_info.output_scanline*row_stride;
			/* jpeg_read_scanlines expects an array of pointers to scanlines.
			* Here the array is only one element long, but you could ask for
			* more than one scanline at a time if that's more convenient.
			*/
			;
			jpeg_read_scanlines(&_jpeg_dec_info, row_pointer, 1);
		}

		_bitmap.width = _jpeg_dec_info.output_width;
		_bitmap.height = _jpeg_dec_info.output_height;
		_bitmap.one_pixel_length = _jpeg_dec_info.output_components;
		_bitmap.stride = row_stride;
		if (_jpeg_dec_info.output_components == 3)
		{
			_bitmap.image_format = RGB_888;
		}
		else if (_jpeg_dec_info.output_components == 4)
		{
			_bitmap.image_format = RGBA_8888;
		}

		/* Step 7: Finish decompression */
		jpeg_finish_decompress(&_jpeg_dec_info);

		fclose(infile);

		return 0;
	}

	int8 JpegTurbo::encode(string out_path)
	{
		jpeg_error_mgr errorMgr;
		_jpeg_enc_info.err = jpeg_std_error(&errorMgr);
		_jpeg_enc_info.err->error_exit = my_error_exit;
		FILE* out_file = fopen(out_path.c_str(), "wb+");
		if (out_file == NULL) {
			fprintf(stderr, "can't open %s\n", out_path.c_str());
			return CODE_FILE_OPEN_FILE;
		}
		jpeg_stdio_dest(&_jpeg_enc_info,out_file);
		_jpeg_enc_info.image_width = _bitmap.width;			//图像信息宽高
		_jpeg_enc_info.image_height = _bitmap.height;
		_jpeg_enc_info.jpeg_width = _bitmap.width;			//缩放完后的宽高（此处不缩放）
		_jpeg_enc_info.jpeg_height = _bitmap.height;
		if (_bitmap.image_format == RGBA_8888)
		{
			_jpeg_enc_info.input_components = 4;			//原图像颜色分量
			_jpeg_enc_info.in_color_space = JCS_EXT_RGBA;	//输入图像色彩空间
		}
		else if(_bitmap.image_format == RGB_888)
		{
			_jpeg_enc_info.input_components = 3;			//原图像颜色分量
			_jpeg_enc_info.in_color_space = JCS_EXT_RGB;	//输入图像色彩空间
		}
		//此处是灰度图像
		//else if (_bitmap.image_format == _bitmap.)
		//{
		//	_jpeg_enc_info.input_components = 1;			//原图像颜色分量
		// _jpeg_enc_info.in_color_space = ;				//输入图像色彩空间
		//}
		
		jpeg_set_defaults(&_jpeg_enc_info);					//
		jpeg_set_quality(&_jpeg_enc_info, 86, TRUE);		//设置压缩质量100表示100%  
		jpeg_start_compress(&_jpeg_enc_info, TRUE);
		JSAMPROW row_pointer[1];							// 一行位图  
		while (_jpeg_enc_info.next_scanline < _bitmap.height)
		{
			row_pointer[0] = (JSAMPROW)((unsigned char*)_bitmap.pixels + _jpeg_enc_info.next_scanline*_bitmap.stride);
			jpeg_write_scanlines(&_jpeg_enc_info, row_pointer, 1);
		}
		jpeg_finish_compress(&_jpeg_enc_info);

		fclose(out_file);
		return CODE_SUCESS;
	}
}
