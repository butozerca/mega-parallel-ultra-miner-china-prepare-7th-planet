#pragma once

#include<vector>
#include<string>

class Miner {
    public:
        virtual int mine(std::string& input, int nonce_begin, int nonce_end, int difficulty) = 0;
};
