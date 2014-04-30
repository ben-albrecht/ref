
/* Example showing the use of CUFFT for fast 1D-convolution using FFT. OpenACC
   is used for the point-wise complex multiply and scale.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <cuda_runtime_api.h>

#include <cufft.h>

void check(cudaError_t result, char const *const func, const char *const file, int const line)
{
    if (result) {
        fprintf(stderr, "%s:%d code=%d (%s) \"%s\"\n", file, line, 
                (unsigned int)result, cudaGetErrorString(result));
    }
}

// This will output the proper CUDA error strings in the event that a CUDA host call returns an error
#define checkCudaErrors(val)           check ( (val), #val, __FILE__, __LINE__ )


// Complex data type
//typedef float2 Complex;
typedef struct {
    float x, y;
} Complex;
static inline Complex ComplexAdd(Complex, Complex);
static inline Complex ComplexScale(Complex, float);
static inline Complex ComplexMul(Complex, Complex);

// Host filtering function
void Convolve(const Complex *, int, const Complex *, int, Complex *);

// Padding function
int PadData(const Complex *, Complex **, int,
            const Complex *, Complex **, int);

// Correctness checking
int compareL2(const float* reference, const float* data,
              const unsigned int len, const float epsilon);

// main test function
void runTest(int argc, char **argv);

// The filter size is assumed to be a number smaller than the signal size
#define SIGNAL_SIZE        500000
#define FILTER_KERNEL_SIZE 33

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    runTest(argc, argv);
    return 0;
}

void complexPointwiseMulAndScale(int n, float *restrict signal, float *restrict filter_kernel)
{
// Multiply the coefficients together and normalize the result
#pragma acc data deviceptr(signal, filter_kernel)
    {
#pragma acc kernels loop independent    
        for (int i = 0; i < n; i++) {
            float ax = signal[2*i];
            float ay = signal[2*i+1];
            float bx = filter_kernel[2*i];
            float by = filter_kernel[2*i+1];
            float s = 1.0f / n;
            float cx = s * (ax * bx - ay * by);
            float cy = s * (ax * by + ay * bx);
            signal[2*i] = cx;
            signal[2*i+1] = cy;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
//! Run a simple test for CUDA
////////////////////////////////////////////////////////////////////////////////
void runTest(int argc, char **argv)
{
    // CUDA events for timing
    cudaEvent_t start, stop, startPointwise, stopPointwise;
    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&stop));
    checkCudaErrors(cudaEventCreate(&startPointwise));
    checkCudaErrors(cudaEventCreate(&stopPointwise));
    
    // Allocate host memory for the signal and filter
    Complex *h_signal = (Complex *)malloc(sizeof(Complex) * SIGNAL_SIZE);
    Complex *h_filter_kernel = (Complex *)malloc(sizeof(Complex) * FILTER_KERNEL_SIZE);
    
    // Initalize the memory for the signal
    for (unsigned int i = 0; i < SIGNAL_SIZE; ++i) {
        h_signal[i] .x = rand() / (float)RAND_MAX;
        h_signal[i].y = 0;
    }

    // Initalize the memory for the filter
    for (unsigned int i = 0; i < FILTER_KERNEL_SIZE; ++i) {
        h_filter_kernel[i].x = rand() / (float)RAND_MAX;
        h_filter_kernel[i].y = 0;
    }

    // Pad signal and filter kernel
    Complex *h_padded_signal;
    Complex *h_padded_filter_kernel;
    int new_size = PadData(h_signal, &h_padded_signal, SIGNAL_SIZE,
                           h_filter_kernel, &h_padded_filter_kernel, FILTER_KERNEL_SIZE);
    int mem_size = sizeof(Complex) * new_size;

    // Allocate device memory for signal
    Complex *d_signal;
    checkCudaErrors(cudaMalloc((void **)&d_signal, mem_size));
    // Copy host memory to device
    checkCudaErrors(cudaMemcpy(d_signal, h_padded_signal, mem_size,
                               cudaMemcpyHostToDevice));

    // Allocate device memory for filter kernel
    Complex *d_filter_kernel;
    checkCudaErrors(cudaMalloc((void **)&d_filter_kernel, mem_size));
    
    // Create CUFFT plan
    cufftHandle plan;
    cufftResult error = cufftPlan1d(&plan, new_size, CUFFT_C2C, 1);
    if (error != CUFFT_SUCCESS)
        printf("CUFFT Error: %d", error);

    // Start timing
    checkCudaErrors(cudaEventRecord(start, 0));

    // Copy host memory to device
    checkCudaErrors(cudaMemcpy(d_filter_kernel, h_padded_filter_kernel, mem_size,
                             cudaMemcpyHostToDevice));

    // Transform signal and kernel
    printf("Transforming signal cufftExecC2C\n");
    error = cufftExecC2C(plan, (cufftComplex *)d_signal, (cufftComplex *)d_signal, CUFFT_FORWARD);
    error = cufftExecC2C(plan, (cufftComplex *)d_filter_kernel, (cufftComplex *)d_filter_kernel, CUFFT_FORWARD);
    if (error != CUFFT_SUCCESS)
        printf("CUFFT Error: %d", error);

    // Multiply the coefficients together and normalize the result
    printf("Performing point-wise complex multiply and scale.\n");
    checkCudaErrors(cudaEventRecord(startPointwise, 0));
    complexPointwiseMulAndScale(new_size, 
                                (float *restrict)d_signal,
                                (float *restrict)d_filter_kernel);
    checkCudaErrors(cudaEventRecord(stopPointwise, 0));

    // Transform signal back
    printf("Transforming signal back cufftExecC2C\n");
    error = cufftExecC2C(plan, (cufftComplex *)d_signal, (cufftComplex *)d_signal, CUFFT_INVERSE);
    if (error != CUFFT_SUCCESS)
        printf("CUFFT Error: %d", error);

    // Copy device memory to host
    Complex *h_convolved_signal = h_padded_signal;
    checkCudaErrors(cudaMemcpy(h_convolved_signal, d_signal, mem_size,
                               cudaMemcpyDeviceToHost));
    checkCudaErrors(cudaEventRecord(stop, 0));
    
    // Allocate host memory for the convolution result
    Complex *h_convolved_signal_ref = (Complex *)malloc(sizeof(Complex) * SIGNAL_SIZE);

    // Convolve on the host
    printf("Performing Convolution on the host and checking correctness\n");
    Convolve(h_signal, SIGNAL_SIZE,
             h_filter_kernel, FILTER_KERNEL_SIZE,
             h_convolved_signal_ref);

    // check result
    int testResult = compareL2((float *)h_convolved_signal_ref, 
                               (float *)h_convolved_signal, 
                               2 * SIGNAL_SIZE, 1e-5f);

    float ms, msPointwise;
    cudaEventSynchronize(stop);
    checkCudaErrors(cudaEventElapsedTime(&ms, start, stop));
    checkCudaErrors(cudaEventElapsedTime(&msPointwise, startPointwise, stopPointwise));
    printf("\nSignal size: %d, filter size: %d\n", SIGNAL_SIZE, FILTER_KERNEL_SIZE);
    printf("Total Device Convolution Time: %f ms (%f for point-wise convolution)\n", ms, msPointwise);
    
    printf("Test %s\n", testResult == 1 ? "PASSED" : "FAILED");

    //Destroy CUFFT context
    error = cufftDestroy(plan);
    if (error != CUFFT_SUCCESS)
        printf("CUFFT Error: %d", error);

    // cleanup memory
    free(h_signal);
    free(h_filter_kernel);
    free(h_padded_signal);
    free(h_padded_filter_kernel);
    free(h_convolved_signal_ref);
    checkCudaErrors(cudaFree(d_signal));
    checkCudaErrors(cudaFree(d_filter_kernel));
    checkCudaErrors(cudaEventDestroy(start));
    checkCudaErrors(cudaEventDestroy(stop));
    //cutilDeviceReset();
}

// Pad data
int PadData(const Complex *signal, Complex **padded_signal, int signal_size,
            const Complex *filter_kernel, Complex **padded_filter_kernel, int filter_kernel_size)
{
    int minRadius = filter_kernel_size / 2;
    int maxRadius = filter_kernel_size - minRadius;
    int new_size = signal_size + maxRadius;

    // Pad signal
    Complex *new_data = (Complex *)malloc(sizeof(Complex) * new_size);
    memcpy(new_data + 0, signal, signal_size * sizeof(Complex));
    memset(new_data + signal_size, 0, (new_size - signal_size) * sizeof(Complex));
    *padded_signal = new_data;

    // Pad filter
    new_data = (Complex *)malloc(sizeof(Complex) * new_size);
    memcpy(new_data + 0, filter_kernel + minRadius, maxRadius * sizeof(Complex));
    memset(new_data + maxRadius, 0, (new_size - filter_kernel_size) * sizeof(Complex));
    memcpy(new_data + new_size - minRadius, filter_kernel, minRadius * sizeof(Complex));
    *padded_filter_kernel = new_data;

    return new_size;
}

////////////////////////////////////////////////////////////////////////////////
// Filtering operations
////////////////////////////////////////////////////////////////////////////////

// Computes convolution on the host
void Convolve(const Complex *signal, int signal_size,
              const Complex *filter_kernel, int filter_kernel_size,
              Complex *filtered_signal)
{
    int minRadius = filter_kernel_size / 2;
    int maxRadius = filter_kernel_size - minRadius;

    // Loop over output element indices
    for (int i = 0; i < signal_size; ++i) {
        filtered_signal[i].x = filtered_signal[i].y = 0;

        // Loop over convolution indices
        for (int j = - maxRadius + 1; j <= minRadius; ++j) {
            int k = i + j;

            if (k >= 0 && k < signal_size) {
                filtered_signal[i] = 
                    ComplexAdd(filtered_signal[i], 
                               ComplexMul(signal[k], 
                                          filter_kernel[minRadius - j]));
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Complex operations
////////////////////////////////////////////////////////////////////////////////

// Complex addition
static Complex ComplexAdd(Complex a, Complex b)
{
    Complex c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

// Complex scale
static inline Complex ComplexScale(Complex a, float s)
{
    Complex c;
    c.x = s * a.x;
    c.y = s * a.y;
    return c;
}

// Complex multiplication
static inline Complex ComplexMul(Complex a, Complex b)
{
    Complex c;
    c.x = a.x * b.x - a.y * b.y;
    c.y = a.x * b.y + a.y * b.x;
    return c;
}

// Complex pointwise multiplication
/*static __global__ void ComplexPointwiseMulAndScale(Complex *a, const Complex *b, int size, float scale)
{
    const int numThreads = blockDim.x * gridDim.x;
    const int threadID = blockIdx.x * blockDim.x + threadIdx.x;

    for (int i = threadID; i < size; i += numThreads) {
        a[i] = ComplexScale(ComplexMul(a[i], b[i]), scale);
    }
}*/

int compareL2(const float* reference, const float* data,
              const unsigned int len, const float epsilon)
{
    float error = 0;
    float ref = 0;

    for(unsigned int i = 0; i < len; ++i) {
        float diff = reference[i] - data[i];
        error += diff * diff;
        ref += reference[i] * reference[i];
    }

    float normRef = sqrtf(ref);
    float normError = sqrtf(error);
    error = normError / normRef;
    int result = error < epsilon ? 1 : 0;
    if(0 == result)
    {
        printf("ERROR, l2-norm error %e is greater than epsilon %e\n",
               error, epsilon);
    }

    return result;
}
