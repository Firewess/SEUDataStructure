## **项目介绍**

此项目为本人本科在东南大学软件学院学习数据结构时的作业，现课程完结存档，绝大部分为可以直接运行的程序，希望后来的学弟学妹不要直接cpoy，作为参考会更有价值。

## 文件结构介绍

+ **.h文件命名格式**：
  文件页码_文件页码.h，例：P93_P94.h代表这个头文件内含有P93、P94的作业，一个文件代表一个小节的作业

+ **.h文件内容**：
  文件内是对应页码的作业，文件最后有一个run函数，如果文件名为P93_P94.h，run函数则被命名为run_P93_P94()，以此类推，run函数为一些测试用例

+ **.h文件使用方法**：
  在一个cpp文件中包含对应的头文件，如#include "P93_P94.h"，后在main()函数中调用对用的run函数即可，如run_P93_P94();


**ps: 对于一些不用编写代码，而是分析、计算的题目，均按照题目顺序，从上至下的写在了.h文件内的注释中**
