//
//  BaseRect.h
//  ImageProcess
//
//  Created by zkzszd on 2017/7/27.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef BaseRect_h
#define BaseRect_h

#include "IGPPoint.h"

namespace zkzszd
{
    struct BaseRect
    {
        //rect应在四点围成的区域内
        int32 min_x;
        int32 max_x;
        int32 min_y;
        int32 max_y;
        
        //点是否在区域内
        virtual bool isContain(IGPPoint& ) = 0;
        //点到边界的距离
        //请确保点在区域内，不然该值没有意义
        //(这也是内部渐变原因，外部渐变可以转化内部渐变)
        virtual float dis_border(IGPPoint &) = 0;
    };
}



#endif /* BaseRect_h */
