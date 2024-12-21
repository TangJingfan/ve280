#include "dlist.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool is_integer(const string &input) {
  try {
    size_t pos;
    std::stoi(input, &pos);
    return pos == input.length();
  } catch (const std::invalid_argument &) {
    return false;
  } catch (const std::out_of_range &) {
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

void handle_input(Dlist<int> &stack, const string &input) {
  if (is_integer(input)) {
    stack.insertFront(new int(stoi(input)));
  } else if (input == "+") {
    // addition
    if (stack.isEmpty() || stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *first = stack.removeFront();
    int *second = stack.removeFront();
    stack.insertFront(new int(*second + *first));
    delete first;
    delete second;
  } else if (input == "-") {
    // substraction
    if (stack.isEmpty() || stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *first = stack.removeFront();
    int *target = stack.removeFront();
    stack.insertFront(new int(*target - *first));
    delete first;
    delete target;
  } else if (input == "*") {
    // multiplication
    if (stack.isEmpty() || stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *first = stack.removeFront();
    int *second = stack.removeFront();
    stack.insertFront(new int((*second) * (*first)));
    delete first;
    delete second;
  } else if (input == "/") {
    // division
    if (stack.isEmpty() || stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *first = stack.removeFront();
    int *second = stack.removeFront();
    if (*first == 0) {
      cout << "Divide by zero" << endl;
      stack.insertFront(second);
      stack.insertFront(first);
      return;
    }
    stack.insertFront(new int((*second) / (*first)));
    delete first;
    delete second;
  } else if (input == "n") {
    // negation
    if (stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *target = stack.removeFront();
    stack.insertFront(new int(-(*target)));
    delete target;
  } else if (input == "d") {
    // duplicate top
    if (stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *a = stack.removeFront();
    stack.insertFront(new int(*a));
    stack.insertFront(new int(*a));
    delete a;
  } else if (input == "r") {
    // exchange
    if (stack.isEmpty() || stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *a = stack.removeFront();
    int *b = stack.removeFront();
    stack.insertFront(a);
    stack.insertFront(b);
  } else if (input == "p") {
    // print top element
    if (stack.isEmpty()) {
      cout << "Not enough operands" << endl;
      return;
    }
    int *top = stack.removeFront();
    cout << *top << endl;
    stack.insertFront(top);
  } else if (input == "c") {
    // clear stack
    while (!stack.isEmpty()) {
      delete stack.removeFront();
    }
  } else if (input == "a") {
    // print all
    print_all(stack);
  } else if (input == "q") {
    // exit
    // clear memory
    while (!stack.isEmpty()) {
      delete stack.removeFront();
    }
    exit(0);
  } else {
    // invalid input
    cout << "Bad input" << endl;
  }
}

int main() {
  Dlist<int> stack;
  string input;
  while (cin >> input) {
    handle_input(stack, input);
  }
  // clear all
  while (!stack.isEmpty()) {
    delete stack.removeFront();
  }
  return 0;
}
