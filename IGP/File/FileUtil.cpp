//
//  FileUtil.cpp
//  ImageProcess
//
//  Created by zkzszd on 2017/5/26.
//  Copyright © 2017年 zkzszd. All rights reserved.
//

#include "FileUtil.hpp"
#include "../Util/StringUtil.h"
#include <sys/stat.h>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <io.h>

#if defined(_WIN32)			//windows系统
#include<direct.h>
#include <Windows.h> 
#define S_ISREG(m) (((m) & 0170000) == (0100000))   
#define S_ISDIR(m) (((m) & 0170000) == (0040000))  
#elif defined(_UNIX)		//unix系统
#include <dirent.h>
#include <unistd.h>
#include <unistd.h>
#endif

namespace zkzszd 
{
    
    int mymkdir(const char* dirname)
    {
        int ret = 0;
#if defined(_WIN32)
		ret = _mkdir(dirname);
#elif defined(_UNIX)
		ret = mkdir(dirname, 0775);
#endif
        return ret;
    }
    
    std::size_t FileUtils::size(std::string& path)
    {
        if(FileUtils::isExist(path)){
            std::ifstream is;
            is.open(path.c_str(), std::ifstream::in);
            is.seekg(0, is.end);
            std::size_t len = is.tellg();
            is.close();
            return len;
        }
        return (-1);
    }
    
    std::string FileUtils::normalizeUnixPath(const std::string& path) {
        std::string nPath;
		if (UtilString::stringStartsWith(path,"./"))
		{
			nPath = getPwd() + path.substr(2);
		}
		else if (UtilString::stringStartsWith(path,"../"))
		{
			nPath = parentDir(getPwd()) + path.substr(3);
		}
		else
		{
			nPath = path;
		}
        while (nPath.length() >= 2 && nPath.substr(2) == "./") {
            nPath.erase(0, 2);
        }
        int index;
        while ((index = (int)nPath.find("/../")) != -1) {
            const int prevIndex = (int)nPath.rfind('/', index - 1);
            if (prevIndex == -1) {
                nPath.erase(0, index + 4);
            } else {
                nPath.erase(prevIndex, index + 3 - prevIndex);
            }
        }
        int len = (int)nPath.length();
        if ((len >= 3) && (nPath.substr(len - 3) == "/..")) {
            int prevIndex = max((int)nPath.rfind('/', len - 4), 0);
            nPath.erase(prevIndex);
        }
        while ((index = (int)nPath.find("/./")) != -1) {
            nPath.erase(index, 2);
        }
        while (nPath.length() >= 2 &&
               nPath.substr(nPath.length() - 2) == "/.") {
            nPath.erase(nPath.length() - 2);
        }
        while ((index = (int)nPath.find("//")) != -1) {
            nPath.erase(index, 1);
        }
		UtilString::replaceAll(nPath,"\\","/");
        return nPath;
    }

	std::string FileUtils::getPwd()
	{
		char pwd[256] = { 0 };
		getcwd(pwd, 256);
		std::string str_pwd(pwd);
		return UtilString::replaceAll(str_pwd, "\\", "/");
	}
    
    std::string	FileUtils::parentDir(const std::string& path)
    {
        //return path.substr(0, path.rfind(shortName(path)));
		return path.substr(0, path.rfind("/"));
    }
    
    std::string FileUtils::extensionName(const std::string& path)
    {
        std::string myShortName = shortName(path);
        int n = (int)myShortName.find_last_of(".");
        
        if(n == std::string::npos){
            return myShortName;
        }
        std::string ext = myShortName.substr(n+1, myShortName.length());
        //logger.println("扩展名为："+ext);
        return ext;
    }
    
    std::string FileUtils::shortName(const std::string& path)
    {
        std::vector<std::string> _names = UtilString::split(path, "/");
        if(!_names.empty()){
            return _names[_names.size() - 1];
        }else
            return "";
    }
    
    bool FileUtils::isExist(const std::string& path)
    {
        if( (access(path.c_str(), 0 )) != -1 )
        {
            return true;
        }
        return false;
    }
    
    bool FileUtils::isDirectory(const std::string& path)
    {
        if(isExist(path))
		{
            struct stat buf;
#if defined(_WIN32)
			if (stat(path.c_str(), &buf) < 0)
			{
				return false;
		}
#elif defined(_UNIX)
			if (lstat(path.c_str(), &buf) < 0)
			{
				return false;
			}
#endif
            if(S_ISDIR(buf.st_mode))			//S_ISDIR是宏，win下没有，需自己定义
            {
                return true;
            }
        }
        return  false;
    }
    
