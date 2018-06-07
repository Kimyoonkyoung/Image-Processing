//
//  FileIO.cpp
//  LaneClustering
//  Created by Rachel.minii on 2018. 03. 12
//  Copyright (c) 2018 Kakao. All rights reserved.
//
#include <sys/stat.h>
#include <dirent.h>
#include <sys/errno.h>
#include "FileIO.h"

FileIO::FileIO() { }
FileIO::~FileIO() { }

bool FileIO::isExistFile(std::string path)
{
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}


/**
 * @brief dir에 있는 모든 파일(해당 확장자)을 읽어온다
 * @param dirPath : 파일을 읽고자하는 dir path
 * @param fils : path+file명 이 포함된 파일 정보를 담는 vector
 * @return dirPath 가 존재하지 않으면 false
 */
bool FileIO::fileLoadFromDir(std::string dirPath, std::string ext, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(dirPath.c_str())) == NULL) {
        printf("Error opening \n");
        return false;
    }

    while((dirp = readdir(dp)) != NULL) {
        std::string file_name = std::string(dirp -> d_name);

        if(hasEnding(file_name, ext))
        {
            files.push_back(dirPath + "/" + file_name);
        }
    }

    closedir(dp);

    return true;
}


/**
 * @brief filename 을 보고, 원하는 확장자 파일이 있는지 확인
 * @param fullString : filename
 * @param ending : 확장자
 * @return 파일이 있으면 true, 없으면 false
 */
bool FileIO::hasEnding(std::string const &fullString, std::string const &ending)
{
    if(fullString.length() >= ending.length()) {
        return (0==fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    else {
        return false;
    }
}

/**
 * @brief path 에서 fileName 추출
 * @param filename : 포함된 전체 path
 * @return filename
 */
std::string FileIO::getFileName(std::string path)
{
    std::string tmp =path.substr(path.find_last_of("/\\") + 1);

    size_t dotIdx = tmp.find_last_of(".");
    std::string fileName = tmp.substr(0, dotIdx);

    return fileName;
}


/**
 * @brief path 에서 fileName 을 extension 포함해서
 * @param filename : 포함된 전체 path
 * @return filename
 */
std::string FileIO::getFileNameWithEXT(std::string path)
{
    return path.substr(path.find_last_of("/\\") + 1);;
}


/**
 * @brief 주어진 path 에 해당하는 dir tree 를 생성
 * @param path : 만들고 싶은 path
 * @return 정상여부에 따른 리턴
 */
bool FileIO::createDirectoryFromPath(std::string path)
{
    // check directory exist
    struct stat sb;
    if (stat(path.c_str(), &sb) == 0)
        return true;

    size_t pre = 0;
    size_t pos;

    std::string dir;
    int ret;

    while ((pos = path.find_first_of('/',pre)) != std::string::npos)
    {
        dir = path.substr(0, pos++);
        pre = pos;

        if (dir.size() == 0)
            continue;

        if ((ret = mkdir(dir.c_str(),0755)) && errno!=EEXIST)
        {
            if (ret == 0)
                return true;
            else
                return false;
        }
    }
}