//
//  FileUtil.hpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/26.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#ifndef FileUtil_hpp
#define FileUtil_hpp

#include <stdio.h>
#include <string>

namespace zkzszd {

	/*以unix为标准路径  即以"/"为标准 */
    class FileUtils {
    public:
		//获取文件大小
        static std::size_t  size(std::string& path);
		//把路径规范化(处理"./"开头)  
		// “\\” 替换为 '/'
		// "//"  替换为 '/'
        static std::string 	normalizeUnixPath(const std::string& path);
		//获取文件的扩展名(不带 . )
        static std::string 	extensionName(const std::string& path);
		//获取文件名（不带路径）
        static std::string 	shortName(const std::string& path);
		//获取文件父目录
        static std::string	parentDir(const std::string& path);
		//文件是否存在
        static bool			isExist(const std::string& path);
		//是否是目录
        static bool			isDirectory(const std::string& path);
		//创建目录（支持递归，父目录不存在会首先创建父目录）
        static bool			makeDir(const std::string& path);
		//删除文件（不支持递归）
        static bool			deleteFile(const std::string& path);
        //递归创建目录，父目录不存在会先创建父目录
        static int          creat_dir(std::string& name);
        //递归删除目录
        static int          delete_dir(std::string& path);
		//获取当前工作目录
		static std::string getPwd();
	private:
		FileUtils();		//防止工具类被实例化
		static int			_WIN32_delete_dir(std::string& path);
		static int			_UNIX_delete_dir(std::string& path);
    };
}

#endif /* FileUtil_hpp */
