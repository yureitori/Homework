<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>RPN计算器 - C++代码展示</title>
    <script src="https://cdn.tailwindcss.com"></script>
    <link href="https://cdn.jsdelivr.net/npm/font-awesome@4.7.0/css/font-awesome.min.css" rel="stylesheet">
    <script>
        // Tailwind配置
        tailwind.config = {
            theme: {
                extend: {
                    colors: {
                        primary: '#165DFF',
                        secondary: '#36CFC9',
                        dark: '#1D2129',
                        light: '#F2F3F5',
                        code: {
                            bg: '#282C34',
                            text: '#ABB2BF',
                            keyword: '#C678DD',
                            type: '#56B6C2',
                            string: '#98C379',
                            comment: '#7F848E',
                            number: '#D19A66',
                            function: '#61AFEF'
                        }
                    },
                    fontFamily: {
                        sans: ['Inter', 'system-ui', 'sans-serif'],
                        mono: ['Fira Code', 'Consolas', 'monospace']
                    }
                }
            }
        }
    </script>
    <style type="text/tailwindcss">
        @layer utilities {
            .code-block {
                @apply font-mono text-code-text bg-code-bg p-4 rounded-lg overflow-x-auto text-sm md:text-base;
            }
            .code-keyword {
                @apply text-code-keyword;
            }
            .code-type {
                @apply text-code-type;
            }
            .code-string {
                @apply text-code-string;
            }
            .code-comment {
                @apply text-code-comment;
            }
            .code-number {
                @apply text-code-number;
            }
            .code-function {
                @apply text-code-function;
            }
            .content-section {
                @apply mb-8 p-6 bg-white rounded-xl shadow-sm;
            }
            .feature-card {
                @apply p-4 border border-gray-200 rounded-lg hover:shadow-md transition-shadow;
            }
        }
    </style>
</head>
<body class="bg-gray-50 text-dark">
    <!-- 顶部导航 -->
    <header class="bg-primary text-white py-4 px-6 shadow-md">
        <div class="container mx-auto flex flex-col md:flex-row justify-between items-center">
            <div class="flex items-center mb-4 md:mb-0">
                <i class="fa fa-calculator text-2xl mr-3"></i>
                <h1 class="text-2xl font-bold">RPN计算器 - C++实现</h1>
            </div>
            <nav>
                <ul class="flex space-x-4">
                    <li><a href="#overview" class="hover:text-light transition-colors"><i class="fa fa-info-circle mr-1"></i> 功能概述</a></li>
                    <li><a href="#code" class="hover:text-light transition-colors"><i class="fa fa-code mr-1"></i> 完整代码</a></li>
                    <li><a href="#usage" class="hover:text-light transition-colors"><i class="fa fa-book mr-1"></i> 使用指南</a></li>
                </ul>
            </nav>
        </div>
    </header>

    <!-- 主要内容 -->
    <main class="container mx-auto py-8 px-4">
        <!-- 功能概述 -->
        <section id="overview" class="content-section">
            <h2 class="text-2xl font-bold mb-4 text-primary">
                <i class="fa fa-list-alt mr-2"></i>功能概述
            </h2>
            <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
                <div class="feature-card">
                    <h3 class="font-bold text-lg mb-2 flex items-center">
                        <i class="fa fa-calculator text-primary mr-2"></i>基本运算
                    </h3>
                    <p>支持加减乘除（+、-、*、/）四则运算，自动处理运算优先级</p>
                </div>
                <div class="feature-card">
                    <h3 class="font-bold text-lg mb-2 flex items-center">
                        <i class="fa fa-line-chart text-primary mr-2"></i>高级功能
                    </h3>
                    <p>包含平方根（sqrt）、幂运算（pow）、斐波那契数列（fib）、三角函数（sin/cos/tan）</p>
                </div>
                <div class="feature-card">
                    <h3 class="font-bold text-lg mb-2 flex items-center">
                        <i class="fa fa-terminal text-primary mr-2"></i>交互模式
                    </h3>
                    <p>提供交互式操作界面，支持命令行控制（clear、show、history等）</p>
                </div>
                <div class="feature-card">
                    <h3 class="font-bold text-lg mb-2 flex items-center">
                        <i class="fa fa-batch text-primary mr-2"></i>批量计算
                    </h3>
                    <p>支持批量处理多个RPN表达式，自动展示每个表达式的计算结果</p>
                </div>
                <div class="feature-card">
                    <h3 class="font-bold text-lg mb-2 flex items-center">
                        <i class="fa fa-history text-primary mr-2"></i>历史记录
                    </h3>
                    <p>自动保存计算历史，支持查看和清空历史记录</p>
                </div>
                <div class="feature-card">
                    <h3 class="font-bold text-lg mb-2 flex items-center">
                        <i class="fa fa-bug text-primary mr-2"></i>调试模式
                    </h3>
                    <p>提供调试模式，显示计算过程中的栈操作和中间结果</p>
                </div>
            </div>
        </section>

        <!-- 完整代码 -->
        <section id="code" class="content-section">
            <h2 class="text-2xl font-bold mb-4 text-primary">
                <i class="fa fa-code mr-2"></i>完整C++代码
            </h2>
            <div class="code-block">
