#include "image.h"
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
  float kappa;
  image u, u_bar;
  unsigned char *image_chars;
  char *input_jpeg_filename, *output_jpeg_filename;

  // Read from command line: kappa, iters, input_jpeg_filename, output_jpeg_filename
  if (argc != 5) {
    printf("Usage: %s kappa iters input_jpeg_filename output_jpeg_filename\n", argv[0]);
    return 1;
  }
  
  kappa = atof(argv[1]);
  iters = atoi(argv[2]);
  input_jpeg_filename  = argv[3];
  output_jpeg_filename = argv[4];

  import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);

  allocate_image(&u, m, n);
  allocate_image(&u_bar, m, n);
  convert_jpeg_to_image(image_chars, &u);

  iso_diffusion_denoising(&u, &u_bar, kappa, iters);

  convert_image_to_jpeg(&u_bar, image_chars);
  export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

  deallocate_image(&u);
  deallocate_image(&u_bar);

  return 0;
}
