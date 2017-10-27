//
//  LineCommonly.h
//  ImageProcess
//
//  Created by zkzszd on 2017/7/26.
//  Copyright © 2017年 zkzszd. All rights reserved.
//  直线方程一般式
//  除了一般式方程，它们要么不能支持所有情况下的直线（比如跟坐标轴垂直或者平行），要么不能支持所有情况下的点（比如x坐标相等，或者y坐标相等）。所以一般式方程在用计算机处理二维图形数据时特别有用。
//  AX+BY+C=0

#ifndef LineCommonly_hpp
#define LineCommonly_hpp
#include "IGPPoint.h"
#include "../Typedef/MyTypedef.h"

namespace zkzszd
{
    class LineCommonly
    {
    public:
        // 直线上两点构造直线方程
        LineCommonly(IGPPoint &onePoint,IGPPoint &secPoint);
        
        /**
         获取一点关于直线的对称点

         @param point <#point description#>
         @return <#return value description#>
         */
        IGPPoint getSymmetry(IGPPoint &point);
        int32 getA()   {return _A;}
        int32 getB()   {return _B;}
        int32 getC()   {return _C;}
    private:
        int32 _A;
        int32 _B;
        int32 _C;
    };
}


#endif /* LineCommonly_h */
