#include "dlist.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// 判断是否为合法整数
bool is_integer(const string &input) {
  try {
    size_t pos;
    std::stoi(input, &pos);
    return pos == input.length();
  } catch (...) {
    return false;
  }
}

// 打印栈中所有元素
void print_all(Dlist<int> &stack) {
  Dlist<int> tempStack;
  bool first = true;
  while (!stack.isEmpty()) {
    int *top = stack.removeFront();
    if (!first) {
      cout << " ";
    }
    cout << *top;
    first = false;
    tempStack.insertBack(top);
  }
  cout << endl;
  while (!tempStack.isEmpty()) {
    stack.insertFront(tempStack.removeBack());
  }
}

// 检查栈中是否有足够的操作数
bool has_enough_operands(Dlist<int> &stack, int required) {
  int count = 0;
  Dlist<int> tempStack;

  // 计算栈中元素数量
  while (!stack.isEmpty() && count < required) {
    tempStack.insertBack(stack.removeFront());
    ++count;
  }

  // 恢复栈
  while (!tempStack.isEmpty()) {
    stack.insertFront(tempStack.removeBack());
  }

  return count >= required;
}

// 栈操作处理
void handle_input(Dlist<int> &stack, const string &input) {
  if (is_integer(input)) {
    // 数字入栈
    stack.insertFront(new int(stoi(input)));
  } else if (input == "+" || input == "-" || input == "*" || input == "/") {
    // 加法、减法、乘法、除法
    if (!has_enough_operands(stack, 2)) {
      cout << "Not enough operands" << endl;
      return;
    }

    int *first = stack.removeFront();
    int *second = stack.removeFront();
    int result = 0;

    if (input == "+") {
      result = *second + *first;
    } else if (input == "-") {
      result = *second - *first;
    } else if (input == "*") {
      result = *second * *first;
    } else if (input == "/") {
      if (*first == 0) {
        cout << "Divide by zero" << endl;
        stack.insertFront(second);
        stack.insertFront(first);
        return;
      }
      result = *second / *first;
    }

    stack.insertFront(new int(result));
    delete first;
    delete second;
  } else if (input == "n") {
    // 取反
    if (stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *top = stack.removeFront();
    stack.insertFront(new int(-(*top)));
    delete top;
  } else if (input == "d") {
    // 复制栈顶元素
    if (stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *top = stack.removeFront();
    stack.insertFront(new int(*top));
    stack.insertFront(new int(*top));
    delete top;
  } else if (input == "r") {
    // 交换栈顶两个元素
    if (!has_enough_operands(stack, 2)) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *first = stack.removeFront();
    int *second = stack.removeFront();
    stack.insertFront(first);
    stack.insertFront(second);
  } else if (input == "p") {
    // 打印栈顶元素
    if (stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *top = stack.removeFront();
    cout << *top << endl;
    stack.insertFront(top);
  } else if (input == "c") {
    // 清空栈
    while (!stack.isEmpty()) {
      delete stack.removeFront();
    }
  } else if (input == "a") {
    // 打印所有元素
    print_all(stack);
  } else if (input == "q") {
    // 退出程序
    while (!stack.isEmpty()) {
      delete stack.removeFront();
    }
    exit(0);
  } else {
    // 无效输入
    cout << "Bad input" << endl;
  }
}

int main() {
  Dlist<int> stack;
  string input;

  while (cin >> input) {
    handle_input(stack, input);
  }

  // 清理内存
  while (!stack.isEmpty()) {
    delete stack.removeFront();
  }

  return 0;
}
