//
// Created by yyx on 2022/4/9.
//
#include <queue>
#include "compress_tree.h"
#include "tools.h"

#define ASSERT(expr)                                     \
    do                                                   \
    {                                                    \
        if (!(expr))                                     \
            std::cout << pmemkv_errormsg() << std::endl; \
        assert(expr);                                    \
    } while (0)
#define LOG(msg) std::cout << msg << std::endl

const uint64_t SIZE = 1024UL * 1024UL * 1024UL;

Tree::Tree() {}

Tree::~Tree() {}

void Tree::addDirNode(const std::string dir_path, TreeNode *cur, int st_mode, int parent_mode)
{
    // traverse all child nodes
    for (auto it : cur->children)
    {
        int pre_idx = findPrefix(dir_path, it->name);
        if (pre_idx == 0)
        {
            continue;
        }
        // match dir path, change to next level dir
        if (pre_idx == it->name.size())
        {
            cur = it;
            std::string next_dir = dir_path.substr(pre_idx, dir_path.size());
            int cur_mode = it->getDirMode();
            return addDirNode(next_dir, cur, st_mode, cur_mode);
        }
    }
    // has the same mode with parent node
    if (st_mode == parent_mode)
    {
        return;
    }
    else
    { // add new node
        TreeNode *add_node = new TreeNode();
        add_node->name = dir_path;
        add_node->setDirMode(st_mode);
        cur->children.push_back(add_node);
        return;
    }
    return;
}

void Tree::deleteDirNode(const std::string dir_path, TreeNode *cur)
{
    // traverse all child nodes
    for (auto it : cur->children)
    {
        int pre_idx = findPrefix(dir_path, it->name);
        // no prefix find
        // eg: dir_path : adsd/bsd/cs and it->name : zcdc/
        if (pre_idx == 0)
        {
            continue;
        }
        // match dir path, change to next level dir
        // eg: dir_path : adsd/bsd and it->name : adsd/
        if (pre_idx == it->name.size())
        {
            // this is the last level, delete this node and return
            if (pre_idx == dir_path.size())
            {
                delete it;
                return;
            }
            cur = it;
            std::string next_dir = dir_path.substr(pre_idx, dir_path.size());
            return deleteDirNode(next_dir, cur);
        }
        // eg: dir_path : adsd/bsd/ and it->name : adsd/bsd/sdd/dsfg/
        else
        {
            if (dir_path[pre_idx] == '/')
            {
                std::vector<std::string> path_name = SplitString(dir_path, "/");
                if (path_name.size() == 1)
                {
                    delete it;
                    return;
                }
                else
                {
                    it->name = path_name[0];
                    for (auto level_path : path_name)
                    {
                        it->name = it->name + "/" + level_path;
                    }
                }
            }
        }
    }
}

TreeNode *Tree::getDirMode(std::string &dir_path, TreeNode *cur)
{

    //    for(int i = 0; i < cur->children.size(); i++){
    //        TreeNode *it = cur->children[i];
    //        int prefix_idx = findPrefix(dir_path, it->name);
    //        if( prefix_idx == it->name.size()){
    //        //match dir path, change to next dir
    //            cur = it;
    //            return getDirMode(dir_path.substr(prefix_idx), cur);
    //        }
    //    }
    while (!dir_path.empty())
    {
        int i;
        for (i = 0; i < cur->children.size(); i++)
        {
            int prefix_idx = 0;
            int length = cur->children[i]->name.size();
            while (prefix_idx < length && !(dir_path[prefix_idx] ^ cur->children[i]->name[prefix_idx]))
            {
                prefix_idx++;
            }
            if (prefix_idx == cur->children[i]->name.size())
            {
                cur = cur->children[i];
                dir_path.erase(0, prefix_idx);
                count1++;
                break;
            }
        }
        if (i == cur->children.size())
        {
            break;
        }
    }
    return cur;
}

void Tree::setFileMeta(std::string &file_path, int mode)
{
    fileMeta *file_meta = new fileMeta();
    file_meta->setMode(mode);

#ifdef USE_PMEMKV
    std::string meta = file_meta->getFileMeta();
    PutMetadataCache(file_path, meta);
#else
    file_map.insert({file_path, file_meta});
#endif
}
std::string Tree::getFileMeta(std::string &file_path)
{

#ifdef USE_PMEMKV
    std::string ret;
    GetMetadataCache(file_path, ret);
    return ret;
#else
    //        std::cout<<file_path<<std::endl;
    fileMeta *file_meta = file_map.at(file_path);
    return file_meta->getFileMeta();
#endif
}

long long Tree::treeTraverse()
{
    long long count1 = 0;
    std::queue<TreeNode *> tree_q;
    std::queue<std::string> name_q;
    name_q.push("root");
    tree_q.push(root);
    while (!tree_q.empty())
    {
        TreeNode *cur_node = tree_q.front();
        tree_q.pop();
        //        std::cout<< name_q.front() <<std::endl;
        count1++;
        name_q.pop();
        for (auto it : cur_node->children)
        {
            tree_q.push(it);
            name_q.push(it->name);
        }
    }

    return count1;
}

#ifdef USE_PMEMKV
void Tree::InitKVengine()
{
    LOG("Creating config");

    s = cfg.put_path("/dev/shm/metadata.poolset");

    ASSERT(s == pmem::kv::status::OK);
    s = cfg.put_size(SIZE);
    ASSERT(s == pmem::kv::status::OK);
    s = cfg.put_create_if_missing(true);
    ASSERT(s == pmem::kv::status::OK);

    //    LOG("Opening pmemkv database with 'cmap' engine");
    s = kv.open("cmap", std::move(cfg));
    ASSERT(s == pmem::kv::status::OK);
}

void Tree::GetMetadataCache(std::string &key, std::string &value)
{
    //    LOG("Reading key back");
    s = kv.get(key, &value);
    ASSERT(s == pmem::kv::status::OK);
}

void Tree::PutMetadataCache(std::string &key, std::string &value)
{
    //    LOG("Putting new key");
    s = kv.put(key, value);
    ASSERT(s == pmem::kv::status::OK);
}

void Tree::RemoveMetadataCache(std::string &key)
{
    //    LOG("Removing existing key");
    s = kv.remove(key);
    ASSERT(s == pmem::kv::status::OK);
}
#endif
