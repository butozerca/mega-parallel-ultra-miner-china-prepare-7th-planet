#include<sstream>
#include "Cpu_miner.hpp"
#include "sha256.hpp"

int Cpu_miner::mine(std::string& input, int offset, int difficulty)
{
    std::string threshold('0', difficulty - 1);
    threshold += "1";
	for (int j = offset; j < NONCE_CAP; j++) {
	   	std::ostringstream str;
	   	str << input << '<' << j;
	   	std::string result = sha256(str.str());
	   	if(result < threshold)
	   		return j;
	}
}