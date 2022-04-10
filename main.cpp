#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include "tools.h"
#include "compress_tree.h"


int main()
{
    Tree *tree1 = new Tree();
    tree1->root = new TreeNode();
    long long count2 = 0;
    long long count3 = 0;

    //add dir node
    std::ifstream infile1("../dirinfo.txt",std::ios::in);
    std::string text;
    while(std::getline(infile1,text)){
        std::vector<std::string> textline = SplitString(text,"&");
//        std::cout << textline[0] << std::endl;
        int mode = stoi(textline[1]);
//        std::cout<< textline[0] <<std::endl;
        tree1->addDirNode(textline[0], tree1->root, mode, 0);
        count2++;
    }

    //add file metadata
    std::ifstream infile2("../fileinfo.txt",std::ios::in);
    while(std::getline(infile2,text)){
        std::vector<std::string> textline = SplitString(text,"&");
//        std::cout << textline[0] << std::endl;
        int mode = stoi(textline[1]);
//        std::cout<< textline[0] <<std::endl;
        tree1->setFileMeta(textline[0], mode);
        count3++;
    }

    long long ret =tree1->treeTraverse();
    std::cout << ret << std::endl;
    std::cout << count2 << std::endl;
    std::cout << count3 << std::endl;
    return 0;
}