#pragma once

#define USE_OPENCV 1				//ʹ��opencv����ʾͼƬ
#define USE_OPENMP 1				//ʹ��openmp������
#define OPENCV_WINDOW_HEIGHT 640	//
#define OPENCV_WINDOW_WIDTH  480
#define USE_LIBPNG 1				//ʹ��libpng


#if USE_OPENMP
#include <omp.h>
#endif

/*****************************************************************************
* @function name :
* @warning : ��ֵ�����߻ҶȻ����Ĳ����ٻҶȻ� ���3ͨ����Ϊ1ͨ��
* @author : zkzszd
* @date : 2017/8/24 16:27
* @inparam :
* @outparam :
* @last change :
*****************************************************************************/