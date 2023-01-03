//
// Created by yyx on 2022/4/10.
//

#include <vector>
#include <queue>
#include "proper_tree.h"
#include "tools.h"

properTreeNode::properTreeNode()
{
    time = get_time();
}

properTreeNode::~properTreeNode() {}

properTree::properTree() {}

properTree::~properTree() {}

void properTree::addNode(std::vector<std::string> path, properTreeNode *cur)
{
    if (path.size() == 0)
    {
        return;
    }
    for (auto child : cur->children)
    {
        if (child.first == path[0])
        {
            path.erase(path.begin());
            return addNode(path, child.second);
        }
    }
    properTreeNode *new_node = new properTreeNode();
    new_node->name = path[0];
    cur->children.insert({path[0], new_node});
    path.erase(path.begin());
    return addNode(path, new_node);
}

properTreeNode *properTree::getNode(std::vector<std::string> path, properTreeNode *cur)
{
    if (path.size() == 0)
    {
        return cur;
    }
    for (auto child : cur->children)
    {
        if (child.first == path[0])
        {
            path.erase(path.begin());
            count2++;
            return getNode(path, child.second);
        }
    }
    return nullptr;
}

long long properTree::treeTraverse()
{
    long long count1 = 0;

    std::queue<properTreeNode *> tree_q;
    std::queue<std::string> name_q;
    name_q.push("root");
    tree_q.push(root);
    while (!tree_q.empty())
    {
        properTreeNode *cur_node = tree_q.front();
        tree_q.pop();
        std::cout << name_q.front() << std::endl;
        count1++;
        name_q.pop();
        for (auto it : cur_node->children)
        {
            tree_q.push(it.second);
            name_q.push(it.first);
        }
    }

    return count1;
}