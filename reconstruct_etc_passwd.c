// gcc -Wall -Wextra -O3 reconstruct_etc_passwd.c -o reconstruct_etc_passwd
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

int
main (void)
{
  char newpasswd[] = "/tmp/passwd.XXXXXX";

  int fd;
  FILE *fp;

  struct passwd *ptr;

  if ((fd = mkstemp (newpasswd)) < 0)
    {
      perror ("mkstemp");
      return 1;
    }

  if ((fp = fdopen (fd, "w")) == NULL)
    {
      perror ("fdopen");
      return 1;
    }

  setpwent ();
  while ((ptr = getpwent ()) != NULL)
    if (putpwent (ptr, fp) < 0)
      perror ("putpwent");

  endpwent ();

  if (fclose (fp) == EOF)
    perror ("fclose");

  puts (newpasswd);

  return 0;
}
