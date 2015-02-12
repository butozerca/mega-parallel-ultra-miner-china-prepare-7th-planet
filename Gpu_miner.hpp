#pragma once

#include<vector>
#include<string>

#include "Miner.hpp"

class Gpu_miner : public Miner {
    public:
        virtual void mine(std::vector<std::string>& input);
};