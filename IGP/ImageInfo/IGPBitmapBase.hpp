//
//  IGPBitmapBase.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/5.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef IGPBitmapBase_hpp
#define IGPBitmapBase_hpp

#include <stdio.h>
#include <stdlib.h>
#include "../Typedef/MyTypedef.h"

namespace zkzszd {
    class IGPBitmapBase
    {
    public:
        IGPBitmapBase();
        virtual ~IGPBitmapBase();
        uint32 getWidth() {return width;}
        void setWidth(uint32 width){this->width = width;}
        uint32 getHeight() {return height;}
        void setHeight(uint32 height) {this->height = height;}
        uint32 getStride() {return stride;}
    private:
        uint32 width;
        uint32 height;
        uint32 stride;              //步幅
    };
}

#endif /* IGPBitmapBase_hpp */
