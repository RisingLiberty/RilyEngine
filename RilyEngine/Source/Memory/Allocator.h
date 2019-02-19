#pragma once

#if defined USE_RILY_ALLOC

#include "MemoryManager.h"
#define MEMORY_ALLIGNMENT 16

namespace Memory
{


class Allocator
{
public:

	static int Initialize();
	static void ShutDown();

	static void* Allocate(uint_t size);
	static void* AlloctateDebug(uint_t size, const char* file, const char* function, uint_t line);
	static void* ForceAllocate(uint_t size);

	static void Free(void* mem);
	static void FreeDebug(void* mem);
	static void ForceFree(void*& mem);

	static bool s_IsInitialized;
};

}
#endif