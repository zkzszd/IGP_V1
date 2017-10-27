//
//  LineCommonly.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/7/26.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "LineCommonly.hpp"
#include "../Util/UtilMath.hpp"

namespace zkzszd
{
    LineCommonly::LineCommonly(IGPPoint &onePoint,IGPPoint &secPoint)
    {
        _A = secPoint.y - onePoint.y;
        _B = onePoint.x - secPoint.x;
        _C = secPoint.x*onePoint.y - onePoint.x*secPoint.y;
    }
    
    IGPPoint LineCommonly::getSymmetry(IGPPoint &point)
    {
        IGPPoint ret_point;
        float temp = (_A*point.x+_B*point.y+_C)/(float)(_A*_A+_B*_B);
        
        ret_point.x = UtilMath::rounding(point.x-2*_A*temp);
        ret_point.y = UtilMath::rounding(point.y-2*_B*temp);
        
//        ret_point.x = UtilMath::rounding(point.y-2*_A*temp);
//        ret_point.y = UtilMath::rounding(point.x-2*_B*temp);
        return ret_point;
    }
}
