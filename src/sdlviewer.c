#include "sdlviewer.h" 

#include <SDL/SDL.h>

void convert_matrix_to_surface(SDL_Surface *surface,unsigned char *data,int channels,unsigned int rows, unsigned int cols) {
    unsigned int x,y;
    unsigned int index_pixel = 0;
    for(y = 0; y < rows;y++){
        for(x = 0; x < cols; x++){
            unsigned r,g,b;
            r = data[index_pixel * channels + 2] << 16;
            g = data[index_pixel * channels + 1] << 8;
            b = data[index_pixel * channels];
            Uint32 *buff = (Uint32 *)surface->pixels + y *(surface->pitch/4) +x;
            *buff = r + g + b; 
            index_pixel++;
        }

    }
}

void view_mat_array(CvMat **mat_array, int nArray)
{
    SDL_Surface *surface;
    SDL_Event event;
    int quit = 0;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr,"Could not initialize SDL_VIDEO");
    }
	int index_page = 0;
    CvMat *mat = mat_array[index_page];
    int channels = mat->step / mat->cols;
	surface = SDL_SetVideoMode(mat->cols,mat->rows,32,SDL_HWSURFACE);
    /*plot pixels */
    while(!quit){
		convert_matrix_to_surface(surface,mat->data.ptr,channels,mat->rows,mat->cols);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) quit = 1;
            else if(SDL_GetKeyState(NULL)[SDLK_ESCAPE]) quit = 1;
			else if(event.type == SDL_KEYDOWN) {
				index_page++;	
				if(index_page >= nArray)
					index_page = 0;
				mat= mat_array[index_page];
			}
        }
        SDL_UpdateRect(surface,0,0,0,0);
        SDL_Delay(5);
    }
    SDL_Quit();

}
void view_mat(CvMat *mat)
{
    SDL_Surface *surface;
    SDL_Event event;
    int quit = 0;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr,"Could not initialize SDL_VIDEO");
    }
    int channels = mat->step / mat->cols;
	surface = SDL_SetVideoMode(mat->cols,mat->rows,32,SDL_HWSURFACE);
    /*plot pixels */
    while(!quit){
		convert_matrix_to_surface(surface,mat->data.ptr,channels,mat->rows,mat->cols);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) quit = 1;
            else if(SDL_GetKeyState(NULL)[SDLK_ESCAPE]) quit = 1;
        }
        SDL_UpdateRect(surface,0,0,0,0);
        SDL_Delay(5);
    }
    SDL_Quit();
}

/**
 * view matrix of image with my data struct for image
 */
void view_matrix(matrix_t *matrix){
    SDL_Surface *surface;
    SDL_Event event;
    int quit = 0;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr,"Could not initialize SDL_VIDEO");
    }
    int channels = matrix->channels; 
	surface = SDL_SetVideoMode(matrix->cols,matrix->rows,32,SDL_HWSURFACE);
    /*plot pixels */
    while(!quit){
		convert_matrix_to_surface(surface,matrix->data,channels,matrix->rows,matrix->cols);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) quit = 1;
            else if(SDL_GetKeyState(NULL)[SDLK_ESCAPE]) quit = 1;
        }
        SDL_UpdateRect(surface,0,0,0,0);
        SDL_Delay(5);
    }
    SDL_Quit();
}
/**
 * view matrix of image with my data struct for image
 * with matrix array
 */
void view_matrix_array(matrix_t **matrix_array,unsigned int n){
    SDL_Surface *surface;
    SDL_Event event;
    int quit = 0;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr,"Could not initialize SDL_VIDEO");
    }
	unsigned int index_page = 0;
    matrix_t *mat = matrix_array[index_page];
    int channels = mat->channels;
	surface = SDL_SetVideoMode(mat->cols,mat->rows,32,SDL_HWSURFACE);
    /*plot pixels */
    while(!quit){
		convert_matrix_to_surface(surface,mat->data,channels,mat->rows,mat->cols);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) quit = 1;
            else if(SDL_GetKeyState(NULL)[SDLK_ESCAPE]) quit = 1;
			else if(event.type == SDL_KEYDOWN) {
				index_page++;	
				if(index_page >= n)
					index_page = 0;
				mat= matrix_array[index_page];
			}
        }
        SDL_UpdateRect(surface,0,0,0,0);
        SDL_Delay(5);
    }
    SDL_Quit();
}
