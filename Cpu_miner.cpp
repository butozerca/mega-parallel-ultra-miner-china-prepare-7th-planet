#include<sstream>
#include "Cpu_miner.hpp"
#include "sha256.hpp"

//TODO handle difficulty and input not being a regular string
int Cpu_miner::mine(const char *input, int nonce_begin, int nonce_end, int difficulty)
{
	std::string threshold('0', difficulty / 8);
	threshold += (char)(255 >> (difficulty % 8));
	for (int j = nonce_begin; j < nonce_end; j++) {
	   	std::ostringstream str;
        int nonce = j;

        char nonc[4];
        for (int i = 3; i >= 0; i--) {
            nonc[i] = nonce & 255;
            nonce >>= 8;
        }
        
	   	str << input << '<' << j;
	   	std::string result = sha256(sha256(str.str()));
	   	if(result < threshold)
	   		return j;
	}
}
