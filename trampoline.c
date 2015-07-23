// gcc -O3 -std=gnu99 trampoline.c -o trampoline
#include <stdlib.h>
#include <stdio.h>

int
g (int a, int (*f)(int))
{
   return f (a);
}

int
main (int argc, char *argv[])
{
   int scale = 5;
   int closure (int a) { return a * scale; }

   if (argc < 2)
     return 1;

   int x = atoi (argv[1]);

   printf ("%d\n", g (x, closure));
}
