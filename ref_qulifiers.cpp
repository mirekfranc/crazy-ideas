// clang++ -Wall -Wextra -std=c++11 ref_qulifiers.cpp -o ref_qulifiers
// C++11 ref qualifiers
#include <iostream>

struct X
{
  void foo () & { std::cout << "l-value" << std:: endl; }
  void foo () && { std::cout << "r-value" << std:: endl; }
  void foo () const & { std::cout << "const l-value" << std:: endl; }
  void foo () const && { std::cout << "const r-value" << std:: endl; }
};

int
main ()
{
  X x;
  const X cx{}; // I don't want to provide default constructor ;)

  x.foo ();
  X ().foo ();
  cx.foo ();
  std::move (cx).foo ();
}
