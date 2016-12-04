#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "tiffreader.h"
int main(int argc, char *argv[])
{
    if(argc == 2){
       matrix_t *matrix = read_image_tiff(argv[1]); 
       CvMat *mat = cvCreateMat(matrix->rows,matrix->cols,CV_8UC3);
       mat->data.ptr = matrix->data;
       cvSaveImage("test.tiff",mat,0);
    }
}
