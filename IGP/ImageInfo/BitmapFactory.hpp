//
//  BitmapFactory.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/25.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef BitmapFactory_hpp
#define BitmapFactory_hpp

#include <stdio.h>
#include "./IGPBitmap.hpp"
#include "../Typedef/MyTypedef.h"
#include <string>

using namespace std;

namespace zkzszd
{
    class BitmapFactory
    {
    public:
        static int8 createWithFile(IGPBitmap &btimap,const string &path);
    private:
        BitmapFactory();
    };
}

#endif /* BitmapFactory_hpp */
