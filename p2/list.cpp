#include <iostream>

#include "p2.h"
#include "recursive.h"

using namespace std;

bool odd(int a) {
  if (a % 2 == 1) {
    return true;
  } else {
    return false;
  }
}

int main() {
  // list_size
  /*
  cout << size(list_make()) << endl;
  list_t a = list_make();
  for (int i = 0; i < 5; i++) {
    a = list_make(i, a);
  }
  cout << size(a) << endl;
  */

  // memberOf
  /*
  list_t a = list_make();
  cout << memberOf(a, 5) << endl;
  list_t b = list_make();
  for (int i = 0; i < 94; i = i + 6) {
    b = list_make(i, b);
  }
  cout << memberOf(b, 6) << endl;
  */

  // dot
  /*
  list_t a = list_make();
  list_t b = list_make();
  for (int i = 0; i < 6; i++) {
    a = list_make(i + 7, a);
  }
  for (int j = 0; j < 4; j++) {
    b = list_make(j + 2, b);
  }
  list_print(a);
  list_print(b);
  cout << dot(a, b) << endl;
  cout << dot(list_make(1, list_make()), a) << endl;
  */

  // isIncreasing
  /*
  list_t a = list_make();
  list_t b = list_make(
      1, list_make(5, list_make(5, list_make(10, list_make(52, list_make())))));
  list_t c = list_make(
      1, list_make(5, list_make(5, list_make(10, list_make(5, list_make())))));
  list_t d = list_make(1, list_make(1, list_make()));
  cout << isIncreasing(a) << endl;
  cout << isIncreasing(b) << endl;
  cout << isIncreasing(c) << endl;
  cout << isIncreasing(d) << endl;
  */

  // reverse
  /*
  list_t a = list_make(
      1, list_make(5, list_make(5, list_make(10, list_make(52, list_make())))));
  list_t b = list_make();
  list_t c = list_make(10, list_make());
  list_print(reverse(a));
  list_print(reverse(b));
  list_print(reverse(c));
  */

  // append
  /*
  list_t a = list_make();
  list_t b =
      list_make(1, list_make(5, list_make(3, list_make(10, list_make()))));
  list_print(append(a, b));
  list_print(append(b, a));
  list_print(append(b, b));
  */

  // isAri
  /*
  list_t a = list_make();
  list_t b = list_make(5, list_make());
  list_t c = list_make(1, list_make());
  list_t d = list_make();
  list_t e = list_make(
      2,
      list_make(
          4, list_make(
                 6, list_make(10, list_make(12, list_make(14, list_make()))))));
  for (int i = 0; i < 100; i++) {
    c = list_make(2 * i, c);
    d = list_make(7 * i, d);
  }
  cout << isArithmeticSequence(a) << " " << isArithmeticSequence(b) << " "
       << isArithmeticSequence(c) << " " << isArithmeticSequence(d) << " "
       << isArithmeticSequence(e) << endl;
  */

  // filter odd
  /*
  list_t a = list_make();
  list_t b = list_make(5, list_make());
  list_t c = list_make(
      4,
      list_make(
          5, list_make(
                 9, list_make(1, list_make(10, list_make(10, list_make()))))));
  list_print(filter_odd(a));
  list_print(filter_odd(b));
  list_print(filter_odd(c));
  */

  // filter
  /*
  list_t a = list_make();
  list_t b = list_make(5, list_make());
  list_t c = list_make(
      4,
      list_make(
          5, list_make(
                 9, list_make(1, list_make(10, list_make(10, list_make()))))));
  list_print(filter(a, odd));
  list_print(filter(b, odd));
  list_print(filter(c, odd));
  */

  // unique
  /*
  list_t a = list_make();
  list_t b = list_make(1, list_make());
  list_t c =
      list_make(1, list_make(1, list_make(1, list_make(1, list_make()))));
  list_t d = list_make(
      5,
      list_make(
          5,
          list_make(
              9,
              list_make(
                  1, list_make(
                         10,
                         list_make(
                             10,
                             list_make(
                                 9, list_make(
                                        10, list_make(
                                                1, list_make(
                                                       6, list_make()))))))))));
  list_print(unique(a));
  list_print(unique(b));
  list_print(unique(c));
  list_print(unique(d));
  */

  // insert
  /*
  list_t a = list_make();
  list_t b = list_make(1, list_make());
  list_t c =
      list_make(1, list_make(1, list_make(1, list_make(1, list_make()))));
  list_t d = list_make(
      5,
      list_make(
          5,
          list_make(
              9,
              list_make(
                  1, list_make(
                         10,
                         list_make(
                             10,
                             list_make(
                                 9, list_make(
                                        10, list_make(
                                                1, list_make(
                                                       6, list_make()))))))))));
  list_print(insert_list(b, a, 1));
  list_print(insert_list(d, c, 4));
  list_print(insert_list(a, d, 0));
  */

  // chop
  /*
  list_t a = list_make();
  list_t b = list_make(1, list_make());
  list_t c =
      list_make(1, list_make(1, list_make(1, list_make(1, list_make()))));
  list_t d = list_make(
      5,
      list_make(
          5,
          list_make(
              9,
              list_make(
                  1, list_make(
                         10,
                         list_make(
                             10,
                             list_make(
                                 9, list_make(
                                        10, list_make(
                                                1, list_make(
                                                       6, list_make()))))))))));
  list_print(chop(a, 0));
  list_print(chop(b, 1));
  list_print(chop(c, 0));
  list_print(chop(c, 2));
  list_print(chop(d, 6));
  */
}