#include<cstdio>
#include"sha256.hpp"

extern "C" {
__global__ 
void Gpu_hash(const char* input, int length, int nonce_offset, int difficulty, int* result)
{
    int nonce=blockIdx.x*blockDim.x+threadIdx.x;
    char nonce_input[80];
    memcpy(nonce_input, input, length);
    memcpy(nonce_input+length, (void*)&nonce, 4);
    
    unsigned char digest[SHA256::DIGEST_SIZE];
 
    SHA256 ctx = SHA256();
    ctx.init();
    ctx.update(nonce_input, length + 4);
    ctx.final(digest);

    ctx.init();
    ctx.update(digest, 32);
    ctx.final(nonce_input);
    
    for (int i = 0; i < (difficulty >> 3); ++i)
        if (nonce_input[i] != 0) return;
    if (nonce_input[difficulty >> 3] <= 255 >> difficulty & 7)
        *result = nonce;
}
}
