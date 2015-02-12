#include<cstdio>
#include<chrono>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>

#include "Cpu_miner.hpp"
#include "Gpu_miner.hpp"

const std::string file_in = "chuj.txt";


int main () {

    std::ifstream input(file_in);
    
    std::vector<std::string> in;

    while (input.good()) {
        std::string s;
        input >> s;
        in.push_back(s);
    }

    if(in.empty())
    {
        std::cout << "Ej no ale serio naprawde\n";
        return 1;
    }

    Cpu_miner cpu_miner;
    Gpu_miner gpu_miner;

    auto start = std::chrono::high_resolution_clock::now();
    cpu_miner.mine(in);
    auto finish = std::chrono::high_resolution_clock::now();

    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
    std::cout << "cpu mining took " << microseconds.count() << "µs\n";

    start = std::chrono::high_resolution_clock::now();
    gpu_miner.mine(in);
    finish = std::chrono::high_resolution_clock::now();

    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
    std::cout << "OUR GLORIOUS GPU mining took " << microseconds.count() << "µs\n";

    return 0;
}
