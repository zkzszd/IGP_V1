//
//  UtilMath.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/4.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "UtilMath.hpp"
#include "../Typedef/_struct.hpp"
#include <math.h>
#include "../Shape/IGPPoint.h"

namespace zkzszd {
    
    int32 UtilMath::rounding(double value)
    {
        if(value >= 0)
        {
            return (int32)(value+0.5);
        }
        else
        {
            return (int32)(value-0.5);
        }
    }
    
    float UtilMath::distance(IGPPoint &fr_point,IGPPoint &se_point)
    {
        float dist = 0.0;
        int32 dist_x = fr_point.x - se_point.x;
        int32 dist_y = fr_point.y - se_point.y;
        dist_x = dist_x > 0 ? dist_x : -dist_x;
        dist_y = dist_y > 0 ? dist_y : -dist_y;
        dist = (float)sqrtf(dist_x*dist_x + dist_y*dist_y);
        return dist;
    }
    
    float UtilMath::dis_point_to_line(IGPPoint &point,IGPPoint &line_start,IGPPoint &line_end)
    {
        int32 le_str_x = point.x-line_start.x;
        int32 le_str_y = point.y-line_start.y;
        int32 le_end_x = point.x-line_end.x;
        int32 le_end_y = point.y-line_end.y;
        int32 le_x = line_end.x-line_start.x;
        int32 le_y = line_end.y-line_start.y;
        float cross = (le_x)*(le_str_x)+(le_y)*(le_str_y);
        if(cross<=0)
            return (float)sqrtf(le_str_x*le_str_x + le_str_y*le_str_y);
        float d2 = le_x*le_x+le_y*le_y;
        if(cross >= d2)
        {
            return (float)sqrtf(le_end_x*le_end_x+le_end_y*le_end_y);
        }
        float r = cross/d2;
        float px = line_start.x+(le_x)*r;
        float py = line_start.y+(le_y)*r;
        return (float)sqrtf((point.x-px)*(point.x-px)+(py-point.y)*(py-point.y));
    }
}
