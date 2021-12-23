#pragma once
#include "../platform.h"
// Include std::any
#include <any>

struct recv_table_t;
struct recv_prop_t;
struct c_client_class;

namespace mem
{
	class ptr_t
	{
	public:
		DEF_CTOR_SECT(ptr_t, mem_ptr = NULL;);
		ptr_t(
			void* _ptr
			)
		{
			mem_ptr = reinterpret_cast<unsigned char*>(_ptr);
		}

		ptr_t(
			ptr_t& _ptr
			)
		{
			mem_ptr = _ptr.mem_ptr;
		}

	public:
		__forceinline STRICT_BOOLRES operator!()
		{
			return !mem_ptr;
		}

		__forceinline ptr_t operator+(void* _value)
		{
			return ptr_t(mem_ptr + reinterpret_cast<int>(_value));
		}

	public:
		template <typename T>
		__forceinline T _get() {
			return *reinterpret_cast<T*>(mem_ptr);
		}

		template <typename T>
		__forceinline T _get(int _off)
		{
			return *reinterpret_cast<T*>(mem_ptr + _off);
		}

		__forceinline ptr_t& _offset_self(int _off)
		{
			mem_ptr += _off;
			return *this;
		}

		template <typename T = ptr_t>
		__forceinline T _offset_self(int _off)
		{
			mem_ptr += _off;
			return *reinterpret_cast<T*>(mem_ptr);
		}

		template <typename T = unsigned int>
		__forceinline T _find_opcode(unsigned int _opcode, int _off)
		{
			auto _ptr = mem_ptr;

			while (*_ptr != _opcode)
			{
				if (*_ptr == _opcode)
				{
					break;
				}

				_ptr += 1u;
			}

			_ptr += _off;

			return *reinterpret_cast<T*>(_ptr);
		}
		
	public:
		unsigned char* mem_ptr;
	};

	template <typename A>
	class vfunc_t
	{
	public:
		DEF_CTOR_SECT(vfunc_t);
		vfunc_t(
			A* _base,
			unsigned _at
			) :
			base(_base),
			at(_at)
		{
			table = reinterpret_cast<unsigned**>(_base);
		}

	public:
		template <typename T>
		__forceinline T _get(void* _base, unsigned _at)
		{
			return reinterpret_cast<T>(vfunc_t(_base, _at).table[_at]);
		}

		template <typename T>
		__forceinline T _get_after_init()
		{
			return reinterpret_cast<T>(table[at]);
		}

	public:
		A* base = NULL;
		unsigned at = 0U;
		unsigned** table = NULL;
	};

	namespace recv
	{
		ptr_t get_item(
			recv_table_t* _table,
			unsigned _name,
			unsigned _off
			);

		ptr_t get_offset(
			unsigned _table,
			unsigned _name
			);

		void init(
			const char* _class_name,
			recv_table_t* _table,
			unsigned _off
			);

		extern std::unordered_map<unsigned, recv_prop_t*> netvar_tree;
		extern std::unordered_map<unsigned, recv_table_t*> table_tree;

		inline bool initialized = false;
	}

	using create_interface_fn = void* (_cdecl*)(const char*, int*);

	using headers = std::tuple<IMAGE_DOS_HEADER*, IMAGE_NT_HEADERS32*, IMAGE_EXPORT_DIRECTORY*>;
	using bytes = std::vector<char>;

	bytes string_to_bytes(
		std::string _str
		);

	bytes string_to_bytes(
		const char* _str
		);

	ptr_t find_signature(
		std::string _mdl,
		std::string _sig
		);

	template <typename T>
	__forceinline T call_virtual(void* _base, unsigned _at)
	{
		return (*static_cast<T**>(_base))[_at];
	}

	/*DEPRECATED: @This is slower cus of ctors*/
	template <typename T>
	__forceinline T __call_virtual_deprecated(void* Base, unsigned Index) { return Vfunc_t(Base, Index).Get_PostInit<T>(); }

	headers dump_headers(
		std::string _name
		);

	template <typename T>
	__forceinline T* get_interface( std::string _mdl, std::string _ver)
	{
		auto _base = GetModuleHandleA(Module.c_str());

		if (!_base)
		{
			return NULL;
		}

		auto _fn_ptr_v = GetProcAddress(_base, XOR("CreateInterface"));
		create_interface_fn _fn = reinterpret_cast<create_interface_fn>(_fn_ptr_v);
		return reinterpret_cast<T*>(_fn(_ver.c_str(), NULL));
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