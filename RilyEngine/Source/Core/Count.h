#pragma once

#include "../Memory/Allocator.h"
#include "../Defines/TypeDefines.h"

template <typename T>
class Count
{
public:
	Count(uint_t limit = INT_T_MAX)
	{
		if (m_Limit == INT_T_MAX)
			m_Limit = limit;
		else if (limit != INT_T_MAX)
			Debug::Log(Debug::LogType::WARNING, "try to rewrite Count, this is const once it's been set");

		++m_Count;
	}

	~Count()
	{
		--m_Count;
	}

	uint_t static GetCount() { return m_Count; }
	uint_t static GetLimit() { return m_Limit; }

	void* operator new(uint_t size)
	{
		if (m_Count == m_Limit)
		{
			Debug::Log(Debug::LogType::WARNING, "Failed to create new instance of", typeid(T).name());
			return nullptr;
		}
		return Memory::Allocator::Allocate(size);
	}

	void* operator new(uint_t size, const char* file, const char* function, const uint_t line)
	{
		if (m_Count == m_Limit)
		{
			Debug::Log(Debug::LogType::WARNING, "Failed to create new instance of ", typeid(T).name());
			return nullptr;
		}
		
#if defined (DEBUG) || defined (_DEBUG)
		return Memory::Allocator::AlloctateDebug(size, file, function, line);
#else
		return Memory::Allocator::Allocate(size);
#endif
	}

	void operator delete (void* mem, const char* file, const char* function, const uint_t line)
	{
		delete(mem);
	}

	void operator delete(void* mem)
	{
#if defined (DEBUG) || defined (_DEBUG)
		Memory::Allocator::FreeDebug(mem);
#else
		Memory::Allocator::Free(mem);
#endif
	}

private:
	static uint_t m_Count;
	static uint_t m_Limit;
};

template <typename T>
uint_t Count<T>::m_Count = 0;
template <typename T>
uint_t Count<T>::m_Limit = INT_T_MAX;

