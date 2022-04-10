//
// Created by yyx on 2022/4/9.
//

#ifndef MODE_COMPRESS_COMPRESS_TREENODE_H
#define MODE_COMPRESS_COMPRESS_TREENODE_H
#include<iostream>
#include <map>



class TreeNode{

public:
    TreeNode();
    void setDirMode(int indir_mode);
    int getDirMode();
    ~TreeNode();
    std::map<std::string, TreeNode*> children;

private:
    int dir_mode;
};


#endif //MODE_COMPRESS_COMPRESS_TREENODE_H
