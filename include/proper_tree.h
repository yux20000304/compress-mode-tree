//
// Created by yyx on 2022/4/10.
//

#ifndef MODE_COMPRESS_PROPER_TREE_H
#define MODE_COMPRESS_PROPER_TREE_H

#include<iostream>
#include <map>

class properTreeNode{

public:
    properTreeNode();
    ~properTreeNode();
    std::map<std::string, properTreeNode *> children;
    std::string name;
    int mode;
    std::string time;
};


class properTree{

public:
    properTree();
    ~properTree();
    properTreeNode *root;
    void addNode(std::vector<std::string> path, properTreeNode *cur);
    properTreeNode *getNode(std::vector<std::string> path, properTreeNode *cur);
    long long treeTraverse();
};



#endif //MODE_COMPRESS_PROPER_TREE_H
