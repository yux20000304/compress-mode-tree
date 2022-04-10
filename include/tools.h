//
// Created by yyx on 2022/4/9.
//

#ifndef MODE_COMPRESS_TOOLS_H
#define MODE_COMPRESS_TOOLS_H


#include<iostream>
#include <vector>
#include <cmath>
#include <cstring>

void printdir(char *dir,int depth, int chmod, std::string pwd);
void printfile();
//get current time
std::string get_time();
//split path
std::vector<std::string> SplitString(const std::string &s, const std::string &delimiters);

inline int findPrefix(const std::string s1, const std::string s2){
    int length = s2.size();
    int index = 0;
    while (index < length && !(s1[index] ^ s2[index])) {
        index++;
    }
    return index;
}

#endif //MODE_COMPRESS_TOOLS_H
