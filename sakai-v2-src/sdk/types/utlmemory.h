#pragma once
// Include some std stuff
#include <windows.h>
#include <cstdint>

FORCEINLINE int UtlMemory_CalcNewAllocationCount(int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem)
{
	if (nGrowSize)
		nAllocationCount = ((1 + ((nNewSize - 1) / nGrowSize)) * nGrowSize);
	else
	{
		if (!nAllocationCount)
			nAllocationCount = (31 + nBytesItem) / nBytesItem;

		while (nAllocationCount < nNewSize)
			nAllocationCount *= 2;
	}

	return nAllocationCount;
}

template <class T, class N = int>
class CUtlMemory
{
public:
	FORCEINLINE T&			operator[](N i) { return m_pMemory[i]; }
	FORCEINLINE const T&	operator[](N i) const { return m_pMemory[i]; }

	FORCEINLINE T*			Base() { return m_pMemory; }
	FORCEINLINE int			NumAllocated() const { return m_iAllocationCount; }

	FORCEINLINE void		Grow(int Num = 1)
	{
		if (IsExternallyAllocated())
			return;

		int OldAllocationCount = m_iAllocationCount;
		int AllocationRequested = m_iAllocationCount + Num;
		int NewAllocationCount = UtlMemory_CalcNewAllocationCount(m_iAllocationCount, m_iGrowSize, AllocationRequested, sizeof(T));

		if (static_cast<int>(static_cast<N>(NewAllocationCount)) < AllocationRequested)
		{
			if (static_cast<int>(static_cast<N>(NewAllocationCount)) == 0 && static_cast<int>(static_cast<N>(NewAllocationCount - 1)) >= AllocationRequested)
				--NewAllocationCount;
			else
			{
				if (static_cast<int>(static_cast<N>(AllocationRequested)) != AllocationRequested)
				{
					return;
				}

				while (static_cast<int>(static_cast<N>(NewAllocationCount)) < AllocationRequested)
					NewAllocationCount = (NewAllocationCount + AllocationRequested) / 2;
			}
		}

		m_iAllocationCount = NewAllocationCount;

		if (m_pMemory != nullptr)
		{
			std::byte* Data = new std::byte[m_iAllocationCount * sizeof(T)];
			std::memcpy(Data, m_pMemory, OldAllocationCount * sizeof(T));
			m_pMemory = reinterpret_cast<T*>(Data);
		}
		else
			m_pMemory = reinterpret_cast<T*>(new std::byte[m_iAllocationCount * sizeof(T)]);
	}

	FORCEINLINE bool		IsExternallyAllocated() const { return m_iGrowSize < 0; }

protected:
	T* m_pMemory;
	int m_iAllocationCount;
	int m_iGrowSize;
};