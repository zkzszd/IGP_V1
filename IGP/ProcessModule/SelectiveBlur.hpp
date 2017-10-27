#pragma once
#include "../Typedef/MyTypedef.h"
#include "../Typedef/_struct.hpp"
#include "../ImageInfo/IGPBitmap.hpp"
#include "../ImageInfo/IGPBitmapChannel.h"

namespace zkzszd
{
	/*ѡ����ģ�� */
	class SelectiveBlur
	{
	public:
		/// <param name="Radius">ָ��ģ��ȡ������Ĵ�С����Ч��Χ[1,127]��</param>
		/// <param name="Threshold">ѡ�������������ɫ��ֵ����������ֵ�����ʱ���ܳ�Ϊģ����һ����,ɫ��ֵ��С����ֵ�����ر��ų���ģ��֮�⣬��Ч��Χ[2,255]��</param> 
		static int32 selectBlur(IGPBitmapChannel &src_btChannel,IGPBitmapChannel &des_btChannel,int32 Radius,int32 Threshold, EdgeMode Edge);
	public:
		SelectiveBlur();
		~SelectiveBlur();
	};
}

