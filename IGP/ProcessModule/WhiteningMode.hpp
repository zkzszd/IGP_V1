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
 		static RET_CODE WhiteningWithLog(IGPBitmap& bitmap,float bata);
	private:
		WhiteningMode();
	};
}

#endif // ! WHITENING_MODE_HPP
