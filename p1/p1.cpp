#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

bool check_illegal(const int &_num, const int &_option) {
  if ((1 <= _option && _option <= 4) && (0 < _num && _num <= 10000000)) {
    return true;
  } else {
    return false;
  }
}

bool test1(const int &_num) {
  int lower_limit = sqrt(2 * _num);
  if (lower_limit * (lower_limit + 1) == 2 * _num) {
    return true;
  }
  return false;
}

bool test2(const int &_num) {
  int limit = static_cast<int>(std::sqrt(_num));
  if (_num == 1) {
    return true;
  } else {
    for (int i = 2; i <= limit; ++i) {
      for (int j = 2; pow(i, j) <= _num; j++) {
        if (pow(i, j) == _num) {
          return true;
        } else if (pow(i, j) > _num) {
          break;
        }
      }
    }
  }
  return false;
}

bool test3(const int &_num) {
  int limit = static_cast<int>(std::sqrt(_num));
  for (int i = 0; i <= limit; ++i) {
    int sum_lower = (i - 1) * i * (2 * i - 1) / 6;
    for (int j = i; j <= limit; ++j) {
      int sum_upper = (j * (j + 1) * (2 * j + 1)) / 6;
      int diff = sum_upper - sum_lower;
      if (diff == _num) {
        return true;
      } else if (diff > _num) {
        break;
      }
    }
  }
  return false;
}

bool test4(const int &_num) {
  int sum = 0;
  for (int i = 1; i <= (_num / 2); i++) {
    if (_num % i == 0) {
      sum += i;
    }
  }
  if (sum > _num) {
    return true;
  }
  return false;
}

bool test_selection(const int &_num, const int &_option) {
  switch (_option) {
  case 1:
    return test1(_num);
    break;
  case 2:
    return test2(_num);
    break;
  case 3:
    return test3(_num);
    break;
  case 4:
    return test4(_num);
    break;
  default:
    return false;
    break;
  }
}

int main() {
  int num = 0, test_option = 0;
  std::cout << "Please enter the integer and the test choice: ";
  std::cin >> num >> test_option;
  // std::cerr << num << " " << test_option << std::endl;
  while (!check_illegal(num, test_option)) {
    std::cout << "Please enter the integer and the test choice: ";
    std::cin >> num >> test_option;
    // std::cerr << num << " " << test_option << std::endl;
  }
  if (test_selection(num, test_option)) {
    std::cout << "Pass" << std::endl;
  } else {
    std::cout << "Fail" << std::endl;
  }
  return 0;
}