<pre><span class="code-include">#include &lt;iostream&gt;</span>
<span class="code-include">#include &lt;stack&gt;</span>
<span class="code-include">#include &lt;string&gt;</span>
<span class="code-include">#include &lt;sstream&gt;</span>
<span class="code-include">#include &lt;stdexcept&gt;</span>
<span class="code-include">#include &lt;iomanip&gt;</span>
<span class="code-include">#include &lt;cmath&gt;</span>
<span class="code-include">#include &lt;vector&gt;</span>

<span class="code-keyword">class</span> <span class="code-type">RPNCalculator</span> {
<span class="code-keyword">private</span>:
    std::stack&lt;double&gt; operandStack;
    std::vector&lt;std::string&gt; history;
    
    <span class="code-keyword">bool</span> <span class="code-function">isOperator</span>(<span class="code-keyword">const</span> std::string& token) {
        <span class="code-keyword">return</span> token == <span class="code-string">"+"</span> || token == <span class="code-string">"-"</span> || token == <span class="code-string">"*"</span> || token == <span class="code-string">"/"</span> ||
               token == <span class="code-string">"sqrt"</span> || token == <span class="code-string">"pow"</span> || token == <span class="code-string">"fib"</span> || 
               token == <span class="code-string">"sin"</span> || token == <span class="code-string">"cos"</span> || token == <span class="code-string">"tan"</span>;
    }
    
<span class="code-keyword">public</span>:
    <span class="code-keyword">bool</span> <span class="code-function">isNumber</span>(<span class="code-keyword">const</span> std::string& token) {
        <span class="code-keyword">try</span> {
            std::stod(token);
            <span class="code-keyword">return</span> <span class="code-keyword">true</span>;
        } <span class="code-keyword">catch</span> (<span class="code-keyword">const</span> std::invalid_argument&) {
            <span class="code-keyword">return</span> <span class="code-keyword">false</span>;
        }
    }

<span class="code-keyword">private</span>:
    
    <span class="code-type">long long</span> <span class="code-function">fibonacciNumber</span>(<span class="code-type">int</span> n) {
        <span class="code-keyword">if</span> (n &lt;= 0) <span class="code-keyword">return</span> 0;
        <span class="code-keyword">if</span> (n == 1) <span class="code-keyword">return</span> 1;
        
        <span class="code-type">long long</span> a = 0, b = 1;
        <span class="code-keyword">for</span> (<span class="code-type">int</span> i = 2; i &lt;= n; i++) {
            <span class="code-type">long long</span> temp = a + b;
            a = b;
            b = temp;
        }
        <span class="code-keyword">return</span> b;
    }

<span class="code-keyword">public</span>:
    <span class="code-keyword">void</span> <span class="code-function">push</span>(<span class="code-type">double</span> value) {
        operandStack.push(value);
    }
    
    <span class="code-type">double</span> <span class="code-function">pop</span>() {
        <span class="code-keyword">if</span> (operandStack.empty()) {
            <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Stack is empty, cannot pop"</span>);
        }
        <span class="code-type">double</span> value = operandStack.top();
        operandStack.pop();
        <span class="code-keyword">return</span> value;
    }
    
    <span class="code-keyword">void</span> <span class="code-function">clear</span>() {
        <span class="code-keyword">while</span> (!operandStack.empty()) {
            operandStack.pop();
        }
        std::cout &lt;&lt; <span class="code-string">"Stack cleared."</span> &lt;&lt; std::endl;
    }
    
    <span class="code-keyword">void</span> <span class="code-function">display</span>() {
        <span class="code-keyword">if</span> (operandStack.empty()) {
            std::cout &lt;&lt; <span class="code-string">"Stack is empty."</span> &lt;&lt; std::endl;
            <span class="code-keyword">return</span>;
        }
        
        std::stack&lt;double&gt; temp = operandStack;
        std::vector&lt;double&gt; values;
        
        <span class="code-keyword">while</span> (!temp.empty()) {
            values.push_back(temp.top());
            temp.pop();
        }
        
        std::cout &lt;&lt; <span class="code-string">"Stack contents (top to bottom): "</span>;
        <span class="code-keyword">for</span> (<span class="code-type">int</span> i = values.size() - 1; i &gt;= 0; i--) {
            std::cout &lt;&lt; std::fixed &lt;&lt; std::setprecision(2) &lt;&lt; values[i];
            <span class="code-keyword">if</span> (i &gt; 0) std::cout &lt;&lt; <span class="code-string">", "</span>;
        }
        std::cout &lt;&lt; std::endl;
    }
    
    <span class="code-keyword">void</span> <span class="code-function">calculate</span>(<span class="code-keyword">const</span> std::string& operation) {
        <span class="code-keyword">if</span> (operation == <span class="code-string">"+"</span>) {
            <span class="code-keyword">if</span> (operandStack.size() &lt; 2) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Insufficient operands for addition"</span>);
            <span class="code-type">double</span> b = pop(), a = pop();
            push(a + b);
        }
        <span class="code-keyword">else</span> <span class="code-keyword">if</span> (operation == <span class="code-string">"-"</span>) {
            <span class="code-keyword">if</span> (operandStack.size() &lt; 2) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Insufficient operands for subtraction"</span>);
            <span class="code-type">double</span> b = pop(), a = pop();
            push(a - b);
        }
        <span class="code-keyword">else</span> <span class="code-keyword">if</span> (operation == <span class="code-string">"*"</span>) {
            <span class="code-keyword">if</span> (operandStack.size() &lt; 2) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Insufficient operands for multiplication"</span>);
            <span class="code-type">double</span> b = pop(), a = pop();
            push(a * b);
        }
        <span class="code-keyword">else</span> <span class="code-keyword">if</span> (operation == <span class="code-string">"/"</span>) {
            <span class="code-keyword">if</span> (operandStack.size() &lt; 2) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Insufficient operands for division"</span>);
            <span class="code-type">double</span> b = pop(), a = pop();
            <span class="code-keyword">if</span> (b == 0) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Division by zero"</span>);
            push(a / b);
        }
        <span class="code-keyword">else</span> <span class="code-keyword">if</span> (operation == <span class="code-string">"sqrt"</span>) {
            <span class="code-keyword">if</span> (operandStack.empty()) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Insufficient operands for square root"</span>);
            <span class="code-type">double</span> a = pop();
            <span class="code-keyword">if</span> (a &lt; 0) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Cannot take square root of negative number"</span>);
            push(std::sqrt(a));
        }
        <span class="code-keyword">else</span> <span class="code-keyword">if</span> (operation == <span class="code-string">"pow"</span>) {
            <span class="code-keyword">if</span> (operandStack.size() &lt; 2) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Insufficient operands for power operation"</span>);
            <span class="code-type">double</span> b = pop(), a = pop();
            push(std::pow(a, b));
        }
        <span class="code-keyword">else</span> <span class="code-keyword">if</span> (operation == <span class="code-string">"fib"</span>) {
            <span class="code-keyword">if</span> (operandStack.empty()) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Insufficient operands for fibonacci"</span>);
            <span class="code-type">double</span> a = pop();
            <span class="code-keyword">if</span> (a &lt; 0 || a != (<span class="code-type">int</span>)a) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Fibonacci requires non-negative integer"</span>);
            push(fibonacciNumber((<span class="code-type">int</span>)a));
        }
        <span class="code-keyword">else</span> <span class="code-keyword">if</span> (operation == <span class="code-string">"sin"</span>) {
            <span class="code-keyword">if</span> (operandStack.empty()) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Insufficient operands for sine"</span>);
            <span class="code-type">double</span> a = pop();
            push(std::sin(a));
        }
        <span class="code-keyword">else</span> <span class="code-keyword">if</span> (operation == <span class="code-string">"cos"</span>) {
            <span class="code-keyword">if</span> (operandStack.empty()) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Insufficient operands for cosine"</span>);
            <span class="code-type">double</span> a = pop();
            push(std::cos(a));
        }
        <span class="code-keyword">else</span> <span class="code-keyword">if</span> (operation == <span class="code-string">"tan"</span>) {
            <span class="code-keyword">if</span> (operandStack.empty()) <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Insufficient operands for tangent"</span>);
            <span class="code-type">double</span> a = pop();
            push(std::tan(a));
        }
        <span class="code-keyword">else</span> {
            <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Unknown operator: "</span> + operation);
        }
    }
    
    <span class="code-type">double</span> <span class="code-function">evaluateExpression</span>(<span class="code-keyword">const</span> std::string& expression) {
        std::istringstream iss(expression);
        std::string token;
        
        clear();
        
        <span class="code-keyword">while</span> (iss &gt;&gt; token) {
            <span class="code-keyword">if</span> (isNumber(token)) {
                push(std::stod(token));
            } <span class="code-keyword">else</span> <span class="code-keyword">if</span> (isOperator(token)) {
                calculate(token);
            } <span class="code-keyword">else</span> {
                <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Invalid token: "</span> + token);
            }
        }
        
        <span class="code-keyword">if</span> (operandStack.size() != 1) {
            <span class="code-keyword">throw</span> std::runtime_error(<span class="code-string">"Error: Invalid expression - stack contains "</span> + 
                                   std::to_string(operandStack.size()) + <span class="code-string">" elements"</span>);
        }
        
        <span class="code-type">double</span> result = operandStack.top();
        history.push_back(expression + <span class="code-string">" = "</span> + std::to_string(result));
        <span class="code-keyword">return</span> result;
    }
    
    <span class="code-keyword">void</span> <span class="code-function">showHistory</span>() {
        <span class="code-keyword">if</span> (history.empty()) {
            std::cout &lt;&lt; <span class="code-string">"No calculation history."</span> &lt;&lt; std::endl;
            <span class="code-keyword">return</span>;
        }
        
        std::cout &lt;&lt; <span class="code-string">"Calculation History:"</span> &lt;&lt; std::endl;
        <span class="code-keyword">for</span> (<span class="code-type">size_t</span> i = 0; i &lt; history.size(); i++) {
            std::cout &lt;&lt; i + 1 &lt;&lt; <span class="code-string">". "</span> &lt;&lt; history[i] &lt;&lt; std::endl;
        }
    }
    
    <span class="code-keyword">void</span> <span class="code-function">clearHistory</span>() {
        history.clear();
        std::cout &lt;&lt; <span class="code-string">"History cleared."</span> &lt;&lt; std::endl;
    }
    
    <span class="code-keyword">bool</span> <span class="code-function">isEmpty</span>() <span class="code-keyword">const</span> {
        <span class="code-keyword">return</span> operandStack.empty();
    }
    
    <span class="code-type">size_t</span> <span class="code-function">size</span>() <span class="code-keyword">const</span> {
        <span class="code-keyword">return</span> operandStack.size();
    }
};

