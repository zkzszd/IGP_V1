//
//  IGP.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/25.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef IGP_h
#define IGP_h

#define OS_WIN 0

#ifdef _WIN32  
#define OS_WIN 1
#endif

#include "./Util/UtilMath.hpp"
#include "./Util/UtilAllocator.hpp"
#include "./Util/StringUtil.h"

#include "./Typedef/MyTypedef.h"
#include "./Typedef/_struct.hpp"

#include "./ImageInfo/IGPBitmap.hpp"
#include "./ImageInfo/IGPBitmapHSL.hpp"
#include "./ImageInfo/IGPBitmapBase.hpp"
#include "./ImageInfo/JpegTurbo.h"
#include "./ImageInfo/IGPBitmapChannel.h"

#include "./ShowImage/OpencvShow.hpp"

#include "./Adapter/SpaceAdapter.hpp"

#include "./Functor/judge.h"
#include "./Functor/ShadeFunctor.h"

#include "./ProcessModule/BlurModule.hpp"
#include "./ProcessModule/FilletModule.hpp"
#include "./ProcessModule/AlphaModule.hpp"
#include "./ProcessModule/BlurModule.hpp"
#include "./ProcessModule/ProjectionModule.hpp"
#include "./ProcessModule/GrayModule.hpp"
#include "./ProcessModule/BlackAndWhiteModule.hpp"
#include "./ProcessModule/SelectiveBlur.hpp"
#include "./ProcessModule/WhiteningMode.hpp"

#include "./Shape/BaseRect.h"
#include "./Shape/IGPPoint.h"
#include "./Shape/IGPCircle.h"
#include "./Shape/LineCommonly.hpp"     //直线（一般式）
#include "./Shape/IGPLineSegment.h"     //线段
#include "./Shape/IGPTetragonum.h"      //四边形


#include "./File/FileUtil.hpp"

namespace zkzszd {
    


    extern struct IGPPoint;
    extern struct IGPLine;
    extern struct IGPCircle;
    extern struct IGPTetragonum;
    extern struct IGPHSL;
    extern class IGPBitmapHSL;
    extern class BlurModule;


}



#endif /* IGP_h */
