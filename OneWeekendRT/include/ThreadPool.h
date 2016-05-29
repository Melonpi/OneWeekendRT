#ifndef OW_THREAD_POOL_H
#define OW_THREAD_POOL_H

#include "Misc.h"
#include <thread>
#include <vector>

namespace ow
{
	class ThreadPool final : public Noncopyable
	{
	public:
		explicit ThreadPool(int threads = std::thread::hardware_concurrency() - 1)
			:threads_(threads)
		{
		}

		void join() const
		{}
	private:
		int threads_;
		std::vector<std::thread> worker_threads_;
	};
}

#endif//OW_THREAD_POOL_H