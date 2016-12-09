#include <tiffio.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "tiffreader.h"

void convert_matrix_to_surface(SDL_Surface *surface,unsigned char *data,int channels,unsigned int rows, unsigned int cols) {
	
    unsigned int x,y;
    unsigned int index_pixel = 0;
    for(y = 0; y < rows;y++){
        for(x = 0; x < cols; x++){
            unsigned r,g,b;
            r = data[index_pixel*channels] << 16;
            g = data[index_pixel * channels + 1] << 8;
            b = data[index_pixel * channels + 2];
            Uint32 *buff = (Uint32 *)surface->pixels + y *(surface->pitch/4) +x;
            *buff = r + g + b; 
            index_pixel++;
        }

    }
}
void view(char *path_to_image) 
{
    SDL_Surface *surface;
    SDL_Event event;
    int quit = 0;
	int npages;
    matrix_t **nmatrix = read_image_tiff(path_to_image,&npages);
    if(nmatrix == NULL)
        return;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr,"Could not initialize SDL_VIDEO");
    }
	int index_page = 0;
	matrix_t *matrix = nmatrix[index_page];
	surface = SDL_SetVideoMode(matrix->cols,matrix->rows,32,SDL_HWSURFACE);
    /*plot pixels */
    while(!quit){
		convert_matrix_to_surface(surface,matrix->data,matrix->channels,matrix->rows,matrix->cols);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) quit = 1;
            else if(SDL_GetKeyState(NULL)[SDLK_ESCAPE]) quit = 1;
			else if(event.type == SDL_KEYDOWN) {
				index_page++;	
				if(index_page >= npages)
					index_page = 0;
				matrix = nmatrix[index_page];
			}
        }
        SDL_UpdateRect(surface,0,0,0,0);
        SDL_Delay(5);
    }
    SDL_Quit();

    return; 
}
int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr,"No such tif file for view\n");
        exit(0);
    }else {
        view(argv[1]);
    }
    return 0;
}
