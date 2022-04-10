# compress tree开发文档

## 实现的目标
实现一个实现权限压缩的权限树，针对目录。

## 测试样例
目录测试样例
````
/home 777
/home/yyx 777
/home/yyx/dir1 777
/home/yyx/dir1/dir2 755
/home/yyx/dir2  555
/home/yyx/dir2/dir3 555
/home/yyx/temp 666

/home   777
|_/yyx/dir1/dir2 755
|_/yyx/dir2 555
|_/yyx/temp 666
````
文件元数据以绝对路径作为键，元数据部分作为值。以键值对的形式存储在std::map中。
一旦发生文件访问操作，首先会获取文件的元数据，其次从压缩过后的文件权限目录树获取对应的文件权限。
