//
//  IGPLineSegment.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/7/28.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include <stdio.h>
#include "IGPLineSegment.h"
#include "../Util/UtilMath.hpp"

namespace zkzszd
{
    IGPLineSegment::IGPLineSegment(uint32 sta_x,uint32 sta_y,uint32 end_x,uint32 end_y):sta_point(sta_x,sta_y),end_point(end_x,end_y)
    {
        if(sta_point.x == end_point.x)
        {
            k = 0;
        }
        else
        {
            k = (float)(sta_point.y-end_point.y)/(sta_point.x-end_point.x);
        }
        updateInfo();
    }
    
    IGPPoint IGPLineSegment::getProjecton(const IGPPoint &point)
    {
        IGPPoint ret_point;
        if(sta_point.x == end_point.x)
        {
            ret_point.x = sta_point.x;
            ret_point.y = point.y;
        }
        else if(sta_point.y == end_point.y)
        {
            ret_point.x = point.x;
            ret_point.y = sta_point.y;
        }
        else
        {
            //此处只的假设是整数方式四舍五入
            // （int）(x+0.5) 正数四舍五入取整
            ret_point.x = (int32)((k*sta_point.x+point.x/k+point.y-sta_point.y)/(1/k+k)+0.5);
            ret_point.y = (int32)((-1/k *(ret_point.x-point.x)+point.y)+0.5);
        }
        return ret_point;
    }
    
    void IGPLineSegment::updateInfo()
    {
        if(sta_point.x > end_point.x)
        {
            min_x = end_point.x;
            max_x = sta_point.x;
        }
        else
        {
            max_x = end_point.x;
            min_x = sta_point.x;
        }
        if(sta_point.y > end_point.y)
        {
            min_y = end_point.y;
            max_y = sta_point.y;
        }
        else
        {
            max_y = end_point.y;
            min_y = sta_point.y;
        }
        distance = UtilMath::distance(sta_point, end_point);
    }
    
    float IGPLineSegment::getPointRatio(const IGPPoint &point)
    {
        IGPPoint pro_point = getProjecton(point);
        if(pro_point.x>= min_x && pro_point.x<= max_x && pro_point.y>=min_y&&pro_point.y<=max_y)
        {
            return UtilMath::distance(pro_point, end_point)/distance;
        }
        else
        {
            return -1;
        }
    }
    
    float IGPLineSegment::getProjectonRatio(IGPPoint &point)
    {
        if(point.x>= min_x && point.x<= max_x && point.y>=min_y&&point.y<=max_y)
        {
            return UtilMath::distance(point, end_point)/distance;
        }
        else
        {
            return -1;
        }
    }
}
