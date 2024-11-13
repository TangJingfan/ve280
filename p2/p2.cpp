#include "p2.h"

#include <cstdlib>
#include <iostream>

#include "recursive.h"

int size(list_t list) {
  // base case: empty list
  if (list_isEmpty(list)) {
    return 0;
  } else {
    // inductive case
    return 1 + size(list_rest(list));
  }
}

bool memberOf(list_t list, int val) {
  // base case: empty list
  if (list_isEmpty(list)) {
    return false;
    // val founded
  } else if (val == list_first(list)) {
    return true;
  } else {
    // inductive case
    return memberOf(list_rest(list), val);
  }
}

int dot(list_t v1, list_t v2) {
  // end point
  if (list_isEmpty(v1) || list_isEmpty(v2)) {
    return 0;
  } else {
    // inductive case
    return list_first(v1) * list_first(v2) + dot(list_rest(v1), list_rest(v2));
  }
}

bool isIncreasing(list_t v) {
  // base case: empty list
  if (list_isEmpty(v)) {
    return true;
    // base case: length 1
  } else if (list_isEmpty(list_rest(v))) {
    return true;
  } else {
    // inductive; test first two element and the whole list
    return (list_first(v) <= list_first(list_rest(v)) &&
            isIncreasing(list_rest(v)));
  }
}

static list_t reverse_helper(list_t _list_to_check, list_t _list_to_have) {
  if (list_isEmpty(_list_to_check)) {
    return _list_to_have;
  } else {
    return reverse_helper(list_rest(_list_to_check),
                          list_make(list_first(_list_to_check), _list_to_have));
  }
}

list_t reverse(list_t list) { return reverse_helper(list, list_make()); }

static list_t append_helper(list_t _list_to_check, list_t _list_to_have) {
  // endpoint
  if (list_isEmpty(_list_to_check)) {
    return _list_to_have;
  } else {
    // inductive case
    return append_helper(list_rest(_list_to_check),
                         list_make(list_first(_list_to_check), _list_to_have));
  }
}

list_t append(list_t first, list_t second) {
  return append_helper(reverse(first), second);
}

bool isArithmeticSequence(list_t v) {
  // base case
  if (size(v) <= 2) {
    return true;
  } else {
    // inductive case; test first three elements and the rest sequence
    int first_diff = list_first(list_rest(v)) - list_first(v);
    int second_diff =
        list_first(list_rest(list_rest(v))) - list_first(list_rest(v));
    return (first_diff == second_diff) && isArithmeticSequence(list_rest(v));
  }
}

static list_t filter_odd_helper(list_t list_to_check, list_t list_to_have) {
  // base case: empty list
  if (list_isEmpty(list_to_check)) {
    return list_to_have;
  } else {
    // inductive case; 2 situations
    if (list_first(list_to_check) % 2 == 1) {
      return filter_odd_helper(
          list_rest(list_to_check),
          list_make(list_first(list_to_check), list_to_have));
    } else {
      return filter_odd_helper(list_rest(list_to_check), list_to_have);
    }
  }
}

list_t filter_odd(list_t list) {
  return filter_odd_helper(reverse(list), list_make());
}

static list_t filter_helper(list_t list_to_check, list_t list_to_have,
                            bool (*fn)(int)) {
  if (list_isEmpty(list_to_check)) {
    return list_to_have;
  } else {
    if (fn(list_first(list_to_check))) {
      return filter_helper(list_rest(list_to_check),
                           list_make(list_first(list_to_check), list_to_have),
                           fn);
    } else {
      return filter_helper(list_rest(list_to_check), list_to_have, fn);
    }
  }
}

list_t filter(list_t list, bool (*fn)(int)) {
  return filter_helper(reverse(list), list_make(), fn);
}

static list_t unique_finder(list_t list_to_check, list_t list_to_have) {
  // base case: empty list
  if (list_isEmpty(list_to_check)) {
    return list_to_have;
    // inductive cases: 2 situations
  } else if (!memberOf(list_to_have, list_first(list_to_check))) {
    return unique_finder(list_rest(list_to_check),
                         list_make(list_first(list_to_check), list_to_have));
  } else {
    return unique_finder(list_rest(list_to_check), list_to_have);
  }
}

list_t unique(list_t list) { return reverse(unique_finder(list, list_make())); }

static list_t insert_helper(list_t left, list_t stack, list_t right,
                            unsigned int n) {
  // base case
  if (n != 0) {
    return insert_helper(list_rest(left), list_make(list_first(left), stack),
                         right, n - 1);
  } else {
    // inductive case; take care of two lists
    if (!list_isEmpty(right)) {
      return insert_helper(list_make(list_first(right), left), stack,
                           list_rest(right), 0);
    } else {
      if (!list_isEmpty(stack)) {
        return insert_helper(list_make(list_first(stack), left),
                             list_rest(stack), right, 0);
      } else {
        return left;
      }
    }
  }
}

list_t insert_list(list_t first, list_t second, unsigned int n) {
  return insert_helper(first, list_make(), reverse(second), n);
}

static list_t chop_helper(list_t list, list_t res, unsigned int n) {
  // inductive case
  if (n != 0) {
    return chop_helper(list_rest(list), list_make(list_first(list), res),
                       n - 1);
  } else {
    // base case; no element need to be removed
    return reverse(res);
  }
}

