#pragma once
#include "../includes.h"
// Include std::any
#include <any>

// Netmanager declarations
struct CRecvTable;
struct CRecvProp;
// Netvar dumper declarations
struct CClientClass;

namespace MEM
{
	/*
	* This class is made to make pointer operations way easier.
	* @This is the main address class for SDK.
	*/
	struct Pointer_t
	{
		// Destructor
		~Pointer_t() = default;

		// Constructors
		Pointer_t()
		{ m_Ptr = NULL; }

		Pointer_t(Pointer_t& Ptr)
		{ m_Ptr = Ptr.m_Ptr; }

		Pointer_t(void* Ptr)
		{ m_Ptr = reinterpret_cast<std::uintptr_t>(Ptr); }

		explicit Pointer_t(std::int32_t Ptr)
		{ m_Ptr = Ptr; }

		explicit Pointer_t(std::uint32_t Ptr)
		{ m_Ptr = Ptr; }

		/*
		* This function just return the pointed memory casted to an object.
		*/
		template <typename T>
		FORCEINLINE T Get() { return reinterpret_cast<T>(m_Ptr); }

		/*
		* Same as previous but also with additional offset.
		*/
		template <typename T>
		FORCEINLINE T Get(std::ptrdiff_t Offset) { return reinterpret_cast<T>(m_Ptr + Offset); }

		/*
		* Offsets the current pointer.
		*/
		FORCEINLINE Pointer_t& OffsetSelf(std::ptrdiff_t Offset) { m_Ptr += Offset; return *this; }

		/*
		* Offsets the current pointer and retrieves it.
		*/
		template <typename T = Pointer_t>
		FORCEINLINE T OffsetSelf(std::ptrdiff_t Offset) { m_Ptr += Offset; return reinterpret_cast<T>(m_Ptr); }

		/*
		* Finds a specified function address.
		*/
		template <typename T = std::uintptr_t>
		FORCEINLINE T FindOpcode(std::uintptr_t Opcode, std::ptrdiff_t Offset)
		{
			auto Ptr = m_Ptr;

			while (Ptr != Opcode)
			{
				if (Ptr == Opcode)
					break;

				Ptr += 1u;
			}

			Ptr += Offset;

			return reinterpret_cast<T>(Ptr);
		}
		
		/*
		* Implementation of ! operator.
		*/
		 bool operator!() { return !m_Ptr; }

		/*
		* Implementation of + operator.
		*/
		FORCEINLINE Pointer_t operator+(void* Value) { return Pointer_t(m_Ptr + reinterpret_cast<std::uintptr_t>(Value)); }

		// Pointer to object
		std::uintptr_t m_Ptr{};
	};

	/*
	* This is a netvar manager class which basically takes
	*	recv table and dumps all netvars from there.
	* @Dumping netvars is a faster way to access them but
	*	may cause memory leaks if not used correctly.
	*	We'll be using netvar dumper for now.
	*/
	namespace NETMGR
	{
		/*
		* Get a recv prop by its name from a recv table.
		*/
		Pointer_t GetItem(CRecvTable* RecvTable, std::uint32_t NameHash, std::uint32_t Offset);

		/*
		* Get an offset for a recv prop.
		*/
		Pointer_t GetOffset(std::uint32_t TableHash, std::uint32_t NameHash);

		/*
		* Dump the whole netvar tree to the m_NetvarTree variable.
		*/
		void DumpNetvars(const char* ClassName, CRecvTable* Table, std::uint32_t Offset);

		// Tree for all dumped netvars.
		extern std::unordered_map<std::uint32_t, CRecvProp*> m_mapNetvarTree;
		extern std::unordered_map<std::uint32_t, CRecvTable*> m_mapTableTree;
		// Are netvar tables dumped?
		inline bool m_bNetvarSysInitialized = false;

#ifdef _DEBUG
		// Dump all netvars to a file
		void DumpToFile();
		// Outfile
		inline std::fstream m_fsDumpStream;
		// Should we dump netvars?
		inline bool m_bDumpNetvars = true;
#endif
	}

	/*
	* A function type for volvo's CreateInterface export.
	*/
	using CreateInterfaceFn_t = void* (*)(const char* Name, int* Code);

	/*
	* Some wrappers here so we don't use that long types.
	*/
	using Headers_t = std::tuple<IMAGE_DOS_HEADER*, IMAGE_NT_HEADERS32*, IMAGE_EXPORT_DIRECTORY*>;
	using Bytes_t = std::vector<int8_t>;

	/*
	* Split a string into byte sequence.
	*/
	Bytes_t StringToBytes(std::string str);
	Bytes_t StringToBytes(const char* Str);

	/*
	* Find a special sequence of bytes in memory
	*	and retrun its address.
	*/
	Pointer_t FindSignature(std::string mdl, std::string sig);

	/*
	* Call a function by an index in a VMT.
	*/
	template <typename T>
	FORCEINLINE auto CallVirtual(void* Base, std::size_t Index) { return (*Pointer_t{ Base }.Get<T**>())[Index]; }

	/*
	* Dump IMAGE_DOS_HEADER, IMAGE_NT_HEADERS32, IMAGE_EXPORT_DIRECTORY
	*	of a module.
	* @IMAGE_DOS_HEADER is an entry header back from MS-DOS left for
	*	data used to load a module.
	* @IMAGE_NT_HEADER32 is a header which specifies all main module specs.
	* @IMAGE_EXPORT_DIRECTORY is a special place where info about all
	*	module exports are stored.
	*/
	Headers_t DumpHeaders(std::string Name);

	template <typename T>
	FORCEINLINE T* Interface(std::string Module, std::string Version)
	{
		// Get handle to the module we want to connect
		auto Base = GetModuleHandleA(Module.c_str());
		if (!Base)
			// If we didn't then return null interface
			return NULL;

		// Get handle to "CreateInterface" function.
		auto CreateInterfaceFn = Pointer_t{ GetProcAddress(Base, "CreateInterface") }.Get<CreateInterfaceFn_t>();

		// Get an interface and return it.
		return reinterpret_cast<T*>(CreateInterfaceFn(Version.c_str(), NULL));
	}
}

/*
* Here are all optimization utilities you should need such as
*	multithreading utilities, vectorization, gpu threading, parallelism etc...
* @Note: please use these tools only if you know what it actually is!
*	Otherwise it may cause errors.
*/
namespace O {

}