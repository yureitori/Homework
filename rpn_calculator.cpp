#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <cmath>
#include <vector>

class RPNCalculator {
private:
    std::stack<double> operandStack;
    std::vector<std::string> history;
    
    bool isOperator(const std::string& token) {
        return token == "+" || token == "-" || token == "*" || token == "/" ||
               token == "sqrt" || token == "pow" || token == "fib" || 
               token == "sin" || token == "cos" || token == "tan";
    }
    
public:
    bool isNumber(const std::string& token) {
        try {
            std::stod(token);
            return true;
        } catch (const std::invalid_argument&) {
            return false;
        }
    }

private:
    
    long long fibonacciNumber(int n) {
        if (n <= 0) return 0;
        if (n == 1) return 1;
        
        long long a = 0, b = 1;
        for (int i = 2; i <= n; i++) {
            long long temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }

public:
    void push(double value) {
        operandStack.push(value);
    }
    
    double pop() {
        if (operandStack.empty()) {
            throw std::runtime_error("Error: Stack is empty, cannot pop");
        }
        double value = operandStack.top();
        operandStack.pop();
        return value;
    }
    
    void clear() {
        while (!operandStack.empty()) {
            operandStack.pop();
        }
        std::cout << "Stack cleared." << std::endl;
    }
    
    void display() {
        if (operandStack.empty()) {
            std::cout << "Stack is empty." << std::endl;
            return;
        }
        
        std::stack<double> temp = operandStack;
        std::vector<double> values;
        
        while (!temp.empty()) {
            values.push_back(temp.top());
            temp.pop();
        }
        
        std::cout << "Stack contents (top to bottom): ";
        for (int i = values.size() - 1; i >= 0; i--) {
            std::cout << std::fixed << std::setprecision(2) << values[i];
            if (i > 0) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    void calculate(const std::string& operation) {
        if (operation == "+") {
            if (operandStack.size() < 2) throw std::runtime_error("Error: Insufficient operands for addition");
            double b = pop(), a = pop();
            push(a + b);
        }
        else if (operation == "-") {
            if (operandStack.size() < 2) throw std::runtime_error("Error: Insufficient operands for subtraction");
            double b = pop(), a = pop();
            push(a - b);
        }
        else if (operation == "*") {
            if (operandStack.size() < 2) throw std::runtime_error("Error: Insufficient operands for multiplication");
            double b = pop(), a = pop();
            push(a * b);
        }
        else if (operation == "/") {
            if (operandStack.size() < 2) throw std::runtime_error("Error: Insufficient operands for division");
            double b = pop(), a = pop();
            if (b == 0) throw std::runtime_error("Error: Division by zero");
            push(a / b);
        }
        else if (operation == "sqrt") {
            if (operandStack.empty()) throw std::runtime_error("Error: Insufficient operands for square root");
            double a = pop();
            if (a < 0) throw std::runtime_error("Error: Cannot take square root of negative number");
            push(std::sqrt(a));
        }
        else if (operation == "pow") {
            if (operandStack.size() < 2) throw std::runtime_error("Error: Insufficient operands for power operation");
            double b = pop(), a = pop();
            push(std::pow(a, b));
        }
        else if (operation == "fib") {
            if (operandStack.empty()) throw std::runtime_error("Error: Insufficient operands for fibonacci");
            double a = pop();
            if (a < 0 || a != (int)a) throw std::runtime_error("Error: Fibonacci requires non-negative integer");
            push(fibonacciNumber((int)a));
        }
        else if (operation == "sin") {
            if (operandStack.empty()) throw std::runtime_error("Error: Insufficient operands for sine");
            double a = pop();
            push(std::sin(a));
        }
        else if (operation == "cos") {
            if (operandStack.empty()) throw std::runtime_error("Error: Insufficient operands for cosine");
            double a = pop();
            push(std::cos(a));
        }
        else if (operation == "tan") {
            if (operandStack.empty()) throw std::runtime_error("Error: Insufficient operands for tangent");
            double a = pop();
            push(std::tan(a));
        }
        else {
            throw std::runtime_error("Error: Unknown operator: " + operation);
        }
    }
    
    double evaluateExpression(const std::string& expression) {
        std::istringstream iss(expression);
        std::string token;
        
        clear();
        
        while (iss >> token) {
            if (isNumber(token)) {
                push(std::stod(token));
            } else if (isOperator(token)) {
                calculate(token);
            } else {
                throw std::runtime_error("Error: Invalid token: " + token);
            }
        }
        
        if (operandStack.size() != 1) {
            throw std::runtime_error("Error: Invalid expression - stack contains " + 
                                   std::to_string(operandStack.size()) + " elements");
        }
        
        double result = operandStack.top();
        history.push_back(expression + " = " + std::to_string(result));
        return result;
    }
    
    void showHistory() {
        if (history.empty()) {
            std::cout << "No calculation history." << std::endl;
            return;
        }
        
        std::cout << "Calculation History:" << std::endl;
        for (size_t i = 0; i < history.size(); i++) {
            std::cout << i + 1 << ". " << history[i] << std::endl;
        }
    }
    
    void clearHistory() {
        history.clear();
        std::cout << "History cleared." << std::endl;
    }
    
    bool isEmpty() const {
        return operandStack.empty();
    }
    
    size_t size() const {
        return operandStack.size();
    }
};

void printHelp() {
    std::cout << "\n=== RPN Calculator Help ===" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  <number>     - Push number onto stack" << std::endl;
    std::cout << "  +, -, *, /   - Basic arithmetic operations" << std::endl;
    std::cout << "  sqrt         - Square root" << std::endl;
    std::cout << "  pow          - Power operation (a^b)" << std::endl;
    std::cout << "  fib          - Fibonacci number" << std::endl;
    std::cout << "  sin, cos, tan- Trigonometric functions" << std::endl;
    std::cout << "  display      - Show current stack" << std::endl;
    std::cout << "  clear        - Clear stack" << std::endl;
    std::cout << "  history      - Show calculation history" << std::endl;
    std::cout << "  clearhistory - Clear calculation history" << std::endl;
    std::cout << "  eval <expr>  - Evaluate complete RPN expression" << std::endl;
    std::cout << "  help         - Show this help" << std::endl;
    std::cout << "  quit         - Exit calculator" << std::endl;
    std::cout << "\nExamples:" << std::endl;
    std::cout << "  3 4 +        → 7" << std::endl;
    std::cout << "  5 2 pow      → 25" << std::endl;
    std::cout << "  9 sqrt       → 3" << std::endl;
    std::cout << "  7 fib        → 13" << std::endl;
    std::cout << "==========================================\n" << std::endl;
}

int main() {
    RPNCalculator calculator;
    std::string input;
    
    std::cout << "RPN Calculator v2.0" << std::endl;
    std::cout << "Type 'help' for instructions or 'quit' to exit" << std::endl;
    
    while (true) {
        std::cout << "RPN[" << calculator.size() << "]> ";
        std::getline(std::cin, input);
        
        if (input.empty()) continue;
        
        std::istringstream iss(input);
        std::string command;
        iss >> command;
        
        try {
            if (command == "quit" || command == "exit") {
                break;
            }
            else if (command == "help") {
                printHelp();
            }
            else if (command == "display") {
                calculator.display();
            }
            else if (command == "clear") {
                calculator.clear();
            }
            else if (command == "history") {
                calculator.showHistory();
            }
            else if (command == "clearhistory") {
                calculator.clearHistory();
            }
            else if (command == "eval") {
                std::string expr;
                std::getline(iss, expr);
                if (!expr.empty() && expr[0] == ' ') expr = expr.substr(1);
                
                if (expr.empty()) {
                    std::cout << "Error: No expression provided for eval command" << std::endl;
                    continue;
                }
                
                double result = calculator.evaluateExpression(expr);
                std::cout << "Result: " << std::fixed << std::setprecision(6) << result << std::endl;
            }
            else if (calculator.isNumber(command)) {
                calculator.push(std::stod(command));
                std::cout << "Pushed: " << command << std::endl;
            }
            else if (command == "+" || command == "-" || command == "*" || command == "/" ||
                     command == "sqrt" || command == "pow" || command == "fib" ||
                     command == "sin" || command == "cos" || command == "tan") {
                calculator.calculate(command);
                if (!calculator.isEmpty()) {
                    std::cout << "Result: " << std::fixed << std::setprecision(6) 
                             << calculator.pop() << std::endl;
                    calculator.push(calculator.pop());
                }
            }
            else {
                std::cout << "Error: Unknown command '" << command << "'. Type 'help' for available commands." << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    
    std::cout << "Thank you for using RPN Calculator!" << std::endl;
    return 0;
}