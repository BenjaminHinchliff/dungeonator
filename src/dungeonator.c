#include "dungeonator.h"

char *hello(const char *name) {
  const char *helloStr = "hello ";
  size_t outSz = strlen(helloStr) + strlen(name) + 1;
  char *out = (char *)malloc(outSz);
  if (!out)
    return NULL;
  strcpy_s(out, outSz, helloStr);
  strcat_s(out, outSz, name);
  return out;
}
