#include<cstdio>
#include"sha256.hpp"

extern "C" {
__global__ 
void Gpu_hash(const char* input, int length, int nonce_offset, int difficulty, int* result)
{
    
}
}