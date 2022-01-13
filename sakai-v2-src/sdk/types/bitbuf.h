#pragma once
// Default std types: std::size_t, std::uint8_t etc...
#include "../../includes.h"

class BfRead_t
{
public:
	BfRead_t() {}
	BfRead_t(const void* Data, int Bytes, int Bits = -1) { StartReading(Data, Bytes, 0, Bits); }

public:
	void	StartReading(const void* Data, int Bytes, int StartBit, int Bits);
	bool	Seek(int pos);
	void	GrabNextDword(bool OverflowImmediately = false);

public:
	const char*		m_szDebugName;
	bool			m_bOverflow;
	int				m_iDataBits;
	std::uint32_t	m_iDataBytes;
	std::uint32_t	m_iInBufWord;
	int				m_nBitsAvail;
	const std::uint32_t* m_pDataIn;
	const std::uint32_t* m_pBufferEnd;
	const std::uint32_t* m_pData;
};

class BfWrite_t
{
public:
	BfWrite_t()
	{
		m_pData = NULL;
		m_nDataBytes = 0;
		m_nDataBits = -1;
		m_iCurBit = 0;
		m_bOverflow = false;
		m_bDoAssertOnOverflow = true;
		m_szDebugName = 0;
	}

	BfWrite_t(void* Data, int Bytes, int Bits = -1)
	{
		m_bDoAssertOnOverflow = true;
		m_szDebugName = 0;

		StartWriting(Data, Bytes, 0, Bits);
	}

	BfWrite_t(const char* DebugName, void* Data, int Bytes, int Bits = -1)
	{
		m_bDoAssertOnOverflow = true;
		m_szDebugName = DebugName;

		StartWriting(Data, Bytes, 0, Bits);
	}

public:
	void StartWriting(void* Data, int Bytes, int StartBit = 0, int Bits = -1);
	void WriteUserCmd(void* Reciever, void* Sender);

	FORCEINLINE std::uint32_t GetBytesWrittenCount() const { return (m_iCurBit + 7) >> 3; }

public:
	std::uint8_t*	m_pData;
	int				m_nDataBytes;
	int				m_nDataBits;
	int				m_iCurBit;
	bool			m_bOverflow;
	bool			m_bDoAssertOnOverflow;
	const char*		m_szDebugName;
};