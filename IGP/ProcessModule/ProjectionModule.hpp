//
//  ProjectionModule.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/7/24.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef ProjectionModule_hpp
#define ProjectionModule_hpp

#include <stdio.h>
#include "../Typedef/MyTypedef.h"
#include "../Shape/Shape.h"
#include "../ImageInfo/IGPBitmap.hpp"

namespace zkzszd
{
	/*****************************************************************************
	* @abstract :  投影
	* @author : zkzszd
	* @date : 2017/8/28 11:19
	*****************************************************************************/
    class ProjectionModule
    {
    public:
        static int8 projection(IGPBitmap &bitmap,IGPBitmap &to_bitmap,BaseRect &rect,LineCommonly &line);
    };
}

#endif /* ProjectionModule_hpp */
