//
// Created by yyx on 2022/4/9.
//

#ifndef MODE_COMPRESS_COMPRESS_TREE_H
#define MODE_COMPRESS_COMPRESS_TREE_H

#include <unordered_map>
#include "compress_treenode.h"
#include "filemeta.h"

#ifdef USE_PMEMKV
    #include <libpmemkv.hpp>
#endif

class Tree
{
public:
    Tree();
    void addDirNode(const std::string dir_path, TreeNode *cur, int st_mode, int parent_mode);
    void deleteDirNode(const std::string dir_path, TreeNode *cur);
    TreeNode *getDirMode(std::string &dir_path, TreeNode *cur);
    std::string getFileMeta(std::string &file_path);
    void setFileMeta(std::string &file_path, int mode);
    long long treeTraverse();
    ~Tree();

    long long count1 = 0;

    TreeNode *root;
    std::unordered_map<std::string, fileMeta *> file_map;

#ifdef USE_PMEMKV
    void InitKVengine();
    void PutMetadataCache(std::string &key, std::string &value);
    void GetMetadataCache(std::string &key, std::string &value);
    void RemoveMetadataCache(std::string &key);

    pmem::kv::db kv;
    pmem::kv::config cfg;
    pmem::kv::status s;
#endif

private:
};

#endif // MODE_COMPRESS_COMPRESS_TREE_H
