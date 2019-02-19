#pragma once

namespace Resources
{
	class TextFile;
}

namespace Memory
{


static const uint_t KILOBYTE = 1000;
static const uint_t MEGABYTE = KILOBYTE * 1000;
static const uint_t GIGABYTE = MEGABYTE * 1000;

#define KB KILOBYTE
#define MB MEGABYTE
#define GB GIGABYTE

struct SystemMemoryInfo
{
	SystemMemoryInfo() = default;
	SystemMemoryInfo(const MEMORYSTATUSEX& status);

	uint_t AvailablePhysicalMemory = 0;
	uint_t TotalPhysicalMemory = 0;

	uint_t AvailableVirtualMemory = 0;
	uint_t TotalVirtualMemory = 0;

	void Log();
};

std::ostream& operator<<(std::ostream& os, const SystemMemoryInfo& info);

struct MemoryStats
{
	uint_t AllocatedBytes = 0;
	uint_t FreedBytes = 0;
	uint_t CurrentlyUsedBytes = 0;
	uint_t TotalAllocations = 0;
	uint_t MaxMemory = UINT_T_MAX;
};

struct PointerMetaData
{
	PointerMetaData() = default;
	PointerMetaData(void* pointer,uint_t Count, const char* file, const char* function, const uint_t line) :
		Pointer(pointer),
		Size(Count),
		File(file),
		Function(function),
		Line(line),
		Exists(true)
	{}

	void* Pointer;
	uint_t Size;
	const char* File;
	const char* Function;
	uint_t Line;
	bool Exists = false;
};



class MemoryManager
{
public:
	MemoryManager() = delete;
	~MemoryManager() = delete;

	static std::string BytesToString(uint_t bytes);
	static void LogLeak(const PointerMetaData& leak, Resources::TextFile* pFile = nullptr);
	
	static int Initialize(uint_t maxMemory = MB);
	static void Shutdown();

	static void AddDebugMem(void* mem,uint_t Count, const char* file, const char* function, const uint_t line);
	static void FreeDebugMem(void *mem);
	
	//static void* Alloc(uint_t Count);
	//static void Dealloc(void* mem);
	//static void ForceFree(void* mem);

private:
	//static void GetMemoryBlock(const uint_t Count);

private:
	static SystemMemoryInfo s_SystemMemInfo;
	static std::unordered_map<void*, PointerMetaData> s_Pointers;
	static bool s_IsInitialized;

	static const std::string MEMLEAK_FILE_PATH;
};

}
