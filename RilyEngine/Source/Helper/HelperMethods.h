#pragma once

template<typename T>
void SafeRelease(T*& pointer)
{
	if (pointer)
		pointer->Release();

	pointer = nullptr;
}

std::string TimeAndDateToString();
std::string TimeToString();
std::string DateToString();
