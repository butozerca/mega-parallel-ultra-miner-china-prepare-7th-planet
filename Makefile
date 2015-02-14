all: main real-cpu real-gpu

-include *.d

%.d:;

%.o: %.cpp
	g++ -c -O2 -g -std=c++11 -MMD -MP $< -o $@ -I/usr/local/cuda/include/

real-cpu.o: real.cpp
	g++ -c -O2 -g -std=c++11 -MMD -MP $< -o $@ -I/usr/include/libblkmaker-0.1/ -DCPU

real-gpu.o: real.cpp
	g++ -c -O2 -g -std=c++11 -MMD -MP $< -o $@ -I/usr/include/libblkmaker-0.1/ -DGPU

main: main.o Cpu_miner.o Gpu_miner.o sha256.o
	g++ -O2 -g -std=c++11 $^ -o $@ -lcuda

real-cpu: real-cpu.o Cpu_miner.o sha256.o
	g++ -O2 -g -std=c++11 $^ -o $@ -lblkmaker-0.1

real-gpu: real-gpu.o Gpu_miner.o sha256.o
	g++ -O2 -g -std=c++11 $^ -o $@ -lblkmaker-0.1 -lcuda

clean:
	rm -rf main real-cpu real-gpu *.o *.d

.PHONY: all clean
