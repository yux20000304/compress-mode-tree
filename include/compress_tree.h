//
// Created by yyx on 2022/4/9.
//

#ifndef MODE_COMPRESS_COMPRESS_TREE_H
#define MODE_COMPRESS_COMPRESS_TREE_H

#include <unordered_map>
#include"compress_treenode.h"

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


class Tree{
public:
    Tree();
    void addDirNode(std::string dir_path, TreeNode* cur, int st_mode, int parent_mode);
    TreeNode *getDirMode(std::string dir_path, TreeNode* cur);
    void addFileNode(std::string& dir_path, int st_mode);
    std::string getFileMeta(std::string& file_path);
    void setFileMeta(std::string& file_path, int mode);
    long long treeTraverse();
    ~Tree();

    TreeNode* root;
    std::unordered_map<std::string, fileMeta*> file_map;
private:



};

#endif //MODE_COMPRESS_COMPRESS_TREE_H
