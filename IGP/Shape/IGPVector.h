//
//  IGPVector.h
//  ImageProcess
//
//  Created by zkzszd on 2017/7/24.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef IGPVector_h
#define IGPVector_h
#include "IGPPoint.h"
#include "../Typedef/MyTypedef.h"

//向量

namespace zkzszd
{
    class IGPVector
    {
    public:
        
    private:
        IGPPoint _sta_point;
        IGPPoint _end_point;
        uint32 _x;
        uint32 _y;
    };
}

#endif /* IGPVector_h */
