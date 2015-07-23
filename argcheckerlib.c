// gcc -Wall -fno-builtin -O3 -std=gnu99 -fpic -shared -Wl,-soname,libargcheck.so argcheckerlib.c -o libargcheck.so
#define _GNU_SOURCE

#include <dlfcn.h>
#include <assert.h>

#define LOAD_ADDRESS(var, str)                  \
  if (var == 0)                                 \
    if ((var = dlsym (RTLD_NEXT, str)) == 0)    \
      __builtin_abort ()


int
strcmp (const char *s1, const char *s2)
{
  static int (*libc_strcmp)(const char *, const char *) = 0;

  assert (s1);
  assert (s2);

  LOAD_ADDRESS (libc_strcmp, "strcmp");

  return libc_strcmp (s1, s2);
}


int
strncmp (const char *s1, const char *s2, size_t n)
{
  static int (*libc_strncmp)(const char *, const char *, size_t) = 0;

  assert (s1);
  assert (s2);

  LOAD_ADDRESS (libc_strncmp, "strncmp");

  return libc_strncmp (s1, s2, n);
}

int
memcmp (const char *s1, const char *s2, size_t n)
{
  static int (*libc_memcmp)(const char *, const char *, size_t) = 0;

  assert (s1);
  assert (s2);

  LOAD_ADDRESS (libc_memcmp, "memcmp");

  return libc_memcmp (s1, s2, n);
}
