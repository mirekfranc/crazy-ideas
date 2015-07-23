// g++ -std=c++11 -O3 -Wall -Wextra delegating_constructors.cpp -o delegating_constructors
// C++11 delegating constructors
#include <iostream>

using namespace std;

struct bullshit {};

class something {
  public:
    something (int m, int n) : _m (m), _n (n) { throw bullshit (); };
    something (int x) : something (x/2, x/2) { };
    something () : something (84) { };
    ~something () { cout << "~something" << endl; }
  private:
    int _m, _n;
};

class something_else {
  public:
    something_else (int m, int n) : _m (m), _n (n) { };
    something_else (int x) : something_else (x/2, x/2) { throw bullshit (); };
    something_else () : something_else (84) { };
    ~something_else () { cout << "~something_else" << endl; }
  private:
    int _m, _n;
};

int main () {
  try {
    something x; // does not print anything since object is never fully contructed ;)
  } catch (...) { }

  try {
    something_else y; // prints ~something_else
  } catch (...) { }
}
