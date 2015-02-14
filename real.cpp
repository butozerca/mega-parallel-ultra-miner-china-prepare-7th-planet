#ifdef CPU
#include "Cpu_miner.hpp"
#else
#include "Gpu_miner.hpp"
#endif

#include "sha256.hpp"

extern "C"
{
#include <libblkmaker-0.1/blkmaker.h>
}

int main()
{
	blktemplate_t *blktemplate;

	blktemplate = blktmpl_create();

	blktmpl_free(blktemplate);
	return 0;
}
