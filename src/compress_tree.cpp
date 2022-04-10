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

void Tree::addDirNode(const std::string dir_path, TreeNode *cur, int st_mode, int parent_mode) {

    for(auto it:cur->children){
        int pre_idx = findPrefix( dir_path, it->name);
        if(pre_idx == 0){
            continue;
        }
        //match dir path, change to next dir
        if(pre_idx == it->name.size()){
            cur = it;
            std::string next_dir = dir_path.substr(pre_idx, dir_path.size());
            int cur_mode = it->getDirMode();
            return addDirNode(next_dir, cur, st_mode, cur_mode);
        }
    }
    //has same mode with parent node
    if(st_mode == parent_mode){
        return;
    }
    else{ //add new node
        TreeNode *add_node = new TreeNode();
        add_node->name = dir_path;
        add_node->setDirMode(st_mode);
        cur->children.push_back(add_node);
        return;
    }
    return;
}

TreeNode *Tree::getDirMode(std::string &dir_path, TreeNode *cur) {


//    for(int i = 0; i < cur->children.size(); i++){
//        TreeNode *it = cur->children[i];
//        int prefix_idx = findPrefix(dir_path, it->name);
//        if( prefix_idx == it->name.size()){
//        //match dir path, change to next dir
//            cur = it;
//            return getDirMode(dir_path.substr(prefix_idx), cur);
//        }
//    }
    while(!dir_path.empty()){
        int i;
        for(i = 0; i < cur->children.size(); i++){
            int prefix_idx = 0;
            int length = cur->children[i]->name.size();
            while (prefix_idx < length && !(dir_path[prefix_idx] ^ cur->children[i]->name[prefix_idx])) {
                prefix_idx++;
            }
            if( prefix_idx == cur->children[i]->name.size()){
                cur = cur->children[i];
                dir_path.erase(0,prefix_idx);
                break;
            }
        }
        if(i == cur->children.size()){
            break;
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
            tree_q.push(it);
            name_q.push(it->name);
        }
    }

    return count1;
}