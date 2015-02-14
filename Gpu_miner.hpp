#pragma once

#include<vector>
#include<string>

#include "Miner.hpp"

class Gpu_miner : public Miner {
    public:
        virtual int mine(std::string& input, int offset, int difficulty);
};
