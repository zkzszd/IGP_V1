#pragma once
#include "../Typedef/MyTypedef.h"
#include "../Typedef/_struct.hpp"
#include "../ImageInfo/IGPBitmap.hpp"
#include "../ImageInfo/IGPBitmapChannel.h"

namespace zkzszd
{
	/*选择性模糊 */
	class SelectiveBlur
	{
	public:
		/// <param name="Radius">指定模糊取样区域的大小，有效范围[1,127]。</param>
		/// <param name="Threshold">选项控制相邻像素色调值与中心像素值相差多大时才能成为模糊的一部分,色调值差小于阈值的像素被排除在模糊之外，有效范围[2,255]。</param> 
		static int32 selectBlur(IGPBitmapChannel &src_btChannel,IGPBitmapChannel &des_btChannel,int32 Radius,int32 Threshold, EdgeMode Edge);
	public:
		SelectiveBlur();
		~SelectiveBlur();
	};
}

