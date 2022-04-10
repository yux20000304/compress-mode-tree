//
// Created by yyx on 2022/4/9.
//
#include <queue>
#include"compress_tree.h"
#include"tools.h"


fileMeta::fileMeta() {
    setFileMeta();
}

fileMeta::~fileMeta() {}

void fileMeta::setFileMeta() {
    time = get_time();
}

std::string fileMeta::getFileMeta() {
    return time + std::to_string(mode);
}

const std::string &fileMeta::getTime() const {
    return time;
}

void fileMeta::setTime(const std::string &time) {
    fileMeta::time = time;
}

int fileMeta::getMode() const {
    return mode;
}

void fileMeta::setMode(int mode) {
    fileMeta::mode = mode;
}

Tree::Tree() {}

Tree::~Tree() {}

void Tree::addDirNode(std::string dir_path, TreeNode *cur, int st_mode, int parent_mode) {

    for(auto it:cur->children){
        int pre_idx = findPrefix(it.first, dir_path);
        if(pre_idx == 0){
            continue;
        }
        //match dir path, change to next dir
        if(pre_idx == it.first.size()){
            cur = cur->children.at(it.first);
            std::string next_dir = dir_path.substr(pre_idx, dir_path.size());
            int cur_mode = it.second->getDirMode();
            return addDirNode(next_dir, it.second, st_mode, cur_mode);
        }
    }
    //has same mode with parent node
    if(st_mode == parent_mode){
        return;
    }
    else{ //add new node
        TreeNode *add_node = new TreeNode();
        add_node->setDirMode(st_mode);
        cur->children.insert({dir_path, add_node});
        return;
    }
    return;
}

TreeNode *Tree::getDirMode(std::string dir_path, TreeNode *cur) {
    for(auto it:cur->children){
        std::string next_dir = dir_path.substr(0,it.first.size());
        if( next_dir == it.first){
        //match dir path, change to next dir
            cur = it.second;
            std::string next_dir = dir_path.substr(it.first.size(), dir_path.size());
            return getDirMode(next_dir, cur);
        }
    }
    return cur;
}

void Tree::setFileMeta(std::string &file_path, int mode) {
    fileMeta *file_meta = new fileMeta();
    file_meta->setMode(mode);
    file_map.insert({file_path, file_meta});
}

std::string Tree::getFileMeta(std::string &file_path) {
    fileMeta *file_meta = file_map.at(file_path);
    return file_meta->getFileMeta();
}

long long Tree::treeTraverse() {
    long long count1 = 0;
    std::queue<TreeNode*> tree_q;
    std::queue<std::string> name_q;
    name_q.push("root");
    tree_q.push(root);
    while(!tree_q.empty()) {
        TreeNode *cur_node = tree_q.front();
        tree_q.pop();
        std::cout<< name_q.front() <<std::endl;
        count1++;
        name_q.pop();
        for(auto it : cur_node->children){
            tree_q.push(it.second);
            name_q.push(it.first);
        }
    }

    return count1;
}