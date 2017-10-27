//
//  IGPPonit.h
//  ImageProcess
//
//  Created by zkzszd on 2017/7/24.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef IGPPonit_h
#define IGPPonit_h
#include "../Typedef/MyTypedef.h"
#include <iostream>

using namespace std;

namespace zkzszd
{
    //因为很多头像头都是固定长度，且非内存对其
#pragma pack(push) //保存对齐状态
#pragma pack(1)
    
    struct IGPPoint
    {
        int32 x;
        int32 y;
        
        IGPPoint(IGPPoint const &point)
        {
            this->x = point.x;
            this->y = point.y;
        }
        
        void operator=(IGPPoint const &point)
        {
            this->x = point.x;
            this->y = point.y;
            
        }
        
        friend IGPPoint operator-(IGPPoint const &fr_point,IGPPoint const &se_point)
        {
            return IGPPoint(fr_point.x - se_point.x,fr_point.y-se_point.y);
        }
        
        IGPPoint()
        {
            x = 0;
            y = 0;
        }
        
        void set(uint32 x,uint32 y)
        {
            this->x = x;
            this->y = y;
        }
        
        IGPPoint(uint32 x,uint32 y)
        {
            this->x = x;
            this->y = y;
        }
        
        friend ostream& operator<<(ostream &out,IGPPoint &point)
        {
            out<<"point---x="<<point.x<<" y="<<point.y<<endl;
            return out;
        }
    };

    
#pragma pack(pop)//恢复对齐状态
}

#endif /* IGPPonit_h */
