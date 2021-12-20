#pragma once
// Include std::uint32_t, FORCEINLINE macro
#include "../platform.h"

class CBaseHandle;
class IClientEntity;

class IHandleEntity {
public:
	virtual ~IHandleEntity() {}

	virtual void		SetRefEHandle(const CBaseHandle& handle) = 0;
	virtual const		CBaseHandle& GetRefEHandle() const = 0;
};

class CBaseHandle {
public:
	CBaseHandle() {}
	CBaseHandle(const CBaseHandle& other) : m_Idx(other.m_Idx) {}

public:
	FORCEINLINE void Init(int Entry, int Serial) {
		assert(Entry >= 0 && (Entry & ((1 << 16) - 1)) == Entry);
		assert(Serial >= 0 && Serial < (1 << 16));

		m_Idx = Entry | (Serial << 16);
	}

	FORCEINLINE void Invalidate() { m_Idx = 0xFFFFFFFF; }

	FORCEINLINE bool IsValid() const { return m_Idx != 0xFFFFFFFF; }

	FORCEINLINE int GetEntryIndex() const { return IsValid() ? m_Idx & ((1 << 16) - 1) : (1 << 13) - 1; }

	FORCEINLINE int GetSerial() const { return m_Idx >> 16; }

	IClientEntity* Get() const;

public:
	std::uint32_t m_Idx;
};