//
//  OpencvShow.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/25.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "OpencvShow.hpp"
namespace zkzszd
{
    void OpencvShow::Show(IGPBitmap &igpBitmap,string windows_name,uint16 windows_width,uint16 windows_height)
    {
#if USE_OPENCV
        CvSize sz;//图像尺寸
        sz.width = igpBitmap.getWidth();
        sz.height = igpBitmap.getHeight();
        IplImage *image = nullptr;
        
        // opencv 中顺序为BGR
        switch (igpBitmap.getFormat())
        {
            case RGB_888:
                image = cvCreateImage(sz, IPL_DEPTH_8U, 3);
                for(int h = 0;h < igpBitmap.getHeight();h++)
                {
                    for(int w = 0;w < igpBitmap.getWidth();w++)
                    {
                        image->imageData[h*igpBitmap.getStride()+w*3] = ((char*)igpBitmap.getPixels())[h*igpBitmap.getStride()+w*3+2];
                        image->imageData[h*igpBitmap.getStride()+w*3+1] = ((char*)igpBitmap.getPixels())[h*igpBitmap.getStride()+w*3+1];
                        image->imageData[h*igpBitmap.getStride()+w*3+2] = ((char*)igpBitmap.getPixels())[h*igpBitmap.getStride()+w*3];
                    }
                }
                break;
            case RGBA_8888:
                image = cvCreateImage(sz, IPL_DEPTH_8U, 4);
                for(int h = 0; h < igpBitmap.getHeight();h++)
                {
                    int8* des_line = (int8*)image->imageData+h*igpBitmap.getStride();
                    int8* src_line = ((int8*)igpBitmap.getPixels()+h*igpBitmap.getStride());
                    for(int w = 0;w<igpBitmap.getWidth();w++)
                    {
                        des_line[w*4] = src_line[w*4+2];
                        des_line[w*4+1] = src_line[w*4+1];
                        des_line[w*4+2] = src_line[w*4];
                        des_line[w*4+3] = src_line[w*4+3];
                    }
                }
                break;
            case GRAY_ONE_CHANNEL:
                image = cvCreateImage(sz, IPL_DEPTH_8U, 1);
                memcpy(image->imageData,igpBitmap.getPixels(),igpBitmap.getStride()*igpBitmap.getHeight());
                break;
            default:
                image = cvCreateImage(sz, IPL_DEPTH_8U, 3);
                memcpy(image->imageData,igpBitmap.getPixels(),igpBitmap.getStride()*igpBitmap.getHeight());
                break;
        }

		//没有缩放
		cvNamedWindow(windows_name.c_str(), CV_WINDOW_AUTOSIZE);
		cvShowImage(windows_name.c_str(), image);
		cvWaitKey(0);
		cvReleaseImage(&image);
		cvDestroyWindow(windows_name.c_str());
        
        ////防止出现超大图片，对大图缩放
        //float zoom_x = 640.0/sz.width;
        //float zoom_y = 480.0/sz.height;
        //
        //if(zoom_x<zoom_y)
        //{
        //    sz.width*=zoom_x;
        //    sz.height*=zoom_x;
        //}
        //else
        //{
        //    sz.width*=zoom_y;
        //    sz.height*=zoom_y;
        //}
        //IplImage *zoom_image = nullptr;
        //zoom_image = cvCreateImage(sz, IPL_DEPTH_8U, image->nChannels);
        //cvResize(image, zoom_image);
        //
        //cvNamedWindow(windows_name.c_str(),CV_WINDOW_AUTOSIZE);
        //cvShowImage(windows_name.c_str(),zoom_image);
        //cvWaitKey(0);
        //cvReleaseImage(&image);
        //cvReleaseImage(&zoom_image);
        //cvDestroyWindow(windows_name.c_str());
#endif
    }
}
