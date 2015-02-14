#ifdef CPU
#include "Cpu_miner.hpp"
#else
#include "Gpu_miner.hpp"
#endif

#include "sha256.hpp"

extern "C"
{
#include <libblkmaker-0.1/blkmaker.h>
#include <libblkmaker-0.1/blkmaker_jansson.h>
}

int main()
{
	blktemplate_t *blktemplate = blktmpl_create();
	json_t *request = blktmpl_request_jansson(blktmpl_addcaps(blktemplate), nullptr);

	json_decref(request);
	blktmpl_free(blktemplate);
	return 0;
}
