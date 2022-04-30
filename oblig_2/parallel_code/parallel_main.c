// Needed header files
#include "image.h"
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.c"

void import_JPEG_file (const char* filename, unsigned char** image_chars,
                       int* image_height, int* image_width,
                       int* num_components);
void export_JPEG_file (const char* filename, const unsigned char* image_chars,
                       int image_height, int image_width,
                       int num_components, int quality);

int main(int argc, char *argv[])
{
  int m, n, c, iters;
  int my_m, my_n, my_rank, num_procs;
  float kappa;
  image u, u_bar, whole_image;
  unsigned char *image_chars, *my_image_chars;
  char *input_jpeg_filename, *output_jpeg_filename;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  // Read from command line: kappa, iters, input_jpeg_filename, output_jpeg_filename
  if (argc != 5) {
    if (my_rank == 0) {
      printf("Usage: %s kappa iters input_jpeg_filename output_jpeg_filename\n", argv[0]);
    }
    MPI_Finalize();
    return 1;
  }

  kappa = atof(argv[1]);
  iters = atoi(argv[2]);
  input_jpeg_filename  = argv[3];
  output_jpeg_filename = argv[4];

  
  if (my_rank == 0){
    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    allocate_image(&whole_image, m, n);
  }

  

  MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  

  // 2D decomposition of the m x n pixels evenly among the MPI processes

  int div = m/num_procs;
  int rem = m%num_procs;

  if (my_rank == 0){
    my_m = div + 1;
  }

  if (my_rank == num_procs - 1){
    my_m = div + rem + 1;
  }

  else{
    my_m = div + 2;
  }

  my_n = n;

  

  allocate_image(&u, my_m, my_n);
  allocate_image(&u_bar, my_m, my_n);

  

  // Each process asks process 0 for a partitioned region
  // of image_chars and copy the values into u
  // ...

  int counts_send[num_procs];
  int displacements[num_procs];

  counts_send[0]  = (div + 1)*n;
  displacements[0] = 0;
  for (int rank = 1; rank < num_procs - 1; rank++){
    counts_send[rank]  = (div + 2)*n;
    displacements[rank] = (rank*div - 1)*n;
  }

  counts_send[num_procs - 1]   = (div + rem + 1)*n;
  displacements[num_procs - 1] = ((num_procs - 1)*div - 1)*n;

  

  // int start, stop;

  // if (my_rank == 0){
  //   start = 0;
  //   stop  = div + 1; 
  // }

  // if (my_rank == num_procs - 1){
  //   start = (num_procs - 1)*div - 1;
  //   stop  = num_procs*div + rem;
  // }

  // else{
  //   start = my_rank*div - 1;
  //   stop  = (my_rank + 1)*div + 1;
  // }

  my_image_chars = (unsigned char *) malloc(my_m*my_n*sizeof(unsigned char));

  

  MPI_Scatterv(image_chars, 
               counts_send, 
               displacements, 
               MPI_UNSIGNED_CHAR, 
               my_image_chars, 
               counts_send[my_rank], 
               MPI_UNSIGNED_CHAR, 
               0, 
               MPI_COMM_WORLD);
  
  

  convert_jpeg_to_image(my_image_chars, &u);
  iso_diffusion_denoising_parallel(&u, &u_bar, kappa, iters);

  

  // Each process sends its resulting content of u_bar to process 0
  // Process 0 receives from each process incoming values and
  // copy them into the designated region of struct whole_image
  // ...

  int counts_recv[num_procs];
  for (int rank = 0; rank < num_procs - 1; rank++){
    counts_recv[rank] = div*n;
    displacements[rank+1] = n;
  }
  counts_recv[num_procs - 1] = (div + rem)*n;


  MPI_Gatherv(u_bar.image_data, 
              counts_recv[my_rank], 
              MPI_FLOAT, 
              whole_image.image_data, 
              counts_recv, 
              displacements, 
              MPI_FLOAT, 
              0, 
              MPI_COMM_WORLD);

  if (my_rank == 3){
    //printf("Process 3 %f \n", u_bar.image_data[u_bar.m - 1][u_bar.n - 1]);
    printf("Process 3 m = %d n = %d \n", u_bar.m, u_bar.n);
  }

  if (my_rank == 0){
    //printf("Process 0 %f \n", whole_image.image_data[whole_image.m - 1][whole_image.n - 1]);
    printf("Process 0 m = %d n = %d \n", whole_image.m, whole_image.n);
  }

  if (my_rank == 0){
    printf("Before convert_image_to_jpeg \n");
    convert_image_to_jpeg(&whole_image, image_chars);
    printf("After convert_image_to_jpeg \n");
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);
    deallocate_image(&whole_image);
  }

  // Temporary
  printf("Checkpoint 14\n");

  deallocate_image(&u);
  deallocate_image(&u_bar);

  // Temporary
  printf("Checkpoint 15\n");

  MPI_Finalize();
  return 0;
}
