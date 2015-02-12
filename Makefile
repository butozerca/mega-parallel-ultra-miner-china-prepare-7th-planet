-include *.d

%.d:;

%.o: %.cpp
	g++ -c -O2 -g -std=c++11 -MMD -MP $^ -o $@

main: main.o Cpu_miner.o Gpu_miner.o sha256.o
	g++ -O2 -g -std=c++11 $^ -o $@ -lcuda

clean:
	rm -rf main *.o *.d

.PHONY: clean 