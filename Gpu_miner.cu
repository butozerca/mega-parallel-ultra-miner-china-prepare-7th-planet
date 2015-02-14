#include<cstdio>
#include"sha256.hpp"

extern "C" {
__global__ 
void Gpu_hash(const char* input, int length, int nonce_offset, int difficulty, int* result)
{
    int nonce=blockIdx.x*blockDim.x+threadIdx.x;
    char nonce_input[length+4];
    memcpy(nonce_input, input, length);
    memcpy(nonce_input+length, (void*)&nonce, 4);
    
    unsigned char digest[SHA256::DIGEST_SIZE];
    memset(digest,0,SHA256::DIGEST_SIZE);
 
    SHA256 ctx = SHA256();
    ctx.init();
    ctx.update(input, length);
    ctx.final(digest);
    
    
    unsigned char digest2[SHA256::DIGEST_SIZE];
    memset(digest2,0,SHA256::DIGEST_SIZE);
 
    SHA256 ctx = SHA256();
    ctx.init();
    ctx.update(input, length);
    ctx.final(digest2);
    
    for (int i = 0; i < (difficulty >> 1); ++i){
        
    }
}
}