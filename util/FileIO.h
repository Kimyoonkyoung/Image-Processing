//
//  FileIO.h
//  LaneClustering
//  Created by Rachel.minii on 2018. 03. 12
//  Copyright (c) 2018 Kakao. All rights reserved.
//

#ifndef __LANECLUSTERING_FILEIO_H__
#define __LANECLUSTERING_FILEIO_H__
#pragma once

#include <iosfwd>
#include <string>
#include <vector>

class FileIO {
protected:
    bool hasEnding(std::string const &fullString, std::string const &ending);

public:
    FileIO();
    virtual ~FileIO();

    // directory 에 존재하는 파일들 한번에 읽는 함수
    // files vector에 저장됨
    bool fileLoadFromDir(std::string dirPath, std::string ext, std::vector<std::string> &files);

    // path 에서 filename 만 추출
    std::string getFileName(std::string path);
    std::string getFileNameWithEXT(std::string path);

    // directory 존재여부 검사 후, 없으면 경로만큼 생성
    bool createDirectoryFromPath(std::string path);

    bool isExistFile(std::string path);
};


#endif//LANECLUSTERING_FILEIO_H
