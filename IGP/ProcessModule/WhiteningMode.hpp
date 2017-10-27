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
		 //ʹ��logarithmic Curve���������ߣ�����ԭ�� new_px = log(px*(b-1)+1)/log(b) bΪ���ڲ�����ֵԽ��Ч��Խ��
		// 1.0 < bata < 10  log(1) = 0 log(10) = 1
 		static RET_CODE WhiteningWithLog(IGPBitmap& bitmap,float bata);
	private:
		WhiteningMode();
	};
}

#endif // ! WHITENING_MODE_HPP
