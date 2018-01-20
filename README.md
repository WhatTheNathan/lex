# n-lexer
编译原理课程lexer大作业，基本是照着lex的方向去写，目前算是半个lex，有完整的RE=>NFA=>DFA=>ODFA(DFA优化)的流程，数据结构采用三元组的形式来表示图，但还存在较多问题，考试周先溜了...

## To Start

mkdir build

cd build

cmake ..

make

cd ..

cd bin/

./n_lexer

double click enter to END

![Image text](https://raw.githubusercontent.com/WhatTheNathan/n-lexer/master/images/image.png)

## To Do

* DFA优化为ODFA时，含终态的OSet不做优化，全部拆开。
* 增加更多RE。
* 实现lex文件转化机制。
* 存在太多暴力for循环，若RE为[a-z]、[A-Z]、[0-9]时构建ODFA耗时太久。
