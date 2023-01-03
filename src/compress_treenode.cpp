//
// Created by yyx on 2022/4/9.
//

#include "compress_treenode.h"

TreeNode::TreeNode() {

}

TreeNode::~TreeNode() {
    for(auto i : children){
        delete i;
    }
}

void TreeNode::setDirMode(int indir_mode) {
    dir_mode = indir_mode;
}

int TreeNode::getDirMode() {
    return dir_mode;
}

