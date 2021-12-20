#include "../sdk.h"

namespace MEM {
	namespace NETMGR {
		Pointer_t GetItem(CRecvTable* RecvTable, std::uint32_t NameHash, std::uint32_t Offset) {
			Pointer_t Return = 0x0;

			// Iterate through all recv props in given table
			for (std::size_t i = 0U; i != RecvTable->m_nProps; i++) {
				CRecvProp* Prop = &RecvTable->m_pProps[i];

				// If prop is a data table then do recursion for this prop
				if (Prop->m_nRecvType == ESendProp::DPT_DT && Prop->m_pDataTable) {
					Return = GetItem(RecvTable, NameHash, Offset);
				}
				// Else if we match the prop
				else if (FNV(Prop->m_szVarName) == NameHash) {
					// Reutrn ptr + offset
					Return.m_Ptr += Prop->m_iOffset + Offset;

					return Return;
				}
				else continue;
			}

			return Return;
		}

		Pointer_t GetOffset(std::uint32_t TableHash, std::uint32_t NameHash) {
			// Get our table
#ifdef DEBUG
			assert(m_bNetvarSysInitialized != NULL);
#else
			if (!m_bNetvarSysInitialized)
				return NULL;
#endif
			CRecvTable* pTable = m_mapTableTree[TableHash];
#ifdef DEBUG
			assert(pTable != NULL);
#else
			if (!pTable)
				return NULL;
#endif
			Pointer_t Offset = GetItem(pTable, NameHash, 0U);

			return Offset;
		}

		void DumpNetvars(const char* ClassName, CRecvTable* Table, std::uint32_t Offset) {
			for (std::size_t i = 0U; i != Table->m_nProps; i++) {
				CRecvProp* pProp = &Table->m_pProps[i];

				// If this is an invalid prop then skip
				if (!pProp
					|| std::isdigit(pProp->m_szVarName[0])
					|| !std::strcmp(pProp->m_szVarName, XOR("baseclass")))
					continue;

				// If prop is a data table then do recursion for this prop
				if (pProp->m_pDataTable
					&& pProp->m_nRecvType == ESendProp::DPT_DT
					&& pProp->m_pDataTable->m_szNetTableName[0] == 'D') {
					DumpNetvars(ClassName, pProp->m_pDataTable, Offset + pProp->m_iOffset);
				}

				char buf[256];
				std::strcpy(buf, ClassName);
				std::strcat(buf, "->");
				std::strcat(buf, pProp->m_szVarName);

				m_mapNetvarTree[FNV(buf)] = pProp;
			}

			if (m_mapTableTree.empty()
				|| m_mapNetvarTree.empty())
				m_bNetvarSysInitialized = false;
			else
				m_bNetvarSysInitialized = true;
		}

		std::unordered_map<std::uint32_t, CRecvProp*> m_mapNetvarTree;
		std::unordered_map<std::uint32_t, CRecvTable*> m_mapTableTree;
	}

	Headers_t DumpHeaders(std::string ModuleName) {
		// Get handle to a module
		const HMODULE Module = GetModuleHandleA(ModuleName.c_str());
		// If we did not find a module then return NULL
		if (!Module)
			return std::make_tuple(nullptr, nullptr, nullptr);

		Pointer_t Base = Pointer_t(Module);

		// Get a DOS image header
		IMAGE_DOS_HEADER* DosHeaders = Base.Get<IMAGE_DOS_HEADER*>();
		if (!DosHeaders
			|| DosHeaders->e_magic != IMAGE_DOS_SIGNATURE)
			// If we did not get a header or header's magic number
			//	doesn't match our number than the image is broken
			return std::make_tuple(nullptr, nullptr, nullptr);

		// Same with NT image header
		IMAGE_NT_HEADERS32* NtHeaders = Base.Get<IMAGE_NT_HEADERS32*>(DosHeaders->e_lfanew); // lfanew is an offset to NT header
		if (!NtHeaders
			|| NtHeaders->Signature != IMAGE_NT_SIGNATURE)
			return std::make_tuple(nullptr, nullptr, nullptr);

		// Get an export dir.
		// This is the place where all info about exported
		//	functions is stored
		IMAGE_EXPORT_DIRECTORY* ExportDir = Base.Get<IMAGE_EXPORT_DIRECTORY*>(NtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
		if (!ExportDir)
			return std::make_tuple(nullptr, nullptr, nullptr);

		return std::make_tuple(DosHeaders, NtHeaders, ExportDir);
	}

	Bytes_t StringToBytes(std::string String) {
		// Get count of symbols
		std::size_t Size = String.size();
		char*		CString = const_cast<char*>(String.c_str());
		Bytes_t		Return = Bytes_t();

		// Iterate through all bytes in a given string
		for (std::uint16_t it = 0u; it != Size; it++) {
			// If we don't meet an unknown byte then transfer a symbol to a byte
			if (CString[it] != '\?') {
				Return.push_back(std::strtoul(CString, &CString, 0x10));
				continue;
			}

			// Otherwise let scanner know that we have a '\?' byte
			Return.push_back(-1);
			continue;
		}

		return Return;
	}

	Bytes_t StringToBytes(const char* Str) {
		auto String = std::string(Str);
		return StringToBytes(String);
	}

	Pointer_t FindSignature(std::string Module, std::string Pattern) {
		// Get module size and base
		Headers_t Headers = DumpHeaders(Module);
		DWORD StartAddress = Headers._Get_rest()._Myfirst._Val->OptionalHeader.ImageBase;
		DWORD EndAddress = Headers._Get_rest()._Myfirst._Val->OptionalHeader.SizeOfImage + StartAddress;
		// Get a byte sequence from a pattern
		Bytes_t	Bytes = StringToBytes(Pattern);

		// Iterate through all bytes in the Module
		for (DWORD it = StartAddress; it != EndAddress; it++) {
			// If we don't find the first sequence byte then continue
			if (it != Bytes[0] || Bytes[0] == -1)
				continue;

			bool Found = true;

			for (auto i = 0u; i < Bytes.size(); i++) {
				if (it + 0x4 * i == Bytes[i]) {
					// If we match the byte then continue.
					continue;
				}
				else {
					// Else continue searching.
					Found = false;
				}
			}

			// If we match the pattern then return its address.
			if (Found)
				return &it;
		}

		return NULL;
	}
}