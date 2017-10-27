//
//  MyTypedef.h
//  
//
//  Created by zkzszd on 2017/4/25.
//
//

#ifndef MyTypedef_h
#define MyTypedef_h

namespace zkzszd {
    typedef unsigned char       uint8;
    typedef char                int8;
    typedef unsigned short      uint16;
    typedef short               int16;
    typedef unsigned int        uint32;
    typedef int                 int32;
    typedef unsigned long long  uint64;
    typedef long long           int64;
	
	typedef uint32				COLOR_ARGB;
	typedef uint32				COLOR_RGB;

#define ABS(a) ((a)<(0)?(-a):(a))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
	
#define CODE_FAIL -1
#define CODE_SUCESS 0
#define CODE_FILE_OPEN_FILE 1
    
    typedef enum
    {
        FORMAT_UNKNOW = 0,
        FORMAT_PIC_PNG,
        FORMAT_PIC_BMP
    }EnumFileFormat;


	enum RET_CODE
	{
		RET_ERR_UNKNOWN = -2,
		RET_FAIL = -1,					//失败
		RET_OK,							//成功
		RET_ERR_NOT_SUPPORT,				//不支持的操作
		RET_ERR_OUTOFMEMORY,					//	内存溢出
		RET_ERR_STACKOVERFLOW,					//	堆栈溢出
		RET_ERR_NULLREFERENCE,					//	空引用
		RET_ERR_ARGUMENTOUTOFRANGE,				//	参数不在正常范围内
		RET_ERR_PARAMISMATCH,					//	参数不匹配 参数错误
		RET_ERR_BITMAP_INFO_DEFECT				//	图像关键信息缺失
	};

	enum ImageFormat
	{
		ImageFormat_unknow = 0,
		RGBA_4444 = 1,
		RGBA_8888,
		RGB_888,
		RGB_565,
		GRAY_ONE_CHANNEL,		//一通道灰度图
		GRAY_THREE_CHANNEL,		//三通道灰度图
	};

	enum FileFormat
	{
		FileFormat_unknow = 0,
		FileFormat_PNG,
		FileFormat_JPEG,
		FileFormat_BMP
	};
    
    
	enum EdgeMode												//	某些领域算法的边界处理方式
	{
		Edge_Mode_Repeat = 1,										//	重复边缘像素
		Edge_Mode_Smear												//	镜像边缘像素
	};
}

#endif /* MyTypedef_h */
