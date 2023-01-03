//
// Created by yyx on 2022/4/15.
//

#include "filemeta.h"

fileMeta::fileMeta()
{
    setFileMeta();
}

fileMeta::~fileMeta() {}

void fileMeta::setFileMeta()
{
    time = get_time();
}

std::string fileMeta::getFileMeta()
{
    return time + std::to_string(mode);
}

const std::string &fileMeta::getTime() const
{
    return time;
}

void fileMeta::setTime(const std::string &time)
{
    fileMeta::time = time;
}

int fileMeta::getMode() const
{
    return mode;
}

void fileMeta::setMode(int mode)
{
    fileMeta::mode = mode;
}