#include "bmp.h"
#include "image.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int parse_bmp(FILE *f, img_t *img)
{
  // cursor starts from filesize (byte 2)
  uint32_t filesize;
  uint32_t bitmap_offset;
  int32_t width;
  int32_t height;
  uint16_t bits_per_pixel;

  if (!fread(&filesize, sizeof(uint32_t), 1, f))
    return -1;
  fseek(f, 4, SEEK_CUR);
  if (!fread(&bitmap_offset, sizeof(uint32_t), 1, f))
    return -1;
  fseek(f, 4, SEEK_CUR);
  if (!fread(&width, sizeof(int32_t), 1, f))
    return -1;
  if (!fread(&height, sizeof(int32_t), 1, f))
    return -1;
  fseek(f, 2, SEEK_CUR);
  if (!fread(&bits_per_pixel, sizeof(int16_t), 1, f))
    return -1;

  img->width = width;
  img->height = height;
  img->bits_per_pixel = bits_per_pixel;
  // hasta aca todo lo anterior podria ser una funcion 'parse_header' o algo asi

  if (fseek(f, bitmap_offset, SEEK_SET) != 0)
    return -1;

  size_t size = (size_t)width * height * (bits_per_pixel / 8);
  uint8_t *pixels = malloc(size);
  if (!pixels)
    return -1;
  img->pixels = pixels;

  if (read_pixels(f, img) < 0)
  {
    free(pixels);
    fclose(f);
    return -1;
  }

  fclose(f);

  return 0;
}

void read_pixels(FILE *f, img_t *img);
