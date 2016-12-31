#ifndef SDL_VIEWER_H_
#define SDL_VIEWER_H_

#include <opencv/cv.h>
#include "matrix.h"

/**
 * This function support for view CVMat array of opencv
 *
 */
void view_mat_array(CvMat **mat_array, int nArray);

/**
 * View single CvMat of openCV
 */
void view_mat(CvMat *mat);

/**
 * view matrix of image with my data struct for image
 */
void view_matrix(matrix_t *matrix);

/**
 * view matrix of image with my data struct for image
 * with matrix array
 */
void view_matrix_array(matrix_t **matrix_array);
#endif //SDL_VIEWER_H_
