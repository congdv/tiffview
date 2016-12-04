#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix_t {
    unsigned int rows;
    unsigned int cols;
    unsigned char *data;
    unsigned char channels;
    unsigned int step;
}matrix_t;

#endif
