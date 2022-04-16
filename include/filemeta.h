//
// Created by yyx on 2022/4/15.
//

#ifndef MODE_COMPRESS_FILEMETA_H
#define MODE_COMPRESS_FILEMETA_H

#include <iostream>
#include "tools.h"

class fileMeta{
public:
    fileMeta();
    void setFileMeta();
    std::string getFileMeta();
    const std::string &getTime() const;
    void setTime(const std::string &time);
    int getMode() const;
    void setMode(int mode);
    ~fileMeta();

private:
    std::string time;
    int mode;
};

#endif //MODE_COMPRESS_FILEMETA_H
