// g++ -Wall -Wextra -std=c++11 alignof_alignas.cpp -o alignof_alignas
// C++11 alignas alignof
#include <iostream>

int
main ()
{
  char a = 'X';
  alignas (long long) char b = 'Y';

  std::cout << alignof (char) << ":" << a << std::endl;
  std::cout << alignof (long long) << ":" << b << std::endl;
  // gcc allows even expressions for alignof
}
