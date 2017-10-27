//
//  IGPCircle.h
//  ImageProcess
//
//  Created by zkzszd on 2017/7/27.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef IGPCircle_h
#define IGPCircle_h

#include "IGPPoint.h"
#include "BaseRect.h"
#include "../Util/UtilMath.hpp"

namespace zkzszd
{
    struct IGPCircle:public BaseRect
    {
        IGPPoint point;
        uint32 radius;
        IGPCircle(int x,int y,int radius):point(x,y)
        {
            this->radius = radius;
            min_x = x - radius;
            max_x = x + radius;
            min_y = y - radius;
            max_y = y + radius;
        }
        
        bool isContain(IGPPoint& _point)
        {
            float dis = UtilMath::distance(point,_point);
            if(radius >= dis)
                return true;
            return false;
        }
        
        float dis_border(IGPPoint &point)
        {
            return radius - UtilMath::distance(this->point,point);
        }
    };
}

#endif /* IGPCircle_h */
