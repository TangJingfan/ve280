#include "dlist.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// judge whether it is valid input
bool is_integer(const string &input) {
  try {
    size_t pos;
    std::stoi(input, &pos);
    return pos == input.length();
  } catch (...) {
    return false;
  }
}

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

bool has_enough_operands(Dlist<int> &stack, int required) {
  int count = 0;
  Dlist<int> tempStack;

  while (!stack.isEmpty() && count < required) {
    tempStack.insertBack(stack.removeFront());
    ++count;
  }

  while (!tempStack.isEmpty()) {
    stack.insertFront(tempStack.removeBack());
  }

  return count >= required;
}

void handle_input(Dlist<int> &stack, const string &input) {
  if (is_integer(input)) {
    stack.insertFront(new int(stoi(input)));
  } else if (input == "+" || input == "-" || input == "*" || input == "/") {
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
    if (stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *top = stack.removeFront();
    stack.insertFront(new int(-(*top)));
    delete top;
  } else if (input == "d") {
    if (stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *top = stack.removeFront();
    stack.insertFront(new int(*top));
    stack.insertFront(new int(*top));
    delete top;
  } else if (input == "r") {
    if (!has_enough_operands(stack, 2)) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *first = stack.removeFront();
    int *second = stack.removeFront();
    stack.insertFront(first);
    stack.insertFront(second);
  } else if (input == "p") {
    if (stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *top = stack.removeFront();
    cout << *top << endl;
    stack.insertFront(top);
  } else if (input == "c") {
    while (!stack.isEmpty()) {
      delete stack.removeFront();
    }
  } else if (input == "a") {
    print_all(stack);
  } else if (input == "q") {
    while (!stack.isEmpty()) {
      delete stack.removeFront();
    }
    exit(0);
  } else {
    cout << "Bad input" << endl;
  }
}

int main() {
  Dlist<int> stack;
  string input;

  while (cin >> input) {
    handle_input(stack, input);
  }

  while (!stack.isEmpty()) {
    delete stack.removeFront();
  }

  return 0;
}
