#pragma once
// Include std::int64_t
#include <cstdint>

struct recv_proxy_data_t;
struct recv_table_t;
struct recv_prop_t;

namespace store
{
	/*map datatable to structure*/
	using recv_var_proxy_fn = void(_cdecl*)(const recv_proxy_data_t*, void*, void*);
	using array_len_proxy_fn = void(_cdecl*)(void*, int, int);
	using dt_recv_var_proxy_fn = void(_cdecl*)(const recv_prop_t*, void**, void*, int);
}

enum e_send_prop
{
	DPT_INT = 0,
	DPT_FLT,
	DPT_VEC,
	DPT_VEC2D,
	DPT_STR,
	DPT_ARR,
	DPT_DT,
	DPT_I64,
	DPT_NUM_SEND_PROP_TYPES
};

struct standard_recv_proxies_t
{
	store::recv_var_proxy_fn _i32_to_i8;
	store::recv_var_proxy_fn _i32_to_i16;
	store::recv_var_proxy_fn _i32_to_i32;
	store::recv_var_proxy_fn _i64_to_i64;
	store::recv_var_proxy_fn _fl_to_fl;
	store::recv_var_proxy_fn _vec_to_vec;
};

struct recv_proxy_data_t
{
	const recv_prop_t* prop_ptr;
	float float_v;
	long int_v;
	char* pchar_v;
	void* pvoid_v;
	float vec_v[3];
	long long i64_v;
	e_send_prop	type;
	int elem;
	int id;
};

struct recv_prop_t
{
	char* name;
	e_send_prop	type;
	int flags;
	int	buf_size;
	bool in_array;
	const void*	extra;
	recv_prop_t* array_prop;
	store::array_len_proxy_fn _arr_len_proxy;
	store::recv_var_proxy_fn _proxy;
	store::dt_recv_var_proxy_fn _dt_proxy;
	recv_table_t* dt_ptr;
	int	offset;
	int	stride;
	int	elem_count;
	const char*	parent_arr_name;
};

struct recv_table_t
{
	recv_prop_t* arr_props;
	int props_count;
	void* decoder;
	char* net_table_name;
	bool initialized;
	bool in_main_list;
};