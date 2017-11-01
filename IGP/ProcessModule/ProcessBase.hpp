#pragma once
#include "../Typedef/_struct.hpp"
#include "../Typedef/MyTypedef.h"
#include "../ImageInfo/IGPBitmap.hpp"

namespace zkzszd
{
	class ProcessBase
	{
	public:
		/*
		*	ProcessWithLayer ��ԭͼ�ϸ���һ���²㣨�²��͸��ͨ����ԭ���ںϣ�
		*	�Ż��������ԭͼ������ɫ���������Ӳ�ͬ��ֵ������ʵ�����ף�
		*/
	 	static RET_CODE ProcessWithLayer(IGPBitmap& bitmap, Color_RGB &layer_color_rgb);

		/*
		*	����RGB��ɫ�ռ��ȡ��ɫ����Χ����Ҫ��������
		*	area_bitmap ���ݻᱻ����
		*/
		static RET_CODE getFaceAreaByRGB(IGPBitmap &bitmap,IGPBitmap &area_bitmap);

		//����ط��ܾ��ᣬ����get˵Ӧ�÷���һ����������һ������ָ����߶������ã��ֲ�������������ȫ����ȡ�ðɣ�������ָ�������
		//static GrayIntegral* getGrayIntegral(IGPBitmap &gray_bitmap)
		//���������������ͱ�ʾ������㷨�ڲ�������ڴ���Ҫ�û�ȥ�ͷš�ȥ�������û���������������ڲ��������ڴ棬���߲�����Ƿ���Ҫ�Լ�ȥ�ͷ�
		//���߷���һ������
		//static GrayIntegral getGrayIntegral(const IGPBitmap &gray_bitmap)
		//���ַ�����java��˼�������ȡ�ģ�������c++�У������ں����оֲ�����ʹ���߶������Ŀ������ƹ��̣����ܶ������unmoveabled�ģ�����ڱȽϴ�Ŀ����������ģ�ͬʱҲ��Ҫ��������=����������ȻĬ��ǳ�����Ǵ����

		//��ȡ�Ҷ�ͼ�Ļ���ͼ����ע�⣺Ϊ�˷�ֹ�ظ��ҶȻ�ԭͼ���˺���ֻ����ҶȻ���ͼ��ԭͼ��������
		static RET_CODE getGrayIntegral(IGPBitmap &gray_bitmap, GrayIntegral &integral);

	private:
		ProcessBase();
	};
}