#pragma once

#include "../Defines/Errors.h"

struct ErrorValue
{
public:
	ErrorValue(int value) :
		m_Value(value)
	{
	}

public:
	int m_Value;
};

template <typename T>
class OptionalReturnWrapper
{
public:
	OptionalReturnWrapper(const T& returnValue) :
		m_ReturnValue(returnValue),
		m_ErrorCode(OK)
	{
	}

	OptionalReturnWrapper(int errorValue):
		m_ErrorCode(errorValue)
	{}

	//Enable conversion for macro
	OptionalReturnWrapper(OptionalReturnWrapper<ErrorValue>& error):
		m_ErrorCode(error.m_ErrorCode)
	{
	}

	operator T() const
	{
		return m_ReturnValue;
	}

	operator OptionalReturnWrapper<ErrorValue>() const
	{
		return OptionalReturnWrapper(ErrorValue);
	}

	bool IsOk() const { return m_ErrorCode == OK; }

	T GetValue() const { return m_ReturnValue; }
	int GetErrorCode() const { return m_ErrorCode; }
private:
	T m_ReturnValue = {};
	int m_ErrorCode = OK;

};

template<>
class OptionalReturnWrapper<int>
{
public:
	OptionalReturnWrapper(int returnValue, int errorValue) :
		m_ReturnValue(returnValue),
		m_ErrorCode(errorValue)
	{
	}

	bool IsOk() const { return m_ErrorCode == OK; }

	int GetValue() const { return m_ReturnValue; }
	int GetErrorCode() const { return m_ErrorCode; }

private:
	int m_ReturnValue;
	int m_ErrorCode = OK;

};
