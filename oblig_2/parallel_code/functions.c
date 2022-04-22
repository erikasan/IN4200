#include "image.h"
#include "mpi.h"
#include <stdlib.h>

void allocate_image(image *u, int m, int n){
    (*u).image_data = (float **) malloc(m*sizeof(float *));
    for (int i = 0; i < m; i++)
    {
        (*u).image_data[i] = (float *) malloc(n*sizeof(float));
    }

    (*u).m = m;
    (*u).n = n;
    
    return;
}

void deallocate_image(image *u){
    int m = (*u).m;

    for (int i = 0; i < m; i++){
        free((*u).image_data[i]);
    }

    free((*u).image_data);
    
    return;
}

void convert_jpeg_to_image(const unsigned char* image_chars, image*u){
    int i, j;
    int m, n;

    m = (*u).m;
    n = (*u).n;

    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            (*u).image_data[i][j] = image_chars[i*n + j];
        }
    }

    return;
}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars){
    int i, j;
    int m, n;

    m = (*u).m;
    n = (*u).n;

    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            image_chars[i*n + j] = (*u).image_data[i][j];
        }
    }

    return;
}

void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters){
    return;
}