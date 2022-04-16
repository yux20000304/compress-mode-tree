# compress-mode-tree

## 目标及意义

- 单个文件访问需要通过在文件目录树中逐级访问父目录获取权限，本项目把目录权限进行压缩。通过减小树高的方式减小逐级访问次数。
- 加速权限查询，同时增大权限树容量。

## 项目结构介绍

````
compress-mode-tree
├── dirinfo.txt     //读取出来的目录信息
├── docs
│       └── compress_tree.md
├── exception.txt
├── fileinfo.txt    //读取出来的文件信息
├── include
│        ├── compress_tree.h
│        ├── compress_treenode.h
│        ├── filemeta.h
│        ├── proper_tree.h
│        └── tools.h
├── LICENSE
├── main.cpp
├── path_generate.py    //读取文件目录和文件名
├── README.md
└── src
    ├── compress_tree.cpp
    ├── compress_treenode.cpp
    ├── filemeta.cpp
    ├── proper_tree.cpp
    └── tools.cpp
````
- 对于压缩权限树，单个文件的元数据以键值对的形式存储在pmem上的数据库中。
- 对于普通文件目录树，单个文件的元数据存储在文件节点中。


## 测试结果

- 原有的文件目录项数目：63434
- 压缩过后的文件目录项数目：4428
- 使用目录树遍历所有文件，访问的目录次数：5705074
- 使用压缩权限树遍历所有文件，访问的目录次数：1869109
- 理论优化率：68.3%
- 实际优化率：等待后续去机器上测试