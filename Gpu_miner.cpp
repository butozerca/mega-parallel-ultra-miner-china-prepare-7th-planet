#include <cuda.h>

#include "Gpu_miner.hpp"

int Gpu_miner::mine(std::string& input, int offset, int difficulty)
{
    cuInit(0);
    
    CUdevice cuDevice;
    CUresult res = cuDeviceGet(&cuDevice, 0);
    if (res != CUDA_SUCCESS){
        printf("cannot acquire device 0\n"); 
        exit(1);
    }

    CUcontext cuContext;
    res = cuCtxCreate(&cuContext, 0, cuDevice);
    if (res != CUDA_SUCCESS){
        printf("cannot create context\n");
        exit(1);
    }

    CUmodule cuModule = (CUmodule)0;
    res = cuModuleLoad(&cuModule, "Gpu_miner.ptx");
    if (res != CUDA_SUCCESS) {
        printf("cannot load module: %d\n", res);  
        exit(1); 
    }

    CUfunction Gpu_hash;
    res = cuModuleGetFunction(&Gpu_hash, cuModule, "Gpu_hash");
    if (res != CUDA_SUCCESS){
        printf("cannot acquire kernel handle\n");
        exit(1);
    }
	
    int gridX=1;
	int gridY=1;
    int gridZ=1;
	int blockX=1;
	int blockY=1;
    int blockZ=1;
    
    const char* data=input.data();
    int size=input.size();
    CUdeviceptr result;
    cuMemAlloc(&result, 4);
    int tmp[1]={-1};
    cuMemcpyHtoD(result, tmp, 4);
    
    void* args[] = {&data, &size, &offset, &difficulty, &result};
    res = cuLaunchKernel(Gpu_hash, gridX, gridY, gridZ, blockX, blockY, blockZ, 0, 0, args, 0);
    if (res != CUDA_SUCCESS){
        printf("cannot run kernel\n");
        exit(1);
    }
	
	cuCtxSynchronize();
    
    cuMemcpyDtoH((void*)tmp, result, 4);
 
    cuCtxDestroy(cuContext);

    return tmp[0];
}
