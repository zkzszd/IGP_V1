//
//  OpencvShow.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/25.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef OpencvShow_hpp
#define OpencvShow_hpp

#include <stdio.h>
#include <string>
#include "../buildConfig.h"
#include "../ImageInfo/IGPBitmap.hpp"

using namespace std;

#if USE_OPENCV
#include "opencv/cv.h"
#include "opencv/highgui.h"
#endif

/*
 *  本想把这个类设计成单例类
 *  暂定设计成工具类
 */

namespace zkzszd
{
    extern class IGPBitmap;
    class OpencvShow
    {
    private:
        OpencvShow(){}
    public:
        static void Show(IGPBitmap &igpBitmap,string windows_name = "窗口",uint16 windows_width = OPENCV_WINDOW_WIDTH,uint16 windows_height = OPENCV_WINDOW_HEIGHT);
    };
}

#endif /* OpencvShow_hpp */
