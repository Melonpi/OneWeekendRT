#ifndef OW_MISC_H
#define OW_MISC_H

#include <stdexcept>

#define OW_EXPECT(x) if(!(x)){ throw std::runtime_error("Expect failed!"); }

#endif OW_MISC_H
