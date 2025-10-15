注意：此项目专为Ubuntu系统设计，在其他操作系统上可能无法正常运行。

RPN Calculator (Ubuntu Only)
这是一个基于C++实现的逆波兰表示法（RPN）计算器，只能在Ubuntu系统上运行。

项目简介
RPN（Reverse Polish Notation）计算器使用后缀表达式进行计算，避免了传统中缀表达式中括号和运算符优先级的问题。本项目实现了一个功能丰富的RPN计算器，支持基本的四则运算、高级数学函数和历史记录功能。

功能特性
基本运算
加法（+）、减法（-）、乘法（*）、除法（/）

自动处理运算优先级

高级功能
平方根计算（sqrt）

幂运算（pow）

斐波那契数列计算（fib）

三角函数：正弦（sin）、余弦（cos）、正切（tan）

交互功能
交互式命令行界面

栈内容显示（display）

栈清空（clear）

批量表达式计算（eval）

历史记录
自动保存计算历史

历史记录查看（history）

历史记录清空（clearhistory）

系统要求
注意：此项目只能在Ubuntu系统上运行

Ubuntu 18.04 或更高版本

GCC 编译器

C++11 或更高标准

安装与编译
克隆项目到本地：

bash
git clone https://github.com/yourusername/rpn-calculator.git
cd rpn-calculator
编译项目：

bash
g++ -std=c++11 -o rpn_calculator rpn_calculator.cpp
运行程序：

bash
./rpn_calculator
使用方法
交互模式
启动程序后，您将进入交互式命令行界面：

text
RPN Calculator v2.0
Type 'help' for instructions or 'quit' to exit
RPN[0]> 
基本操作示例
text
RPN[0]> 5
Pushed: 5
RPN[1]> 3
Pushed: 3
RPN[2]> +
Result: 8.000000
RPN[1]> 
命令列表
<number> - 将数字压入栈

+, -, *, / - 基本算术运算

sqrt - 平方根

pow - 幂运算 (a^b)

fib - 斐波那契数

sin, cos, tan - 三角函数

display - 显示当前栈内容

clear - 清空栈

history - 显示计算历史

clearhistory - 清空历史记录

eval <expr> - 计算完整的RPN表达式

help - 显示帮助信息

quit - 退出计算器

表达式计算示例
使用 eval 命令计算完整表达式：

text
RPN[0]> eval 3 4 + 2 *
Result: 14.000000
或者直接在交互模式下逐步输入：

text
RPN[0]> 3
Pushed: 3
RPN[1]> 4
Pushed: 4
RPN[2]> +
Result: 7.000000
RPN[1]> 2
Pushed: 2
RPN[2]> *
Result: 14.000000
RPN[1]> 
高级功能示例
text
RPN[0]> 9 sqrt
Result: 3.000000
RPN[1]> 5 2 pow
Result: 25.000000
RPN[1]> 7 fib
Result: 13.000000
RPN[1]> 45 sin
Result: 0.850904
项目结构
text
rpn-calculator/
├── rpn_calculator.cpp    # 主程序源代码
├── rpn_calc.html         # 项目展示页面
├── README.md             # 项目说明文档
└── Makefile              # 编译脚本（可选）
技术实现
使用C++标准库中的stack容器管理操作数

采用面向对象设计，封装RPN计算逻辑

实现错误处理和异常管理

提供完整的用户交互界面

开发人员
项目作者：Your Name

联系方式：your.email@example.com

许可证
本项目采用MIT许可证。详情请参阅LICENSE文件。

贡献指南
欢迎提交Issue和Pull Request来改进这个项目。
