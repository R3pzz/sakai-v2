#include "bitbuf.h"

/*buf_read_t functions*/
void
__cdecl
buf_read_t::
_start_reading(
	const void* _data,
	int _bytes,
	int _start_bit,
	int _bits
	)
{
	data_ptr = reinterpret_cast<const unsigned*>(_data);
	inc_data_ptr = data_ptr;
	data_bytes = _bytes;
	data_bits = _bits == -1 ? _bytes << 3 : _bits;
	is_overflow = false;
	buf_end = reinterpret_cast<const unsigned*>(reinterpret_cast<const unsigned char*>(data_ptr) + _bytes);

	if (data_ptr)
	{ 
		_seek(_start_bit);
	}
}

bool
_cdecl
buf_read_t::
_seek(
	int _pos
	)
{
	bool _ret = true;

	if (_pos < 0 || _pos > data_bits)
	{
		is_overflow = true;
		_ret = false;
		_pos = data_bits;
	}

	const unsigned _head = data_bytes & 3;
	const unsigned _offset = _pos * 0.125f;

	if (data_bytes < 4 || _head && _offset < _head)
	{
		auto _portion_of_data = reinterpret_cast<const unsigned char*>(data_ptr);

		if (data_ptr)
		{
			word_in_buf = *(_portion_of_data + 1);

			if (_head > 1)
				word_in_buf |= (*_portion_of_data++) << 8;

			if (_head > 2)
				word_in_buf |= (*_portion_of_data++) << 16;
		}

		inc_data_ptr = reinterpret_cast<const unsigned*>(_portion_of_data);
		word_in_buf >>= (_pos & 31);
		avail_bits = (_head << 3) - (_pos & 31);
	}
	else
	{
		const unsigned _adj_pos = _pos - (_head << 3);
		inc_data_ptr = reinterpret_cast<const unsigned*>(reinterpret_cast<const unsigned char*>(data_ptr) + ((_adj_pos / 32) << 2) + _head);

		if (data_ptr)
		{
			avail_bits = 32;
			_grab_next_dw();
		}
		else
		{
			word_in_buf = 0;
			avail_bits = 1;
		}

		word_in_buf >>= (_adj_pos & 31);
		avail_bits = std::min<int>(avail_bits, 32 - (_adj_pos & 31));
	}

	return _ret;
}

void
_cdecl
buf_read_t::
_grab_next_dw(
	bool _overflow
	)
{
	if (inc_data_ptr == buf_end)
	{
		avail_bits = 1;
		word_in_buf = 0;
		inc_data_ptr++;

		if (_overflow)
		{
			is_overflow = true;
		}
	}
	else if (inc_data_ptr > buf_end)
	{
		is_overflow = true;
		word_in_buf = 0;
	}
	else
	{
		word_in_buf = *(inc_data_ptr++);
	}
}

/*buf_write_t functions*/
void
_cdecl
buf_write_t::
_start_writing(
	void* _data,
	int _bytes,
	int _start_bit,
	int _bits
	)
{
	_bytes &= ~3;
	data_ptr = reinterpret_cast<unsigned char*>(_data);
	data_bytes = _bytes;
	data_bits = _bits == -1 ? _bytes << 3 : _bits;
	cur_bit = _start_bit;
	is_overflow = false;
}

void
_cdecl
buf_write_t::
_write_cmd(
	void* _to,
	void* _from
	)
{
	static const unsigned char* _write_fn = SIG("client.dll", "55 8B EC 83 E4 F8 51 53 56 8B D9 8B 0D").mem_ptr;
	__asm
	{
		mov     ecx, this
		mov     edx, _to
		push	_from
		call    _write_fn
		add     esp, 4
	}
}