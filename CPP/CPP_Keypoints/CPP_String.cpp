/*******************************************************************************
                      字符串
    C++ 提供两种类型的字符串表示形式
    1. C-样式的字符串 （字符串数组)
    2.  string 类

*******************************************************************************/
/**
1. 字符串数组
   （1）char vowels[] = "aeiou";
    (2) C++ 用来操作字符串的有用的函数
        <1> strcpy(str1, str2);  // 复制字符串 str2 到 字符串 str1
        <2> strcat(str1, str2);  // 链接字符串 str2 到 字符串 str1 的末尾
        <3> strlen(str1);        // 返回字符串 str1 的长度
        <4> strcmp(str1, str2);  // 比较两个字符串，返回 0, <0, 或者 >0
        <5> strchr(str1, ch);    // 返回一个指针，指向字符串 str1 中字符 ch 的第一次出现的位置
        <6> strstr(str1, str2);  // 返回一个指针，指向字符串 str1 中字符 str2 的第一次出现的位置

**/


/**
2. string 类
   （1）使用string类，需包含头文件<string>, 同时需要一个 using 声明
    (2) 声明 string 对象
        string myStream;   // An empty string
        string proverb = "Many a mickle makes a muckle";
    (3) string 类型的操作：
        <1> 连接
        <2> string 类的各种成员函数操作
            assign()                         // 赋以新值
            swap()                           // 交换两个字符串的内容
            +=, append(), push_back()        // 在尾部添加字符
            insert()                         // 插入字符
            erase()                          // 删除字符
            clear()                          // 清楚全部字符
            replace()                        // 替换字符
            +                                // 串联字符串
            ==,!=,<,<=,>,>=,compare()        // 比较字符串
            size(), length()                 // 返回字符数量
            max_size()                       // 返回字符的可能最大个数
            empty()                          // 判断字符串是否为空
            capacity()                       // 返回重新分配之前的字符容量
            [], at()                         // 存取单一字符
            >>,getline                       // 从stream读取某值
            <<                               // 将某值写入stream
            copy()                           // 将某值复制给一个C_string
            c_str()                          // 将内容以C_string返回
            data()                           // 将内容以字符数组形式返回
            substr()                         // 返回某个子字符串
            find()                           // 查找
            .......
    参考链接：
    https://blog.csdn.net/pengnanzheng/article/details/80549445
    https://blog.csdn.net/pengnanzheng/article/details/80549445
**/



#if 1

/// string member functions




/// member constants




//// non-member overloads


#endif
