//
//  UtilMath.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/4.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef UtilMath_hpp
#define UtilMath_hpp

#include <stdio.h>
#include "../Typedef/MyTypedef.h"

namespace zkzszd
{
    extern class IGPPoint;
    class UtilMath
    {
    public:
        
        
        /**
         四舍五入取整 (可以处理负数问题)

         @param value <#value description#>
         @return 取整结果
         */
        static int32 rounding(double value);
        
        /**
         两点间距离

         @param fr_point <#fr_point description#>
         @param se_point <#se_point description#>
         @return <#return value description#>
         */
        static float distance(IGPPoint& fr_point,IGPPoint& se_point);
        
        /**
         点到 线段（非直线）的最短距离

         @param point 点
         @param line_start 线段起点
         @param line_end 线段末点
         @return 距离
         */
        static float dis_point_to_line(IGPPoint &point,IGPPoint &line_start,IGPPoint &line_end);
        
        /**
         求一堆东西里面的最小值,第一个参数类型就是返回值类型
         注：如果放的不是一堆东西，请确保重载 <

         @param val 只少有一个val
         @param args <#args description#>
         @return <#return value description#>
         */
        template <typename T,typename... Type>
        static const T& Min(const T& val,const Type&... args)
        {
            return __Min(val,args...);
        }
        
        template <typename T,typename... Type>
        static const T& Max(const T& val,const Type&... args)
        {
            return __Max(val,args...);
        }
        
    private:
        UtilMath();
        
        template <typename T>
        static const T& __Max(const T& val)
        {
            return val;
        }
        
        template <typename T>
        static const T& __Max(const T& first,const T& second)
        {
            return first > second ? first :second;
        }
        
        template <typename T,typename... Type>
        static const T& __Max(const T& val,const Type&... args)
        {
            //此处的temp也是一个引用变量，所以不存在局部变量返回问题
            const T& temp = __Max(args...);
            return val > temp ? val:temp;
        }
        
        template <typename T>
        static const T& __Min(const T& val)
        {
            return val;
        }
        
        template <typename T,typename... Type>
        static const T& __Min(const T& val,const Type&... args)
        {
            //此处的temp也是一个引用变量，所以不存在局部变量返回问题
            const T& temp = __Min(args...);
            return val < temp ? val:temp;
        }
    };
}
#endif /* UtilMath_hpp */
