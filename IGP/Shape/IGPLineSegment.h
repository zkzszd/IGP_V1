//
//  IGPLineSegment.h
//  ImageProcess
//
//  Created by zkzszd on 2017/7/27.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef IGPLineSegment_h
#define IGPLineSegment_h

#include "IGPPoint.h"

// 线段
namespace zkzszd
{
    struct IGPLineSegment
    {
    public:
        IGPLineSegment(uint32 sta_x,uint32 sta_y,uint32 end_x,uint32 end_y);
        
        /**
         获取直线斜率

         @return <#return value description#>
         */
        float getSlope(){return k;}

        /**
         获取点在该直线上的投影点坐标

         @param point
         @return 投影点
         */
        IGPPoint getProjecton(const IGPPoint &point);

        /**
         获取投影点在两个端点间的比例
         目前没有没有做外部渐变，所以在两个端点外部不需要计算距离，直接return-1
         返回值
         正 投影点在两个端点比例
         负 投影点在两个端点外
         @param poin 投影点
         @return 投影点到端点的比例
         */
        float getProjectonRatio(IGPPoint &poin);

        float getPointRatio(const IGPPoint &poin);

    private:
        void updateInfo();
    private:
        IGPPoint sta_point;
        IGPPoint end_point;
        float k;                //如果k=0 斜率不存在

        uint32 min_x,min_y;
        uint32 max_x,max_y;
        float distance;         //两点间距离
    };
}


#endif /* IGPLineSegment_h */
