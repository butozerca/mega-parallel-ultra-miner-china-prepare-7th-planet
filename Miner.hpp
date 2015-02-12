#pragma once

#include<vector>
#include<string>

#define NONCE_CAP 100000

class Miner {
    public:
        virtual void mine(std::vector<std::string>& input) = 0;
};