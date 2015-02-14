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

bool sha256_impl(void *hash, const void *msg, size_t len)
{
	SHA256 sha;
	sha.init();
	sha.update(reinterpret_cast<const unsigned char *>(msg), len);
	sha.final(reinterpret_cast<unsigned char *>(hash));
	return true;
}

int main()
{
	blkmk_sha256_impl = sha256_impl;

#ifdef CPU
	Cpu_miner miner;
#else
	Gpu_miner miner;
#endif

	while(true)
	{
		blktemplate_t *blktemplate = blktmpl_create();
		json_t *request = blktmpl_request_jansson(blktmpl_addcaps(blktemplate), nullptr);
		json_t *response;

		//TODO send request and get response

		json_decref(request);

		blktmpl_add_jansson(blktemplate, response, time(nullptr));
		json_decref(response);

		int nonce = 0;

		while(blkmk_time_left(blktemplate, time(nullptr)) && blkmk_work_left(blktemplate))
		{
			char data[80];
			unsigned int id;
			unsigned int size = blkmk_get_data(blktemplate, data, sizeof(data), time(nullptr), nullptr, &id);

			nonce = miner.mine(data, nonce, nonce + 1000000, 2); //TODO change difficulty and adjust nonce_end
			*reinterpret_cast<int *>(data + 76) = nonce;

			json_t *request = blkmk_submit_jansson(blktemplate, reinterpret_cast<const unsigned char *>(data), id, nonce);

			//TODO send request

			json_decref(request);
		}

		blktmpl_free(blktemplate);
	}
	return 0;
}
