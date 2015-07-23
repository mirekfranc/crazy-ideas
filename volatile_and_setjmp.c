// gcc -O3 -std=gnu99 volatile_and_setjmp.c -o volatile_and_setjmp
#include <setjmp.h>
#include <stdio.h>

jmp_buf buf;
int called_before;

static void
f ()
{
  longjmp (buf, 1);
}

int
main (int argc, char *argv[])
{
  volatile int i = 5;

  if ((called_before = setjmp (buf)))
    puts ("second:");
  else
    puts ("first: ");

  ++i; // without volatile this might not be visible

  printf ("%d\n", i);


  if (!called_before)
    f ();
}
