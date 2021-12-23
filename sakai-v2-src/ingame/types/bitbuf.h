#pragma once
// Default std types: unsigned, std::uint8_t etc...
#include "../../cheat/platform.h"

class buf_read_t {
public:
	DEF_CTOR_SECT(buf_read_t);
	buf_read_t(
		const void* _data, int _bytes, int _bits = -1
		)
	{
		_start_reading(_data, _bytes, 0, _bits);
	}

public:
	void _cdecl _start_reading(
		const void* _data,
		int _bytes,
		int _start_bit,
		int _bits
		);

	bool _cdecl _seek(
		int _pos
		);

	void _cdecl _grab_next_dw(
		bool _overflow = false
		);

public:
	const char* debug_name;
	bool is_overflow;
	int data_bits;
	unsigned data_bytes;
	unsigned word_in_buf;
	int	avail_bits;
	const unsigned* inc_data_ptr;
	const unsigned* buf_end;
	const unsigned* data_ptr;
};

class buf_write_t {
public:
	DEF_CTOR_SECT(buf_write_t,
		data_ptr = NULL;
		data_bytes = 0;
		data_bits = -1;
		cur_bit = 0;
		is_overflow = false;
		assert_on_overflow = true;
		debug_name = 0;
		)

	buf_write_t(
		void* _data,
		int _bytes,
		int _bits = -1
		)
	{
		assert_on_overflow = true;
		debug_name = 0;

		_start_writing(_data, _bytes, 0, _bits);
	}

	buf_write_t(const char* _dbg_name, void* _data, int _bytes, int _bits = -1) {
		assert_on_overflow = true;
		debug_name = _dbg_name;

		_start_writing(_data, _bytes, 0, _bits);
	}

public:
	__forceinline unsigned _get_written_count() const
	{
		return (cur_bit + 7) >> 3;
	}

	void _cdecl _start_writing(
		void* _data,
		int _bytes,
		int _start_bit = 0,
		int _bits = -1
		);

	void _cdecl _write_cmd(
		void* _to,
		void* _from
		);

public:
	unsigned char* data_ptr;
	int	data_bytes;
	int	data_bits;
	int	cur_bit;
	bool is_overflow;
	bool assert_on_overflow;
	const char* debug_name;
};