list_t chop(list_t list, unsigned int n) {
  return chop_helper(list, list_make(), size(list) - n);
}

int tree_sum(tree_t tree) {
  if (tree_isEmpty(tree)) {
    return 0;
  } else {
    return tree_elt(tree) + tree_sum(tree_left(tree)) +
           tree_sum(tree_right(tree));
  }
}

bool tree_search(tree_t tree, int val) {
  // base case; do isEmpty first
  if (tree_isEmpty(tree)) {
    return false;
  }
  // base case: element found
  if (tree_elt(tree) == val) {
    return tree;
  }
  // inductive case
  return tree_search(tree_left(tree), val) ||
         tree_search(tree_right(tree), val);
}

// return the bigger one between two elements
static int my_max(int a, int b) { return (a > b) ? a : b; }
// return the bigger one among three elements
static int my_max(int a, int b, int c) { return my_max(a, my_max(b, c)); }

int depth(tree_t tree) {
  // base case
  if (tree_isEmpty(tree)) {
    return 0;
  } else {
    // inductive case
    return 1 + my_max(depth(tree_left(tree)), depth(tree_right(tree)));
  }
}

int tree_max(tree_t tree) {
  // base case
  if (tree_isEmpty(tree)) {
    return 0;
  }
  // inductive case
  return my_max(tree_elt(tree), tree_max(tree_left(tree)),
                tree_max(tree_right(tree)));
}

list_t traversal(tree_t tree) {
  // base case
  if (tree_isEmpty(tree)) {
    return list_make();
  } else {
    // inductive case
    return append(traversal(tree_left(tree)),
                  list_make(tree_elt(tree), traversal(tree_right(tree))));
  }
}

static bool monotonic_path_checker(tree_t tree, tree_t subtree,
                                   bool is_increasing) {
  // base case
  if (tree_isEmpty(tree)) {
    return false;
  }
  // inductive cases
  if (is_increasing) {
    // not root-to-leaf path
    if (tree_isEmpty(subtree)) {
      return false;
      // not monotonic
    } else if (tree_elt(tree) >= tree_elt(subtree)) {
      return false;
      // right case
    } else if (tree_elt(tree) < tree_elt(subtree) &&
               tree_isEmpty(tree_left(subtree)) &&
               tree_isEmpty(tree_right(subtree))) {
      return true;
    }
  } else {
    if (tree_isEmpty(subtree)) {
      return false;
    } else if (tree_elt(tree) <= tree_elt(subtree)) {
      return false;
    } else if (tree_elt(tree) > tree_elt(subtree) &&
               tree_isEmpty(tree_left(subtree)) &&
               tree_isEmpty(tree_right(subtree))) {
      return true;
    }
  }
  return monotonic_path_checker(subtree, tree_left(subtree), is_increasing) ||
         monotonic_path_checker(subtree, tree_right(subtree), is_increasing);
}

bool tree_hasMonotonicPath(tree_t tree) {
  // base case
  if (depth(tree) == 1) {
    return true;
  }
  return monotonic_path_checker(tree, tree_left(tree), true) ||
         monotonic_path_checker(tree, tree_left(tree), false) ||
         monotonic_path_checker(tree, tree_right(tree), true) ||
         monotonic_path_checker(tree, tree_right(tree), false);
}

static bool all_path_sum_checker(tree_t tree, int current_sum, int sum) {
  if (tree_isEmpty(tree)) {
    return false;
  }
  current_sum += tree_elt(tree);
  if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {
    return current_sum > sum;
  }
  if (tree_isEmpty(tree_left(tree)) && !tree_isEmpty(tree_right(tree))) {
    return all_path_sum_checker(tree_right(tree), current_sum, sum);
  }
  if (!tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {
    return all_path_sum_checker(tree_left(tree), current_sum, sum);
  }
  return all_path_sum_checker(tree_left(tree), current_sum, sum) &&
         all_path_sum_checker(tree_right(tree), current_sum, sum);
}

bool tree_allPathSumGreater(tree_t tree, int sum) {
  if (tree_isEmpty(tree)) {
    return false;
  }
  return all_path_sum_checker(tree, 0, sum);
}

bool covered_by(tree_t A, tree_t B) {
  // base cases
  if (tree_isEmpty(A)) {
    return true;
  }
  if (tree_isEmpty(B)) {
    return false;
  }
  // inductive case
  if (tree_elt(A) != tree_elt(B)) {
    return false;
  }
  return covered_by(tree_left(A), tree_left(B)) &&
         covered_by(tree_right(A), tree_right(B));
}

bool contained_by(tree_t A, tree_t B) {
  // base cases
  if (tree_isEmpty(A)) {
    return true;
  }
  if (tree_isEmpty(B)) {
    return false;
  }
  // inductive case
  return covered_by(A, B) || contained_by(A, tree_left(B)) ||
         contained_by(A, tree_right(B));
}

tree_t insert_tree(int elt, tree_t tree) {
  // base case: add one element with two empty subtree;
  if (tree_isEmpty(tree)) {
    return tree_make(elt, tree_make(), tree_make());
  }
  // inductive case; store important variables
  tree_t left = tree_left(tree);
  tree_t right = tree_right(tree);
  if (elt >= tree_elt(tree)) {
    right = insert_tree(elt, right);
  } else {
    left = insert_tree(elt, left);
  }
  return tree_make(tree_elt(tree), left, right);
}