#pragma once

#define USE_OPENCV 1				//使用opencv来显示图片
#define USE_OPENMP 1				//使用openmp来并行
#define OPENCV_WINDOW_HEIGHT 640	//
#define OPENCV_WINDOW_WIDTH  480
#define USE_LIBPNG 1				//使用libpng


#if USE_OPENMP
#include <omp.h>
#endif

/*****************************************************************************
* @function name :
* @warning : 二值化或者灰度化过的不能再灰度化 会把3通道变为1通道
* @author : zkzszd
* @date : 2017/8/24 16:27
* @inparam :
* @outparam :
* @last change :
*****************************************************************************/