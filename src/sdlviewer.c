#include <tiffio.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "tiffreader.h"

void view(char *path_to_image) 
{
    SDL_Surface *surface;
    SDL_Event event;
    int quit = 0;
    matrix_t *matrix = read_image_tiff(path_to_image);
    if(matrix == NULL)
        return;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr,"Could not initialize SDL_VIDEO");
    }
    surface = SDL_SetVideoMode(matrix->cols,matrix->rows,32,SDL_HWSURFACE);
    /*plot pixels */
    unsigned int x,y;
    unsigned char *data = matrix->data;

    unsigned int index_pixel = 0;
    for(y = 0; y < matrix->rows;y++){
        for(x = 0; x < matrix->cols; x++){
            unsigned r,g,b;
            r = data[index_pixel* matrix->channels] << 16;
            g = data[index_pixel * matrix->channels + 1] << 8;
            b = data[index_pixel * matrix->channels + 2];
            Uint32 *buff = (Uint32 *)surface->pixels + y *(surface->pitch/4) +x;
            *buff = r + g + b; 
            index_pixel++;
        }

    }
    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) quit = 1;
            else if(SDL_GetKeyState(NULL)[SDLK_ESCAPE]) quit = 1;
        }
        SDL_UpdateRect(surface,0,0,0,0);
        SDL_Delay(5);
    }
    free(matrix->data);
    free(matrix);
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
