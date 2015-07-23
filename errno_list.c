// gcc -std=gnu99 errno_list.c -o errno_list
#define _GNU_SOURCE
#include <stdio.h>

int
main ()
{
  for (int i = 1; i < _sys_nerr; ++i)
    {
      if (_sys_errlist[i] == NULL)
        continue;
      puts (_sys_errlist[i]);
    }
}
