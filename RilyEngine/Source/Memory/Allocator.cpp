#include "stdafx.h"

#include <assert.h>

#include "Allocator.h"


#if defined USE_RILY_ALLOC
namespace Memory
{

bool Allocator::s_IsInitialized = false;

int Allocator::Initialize()
{
	s_IsInitialized = true;
	return OK;
}

void Allocator::ShutDown()
{
	s_IsInitialized = false;
}

void* Allocator::Allocate(uint_t size)
{
	return malloc(size);
}
void* Allocator::AlloctateDebug(uint_t size, const char* file, const char* function, uint_t line)
{
	void* mem = Allocate(size);
	MemoryManager::AddDebugMem(mem, size, file, function, line);
	return mem;
}

void* Allocator::ForceAllocate(uint_t size)
{
	return Allocate(size);
}

void Allocator::Free(void* mem)
{
	ForceFree(mem);
}

void Allocator::FreeDebug(void* mem)
{
	MemoryManager::FreeDebugMem(mem);
	Free(mem);
}

void Allocator::ForceFree(void*& mem)
{
	free(mem);
	mem = nullptr;
}

}
#endif