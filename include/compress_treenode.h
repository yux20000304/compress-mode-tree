//
// Created by yyx on 2022/4/9.
//

#ifndef MODE_COMPRESS_COMPRESS_TREENODE_H
#define MODE_COMPRESS_COMPRESS_TREENODE_H
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

class TreeNode
{

public:
    TreeNode();
    void setDirMode(int indir_mode);
    int getDirMode();
    ~TreeNode();
    std::vector<TreeNode *> children;
    std::string name;

private:
    int dir_mode;
};

#endif // MODE_COMPRESS_COMPRESS_TREENODE_H
