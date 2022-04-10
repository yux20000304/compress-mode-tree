//
// Created by yyx on 2022/4/9.
//

#ifndef MODE_COMPRESS_TOOLS_H
#define MODE_COMPRESS_TOOLS_H


#include<iostream>
#include <vector>
#include <cmath>

void printdir(char *dir,int depth, int chmod, std::string pwd);
void printfile();
//get current time
std::string get_time();
//split path
std::vector<std::string> SplitString(const std::string &s, const std::string &delimiters);
//find prefix
int findPrefix(const std::string& s1, const std::string& s2);


#endif //MODE_COMPRESS_TOOLS_H
