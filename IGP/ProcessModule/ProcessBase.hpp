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
		*	ProcessWithLayer 在原图上覆盖一个新层（新层带透明通道和原层融合）
		*	优化后就是在原图个个颜色分量上增加不同的值（可以实现美白）
		*/
	 	static RET_CODE ProcessWithLayer(IGPBitmap& bitmap, Color_RGB &layer_color_rgb);

		/*
		*	根据RGB颜色空间获取肤色区域范围（需要扩充区域）
		*	area_bitmap 数据会被重置
		*/
		static RET_CODE getFaceAreaByRGB(IGPBitmap &bitmap,IGPBitmap &area_bitmap);

		//这个地方很纠结，按理get说应该返回一个对象或这个一个对象指针或者对象引用（局部变量的引用完全不可取好吧），对象指针则定义成
		//static GrayIntegral* getGrayIntegral(IGPBitmap &gray_bitmap)
		//但是如果这样定义就表示会出现算法内部分配的内存需要用户去释放、去管理，而用户往往不清楚函数内部分配了内存，或者不清楚是否需要自己去释放
		//或者返回一个对象
		//static GrayIntegral getGrayIntegral(const IGPBitmap &gray_bitmap)
		//这种方法按java的思想是最可取的，但是在c++中，这会存在函数中局部对象到使用者定义对象的拷贝复制过程，而很多对象都是unmoveabled的，会存在比较大的拷贝复制消耗，同时也需要对象重载=操作符，不然默认浅拷贝是错误的

		//获取灰度图的积分图，（注意：为了防止重复灰度化原图，此函数只处理灰度化的图，原图不做处理）
		static RET_CODE getGrayIntegral(IGPBitmap &gray_bitmap, GrayIntegral &integral);

	private:
		ProcessBase();
	};
}