#include<chrono>
#include<climits>
#include<cstdio>
#include<cstring>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>

#include "Cpu_miner.hpp"
#include "Gpu_miner.hpp"
#include "sha256.hpp"

const std::string file_in = "input.txt";


void confirm_nonce(const char *data, int nonce, int difficulty)
{
	unsigned char data2[80], hash[32], hash2[32];

	memcpy(data2, data, 76);
	*reinterpret_cast<int *>(data2 + 76) = nonce;

	SHA256 sha;
	sha.init();
	sha.update(data2, 80);
	sha.final(hash);

	sha.init();
	sha.update(hash, 32);
	sha.final(hash2);

	char hash_str[65];
	for(int i = 0; i < 32; ++i)
		sprintf(hash_str + 2 * i, "%02x", hash2[i]);
	hash_str[64] = 0;

	std::cout << "Policzony hash " << hash_str << std::endl;

	--difficulty;
	char cmp_str[65];

	for(int i = 0; i < difficulty / 4; ++i)
		cmp_str[i] = '0';

	cmp_str[difficulty / 4] = '0' + (8 >> (difficulty % 4));
	cmp_str[difficulty / 4 + 1] = 0;

	if(strcmp(hash_str, cmp_str) < 0)
		std::cout << "Dobry hash" << std::endl;
	else
		std::cout << "Zły hash" << std::endl;
}

int main()
{

    std::ifstream input(file_in);
    
    std::vector<std::string> in;

    while(input.good())
    {
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

    int difficulty = 25;
    int max_nonce = 10000000;


    for (auto &s: in) {
        std::cout << "hashing: " << s << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        int res = cpu_miner.mine(s.c_str(), 0, max_nonce, difficulty);
        auto finish = std::chrono::high_resolution_clock::now();
        printf("cpu nonce=%d\n", res);
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
        std::cout << "cpu mining took " << microseconds.count() << "µs\n";
        confirm_nonce(s.c_str(), res, difficulty);
    
        start = std::chrono::high_resolution_clock::now();
        res = gpu_miner.mine(s.c_str(), 0, max_nonce, difficulty);
        finish = std::chrono::high_resolution_clock::now();
        printf("gpu nonce=%d\n", res);
        microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
        std::cout << "GPU mining took " << microseconds.count() << "µs\n";
        confirm_nonce(s.c_str(), res, difficulty);
    }

    return 0;
}
