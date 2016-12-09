#include "tiffreader.h"

#include <tiffio.h>
#include <stdio.h>
#include <stdlib.h>

#define GetValuePixel(abgr,nbit) (((abgr)>>nbit) & 0xff)
#define NBIT 8

void parse_raster(uint32 *raster,matrix_t *matrix){ 
    unsigned int rows = matrix->rows;
    unsigned int cols = matrix->cols;
    unsigned int channels = matrix->channels;
    unsigned int npixels = rows *cols ;
    unsigned char *data = (unsigned char *)malloc((npixels * matrix->channels) * sizeof(unsigned char));
    unsigned int row,col,channel;
    unsigned int index_pixel = 0;
    for(row = 0; row < rows; row++){
        for(col = 0; col < cols; col++){
            for(channel =0 ; channel < channels; channel++){
                data[index_pixel* channels +  channel]= GetValuePixel(raster[row * cols + col],channel * NBIT);
            }
            index_pixel++;
        }
    }
    /*Assign data matrix*/
    matrix->data = data;
}

matrix_t *matrix_at(int index_page, TIFF *tif)
{
	matrix_t *matrix = (matrix_t *)malloc(sizeof(matrix_t));
    uint32 *raster;
    uint32 width, height;
    uint32 spp;/*sample per pixel*/
    TIFFSetDirectory(tif,index_page);
    /*Get width, height, and spp of image*/
    TIFFGetField(tif,TIFFTAG_IMAGEWIDTH,&width);
    TIFFGetField(tif,TIFFTAG_IMAGELENGTH,&height);
    TIFFGetField(tif,TIFFTAG_SAMPLESPERPIXEL,&spp);

    matrix->rows = height;
    matrix->cols = width;
    matrix->step = width * spp;/*Size of array on a row*/
    matrix->channels = spp;/*Number channels of image*/
    uint32 npixels = width * height;
    /*Allocate memory for raster*/
    raster = (uint32 *)_TIFFmalloc(npixels * sizeof(uint32));
    if(raster != NULL){
        if(TIFFReadRGBAImageOriented(tif,width,height,raster,ORIENTATION_TOPLEFT,1)){
            parse_raster(raster,matrix); 
        }
        _TIFFfree(raster);
    }

    return matrix;
}
int page_quanity(TIFF *tif) 
{
	int counter = 0;
	do {
		counter++;
	}while(TIFFReadDirectory(tif));
	return counter;
}
matrix_t **read_image_tiff(const char *path_to_image,int *npages)
{

    /*Read image */
    TIFF *tif = TIFFOpen(path_to_image,"r");
    if(tif == NULL)
        return NULL;
	*npages = page_quanity(tif);
    matrix_t **nmatrix = (matrix_t **)malloc(*npages *sizeof(matrix_t *));
	for(int i = 0; i < *npages; i++){
		nmatrix[i] = matrix_at(i,tif);
	}
	return nmatrix;
}
