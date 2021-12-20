#include "bitbuf.h"
// SIG()
#include "../platform.h"

/*
* BfRead_t functions.
*/
void BfRead_t::StartReading(const void* Data, int Bytes, int StartBit, int Bits) {
	m_pData = reinterpret_cast<const std::uint32_t*>(Data);
	m_pDataIn = m_pData;
	m_iDataBytes = Bytes;

	m_iDataBits = Bits == -1 ? Bytes << 3 : Bits;

	m_bOverflow = false;
	m_pBufferEnd = reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const std::uint8_t*>(m_pData) + Bytes);

	if (m_pData)
		Seek(StartBit);
}

bool BfRead_t::Seek(int Pos) {
	bool Success = true;

	if (Pos < 0 || Pos > m_iDataBits) {
		m_bOverflow = true;
		Success = false;
		Pos = m_iDataBits;
	}

	const std::uint32_t Head = m_iDataBytes & 3;
	const std::uint32_t Offset = Pos / 8;

	if (m_iDataBytes < 4
		|| Head && Offset < Head) {
		auto Partial = reinterpret_cast<const std::uint8_t*>(m_pData);

		if (m_pData) {
			m_iInBufWord = *(Partial++);

			if (Head > 1)
				m_iInBufWord |= (*Partial++) << 8;

			if (Head > 2)
				m_iInBufWord |= (*Partial++) << 16;
		}

		m_pDataIn = reinterpret_cast<const std::uint32_t*>(Partial);
		m_iInBufWord >>= (Pos & 31);
		m_nBitsAvail = (Head << 3) - (Pos & 31);
	}
	else {
		const auto AdjustPos = Pos - (Head << 3);

		m_pDataIn = reinterpret_cast<const std::uint32_t*>(reinterpret_cast<const std::uint8_t*>(m_pData) + ((AdjustPos / 32) << 2) + Head);

		if (m_pData) {
			m_nBitsAvail = 32;

			GrabNextDword();
		}
		else {
			m_iInBufWord = 0;
			m_nBitsAvail = 1;
		}

		m_iInBufWord >>= (AdjustPos & 31);
		m_nBitsAvail = std::min<int>(m_nBitsAvail, 32 - (AdjustPos & 31));
	}

	return Success;
}

void BfRead_t::GrabNextDword(bool OverflowImmediately) {
	if (m_pDataIn == m_pBufferEnd) {
		m_nBitsAvail = 1;
		m_iInBufWord = 0;
		m_pDataIn++;

		if (OverflowImmediately)
			m_bOverflow = true;
	}
	else if (m_pDataIn > m_pBufferEnd) {
		m_bOverflow = true;
		m_iInBufWord = 0;
	}
	else {
		m_iInBufWord = *(m_pDataIn++);
	}
}

/*
* BfWrite_t functions.
*/
void BfWrite_t::StartWriting(void* Data, int Bytes, int StartBit, int Bits) {
	Bytes &= ~3;

	m_pData = reinterpret_cast<std::uint8_t*>(Data);
	m_nDataBytes = Bytes;
	m_nDataBits = Bits == -1 ? Bytes << 3 : Bits;

	m_iCurBit = StartBit;
	m_bOverflow = false;
}

void BfWrite_t::WriteUserCmd(void* Reciever, void* Sender) {
	static const std::uint8_t* WriteUserCmdFn = SIG("client.dll", "55 8B EC 83 E4 F8 51 53 56 8B D9 8B 0D").m_Ptr;

	__asm {
		mov     ecx, this
		mov     edx, Reciever
		push	Sender
		call    WriteUserCmdFn
		add     esp, 4
	}
}