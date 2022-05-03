
void allocate_image(image *u, int m, int n){

    (*u).image_data = malloc(m * sizeof *((*u).image_data));
    (*u).image_data[0] = malloc(m*n * sizeof *((*u).image_data[0]));
    for (int i = 1; i < m; i++){
        (*u).image_data[i] = &((*u).image_data[0][i*n]);
    }

    (*u).m = m;
    (*u).n = n;
    
    return;
}

void deallocate_image(image *u){
     
    free((*u).image_data[0]);
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
    int i, j;
    int m, n;

    m = (*u).m;
    n = (*u).n; 

    int iter;
    float temp;

    int iters_min_1 = iters - 1;
    int m_min_1     = m - 1;
    int n_min_1     = n - 1;

    // Copy boundary pixels
    for (i = 0; i < m; i++){
        (*u_bar).image_data[i][0]   = (*u).image_data[i][0];
        (*u_bar).image_data[i][n_min_1] = (*u).image_data[i][n_min_1];
    }

    for (j = 0; j < n; j++){
        (*u_bar).image_data[0][j]   = (*u).image_data[0][j];
        (*u_bar).image_data[m_min_1][j] = (*u).image_data[m_min_1][j];
    }

    // Main algorithm
    for (iter = 0; iter < iters_min_1; iter++){
        for (i = 1; i < m_min_1; i++){
        for (j = 1; j < n_min_1; j++){
            temp = (*u).image_data[i-1][j] + (*u).image_data[i][j-1] - 4*(*u).image_data[i][j] + (*u).image_data[i][j+1] + (*u).image_data[i+1][j];
            (*u_bar).image_data[i][j] = (*u).image_data[i][j] + kappa*temp;
        }}

        for (i = 1; i < m_min_1; i++){
        for (j = 1; j < n_min_1; j++){
            (*u).image_data[i][j] = (*u_bar).image_data[i][j];
        }}
        
    }

    // Last iteration
    for (i = 1; i < m_min_1; i++){
    for (j = 1; j < n_min_1; j++){
        temp = (*u).image_data[i-1][j] + (*u).image_data[i][j-1] - 4*(*u).image_data[i][j] + (*u).image_data[i][j+1] + (*u).image_data[i+1][j];
        (*u_bar).image_data[i][j] = (*u).image_data[i][j] + kappa*temp;
    }}
    

    return;
}