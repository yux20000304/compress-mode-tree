//
// Created by yyx on 2022/4/9.
//

#include "tools.h"
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include <unistd.h>


long long count1=0;
long long count2=0;
long long count3=0;


void printdir(char *dir,int depth, int chmod, std::string pwd){
    //打开目录指针
    DIR *Dp;
    //文件目录结构体
    struct dirent *enty;
    //详细文件信息结构体
    struct stat statbuf;
    if(pwd == "/")
    {
        pwd = "";
    }
    //打开指定的目录，获得目录指针
    if(NULL == (Dp = opendir(dir)))
    {
        fprintf(stderr,"can not open dir:%s\n",dir);
        return;
    }
    //切换到这个目录
    chdir(dir);
    //遍历这个目录下的所有文件
    while(NULL != (enty = readdir(Dp) ))
    {
        //通过文件名，得到详细文件信息
        lstat(enty->d_name,&statbuf);
        //判断是不是目录
        if(S_ISDIR(statbuf.st_mode))
        {
            //当前目录和上一目录过滤掉
            if(0 == strcmp(".",enty->d_name) ||
               0 == strcmp("..",enty->d_name))
            {
                continue;
            }
            //输出当前目录名
            if(statbuf.st_mode != chmod){
                printf("%s%s/    %d\n",pwd.c_str(),enty->d_name,statbuf.st_mode);
                count1++;
            }
            else{
                // printf("%*s%s/\n",depth," ",enty->d_name);
            }
            count2++;
            pwd.append("/");
            printdir(enty->d_name,depth+4,statbuf.st_mode,pwd.append(enty->d_name));
        }
        else
        {      //输出文件名
            // printf("%*s%s\n",depth," ",enty->d_name);
        }
        count3++;
    }
    //切换到上一及目录
    chdir("..");
    //关闭文件指针
    closedir(Dp);
}

void printfile(){
    printf("%lld\n",count1);
    printf("%lld\n",count2);
    printf("%lld\n",count3);
}

std::string get_time(){
    time_t current_time = time(0);
    std::string current_time_string = std::string(ctime(&current_time));
    std::vector<std::string> time_parts;
    time_parts = SplitString(current_time_string,"/");
    std::string result = time_parts[0];
    for (int i = 1; i < time_parts.size(); ++i) {
        result += ("-" + time_parts[i]);
    }
    return result;
}

std::vector<std::string> SplitString(const std::string &s, const std::string &delimiters) {
    std::vector<std::string> tokens;
    std::string::size_type lastPos=s.find_first_not_of(delimiters, 0);
    std::string::size_type pos=s.find_first_of(delimiters, lastPos);
    while(lastPos!=std::string::npos || pos!=std::string::npos) {
        tokens.push_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
    return tokens;
}