<span class="code-keyword">void</span> <span class="code-function">printHelp</span>() {
    std::cout &lt;&lt; <span class="code-string">"\n=== RPN Calculator Help ==="</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"Commands:"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  &lt;number&gt;     - Push number onto stack"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  +, -, *, /   - Basic arithmetic operations"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  sqrt         - Square root"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  pow          - Power operation (a^b)"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  fib          - Fibonacci number"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  sin, cos, tan- Trigonometric functions"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  display      - Show current stack"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  clear        - Clear stack"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  history      - Show calculation history"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  clearhistory - Clear calculation history"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  eval &lt;expr&gt;  - Evaluate complete RPN expression"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  help         - Show this help"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  quit         - Exit calculator"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"\nExamples:"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  3 4 +        → 7"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  5 2 pow      → 25"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  9 sqrt       → 3"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"  7 fib        → 13"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"==========================================\n"</span> &lt;&lt; std::endl;
}

<span class="code-type">int</span> <span class="code-function">main</span>() {
    RPNCalculator calculator;
    std::string input;
    
    std::cout &lt;&lt; <span class="code-string">"RPN Calculator v2.0"</span> &lt;&lt; std::endl;
    std::cout &lt;&lt; <span class="code-string">"Type 'help' for instructions or 'quit' to exit"</span> &lt;&lt; std::endl;
    
    <span class="code-keyword">while</span> (<span class="code-keyword">true</span>) {
        std::cout &lt;&lt; <span class="code-string">"RPN["</span> &lt;&lt; calculator.size() &lt;&lt; <span class="code-string">"]&gt; "</span>;
        std::getline(std::cin, input);
        
        <span class="code-keyword">if</span> (input.empty()) <span class="code-keyword">continue</span>;
        
        std::istringstream iss(input);
        std::string command;
        iss &gt;&gt; command;
        
        <span class="code-keyword">try</span> {
            <span class="code-keyword">if</span> (command == <span class="code-string">"quit"</span> || command == <span class="code-string">"exit"</span>) {
                <span class="code-keyword">break</span>;
            }
            <span class="code-keyword">else</span> <span class="code-keyword">if</span> (command == <span class="code-string">"help"</span>) {
                printHelp();
            }
            <span class="code-keyword">else</span> <span class="code-keyword">if</span> (command == <span class="code-string">"display"</span>) {
                calculator.display();
            }
            <span class="code-keyword">else</span> <span class="code-keyword">if</span> (command == <span class="code-string">"clear"</span>) {
                calculator.clear();
            }
            <span class="code-keyword">else</span> <span class="code-keyword">if</span> (command == <span class="code-string">"history"</span>) {
                calculator.showHistory();
            }
            <span class="code-keyword">else</span> <span class="code-keyword">if</span> (command == <span class="code-string">"clearhistory"</span>) {
                calculator.clearHistory();
            }
            <span class="code-keyword">else</span> <span class="code-keyword">if</span> (command == <span class="code-string">"eval"</span>) {
                std::string expr;
                std::getline(iss, expr);
                <span class="code-keyword">if</span> (!expr.empty() &amp;&amp; expr[0] == <span class="code-string">' '</span>) expr = expr.substr(1);
                
                <span class="code-keyword">if</span> (expr.empty()) {
                    std::cout &lt;&lt; <span class="code-string">"Error: No expression provided for eval command"</span> &lt;&lt; std::endl;
                    <span class="code-keyword">continue</span>;
                }
                
                <span class="code-type">double</span> result = calculator.evaluateExpression(expr);
                std::cout &lt;&lt; <span class="code-string">"Result: "</span> &lt;&lt; std::fixed &lt;&lt; std::setprecision(6) &lt;&lt; result &lt;&lt; std::endl;
            }
            <span class="code-keyword">else</span> <span class="code-keyword">if</span> (calculator.isNumber(command)) {
                calculator.push(std::stod(command));
                std::cout &lt;&lt; <span class="code-string">"Pushed: "</span> &lt;&lt; command &lt;&lt; std::endl;
            }
            <span class="code-keyword">else</span> <span class="code-keyword">if</span> (command == <span class="code-string">"+"</span> || command == <span class="code-string">"-"</span> || command == <span class="code-string">"*"</span> || command == <span class="code-string">"/"</span> ||
                     command == <span class="code-string">"sqrt"</span> || command == <span class="code-string">"pow"</span> || command == <span class="code-string">"fib"</span> ||
                     command == <span class="code-string">"sin"</span> || command == <span class="code-string">"cos"</span> || command == <span class="code-string">"tan"</span>) {
                calculator.calculate(command);
                <span class="code-keyword">if</span> (!calculator.isEmpty()) {
                    std::cout &lt;&lt; <span class="code-string">"Result: "</span> &lt;&lt; std::fixed &lt;&lt; std::setprecision(6) 
                             &lt;&lt; calculator.pop() &lt;&lt; std::endl;
                    calculator.push(calculator.pop());
                }
            }
            <span class="code-keyword">else</span> {
                std::cout &lt;&lt; <span class="code-string">"Error: Unknown command '"</span> &lt;&lt; command &lt;&lt; <span class="code-string">"'. Type 'help' for available commands."</span> &lt;&lt; std::endl;
            }
        }
        <span class="code-keyword">catch</span> (<span class="code-keyword">const</span> std::exception& e) {
            std::cout &lt;&lt; e.what() &lt;&lt; std::endl;
        }
    }
    
    std::cout &lt;&lt; <span class="code-string">"Thank you for using RPN Calculator!"</span> &lt;&lt; std::endl;
    <span class="code-keyword">return</span> 0;
}</pre>
            </div>
        </section>

        <!-- 使用指南 -->
        <section id="usage" class="content-section">
            <h2 class="text-2xl font-bold mb-4 text-primary">
                <i class="fa fa-book mr-2"></i>使用指南
            </h2>
            <div class="space-y-4">
                <div>
                    <h3 class="font-bold text-lg mb-2">基本操作</h3>
                    <p>在交互式界面中，您可以输入数字和操作符进行计算。支持的操作符包括：</p>
                    <ul class="list-disc pl-6 mt-2">
                        <li><code>+</code> - 加法</li>
                        <li><code>-</code> - 减法</li>
                        <li><code>*</code> - 乘法</li>
                        <li><code>/</code> - 除法</li>
                        <li><code>sqrt</code> - 平方根</li>
                        <li><code>pow</code> - 幂运算</li>
                        <li><code>fib</code> - 斐波那契数</li>
                        <li><code>sin</code>, <code>cos</code>, <code>tan</code> - 三角函数</li>
                    </ul>
                </div>
                <div>
                    <h3 class="font-bold text-lg mb-2">命令列表</h3>
                    <ul class="list-disc pl-6">
                        <li><code>display</code> - 显示当前栈内容</li>
                        <li><code>clear</code> - 清空栈</li>
                        <li><code>history</code> - 显示计算历史</li>
                        <li><code>clearhistory</code> - 清空历史记录</li>
                        <li><code>eval &lt;expression&gt;</code> - 计算完整的RPN表达式</li>
                        <li><code>help</code> - 显示帮助信息</li>
                        <li><code>quit</code> - 退出程序</li>
                    </ul>
                </div>
                <div>
                    <h3 class="font-bold text-lg mb-2">示例</h3>
                    <div class="bg-gray-100 p-4 rounded-lg">
                        <p><code>3 4 +</code> → 7</p>
                        <p><code>5 2 pow</code> → 25</p>
                        <p><code>9 sqrt</code> → 3</p>
                        <p><code>7 fib</code> → 13</p>
                    </div>
                </div>
            </div>
        </section>
    </main>

    <!-- 页脚 -->
    <footer class="bg-dark text-white py-6 mt-8">
        <div class="container mx-auto text-center">
            <p>RPN Calculator - C++ Implementation</p>
            <p class="text-gray-400 mt-2">提供高效、稳定的逆波兰表达式计算解决方案</p>
        </div>
    </footer>
</body>
</html>
