#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include "sdlviewer.h"
int main(int argc, char *argv[])
{
    if(argc == 2){
       CvMat *mat = cvLoadImageM(argv[1],1); 
       view_mat(mat);
    }
}
