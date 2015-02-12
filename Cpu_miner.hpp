#pragma once

#include<vector>
#include<string>

#include "Miner.hpp"

class Cpu_miner : public Miner {
    public:
        virtual void mine(std::vector<std::string>& input);
};