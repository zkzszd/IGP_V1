//
//  main.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/4/24.
//  Copyright © 2017年 zkzszd. All rights reserved.
//
#include <iostream>
#include <time.h>
#include "IGP.hpp"
#include "./ProcessModule/ProcessBase.hpp"
using namespace zkzszd;
using namespace std;

#include <string>
int main(int argc, const char * argv[]) 
{
	std::string png_320_480_path("F:\\vs2015\\vsWork\\IGP\\IGP\\TestFile\\320_480.png");
	std::string png_sun_path("F:\\vs2015\\vsWork\\IGP\\IGP\\TestFile\\sun.png");
	std::string jpg_str_img_IMG("F:\\vs2015\\vsWork\\IGP\\IGP\\TestFile\\IMG.jpg");
	std::string png_str_img_IMG("F:\\vs2015\\vsWork\\IGP\\IGP\\TestFile\\IMG.png");
	std::string jpg_str_img_mohu("F:\\vs2015\\vsWork\\IGP\\IGP\\TestFile\\mohu.jpg");
	std::string png_str_img_mohu("F:\\vs2015\\vsWork\\IGP\\IGP\\TestFile\\mohu.png");
	std::string png_str_img_eyes("F:\\vs2015\\vsWork\\IGP\\IGP\\TestFile\\eyes.png");
	std::string jpg_str_img_hei("F:\\vs2015\\vsWork\\IGP\\IGP\\TestFile\\hei.jpg");
//    std::string str = "#ff00ff00";
//    
//    printf("%lx\n",strtol(str.substr(1,str.length()-1).c_str(), nullptr, 16));
//    // insert code here...
//    // /Users/zkzszd/Desktop/Image/ImageProcess/ImageProcess/TestFile/320_480.png
//    uint32 pix = 0x00000000;
//    // 通过宽高创建
//    //IGPBitmap igpBitmap = IGPBitmap(320, 320,pix,IGPBitmap::RGB_888);
//
//    // 通过图片创建（png）
//    IGPBitmap igpBitmap = IGPBitmap(png_str_img_IMG,FORMAT_PIC_PNG);
//    
//    //缩放
////    IGPBitmap small_igpBitmap = IGPBitmap(350, 350,pix,igpBitmap.getFormat());
////    ZoomModule::Zoom(igpBitmap, small_igpBitmap);
//    
//    //灰度化
//    //GrayModule::GrayOwn(igpBitmap,GrayModule::GRAY_MODE_VISION);
//    
//    IGPCircle circle(igpBitmap.getWidth()/2,igpBitmap.getHeight()/2,200);
//    
//    IGPRect rect(IGPPoint(0,0),IGPPoint(480,0),IGPPoint(480,640),IGPPoint(0,640));
////    //（中心点）正方形
////    rect._1_point.set(100,180);
////    rect._2_point.set(220,180);
////    rect._3_point.set(220,300);
////    rect._4_point.set(100,300);
//    
//    //测试原点
////    rect._1_point.set(0,0);
////    rect._2_point.set(0,100);
////    rect._3_point.set(100,100);
////    rect._4_point.set(100,0);
//    
//    //梯形
////    rect._1_point.set(100,180);
////    rect._2_point.set(220,180);
////    rect._3_point.set(260,300);
////    rect._4_point.set(60,300);
//    
//    //构造三变形
////        rect._1_point.set(160,180);
////        rect._2_point.set(160,180);
////        rect._3_point.set(260,300);
////        rect._4_point.set(60,300);
//    
////    //不规则四边形
////    rect._1_point.set(89,218);
////    rect._2_point.set(120,234);
////    rect._3_point.set(260,300);
////    rect._4_point.set(60,300);
//
//    
////    GrayModule::GrayOwn(igpBitmap,circle);
//    
//    //测试rgb转hsl
////    IGPBitmapHSL hsl_bitmap;
////    SpaceAdapter::RGB2HSL(igpBitmap, hsl_bitmap);
////    SpaceAdapter::HSL2RGB(hsl_bitmap, igpBitmap);
//    
////    //通过直线构造左右渐变效果
////    IGPLine igpLine = IGPLine(50, 50, igpBitmap.getWidth()-50,igpBitmap.getHeight()-50);
////    GrayModule::GrayShade(igpBitmap, igpLine, IGP_linear());
//    
//    //GrayShade(igpBitmap, igpLine);
//    
//    //GrayOwnww(igpBitmap,circle,igp_linear);
//    
//    
////    //灰度化
////    GrayModule::GrayOwn(igpBitmap, circle, IGP_linear(),30);
//    
//    //普通模糊
//    //BlurModule::BlurOwn(igpBitmap,12);
//    
//    //带区域模糊
		//IGPCircle circle(igpBitmap.getWidth() / 2, igpBitmap.getHeight() / 2, 100);
		//BlurModule::BlurOwn(igpBitmap, 20, circle,IGP_linear(),30);
		//OpencvShow::Show(igpBitmap);
//    
////    //圆角
//////    FilletModule::FilletOwn(igpBitmap, 100, 0xffffffff, 100, 0xffffffff, 100, 0xffffffff,100, 0xffffffff);
    
 //   IGPBitmap outBitmap(png_str_img_mohu,FORMAT_PIC_PNG);
	//IGPTetragonum rect(IGPPoint(0, 0), IGPPoint(igpBitmap.getWidth(), 0), IGPPoint(igpBitmap.getWidth(), igpBitmap.getHeight()), IGPPoint(0, igpBitmap.getHeight()));
 //   BlurModule::gaussian(igpBitmap, igpBitmap, rect, 20,IGP_linear(),20);
 //   
 //   OpencvShow::Show(igpBitmap,"hui");
    
    
    
    //测试贴图
    //IGPBitmap bg_bitmap = IGPBitmap(png_320_480_path,FORMAT_PIC_PNG);
    //IGPBitmap cv_bitmap = IGPBitmap(png_sun_path,FORMAT_PIC_PNG);
    //IGPPoint point(0,100);
    //AlphaModule::coverToBg(bg_bitmap, cv_bitmap, point);
    //OpencvShow::Show(bg_bitmap,"hui");
    
//    //测试模糊
//    //IGPBitmap bg_bitmap = IGPBitmap(1080, 1440,0xffffffff);
//    IGPBitmap bg_bitmap = IGPBitmap("/Users/zkzszd/Desktop/Image/ImageProcess/ImageProcess/TestFile/IMG.png",FORMAT_PIC_PNG);
//    IGPBitmap cv_bitmap = IGPBitmap("/Users/zkzszd/Desktop/Image/ImageProcess/ImageProcess/TestFile/IMG.png",FORMAT_PIC_PNG);
//    BlurModule::BlurOwn(cv_bitmap, 30);
//    IGPCircle circle(cv_bitmap.getWidth()/2,cv_bitmap.getHeight()/2,300);
//    IGP_linear linear;
//    AlphaModule::shade(cv_bitmap, circle,linear,255,0,200);
//    IGPPoint point(0,0);
//    AlphaModule::coverToBg(bg_bitmap, cv_bitmap,point);
//    OpencvShow::Show(bg_bitmap,"hui");
    
    //测试二值化 (编译失败)
//    IGPBitmap bg_bitmap = IGPBitmap("/Users/zkzszd/Desktop/Image/ImageProcess/ImageProcess/TestFile/IMG.png",FORMAT_PIC_PNG);
//    GrayModule::GrayOwn(bg_bitmap);
//    BlackAndWhiteModule::processGray(bg_bitmap);
//    OpencvShow::Show(bg_bitmap,"hui");
    
    //测试直线对称点
//    IGPPoint st_point(560,720);
//    IGPPoint end_point(560,0);
//    IGPPoint point(56,0);
//    LineCommonly line = LineCommonly(st_point,end_point);
//    IGPPoint pp = line.getSymmetry(point);
//    cout<<pp;
    
    //测试图片投影
    //IGPBitmap bg_bitmap = IGPBitmap(str_img,FORMAT_PIC_PNG);
    //IGPBitmap bitmap = IGPBitmap(bg_bitmap.getWidth(), bg_bitmap.getHeight(),0xffffffff);
    //IGPPoint _1_point(0,0);
    //IGPPoint _2_point(bg_bitmap.getWidth()/2,0);
    //IGPPoint _3_point(bg_bitmap.getWidth()/2,bg_bitmap.getHeight());
    //IGPPoint _4_point(0,bg_bitmap.getHeight());
    //LineCommonly line(_2_point,_3_point);
    //IGPTetragonum rect(_1_point,_2_point,_3_point,_4_point);
    //ProjectionModule::projection(bg_bitmap,bg_bitmap,rect,line);
    //OpencvShow::Show(bg_bitmap,"hui");

	//测试openmp
//#if USE_OPENMP
//	clock_t  start, end;
//
//	IGPBitmap bg_bitmap = IGPBitmap(str_img, FORMAT_PIC_PNG);
//	//uint32 width,uint32 height,uint32 pixel,EnumImageFormat image_format
//	IGPBitmap bitmap = IGPBitmap(bg_bitmap.getWidth(),bg_bitmap.getHeight(),0x00000000,bg_bitmap.getFormat());
//	IGPBitmapHSL bitmap_hsl;
//	
//	start = clock();
//	//for (int i = 0; i < 100; i++)
//	{
//		SpaceAdapter::RGB2HSL(bg_bitmap, bitmap_hsl);
//		SpaceAdapter::HSL2RGB(bitmap_hsl, bitmap);
//	}
//
//	end = clock();
//
//	printf("time = %d\n",end-start);
//	OpencvShow::Show(bitmap, "hui");
//#endif    

//测试黑白化
	//IGPBitmap bg_bitmap = IGPBitmap(str_img, FORMAT_PIC_PNG);
	//GrayModule::GrayOwn(bg_bitmap);
	//BlackAndWhiteModule::processGray(bg_bitmap);

	//OpencvShow::Show(bg_bitmap);

//测试jpegturbo
	//JpegTurbo jpegTurbo;
	//jpegTurbo.decode("F:\\vs2015\\vsWork\\IGP\\IGP\\TestFile\\IMG.jpg");
	//IGPBitmap& bitmap = jpegTurbo.getBitamp();
	//SpaceAdapter::RGBToRGBA(bitmap);
	//OpencvShow::Show(bitmap);
	////OpencvShow::Show(bitmap);
	////IGPBitmap cv_bitmap = IGPBitmap(str_img, FORMAT_PIC_PNG);
	////BlurModule::BlurOwn(cv_bitmap, 20);
 ////   IGPCircle circle(cv_bitmap.getWidth()/2,cv_bitmap.getHeight()/2,500);
 ////   IGP_linear linear;
 ////   AlphaModule::shade(cv_bitmap, circle,linear,0,255,300);
 ////   IGPPoint point(0,0);
 ////   AlphaModule::coverToBg(bitmap, cv_bitmap,point);

	//jpegTurbo.encode("test.jpg");


	//JpegTurbo jpegTurbo;
	//jpegTurbo.decode("F:\\vs2015\\vsWork\\IGP\\IGP\\TestFile\\IMG.jpg");
	//IGPBitmap& bitmap = jpegTurbo.getBitamp();
	////	测试灰度化
	//GrayModule::GrayOwn(bitmap, GrayModule::GRAY_MODE_AVERAGE);
	//BlackAndWhiteModule::processGray(bitmap, BlackAndWhiteModule::ThresholdRockBottom());

	////测试模糊（模糊并行优化有问题）
	//BlurModule::BlurOwn(bitmap,0);
	//OpencvShow::Show(bitmap); 

	//测试圆角
	//IGPBitmap bitmap(png_320_480_path,FORMAT_PIC_PNG);
	//clock_t  start, end;
	//
	////for(int i = 0;i<100;i++)
	//FilletModule::FilletOwn(bitmap, 300,0xff000000,300,0xff000000,300,0xff000000, 300,0xff000000);
	

	//OpencvShow::Show(bitmap); 
	//jpegTurbo.encode("sun.jpeg");

	////测试adapter split 
	//IGPBitmapChannel bt_channel;
	//IGPBitmapChannel des_chanel(bitmap.getWidth(),bitmap.getHeight(),bitmap.getFormat());
	//IGPBitmap new_bitmap;
	//start = clock();
	////for(int i = 0;i<10000;i++)
	//	SpaceAdapter::BitmapSplit(bitmap, bt_channel);
	//	SelectiveBlur::selectBlur(bt_channel, des_chanel,10,45, Edge_Repeat);
	//	SpaceAdapter::CombineBitmap(des_chanel, new_bitmap);
	//	
	//end = clock();
	//printf("time = %d\n", end - start);

	////测试选择模糊
	//JpegTurbo jpegTurbo;
	//jpegTurbo.decode(jpg_str_img_mohu);

	//IGPBitmap bitmap(png_str_img_mohu,FORMAT_PIC_PNG);//jpegTurbo.getBitamp();
	////OpencvShow::Show(bitmap);
	//IGPBitmap new_bitmap;
	//
	//IGPBitmapChannel bt_channel;
	//IGPBitmapChannel des_chanel(bitmap.getWidth(),bitmap.getHeight(),bitmap.getFormat());
	//SpaceAdapter::BitmapSplit(bitmap, bt_channel);

	//SelectiveBlur::selectBlur(bt_channel, des_chanel, 10, 25, Edge_Mode_Repeat);
	//SpaceAdapter::CombineBitmap(des_chanel, new_bitmap);
	//
	//OpencvShow::Show(new_bitmap);


	////测试color
	//Color_ARGB argb = Color_ARGB(0xff010203);
	//printf("%x %x %x %x\n",argb.A, argb.R, argb.G, argb.B);
	//getchar();

	//测试processbase的美白
	//IGPBitmap bitmap(png_str_img_mohu, FORMAT_PIC_PNG);
	//ProcessBase::ProcessWithLayer(bitmap,Color_RGB(25,19,25));
	//OpencvShow::Show(bitmap);

	////测试对数log美白
	//JpegTurbo jpegTurbo;
	//jpegTurbo.decode(jpg_str_img_hei);
	//IGPBitmap &bitmap = jpegTurbo.getBitamp();
	//WhiteningMode::WhiteningWithLog(bitmap,9.9);

	//IGPCircle circle(bitmap.getWidth() / 2, bitmap.getHeight() / 2, 100);

	//BlurModule::BlurOwn(bitmap, 12, circle, IGP_linear(), 20);
	//OpencvShow::Show(bitmap);


	////测试肤色区域  (部分景物照，效果不佳)
	//JpegTurbo jpegTurbo;
	//jpegTurbo.decode(jpg_str_img_hei);
	//IGPBitmap &bitmap = jpegTurbo.getBitamp();
	//IGPBitmap area_bitmap;
	//ProcessBase::getFaceAreaByRGB(bitmap,area_bitmap);
	//OpencvShow::Show(area_bitmap);


	//测试卷积
	//IGPBitmap bitmap = IGPBitmap(10,10,0x010101, GRAY_ONE_CHANNEL);
	//GrayIntegral integral(10,10);
	//ProcessBase::getGrayIntegral(bitmap,integral);
	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		printf("%4u\t", integral.data[i * 10 + j]);
	//	}
	//	printf("\n");
	//}
	//getchar();
	//测试ok



		////制作圆角头像
		//JpegTurbo cv_jpeg,bg_jpeg;
		//IGPBitmap bg_bitmap(320,320,0xffffffff,RGBA_8888);
		//IGPBitmap bg1_bitmap(320, 320, 0xffffffff, RGBA_8888);
		//cv_jpeg.decode("C:/Users/lnb/Desktop/icon/head_alvaro_1.jpg");
		//bg_jpeg.decode("C:/Users/lnb/Desktop/icon/head_alvaro_1.jpg");

	 //   BlurModule::BlurOwn(cv_jpeg.getBitamp(), 20);
	 //   IGPCircle circle(cv_jpeg.getBitamp().getWidth()/2, cv_jpeg.getBitamp().getHeight()/2,160);
	 //   IGP_linear linear;
		//IGPPoint point(0, 0);
		//AlphaModule::shade(bg_jpeg.getBitamp(), circle, linear, 255, 0, 20);
		//AlphaModule::coverToBg(bg_bitmap, bg_jpeg.getBitamp(), point);
		//OpencvShow::Show(bg_bitmap, "hui");

	 //   AlphaModule::shade(cv_jpeg.getBitamp(), circle,linear,0,255,30);
	 //   AlphaModule::coverToBg(bg_bitmap, cv_jpeg.getBitamp(), point);
		//OpencvShow::Show(bg_bitmap, "hui");

		//AlphaModule::shade(bg1_bitmap, circle, linear, 0, 255, 0);
		//AlphaModule::coverToBg(bg_bitmap, bg1_bitmap, point);
		//OpencvShow::Show(bg_bitmap, "hui");

	//测试fileUtil
	string path("C:/Users/lnb/Desktop/icon/head_alvaro_1.jpg");
	cout << "path：" << path << endl;
	cout<< "文件大小："<< FileUtils::size(path)<<endl;
	cout << "pwd:" << FileUtils::getPwd() << endl;
	cout << "规范路径：" << FileUtils::normalizeUnixPath("..//2222//111.jpg")<<endl;
	cout << "扩展名：" << FileUtils::extensionName(path) << endl;
	cout << "文件短名：" << FileUtils::shortName(path) << endl;
	cout << "父目录：" <<FileUtils::parentDir(path) << endl;
	cout << "是否存在：" <<FileUtils::isExist(path) << endl;
	cout << "是否是目录：" << FileUtils::isDirectory(path) << endl;


	////测试stringutil
	//string str_src = "12212";
	//cout << "src_str=" << str_src << endl;
	//cout<<"replace end:"<<StringUtil::replaceAllDistinct(str_src,"12","21")<<endl;

    std::cout << "Hello, World!\n";
	getchar();
    return 0; 
}
