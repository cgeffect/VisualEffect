
//https://blog.csdn.net/libing_zeng/article/details/78350329
/*
 Xcode 报错：a missing vtable usually means the first non-inline virtual member function has no definition.

 原因：

        如果子类继承了父类但是没有实现父类的虚函数，就会报如上错误。
        同时，没有实现析构函数也会出现同样问题。

 所以你要注意自己继承的父类的函数，如果前面加了virtual 但是却没有自定义实现，那就把这个函数删掉。

 */

//这个错误两种解决办法, 第一个添加libc++库, 或者工程种创建.mm文件
