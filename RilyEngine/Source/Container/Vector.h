#pragma once

#include <vector>

namespace Container
{
	template <typename T>
	class Vector
	{
	public:
		Vector() = default;
		Vector(std::initializer_list<T> list)
		{
			for (const T e : list)
				AddC(e);
		}

		T operator[](uint_t idx) const
		{
			return m_Elements[idx];
		}

		//Add copy
		void AddC(const T& element)
		{
			m_Elements.push_back(element);
		}

		//Add with move operator
		void AddM(const T&& element)
		{
			m_Elements.emplace_back(element);
		}

		//remove from element
		void Remove(T element)
		{
			m_Elements.erase(Find(element));
		}

		//remove at index
		void RemoveAtIndex(uint_t i)
		{
			m_Elements.erase(m_Elements.Begin() + i);
		}

		//remove last item
		void RemoveLast()
		{
			m_Elements.pop_back();
		}

		//clears vector and sets count to 0
		void Clear()
		{
			m_Elements.clear();
		}

		//deletes all pointers in vector
		void DeleteAllPointers()
		{
			for (T ptr : m_Elements)
				delete ptr;
		}

		//resizes vector to certain Count
		void Resize(uint_t Count)
		{
			m_Elements.resize(Count);
		}

		//allocates memory but doesn't change vector's Count
		void Reserve(uint_t Count)
		{
			m_Elements.reserve(Count);
		}

		//returns nr of elements in vector
		uint_t Count() const
		{
			return m_Elements.size();
		}

		//returns total amount of memory used by vector
		uint_t Size() const
		{
			return Count * sizeof(First());
		}

		//returns the first element
		const T& First() const
		{
			return m_Elements.front();
		}

		//returns the last element
		const T& Last() const
		{
			return m_Elements.back();
		}

		//returns a pointer to the first element
		const T* RawData() const
		{
			return m_Elements.data();
		}

		//check if a certain element is in the vector
		bool Exists(T element) const
		{
			return Find(element) != this->End();
		}

		//check if vector is empty
		bool IsEmpty() const
		{
			return m_Elements.empty();
		}

		//returns iterator to element in vector
		auto Find(T element) const
		{
			 auto it = std::find_if(m_Elements.begin(), m_Elements.end(),[&](T listElement)
			 {
				 return element == listElement;
			 });

			 return it;
		}

		//insert value before index in vector
		void Insert(uint_t idx, T value)
		{
			m_Elements(m_Elements.begin() + idx, value);
		}

		//range based for loop needs a begin method
		auto begin()
		{
			return Begin();
		}

		//range based for loop needs an end method
		auto end()
		{
			return End();
		}
		
		//for range based for loop with const begin
		auto begin() const
		{
			return CBegin();
		}

		//for range based for loop with const end
		auto end() const
		{
			return CEnd();
		}

		//returns iterator to first element
		auto Begin()
		{
			return m_Elements.begin();
		}

		//returns const iterator to first element
		auto CBegin() const
		{
			return m_Elements.cbegin();
		}

		//returns iterator to last element
		auto End()
		{
			return m_Elements.end();
		}

		//returns const iterator to last element
		auto CEnd() const
		{
			return m_Elements.cend();
		}

		//output all elements to output window
		void ShowAll() const
		{
			for (T e : m_Elements)
				Debug::Log(Debug::LogType::FORCE, e);
		}

	private:
		std::vector<T> m_Elements;
	};
}