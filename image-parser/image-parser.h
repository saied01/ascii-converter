#ifndef IMAGE_PARSER_H
#define IMAGE_PARSER_H

#include <stdint.h>

typedef enum
{
  BMP,
  PNG,
  JPG
} img_type;

struct img
{
  int rows;
  int cols;
  uint8_t *bits;
  img_type type;
};

int parse_img(const char *path, struct img *out);

#endif // !IMAGE_PARSER_H