    bool FileUtils::makeDir(const std::string& path)
    {
        if(isDirectory(path)){
            return true;
        }
        
        char   DirName[256];
        strcpy(DirName, path.c_str());
        int i, len = (int)strlen(DirName);
        if(DirName[len-1]!='/')
            strcat(DirName,   "/");
        
        len = (int)strlen(DirName);
        
        for(i=1; i<len; i++)
        {
            if(DirName[i]=='/')
            {
                DirName[i]   =   0;
                if(access(DirName, 0) != 0)
                {
#if defined(_UNIX)
                    if(mkdir(DirName, 0755) == -1)
                    {
                        perror("mkdir error!");
                        return false;
                    }
#elif defined(_WIN32)
					if (mkdir(DirName) == -1)
					{
						perror("mkdir error!");
						return false;
					}
#endif
                }
                DirName[i] = '/';
            }
        }
        return true;
    }
    bool FileUtils::deleteFile(const std::string& path)
    {
        if(isExist(path)){
            if(remove(path.c_str()) != 0)
                return false;
        }
        return true;
    }
    
    int FileUtils::creat_dir(std::string& pszDir)
    {
        int i = 0;
        int iRet;
        int iLen = (int)pszDir.length();
        char temp_path[1024];
        memset(temp_path, '\0', 1024);
        strcpy(temp_path,pszDir.c_str());
        
        //在末尾加/
        if (temp_path[iLen - 1] != '\\' && temp_path[iLen - 1] != '/')
        {
            temp_path[iLen] = '/';
            temp_path[iLen + 1] = '\0';
        }
        if(temp_path[0] == '/')
        {
            i = 1;
        }
        else
            i = 0;
        // 创建目录
        for (;i <= iLen;i ++)
        {
            if (temp_path[i] == '\\' || temp_path[i] == '/')
            {
                temp_path[i] = '\0';
                
                //如果不存在,创建
                //iRet = access(pszDir,0);
#if defined(_WIN32)
				WIN32_FIND_DATA wfd;
				HANDLE hFind = FindFirstFile(temp_path, &wfd);
				if (INVALID_HANDLE_VALUE != hFind && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					//目录存在
				}
				else  //目录不存在
				{
					iRet = mymkdir(temp_path);
					if (iRet != 0)
					{
						return -1;
					}
				}
#elif defined(_UNIX)
				if (opendir(temp_path) == 0)
					//if (iRet != 0)
				{
					iRet = mymkdir(temp_path);
					if (iRet != 0)
					{
						return -1;
					}
				}
#endif
                //支持linux,将所有\换成/
                temp_path[i] = '/';
            }   
        }  
        return 0;
    }

	int FileUtils::delete_dir(std::string& path)
	{
		int ret_code = -1;
#if defined(_WIN32)
		ret_code = _WIN32_delete_dir(path);
#elif defined(_UNIX)
		ret_code = _UNIX_delete_dir(path);
#endif
		return ret_code;
	}
    
	/*
	*	linux递归删除目录
	*	递归删除目录
	*/
    int FileUtils::_UNIX_delete_dir(std::string& path)
    {
#if defined(_UNIX)
        if(path[path.length() - 1] != '/')
        {
            path.append("/");
        }
        DIR* dp = NULL;
        DIR* dpin = NULL;
        std::string pathname;
        struct dirent* dirp;
        dp = opendir(path.c_str());
        if(dp == NULL)
        {
            //printf("%s\n", "your input directory is not exist!");
            return -1;
        }
        
        while((dirp = readdir(dp)) != NULL)
        {
            if(strcmp(dirp->d_name, "..") == 0 || strcmp(dirp->d_name, ".") == 0)
                continue;
            pathname = path;
            pathname.append(dirp->d_name);
            dpin = opendir(pathname.c_str());
            if(dpin != NULL)
                delete_dir(pathname);
            else
                remove(pathname.c_str());
            
            pathname.clear();
            if(dpin != NULL)
                closedir(dpin);
            dpin = NULL;
        }
        rmdir(path.c_str());
        closedir(dp);
        dirp = NULL;
#endif
        return 0;
    }

	int FileUtils::_WIN32_delete_dir(std::string& path)
	{
#ifdef _WIN32
		//  CFileFind tempFind;     //声明一个CFileFind类变量，以用来搜索  
		char szCurPath[MAX_PATH];       //用于定义搜索格式  
		_snprintf(szCurPath, MAX_PATH, "%s//*.*", path.c_str()); //匹配格式为*.*,即该目录下的所有文件  
		WIN32_FIND_DATAA FindFileData;
		ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));
		HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData);
		BOOL IsFinded = TRUE;
		while (IsFinded)
		{
			IsFinded = FindNextFileA(hFile, &FindFileData); //递归搜索其他的文件  
			if (strcmp(FindFileData.cFileName, ".") && strcmp(FindFileData.cFileName, "..")) //如果不是"." ".."目录  
			{
				std::string strFileName = "";
				strFileName = strFileName + path + "//" + FindFileData.cFileName;
				std::string strTemp;
				strTemp = strFileName;
				if (isDirectory(strFileName)) //如果是目录，则递归地调用  
				{
					printf("目录为:%s/n", strFileName.c_str());
					_WIN32_delete_dir(strTemp);
				}
				else
				{
					remove(strTemp.c_str());
				}
			}
		}
		FindClose(hFile);

		BOOL bRet = rmdir(path.c_str());
		if (bRet == 0) //删除目录  
		{
			printf("删除%s目录失败！/n", path.c_str());
			return -1;
		}
#endif
		return 0;
	}    
} /* namespace zkzszd */