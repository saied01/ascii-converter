#ifndef IMAGE_PARSER_H
#define IMAGE_PARSER_H

#include <stdint.h>

typedef enum
{
  BMP,
  PNG,
  JPG
} img_type;

typedef struct
{
  int width;
  int height;
  uint8_t *pixels;
  uint16_t bits_per_pixel;
  img_type type;
} img_t;

int parse_img(const char *path, img_t *out);
void image_free(img_t *img);

#endif // !IMAGE_PARSER_H
