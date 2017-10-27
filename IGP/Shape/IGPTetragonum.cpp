//
//  IGPTetragonum.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/7/28.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include <stdio.h>
#include "IGPTetragonum.h"
#include "../Util/UtilMath.hpp"
#include "../IGP.hpp"
#include "../Typedef/My_define.h"

namespace zkzszd
{
    bool IGPTetragonum::isContain(IGPPoint& point)
    {
        int a[4] = {0};
        a[0] = (_2_point.x-_1_point.x)*(point.y-_1_point.y)
        -(_2_point.y-_1_point.y)*(point.x-_1_point.x);
        a[1] = (_3_point.x-_2_point.x)*(point.y-_2_point.y)
        -(_3_point.y-_2_point.y)*(point.x-_2_point.x);
        a[2] = (_4_point.x-_3_point.x)*(point.y-_3_point.y)
        -(_4_point.y-_3_point.y)*(point.x-_3_point.x);
        a[3] = (_1_point.x-_4_point.x)*(point.y-_4_point.y)
        -(_1_point.y-_4_point.y)*(point.x-_4_point.x);
        if((a[0]>=0&&a[1]>=0&&a[2]>=0&&a[3]>=0)||(a[0]<=0&&a[1]<=0&&a[2]<=0&&a[3]<=0))
        {
            return true;
        }
        return false;
    }
    
    float IGPTetragonum::dis_border(IGPPoint &point)
    {
        float dis[4];
        dis[0] = UtilMath::dis_point_to_line(point, _1_point, _2_point);
        dis[1] = UtilMath::dis_point_to_line(point, _2_point, _3_point);
        dis[2] = UtilMath::dis_point_to_line(point, _4_point, _3_point);
        dis[3] = UtilMath::dis_point_to_line(point, _4_point, _1_point);
        float min = zk_MIN(dis[0],dis[1],dis[2]);
        return min<dis[3]?min:dis[3];
    }
}
