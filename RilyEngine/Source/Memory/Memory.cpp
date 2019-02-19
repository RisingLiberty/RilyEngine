#include "stdafx.h"

#include "Memory.h"

#include "../Defines/NoMemoryDefines.h"

void* operator new(uint_t size)
{
	return Memory::Allocator::Allocate(size);
}
void* operator new(uint_t size, const char* file, const char* function, const uint_t line)
{
#if defined (DEBUG) || defined (_DEBUG)
	return Memory::Allocator::AlloctateDebug(size, file, function, line);
#else
	return Allocator::Allocate(size);
#endif
}

void operator delete(void* mem)
{
#if defined (DEBUG) || defined (_DEBUG)
	return Memory::Allocator::FreeDebug(mem);
#else
	return Allocator::Free(mem);
#endif
}

void operator delete(void* mem, const char* file, const char* function, const uint_t line)
{
#if defined (DEBUG) || defined (_DEBUG)
	return Memory::Allocator::FreeDebug(mem);
#else
	return Allocator::Free(mem);
#endif
}
