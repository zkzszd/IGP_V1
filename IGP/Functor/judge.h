//
//  judge.h
//  ImageProcess
//
//  Created by zkzszd on 2017/5/10.
//  Copyright © 2017年 zkzszd. All rights reserved.
//
//  此处所有仿函数主要用来判断一个点是否在区域内，返回点距边界的距离
#ifndef judge_h
#define judge_h
#include "../Util/UtilMath.hpp"
#include "../Typedef/_struct.hpp"
#include "../Typedef/MyTypedef.h"
#include "../Shape/IGPCircle.h"
#include "../Shape/IGPPoint.h"
#include "../Shape/IGPTetragonum.h"
namespace zkzszd
{
    extern class UtilMath;
    
    //正圆形 判断点是否在圆内
    struct Jd_circle
    {
        float operator()(IGPPoint &point,IGPCircle &circle)
        {
            return circle.radius - UtilMath::distance(circle.point,point);
        }
    };
    
    // 返回点到边界线距离
    typedef struct Jd_circle Jd_circle_len;
    
    struct Jd_rect
    {
        float operator()(IGPPoint &point,IGPTetragonum &rect)
        {
            
            return 1;
        }
    };
    
}

#endif /* judge_h */
