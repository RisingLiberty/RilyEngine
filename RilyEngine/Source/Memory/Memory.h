#pragma once


#include "Allocator.h"

void* operator new(uint_t Count);
void* operator new(uint_t Count, const char* file, const char* function, const uint_t line);

void operator delete(void* mem);
void operator delete(void* mem, const char* file, const char* function, const uint_t line);

void operator delete[](void* mem);

#define SAFE_DELETE(x) if (x) {delete x;} x = nullptr;

#include "../Defines/MemoryDefines.h"
