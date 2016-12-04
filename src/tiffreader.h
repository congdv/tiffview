#ifndef TIFF_READER_H
#define TIFF_READER_H
#include "matrix.h"

matrix_t *read_image_tiff(const char *path_to_image);

#endif
