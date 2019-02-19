#include "stdafx.h"

#include <ctime>
#include <chrono>

#include "MemoryManager.h"

#include "Allocator.h"

#include "../Resources/Files/TextFile.h"
#include "../Resources/Files/File.h"

namespace Memory
{


SystemMemoryInfo::SystemMemoryInfo(const MEMORYSTATUSEX& status):
	AvailablePhysicalMemory((uint_t)status.ullAvailPhys),
	TotalPhysicalMemory((uint_t)status.ullTotalPhys),
	AvailableVirtualMemory((uint_t)status.ullAvailVirtual),
	TotalVirtualMemory((uint_t)status.ullTotalVirtual)
{}

void SystemMemoryInfo::Log()
{
	Debug::Log(Debug::LogType::INFO, this);
}

std::ostream& operator<<(std::ostream& os, const SystemMemoryInfo& info)
{
	os << "Available physical memory: " << MemoryManager::BytesToString(info.AvailablePhysicalMemory);
	os << "\nTotal physical memory: " << MemoryManager::BytesToString(info.TotalPhysicalMemory);
	os << "\nAvailable virtual memory: " << MemoryManager::BytesToString(info.AvailableVirtualMemory);
	os << "\nTotal virtual memory: " << MemoryManager::BytesToString(info.TotalVirtualMemory);
	return os;
}

SystemMemoryInfo MemoryManager::s_SystemMemInfo = SystemMemoryInfo();
std::unordered_map<void*, PointerMetaData> MemoryManager::s_Pointers = {};
//byte MemoryManager::s_Memory[MB] = {};
//uint_t MemoryManager::s_Current = 0;
bool MemoryManager::s_IsInitialized = false;
const std::string MemoryManager::MEMLEAK_FILE_PATH = LOG_PATH + "Memoryleaks.log";

int MemoryManager::Initialize(uint_t maxMemory)
{
	//Windows only!
	BOOL result = HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(12968);

	if (result != FALSE)
		Debug::Log(Debug::LogType::INFO, "Heap terminate on corruption has been enabled");
	else
		Debug::Log(Debug::LogType::INFO, "Failed to enable heap terminate on corruption");

	MEMORYSTATUSEX status;
	status.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&status);
	s_SystemMemInfo = SystemMemoryInfo(status);
	s_IsInitialized = true;
	Allocator::Initialize();


	return OK;
}

void MemoryManager::Shutdown()
{
	Container::Vector<PointerMetaData> pointers;

	std::for_each(s_Pointers.begin(), s_Pointers.end(),
		[&](auto& pair)
		{
			pointers.AddC(pair.second);
		});

	Resources::TextFile outputFile = Resources::TextFile(MEMLEAK_FILE_PATH);
	outputFile.Open(std::ios::out);

	//std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	//char buff[30];
	//ctime_s(buff, sizeof buff, &time);

	std::string time = TimeAndDateToString();

	if (!outputFile.IsOpen())
		PUSH_WARNING("Failed to open memory leak file");

	outputFile << time << "\n\n";

	if (!pointers.IsEmpty())
	{
		outputFile.Write("<<< Memory leaks detected! >>>\n");
		Debug::Log(Debug::LogType::WARNING, "<<< Memory leaks detected! >>>");

		for (PointerMetaData& ptr : pointers)
		{
			LogLeak(ptr, &outputFile);
			Allocator::ForceFree(ptr.Pointer);
		}
		BreakHere;
	}

	else
		outputFile.Write("<<< No memories detected! >>>");


	outputFile.Close();

	s_IsInitialized = false;
	Allocator::ShutDown();
}

//void* MemoryManager::Alloc(uint_t Count)
//{
//	if (!s_IsInitialized)
//		return malloc(Count);
//
//	GetMemoryBlock(Count);
//
//	s_Memory[s_Current] = 1;
//	s_Current += sizeof(byte);
//
//	s_Memory[s_Current] = Count;
//	s_Current += sizeof(uint_t);
//
//	void* mem = &s_Memory[s_Current];
//	//s_Current += Count;
//
//	return mem;
//}
//
//void MemoryManager::Dealloc(void* mem)
//{
//	if (!s_IsInitialized)
//		return free(mem);
//
//	//set bool to false --> can be overwriten
//	uint_t current = (int)mem - (int)s_Memory;
//	s_Memory[current - sizeof(uint_t) - sizeof(byte)] = 0;
//}

std::string MemoryManager::BytesToString(uint_t bytes)
{
	std::string result;
	if (bytes > GB)
		result = std::to_string(bytes / GB) + " Gigabyte";
	else if (bytes > MB)
		result = std::to_string(bytes / MB) + " Megabyte";
	else if (bytes > KB)
		result = std::to_string(bytes / KB) + " Kilobyte";
	else
		result = std::to_string(bytes) + " Bytes";

	return result;
}

void MemoryManager::LogLeak(const PointerMetaData& leak, Resources::TextFile* pFile)
{
	if (pFile == nullptr)
	{
		Debug::Log(Debug::LogType::WARNING, 
		"------------------------------\n",
		"Memory leak detected at: ", (uint_t)leak.Pointer, "with Count of ", sizeof(leak.Pointer), " bytes \n"
		"Created at: ", leak.File, "\n"
		"In function: ", leak.Function, "\n"
		"On line: ", leak.Line,"\n"
		"------------------------------\n\n");
	}
	else
	{
		pFile->Write("------------------------------\n");
		pFile->Write("Memory leak detected at: ");
		pFile->Write((uint_t)leak.Pointer);
		pFile->Write("\nWith Count of ");
		pFile->Write(leak.Size);
		pFile->Write(" bytes\nCreated at: ");
		pFile->Write(leak.File);
		pFile->Write("\nIn function: ");
		pFile->Write(leak.Function);
		pFile->Write("\nOn line: ");
		pFile->Write(leak.Line);
		pFile->Write("\n------------------------------\n\n");
	}
}

void MemoryManager::AddDebugMem(void* mem, uint_t size, const char* file, const char* function, const uint_t line)
{
	if (!s_IsInitialized)
		return;

	auto it = s_Pointers.find(mem);

	if (it != s_Pointers.end())
		Debug::Log(Debug::LogType::WARNING, "Memory already in use!");

	else
		s_Pointers[mem] = PointerMetaData(mem, size, file, function, line);
}

void MemoryManager::FreeDebugMem(void* mem)
{
	if (!s_IsInitialized)
		return;

	auto it = s_Pointers.find(mem);

	if (it != s_Pointers.end())
		s_Pointers.erase(mem);
}

//void MemoryManager::ForceFree(void* mem)
//{
//	s_Pointers.erase(mem);
//}
//
//void MemoryManager::GetMemoryBlock(const uint_t Count)
//{
//	byte* ptr = s_Memory;
//	int current = 0;
//	
//	//get bool
//	bool skip = ptr[current];
//	uint_t newSize = 0;
//	if (!skip)
//	{
//		newSize = ptr[current + 1];
//		skip = (newSize < Count) && (newSize != 0);
//	}
//
//	while (skip)
//	{
//		//get Count
//		++current;
//		newSize = ptr[current];
//
//		//increase with Count
//		current += sizeof(uint_t) + newSize;
//
//		//get new bool
//		skip = ptr[current];
//
//		//check if we can store our data here
//		if (!skip)
//		{
//			newSize = ptr[current + 1];
//			skip = (newSize < Count) && (newSize != 0);
//		}
//	}
//
//	s_Current = current;
//}
}