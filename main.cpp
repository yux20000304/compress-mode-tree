#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include "tools.h"
#include "compress_tree.h"
#include "proper_tree.h"


int main()
{
    Tree *tree1 = new Tree();
    properTree *tree2 = new properTree();

    tree1->root = new TreeNode();
    tree2->root = new properTreeNode();
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
        std::vector<std::string> path_name = SplitString(textline[0],"/");
        tree2->addNode(path_name,tree2->root);
        count2++;
    }
    infile1.close();

    //add file metadata
    std::ifstream infile2("../fileinfo.txt",std::ios::in);
    while(std::getline(infile2,text)){
        std::vector<std::string> textline = SplitString(text,"&");
//        std::cout << textline[0] << std::endl;
        int mode = stoi(textline[1]);
//        std::cout<< textline[0] <<std::endl;
        tree1->setFileMeta(textline[0], mode);
        std::vector<std::string> path_name = SplitString(textline[0],"/");
        tree2->addNode(path_name, tree2->root);
        count3++;
    }
    infile2.close();

//    long long ret =tree1->treeTraverse();
//    long long ret1 =tree2->treeTraverse();
//    std::cout << ret << std::endl;
//    std::cout << ret1 << std::endl;
    std::cout << count2 << std::endl;
    std::cout << count3 << std::endl;

    clock_t start,stop;
    double duration;
    std::ifstream infile3("../fileinfo.txt",std::ios::in);
    start = clock();
    while(std::getline(infile3,text)){
        std::vector<std::string> textline = SplitString(text,"&");
        tree1->getDirMode(textline[0], tree1->root);
//        tree1->getFileMeta(textline[0]);
    }
    stop = clock();
    duration = (stop-start)/CLOCKS_PER_SEC;
    std::cout<< "time:" << duration << "s" << std::endl;

    std::ifstream infile4("../fileinfo.txt",std::ios::in);
    start = clock();
    while(std::getline(infile4,text)){
        std::vector<std::string> textline = SplitString(text,"&");
        std::vector<std::string> path_name = SplitString(textline[0],"/");
        properTreeNode *temp = tree2->getNode(path_name, tree2->root);
        int temp1 = temp->mode;
        std::string time_meta = temp->time + std::to_string(temp1);
    }
    stop = clock();
    duration = (stop-start)/CLOCKS_PER_SEC;
    std::cout<< "time:" << duration << "s" << std::endl;

    return 0;
}