#pragma once
#if defined WINDOWS_PLATFORM

namespace Settings
{

struct DirectXSettings
{
public:
	DirectXSettings() = default;
	~DirectXSettings() = default;

	IDXGIAdapter* pAdapter = nullptr;
	IDXGIOutput* pOutput = nullptr;
};


}

#endif