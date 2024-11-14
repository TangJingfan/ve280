#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
  string a = "Hello 5";
  istringstream b(a);
  string c;
  int d = 0;
  b >> c >> d;
  cout << c << d;
}