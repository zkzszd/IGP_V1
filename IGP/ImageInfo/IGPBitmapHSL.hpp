//
//  IGPBitmapSHL.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/5.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef IGPBitmapSHL_hpp
#define IGPBitmapSHL_hpp

#include <stdio.h>
#include "IGPBitmapBase.hpp"
#include "../Util/UtilAllocator.hpp"
#include "../Typedef/MyTypedef.h"
#include "../Typedef/_struct.hpp"

namespace zkzszd
{
    class IGPBitmapHSL : public IGPBitmapBase
    {
    public:
        IGPBitmapHSL():IGPBitmapBase(){}
		~IGPBitmapHSL() 
		{
			if (_pixels != nullptr)
			{
				free(_pixels);
			}
		}
        
        void init(uint32 width,uint32 height);

		IGPHSL *getPixels() { return _pixels; }

		void setPixels(IGPHSL *pixels)
		{
			if (_pixels != NULL)
			{
				free(_pixels);
			}
			_pixels = pixels;
		}
    
        void updateOnePXLenAndStride();
    private:
		IGPHSL *_pixels;
    };
}

#endif /* IGPBitmapSHL_hpp */
