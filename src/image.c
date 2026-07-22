#include "image.h"
#include "bmp.h"
#include <stdint.h>
#include <stdio.h>

int parse_img(const char *path, img_t *out)
{
  FILE *f = fopen(path, "rb");
  if (!f)
    return -1;

  char type[3] = {0};
  if (fread(type, 1, 2, f) != 2)
    return -1;

  if (type[0] == 'B' && type[1] == 'M')
    return parse_bmp(f, out);

  return 0;
}
