#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <thread>
#include "tools.h"
#include "include/compress_tree.h"
#include "include/proper_tree.h"

#define MULTI_THREADS 0

const uint64_t SIZE = 1024UL * 1024UL * 1024UL;

void *getMode(Tree *tree, std::string &dir_path, TreeNode *root_node)
{
    tree->getDirMode(dir_path, tree->root);
    return nullptr;
}

int main()
{
    // tree1 is the mode compressed tree
    // tree2 is the proper file tree
    Tree *tree1 = new Tree();
    properTree *tree2 = new properTree();

    tree1->root = new TreeNode();
    tree2->root = new properTreeNode();

    long long count1 = 0;
    long long count2 = 0;
    long long count3 = 0;

#ifdef USE_PMEMKV
    tree1->InitKVengine();
#endif

    // create mode compressed tree
    std::ifstream infile1("../dirinfo.txt", std::ios::in); // read data from dirinfo.txt
    std::string text;
    while (std::getline(infile1, text))
    {
        std::vector<std::string> textline = SplitString(text, "&");
        //        std::cout << textline[0] << std::endl;
        int mode = stoi(textline[1]); // get mode
        //        std::cout<< textline[0] <<std::endl;
        tree1->addDirNode(textline[0], tree1->root, mode, 0);
        std::vector<std::string> path_name = SplitString(textline[0], "/");
        tree2->addNode(path_name, tree2->root);
        count1++;
    }
    infile1.close();

    // put file metadata.
    // for mode compressed tree, file metadata is put into a hashmap
    // for proper file tree, file metadata is added as a node
    std::ifstream infile2("../fileinfo.txt", std::ios::in);
    while (std::getline(infile2, text))
    {
        std::vector<std::string> textline = SplitString(text, "&");
        //        std::cout << textline[0] << std::endl;
        int mode = stoi(textline[1]); // get mode
        //        std::cout<< textline[0] <<std::endl;
        tree1->setFileMeta(textline[0], mode);
        std::vector<std::string> path_name = SplitString(textline[0], "/");
        tree2->addNode(path_name, tree2->root);
        count2++;
    }
    infile2.close();

    count3 = tree1->treeTraverse();
    //    long long ret1 =tree2->treeTraverse();
    //    std::cout << ret << std::endl;
    //    std::cout << ret1 << std::endl;
    std::cout << "directory number:" << count1 << std::endl;
    std::cout << "file number:" << count2 << std::endl;
    std::cout << "compress directory number:" << count3 << std::endl;

    // get all file metadata from the mode compressed tree
    clock_t start, stop;
    double duration;
    std::ifstream infile3("../fileinfo.txt", std::ios::in);
    start = clock();
    while (std::getline(infile3, text))
    {
        std::vector<std::string> textline = SplitString(text, "&");
        std::string temptextline = textline[0];
        if (MULTI_THREADS)
        {
            std::thread t1(getMode, std::ref(tree1), std::ref(textline[0]), std::ref(tree1->root));
            tree1->getFileMeta(temptextline);
            t1.join();
        }
        else
        {
            tree1->getDirMode(textline[0], tree1->root);
            tree1->getFileMeta(temptextline);
        }
    }
    stop = clock();
    duration = (stop - start) / CLOCKS_PER_SEC;
    std::cout << "time:" << duration << "s" << std::endl;

    // get all file metadata from the proper file tree
    std::ifstream infile4("../fileinfo.txt", std::ios::in);
    start = clock();
    while (std::getline(infile4, text))
    {
        std::vector<std::string> textline = SplitString(text, "&");
        std::vector<std::string> path_name = SplitString(textline[0], "/");
        properTreeNode *temp = tree2->getNode(path_name, tree2->root);
        int temp1 = temp->mode;
        std::string time_meta = temp->time + std::to_string(temp1);
    }
    stop = clock();
    duration = (stop - start) / CLOCKS_PER_SEC;
    std::cout << "time:" << duration << "s" << std::endl;

    std::cout << "compress tree dir visit number:" << tree1->count1 << std::endl;
    std::cout << "proper tree dir visit number:" << tree2->count2 << std::endl;

    return 0;
}