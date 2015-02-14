#pragma once

#include<vector>
#include<string>

class Miner {
    public:
        virtual int mine(std::string& input, int offset, int max_nonce, int difficulty) = 0;
};
