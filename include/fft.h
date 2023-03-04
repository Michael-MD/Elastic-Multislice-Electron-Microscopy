// 1D FFT
void rad2FFT(float xr[], float xi[], unsigned int N);
void irad2FFT(float Xr[], float Xi[], unsigned int N);

// 2D FFT
void rad2FFT2(float **xr, float **xi, unsigned int Nx, unsigned int Ny);
void irad2FFT2(float **Xr, float **Xi, unsigned int Nx, unsigned int Ny);

//fftshift
void fftshift(float xr[], float xi[], unsigned int N);
void fftshift2(float **xr, float **xi, unsigned int Nx, unsigned int Ny);