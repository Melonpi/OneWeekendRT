#ifndef OW_MISC_H
#define OW_MISC_H

#include <stdexcept>

#define OW_EXPECT(x) if(!(x)){ throw std::runtime_error("Expect failed!"); }

namespace ow
{
	class Noncopyable
	{
	public:
		Noncopyable() {}
	private:
		Noncopyable(const Noncopyable&) = delete;
		Noncopyable& operator=(const Noncopyable&) = delete;
	};
}

#endif OW_MISC_H
