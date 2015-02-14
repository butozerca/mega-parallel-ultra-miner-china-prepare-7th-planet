#pragma once

#include<vector>
#include<string>

#include "Miner.hpp"

class Gpu_miner : public Miner {
    public:
        virtual int mine(std::string& input, int nonce_begin, int nonce_end, int difficulty);
};
