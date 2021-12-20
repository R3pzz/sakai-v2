#pragma once

// For Create... delcarations
struct IClientNetworkable;
// For client class recv table declaration
struct CRecvTable;

namespace U {
	/*
	* Function for creating a client class.
	*/
	using CreateClientClassFn = IClientNetworkable * (*)(int EntNum, int Serial);

	/*
	* Function for creating an event corresponding to client class.
	*/
	using CreateEventFn = IClientNetworkable * (*)();
}

class CClientClass {
public:
	U::CreateClientClassFn	m_fnCreateClientClass;
	U::CreateEventFn		m_fnCreateEvent;
	char*					m_szNetTableName;
	CRecvTable*				m_pRecvTable;
	CClientClass*			m_pNext;
	int						m_nClassID;
	const char*				m_szClassName;
};