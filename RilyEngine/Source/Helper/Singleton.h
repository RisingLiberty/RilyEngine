#pragma once

template <typename T>
class Singleton : public Count<T>
{
public:
	Singleton():Count<T>(1) {};
	~Singleton() = default;

	static void CreateInstance() { s_Instance = new T(); };
	static T* GetInstance() { return s_Instance; };
	static void DestroyInstance() { delete s_Instance; s_Instance = nullptr; };

protected:
	static T* s_Instance;
};

template <typename T>
T* Singleton<T>::s_Instance = nullptr;