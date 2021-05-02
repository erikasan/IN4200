void single_layer_convolution(int M, int N, float **input,
                              int K, float **kernel,
                              float **output)
  /*
    input is an M x N array
    kernel is a K x K array
    output is an (M - K + 1) x (N - K + 1) array
  */
{
  int i, j, ii, jj;
  double temp;

  for (i = 0; i <= M - K; i++){ // Loop over each possible projection of the kernel
  for (j = 0; j <= N - K; j++){ // onto the input array

    temp = 0;

    for (ii = 0; ii < K; ii++){ // Take the "dot product" between the kernel
    for (jj = 0; jj < K; jj++){ // and a projection

      temp += input[i+ii][j+jj]*kernel[ii][jj];

    }}

    output[i][j] = temp;

  }}


  return;
}
