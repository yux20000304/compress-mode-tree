//
// Created by yyx on 2022/4/9.
//

#ifndef MODE_COMPRESS_COMPRESS_TREE_H
#define MODE_COMPRESS_COMPRESS_TREE_H

#include <unordered_map>
#include"compress_treenode.h"
#include <libpmemkv.hpp>
#include "filemeta.h"


#define USE_PMEMKV  1




class Tree{
public:
    Tree();
    void addDirNode(const std::string dir_path, TreeNode* cur, int st_mode, int parent_mode);
    TreeNode *getDirMode(std::string &dir_path, TreeNode* cur);
    void addFileNode(std::string& dir_path, int st_mode);
    std::string getFileMeta(std::string& file_path);
    void setFileMeta(std::string& file_path, int mode);
    long long treeTraverse();

    void InitKVengine();
    void PutMetadataCache(std::string& key, std::string& value);
    void GetMetadataCache(std::string& key, std::string& value);
    void RemoveMetadataCache(std::string& key);

    ~Tree();

    long long count1 = 0;

    TreeNode* root;
    std::unordered_map<std::string, fileMeta*> file_map;

    pmem::kv::db kv;
    pmem::kv::config cfg;
    pmem::kv::status s;
private:



};

#endif //MODE_COMPRESS_COMPRESS_TREE_H
