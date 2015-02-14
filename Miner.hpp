#pragma once

#include<vector>
#include<string>

#define NONCE_CAP 100000

class Miner {
    public:
        virtual int mine(std::string& input, int offset, int difficulty) = 0;
};