#pragma once

// For Create... delcarations
struct i_client_networkable;
// For client class recv table declaration
struct recv_table_t;

namespace store
{
	/*create client class*/
	using _create_client_class_fn = i_client_networkable* (_cdecl*)(int, int);
	/*event creation*/
	using _create_event_fn = i_client_networkable* (_cdecl*)();
}

class c_client_class
{
public:
	store::_create_client_class_fn _create_client_class;
	store::_create_event_fn	_create_event;
	char* net_table_name;
	recv_table_t* recv_table;
	c_client_class* next_class;
	int	class_id;
	const char*	class_name;
};