#include <cstring>
#include "Cpu_miner.hpp"
#include "sha256.hpp"

inline bool cmp_str_n(const unsigned char* A, const unsigned char* B, int n) {
    for (int i = 0; i < n; ++i)
        if (A[i] != B[i])
            return A[i] < B[i];
    return true;
}

int Cpu_miner::mine(const char *input, int nonce_begin, int nonce_end, int difficulty)
{   
    char threshold[(difficulty >> 3) + 1];
    memset(threshold, 0, difficulty >> 3);
    threshold[difficulty >> 3] = (char)(255 >> (difficulty & 7));
    
    char in[80];
    memcpy(in, input, 76);

    for (int j = nonce_begin; j < nonce_end; j++) {
        memcpy(in + 76, (const void*)&j, 4);
    
        char buf[32];
        sha256(in, 80, buf);   
        sha256(buf, 32, buf);
        if (cmp_str_n((unsigned char*)buf, (unsigned char*)threshold, (difficulty >> 3) + 1))
            return j;
	}
    return -1;
}


