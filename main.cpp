#include<cstdio>
#include<chrono>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>

#include "Cpu_miner.hpp"
#include "Gpu_miner.hpp"

const std::string file_in = "input.txt";


int main () {

    std::ifstream input(file_in);
    
    std::vector<std::string> in;

    while (input.good()) {
        std::string s;
        input >> s;
        if (s.size() != 76) break;
        in.push_back(s);
    }

    if(in.empty())
    {
        std::cout << "Ej no ale serio naprawde\n";
        return 1;
    }

    Cpu_miner cpu_miner;
    Gpu_miner gpu_miner;

    int difficulty = 4;
    int max_nonce = 1;


    for (auto &s: in) {
        std::cout << "hashing: " << s << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        int res = cpu_miner.mine(s.c_str(), 0, max_nonce, difficulty);
        auto finish = std::chrono::high_resolution_clock::now();
        printf("cpu res=%d\n", res);
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
        std::cout << "cpu mining took " << microseconds.count() << "µs\n";
    
        start = std::chrono::high_resolution_clock::now();
        res = gpu_miner.mine(s.c_str(), 0, max_nonce, difficulty);
        finish = std::chrono::high_resolution_clock::now();
        printf("gpu res=%d\n", res);
        microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
        std::cout << "GPU mining took " << microseconds.count() << "µs\n";
    }

    return 0;
}
