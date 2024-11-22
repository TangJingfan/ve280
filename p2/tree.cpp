#include <iostream>

#include "p2.h"
#include "recursive.h"

using namespace std;

int main() {
  // sum
  /*
  tree_t a = tree_make();
  tree_t b = tree_make(10, tree_make(), tree_make());
  tree_t c = tree_make(10, tree_make(10, a, b), tree_make(5, a, b));
  cout << tree_sum(a) << " " << tree_sum(b) << " " << tree_sum(c) << endl;
  */

  // search
  /*
  tree_t a = tree_make();
  tree_t b = tree_make(10, tree_make(), tree_make());
  tree_t c = tree_make(
      4,
      tree_make(
          4,
          tree_make(
              5,
              tree_make(9,
                        tree_make(10, tree_make(6, tree_make(), tree_make()),
                                  tree_make(10, tree_make(), b)),
                        b),
              tree_make(543, b, a)),
          tree_make(100, tree_make(), tree_make(6, b, b))),
      tree_make(9, b, a));
  cout << tree_search(a, 10) << endl;
  cout << tree_search(b, 10) << endl;
  cout << tree_search(b, 1) << endl;
  cout << tree_search(c, 543) << endl;
  cout << tree_search(c, 5) << endl;
  cout << tree_search(c, 432) << endl;
  */

  // depth
  /*
  tree_t b = tree_make(10, tree_make(), tree_make());
  tree_t a = tree_make();
  tree_t c = tree_make(
      4,
      tree_make(
          4,
          tree_make(
              5,
              tree_make(9,
                        tree_make(10, tree_make(6, tree_make(), tree_make()),
                                  tree_make(10, tree_make(), b)),
                        b),
              tree_make(543, b, a)),
          tree_make(100, tree_make(), tree_make(6, b, b))),
      tree_make(9, b, a));
  cout << depth(b) << endl;
  cout << depth(a) << endl;
  cout << depth(c) << endl;
  */

  // max
  /*
  tree_t b = tree_make(10, tree_make(), tree_make());
  tree_t a = tree_make();
  tree_t c = tree_make(
      4,
      tree_make(
          4,
          tree_make(
              5,
              tree_make(544,
                        tree_make(10, tree_make(6, tree_make(), tree_make()),
                                  tree_make(10, tree_make(), b)),
                        b),
              tree_make(543, b, a)),
          tree_make(100, tree_make(544, a, a), tree_make(6, b, b))),
      tree_make(9, b, a));
  cout << tree_max(b) << endl;
  cout << tree_max(c) << endl;
  */

  // traversal
  /*
  tree_t a = tree_make();
  tree_t b = tree_make(10, tree_make(), tree_make());
  tree_t c = tree_make(10,
                       tree_make(5, tree_make(4, b, tree_make()),
                                 tree_make(9, tree_make(), tree_make())),
                       tree_make(5, tree_make(4, tree_make(), tree_make()),
                                 tree_make(9, b, tree_make())));
  list_print(traversal(a));
  list_print(traversal(b));
  list_print(traversal(c));
  */

  // path_greater

  tree_t b = tree_make(10, tree_make(), tree_make());
  tree_t a = tree_make();
  tree_t c = tree_make(
      4,
      tree_make(
          4,
          tree_make(
              5,
              tree_make(544,
                        tree_make(10, tree_make(6, tree_make(), tree_make()),
                                  tree_make(10, tree_make(), b)),
                        b),
              tree_make(543, b, a)),
          tree_make(100, tree_make(544, a, a), tree_make(6, b, b))),
      tree_make(9, b, a));

  tree_t d = tree_make(
      1, tree_make(2, tree_make(3, tree_make(), tree_make()), tree_make()),
      tree_make());
  cout << tree_allPathSumGreater(b, 10) << endl;
  cout << tree_allPathSumGreater(b, 9) << endl;
  cout << tree_allPathSumGreater(c, 1500) << endl;
  cout << tree_allPathSumGreater(c, 1600) << endl;
  cout << tree_allPathSumGreater(c, 22) << endl;
  cout << tree_allPathSumGreater(d, 5) << endl;
  cout << tree_hasMonotonicPath(c) << endl;

  // monotonic
  //   tree_t a = tree_make(
  //       4,
  //       tree_make(
  //           6, tree_make(5, tree_make(9, tree_make(), tree_make()),
  //           tree_make()), tree_make(7, tree_make(), tree_make())),
  //       tree_make());
  //   tree_t b = tree_make(4, tree_make(5, tree_make(), tree_make()),
  //   tree_make()); cout << tree_hasMonotonicPath(a) << endl; cout <<
  //   tree_hasMonotonicPath(b) << endl;
}