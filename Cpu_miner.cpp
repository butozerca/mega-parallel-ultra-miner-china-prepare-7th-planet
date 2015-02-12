#include "Cpu_miner.hpp"
#include "sha256.hpp"

void Cpu_miner::mine(std::vector<std::string>& input)
{
	for(auto &i : input) {
	    for (int j = 0; j < NONCE_CAP; j++) {
	    	std::istringstream str;
	    	str << i << '<' << j;
	    	std::string result = sha256(str.str());
	    	if(result < "0001")
	    		return;
	    }
	}
}