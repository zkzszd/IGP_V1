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
		RET_FAIL = -1,					//ʧ��
		RET_OK,							//�ɹ�
		RET_ERR_NOT_SUPPORT,				//��֧�ֵĲ���
		RET_ERR_OUTOFMEMORY,					//	�ڴ����
		RET_ERR_STACKOVERFLOW,					//	��ջ���
		RET_ERR_NULLREFERENCE,					//	������
		RET_ERR_ARGUMENTOUTOFRANGE,				//	��������������Χ��
		RET_ERR_PARAMISMATCH,					//	������ƥ�� ��������
		RET_ERR_BITMAP_INFO_DEFECT				//	ͼ��ؼ���Ϣȱʧ
	};

	enum ImageFormat
	{
		ImageFormat_unknow = 0,
		RGBA_4444 = 1,
		RGBA_8888,
		RGB_888,
		RGB_565,
		GRAY_ONE_CHANNEL,		//һͨ���Ҷ�ͼ
		GRAY_THREE_CHANNEL,		//��ͨ���Ҷ�ͼ
	};

	enum FileFormat
	{
		FileFormat_unknow = 0,
		FileFormat_PNG,
		FileFormat_JPEG,
		FileFormat_BMP
	};
    
    
	enum EdgeMode												//	ĳЩ�����㷨�ı߽紦��ʽ
	{
		Edge_Mode_Repeat = 1,										//	�ظ���Ե����
		Edge_Mode_Smear												//	�����Ե����
	};
}

#endif /* MyTypedef_h */
