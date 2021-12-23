#include "memory.h"
// include FNV(), XOR()
#include "security.h"
// include c_client_class, recv_table_t, recv_prop_t
#include "../../ingame/types/recv.h"

namespace mem
{
	namespace recv
	{
		ptr_t
		get_item(
			recv_table_t* _table,
			std::uint32_t _name,
			std::uint32_t _off
			)
		{
			ptr_t _ret = 0x0;

			for (unsigned i = 0U; i != _table->props_count; i++)
			{
				recv_prop_t* _prop = &_table->arr_props[i];

				if (_prop->type == e_send_prop::DPT_DT && _prop->dt_ptr)
				{
					_ret = get_item(_table, _name, _off);
				}
				else if (FNV(_prop->name) == _name)
				{
					_ret.mem_ptr += _prop->offset + _off;
					return _ret;
				}
			}

			return _ret;
		}

		ptr_t
		get_offset(
			std::uint32_t _table,
			std::uint32_t _name
			)
		{
			// Get our table
#ifdef DEBUG
			assert(initialized == true);
#else
			if (!initialized)
			{
				return NULL;
			}
#endif
			recv_table_t* _table_v = table_tree[_table];
#ifdef DEBUG
			assert(pTable != NULL);
#else
			if (!_table_v)
			{
				return NULL;
			}
#endif
			ptr_t _ret = get_item(_table_v, _name, 0U);
			return _ret;
		}

		void
		dump(
			const char* _class_name,
			recv_table_t* _table,
			unsigned _off
			)
		{
			for (unsigned i = 0U; i != _table->props_count; i++)
			{
				auto* _prop = &_table->arr_props[i];

				// If this is an invalid prop then skip
				if (!_prop
					|| std::isdigit(_prop->name[0])
					|| !std::strcmp(_prop->name, XOR("baseclass")))
				{
					continue;
				}

				// If prop is a data table then do recursion for this prop
				if (_prop->dt_ptr
					&& _prop->type == e_send_prop::DPT_DT
					&& _prop->dt_ptr->net_table_name[0] == 'D')
				{
					dump(_class_name, _prop->dt_ptr, _off + _prop->offset);
				}

				char _buf[256];

				std::strcpy(_buf, _class_name);
				std::strcat(_buf, "->");
				std::strcat(_buf, _prop->name);

				netvar_tree[FNV(_buf)] = _prop;
			}

			if (table_tree.empty() || netvar_tree.empty())
			{
				initialized = false;
			}
			else
			{
				initialized = true;
			}
		}

		std::unordered_map<unsigned, recv_prop_t*> netvar_tree;
		std::unordered_map<unsigned, recv_table_t*> table_tree;
	}

	headers
	dump_headers(
		std::string _name
		)
	{
		const auto _mdl = GetModuleHandleA(_name.c_str());

		if (!_mdl)
		{ 
			return std::make_tuple(nullptr, nullptr, nullptr);
		}

		auto _base = ptr_t(_mdl);
		auto* _dos = _base._get<IMAGE_DOS_HEADER*>();

		if (!_dos || _dos->e_magic != IMAGE_DOS_SIGNATURE)
		{
			return std::make_tuple(nullptr, nullptr, nullptr);
		}

		auto* _nt = _base._get<IMAGE_NT_HEADERS32*>(_dos->e_lfanew);

		if (!_nt || _nt->Signature != IMAGE_NT_SIGNATURE)
		{
			return std::make_tuple(nullptr, nullptr, nullptr);
		}

		auto* _exp_dir = _base._get<IMAGE_EXPORT_DIRECTORY*>(_nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

		if (!_exp_dir)
		{
			return std::make_tuple(nullptr, nullptr, nullptr);
		}

		return std::make_tuple(_dos, _nt, _exp_dir);
	}

	bytes
	string_to_bytes(
		std::string _str
		)
	{
		auto _sz = _str.size();
		auto* _c = const_cast<char*>(_str.c_str());
		auto* _end = _c + _sz;
		auto _ret = bytes();

		// Iterate through all bytes in a given string
		for (auto it = _c; it != _end; it++)
		{
			if (*it != '\?')
			{
				_ret.push_back(std::strtoul(it, &it, 0x10));
				continue;
			}

			_ret.push_back(-1);
		}

		return _ret;
	}

	bytes
	string_to_bytes(
		const char* _str
		)
	{
		return string_to_bytes(_str);
	}

	ptr_t
	find_signature(
		std::string _mdl,
		std::string _sig
		)
	{
		auto _headers = dump_headers(_mdl);
		auto _start = _headers._Get_rest()._Myfirst._Val->OptionalHeader.ImageBase;
		auto _end = _headers._Get_rest()._Myfirst._Val->OptionalHeader.SizeOfImage + _start;
		auto _bytes = string_to_bytes(_sig);

		for (auto it = _start; it != _end; it++)
		{
			if (it != _bytes[0] || _bytes[0] == -1)
			{
				continue;
			}

			bool _flag = true;

			for (auto i = 0u; i < _bytes.size(); i++)
			{
				if (it + 0x4 * i == _bytes[i])
				{
					continue;
				}
				else
				{
					_flag = false;
				}
			}

			if (_flag)
			{
				return &it;
			}
		}

		return NULL;
	}
}