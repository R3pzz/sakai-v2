#pragma once
// Include CUtlMemory<>
#include "utlmemory.h"

template <class T>
FORCEINLINE void Destruct(T* pMemory)
{
	pMemory->~T();
}

template <class T>
FORCEINLINE T* Construct(T* pMemory)
{
	return new(pMemory) T;
}

template< class T >
FORCEINLINE T* Copy(T* pMemory, T const& src)
{
	return new(pMemory) T(src);
}

template <class T, class A = CUtlMemory<T>>
class CUtlVector
{
	using CAllocator = A;
public:
	FORCEINLINE auto		Begin() noexcept { return m_pMemory.Base(); }
	FORCEINLINE auto		End() noexcept { return m_pMemory.Base() + m_iSize; }

	FORCEINLINE T&			operator[](std::size_t Size) { return m_pMemory[Size]; }
	FORCEINLINE	const T&	operator[](std::size_t Size) const { return m_pMemory[Size]; }

	FORCEINLINE T&			Element(std::size_t Size) { return m_pMemory[Size]; }
	FORCEINLINE const T&	Element(std::size_t Size) const { return m_pMemory[Size]; }

	FORCEINLINE T*			Base() { return m_pMemory.Base(); }

	FORCEINLINE int			Count() const { return m_iSize; }
	FORCEINLINE int&		Size() { return m_iSize; }

	FORCEINLINE void		GrowVector(int Count = 1)
	{
		if (m_iSize + Count > m_pMemory.NumAllocated())
			m_pMemory.Grow(m_iSize + Count - m_pMemory.NumAllocated());

		m_iSize += Count;
	}

	FORCEINLINE void		ShiftElementsRight(const int nElement, const int Shift = 1)
	{
		const int ToMove = m_iSize - nElement - Shift;

		if (ToMove > 0 && Shift > 0)
			std::memmove(&Element(nElement + Shift), &Element(nElement), ToMove * sizeof(T));
	}

	FORCEINLINE void		ShiftElementsLeft(const int nElement, const int Shift = 1)
	{
		const int ToMove = m_iSize - nElement - Shift;

		if (ToMove > 0 && Shift > 0)
			std::memmove(&Element(nElement), &Element(nElement + Shift), ToMove * sizeof(T));
	}

	FORCEINLINE int			InsertBefore(const int nElement)
	{
		GrowVector();
		ShiftElementsRight(nElement);
		Construct(&Element(nElement));
		return nElement;
	}

	FORCEINLINE int			InsertBefore(int nElement, const T& Src)
	{
		GrowVector();
		ShiftElementsRight(nElement);
		Copy(&Element(nElement), Src);
		return nElement;
	}

	FORCEINLINE int			AddToTail() { return InsertBefore(m_iSize); }
	FORCEINLINE int			AddToTail(const T& Src) { return InsertBefore(m_iSize, Src); }

	FORCEINLINE int			Find(const T& Src) const
	{
		for (int i = 0; i < Count(); ++i)
		{
			if (Element(i) == Src)
				return i;
		}

		return -1;
	}

	FORCEINLINE void		Remove(const int nElement)
	{
		Destruct(&Element(nElement));
		ShiftElementsLeft(nElement);
		--m_iSize;
	}

	FORCEINLINE void		Clear()
	{
		for (int i = m_iSize; --i >= 0;)
			Destruct(&Element(i));

		m_iSize = 0;
	}

	FORCEINLINE bool		FindAndRemove(const T& Src)
	{
		if (int Elem = Find(Src); Elem != -1)
		{
			Remove(Elem);
			return true;
		}

		return false;
	}

protected:
	CAllocator m_pMemory;
	int m_iSize;
	T* m_pElements;
};