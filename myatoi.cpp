// g++ -O3 -std=c++11 -Wall -Wextra myatoi.cpp -o myatoi
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

int myatoi (char a[])
{
  int ret = 0, multiple = 1;

  if (*a != '\0')
    {
      if (*a == '-')
        {
          multiple = -1;
          ++a;
        }
      else if (*a == '+')
        ++a;
    }

  while (*a != '\0')
    {
      if (*a < '0' || *a > '9')
          break;
      ret *= 10;
      ret += *a++ - '0';
    }

  ret *= multiple;

  return ret;
}


int main (int argc, char **argv)
{
  using namespace std;

  if (argc < 2)
    return 1;

  cout << myatoi (argv[1]) << endl;
  cout << atoi (argv[1]) << endl;
  cout << stoi (argv[1]) << endl;
}
