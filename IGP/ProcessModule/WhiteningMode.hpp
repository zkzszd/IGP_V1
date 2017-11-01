#ifndef  WHITENING_MODE_HPP
#define WHITENING_MODE_HPP

#include "../Typedef/_struct.hpp"
#include "../Typedef/MyTypedef.h"
#include "../ImageInfo/IGPBitmap.hpp"

namespace zkzszd
{
	class  WhiteningMode
	{
	public:
		 //使用logarithmic Curve（对数曲线）函数原型 new_px = log(px*(b-1)+1)/log(b) b为调节参数，值越大效果越大
		// 1.0 < bata < 10  log(1) = 0 log(10) = 1
		//引用不能做默认参数，只好重载咯
 		static RET_CODE WhiteningWithLog(IGPBitmap& bitmap,float bata);

		//map_bitmap需要美白处理的映射
		static RET_CODE WhiteningWithLog(IGPBitmap& bitmap, float bata,IGPBitmap& map_bitmap);
	private:
		WhiteningMode();
	};
}

#endif // ! WHITENING_MODE_HPP
