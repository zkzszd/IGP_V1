//
//  IGPTetragonum.h
//  ImageProcess
//
//  Created by zkzszd on 2017/7/27.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef IGPTetragonum_h
#define IGPTetragonum_h

#include "IGPPoint.h"
#include "BaseRect.h"
#include "../Util/UtilMath.hpp"

namespace zkzszd
{
    //顺时针四点的四边形
    // isContain 只适合凸四边形
    struct IGPTetragonum:public BaseRect
    {
        IGPPoint _1_point;
        IGPPoint _2_point;
        IGPPoint _3_point;
        IGPPoint _4_point;
        IGPTetragonum(const IGPPoint& onePoint,const IGPPoint& twoPoint,
                const IGPPoint& threePoint,const IGPPoint& fourPoint)
        :_1_point(onePoint),_2_point(twoPoint),_3_point(threePoint),_4_point(fourPoint)
        {
            min_x = UtilMath::Min(_1_point.x, _2_point.x,_3_point.x,_4_point.x);
            max_x = UtilMath::Max(_1_point.x, _2_point.x,_3_point.x,_4_point.x);
            min_y = UtilMath::Min(_1_point.y, _2_point.y,_3_point.y,_4_point.y);
            max_y = UtilMath::Max(_1_point.y, _2_point.y,_3_point.y,_4_point.y);
        }
        bool isContain(IGPPoint& point);
        float dis_border(IGPPoint &point);
        
    };
}

#endif /* IGPTetragonum_h */
