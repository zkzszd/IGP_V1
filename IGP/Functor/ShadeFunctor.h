//
//  ShadeFunctor.h
//  ImageProcess
//
//  Created by zkzszd on 2017/5/18.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef ShadeFunctor_h
#define ShadeFunctor_h

namespace zkzszd
{
    
    /**
     线性渐变  y = x
     */
    struct IGP_linear
    {
        float operator()(float loc)
        {
            return loc;
        }
    };
    
    struct IGP_cos
    {
        float operator()(float loc)
        {
            return cos(loc*2/3.1415);
        }
    };
}

#endif /* ShadeFunctor_h */
