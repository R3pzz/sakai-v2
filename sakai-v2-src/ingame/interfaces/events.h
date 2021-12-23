#pragma once
// Include std::uint64_t
#include "../platform.h"

class IGameEvent;

class IGameEventListener {
public:
	// Keeping this just for VMT to be correct...
	virtual	~IGameEventListener() {}

	virtual void		FireGameEvent(IGameEvent* Event) = 0;
	virtual int			GetEventDebugID() = 0;
};

class IGameEvent {
public:
	// Keeping this just for VMT to be correct...
	virtual ~IGameEvent() {}

	virtual const char* GetName() const = 0;
	virtual bool		IsReliable() const = 0;
	virtual bool		IsLocal() const = 0;
	virtual bool		IsEmpty(const char* Name = NULL) const = 0;
	// Get Event parameter by its Name and type:
	virtual bool		GetBool(const char* Name, bool Default = false) const = 0;
	virtual int			GetInt(const char* Name, int Default = 0) const = 0;
	virtual std::uint64_t GetI64(const char* Name, std::uint64_t Default = 0) const = 0;
	virtual float		GetFloat(const char* Name, float Default = 0.0f) const = 0;
	virtual const char* GetString(const char* Name, const char* Default = "") const = 0;
	virtual const wchar_t* GetWstring(const char* Name, const wchar_t* Default = L"") const = 0;
	virtual const void* GetPtr(const char* Name) const = 0;
	// Set Event parameter by its Name and type:
	virtual void		SetBool(const char* Name, bool Value) = 0;
	virtual void		SetInt(const char* Name, int Value) = 0;
	virtual void		SetI64(const char* Name, std::uint64_t Value) = 0;
	virtual void		SetFloat(const char* Name, float Value) = 0;
	virtual void		SetString(const char* Name, const char* Value) = 0;
	virtual void		SetWstring(const char* Name, const wchar_t* Value) = 0;
	virtual void		SetPtr(const char* Name, const void* Value) = 0;
};

// Undef it just because compiler thinks it is a CreateEventA function...
#undef CreateEvent

class IGameEventManager {
public:
	// Keeping this just for VMT to be correct...
	virtual	~IGameEventManager() {}
	// Do not use this directly as it might be a bit confusing,
	//	better use it from CEventManager
	virtual int			LoadEventsFromFile(const char* File) = 0;
	// Free the current manager (delete all events etc...):
	virtual void		Reset() = 0;
	// Listener operations:
	virtual bool		AddListener(IGameEventListener* Listener, const char* Name, bool ServerSide) = 0;
	virtual bool		FindListener(IGameEventListener* Listener, const char* Name) = 0;
	virtual void		RemoveListener(IGameEventListener* Listener) = 0;
	virtual bool		AddListenerGlobal(IGameEventListener* Listener, bool ServerSide) = 0;
	// Events management:
	virtual IGameEvent* CreateEvent(const char* Name, bool Force = false, int* Cookie = NULL) = 0;
	virtual bool		FireEvent(IGameEvent* Event, bool DontBroadcast = false) = 0;
	virtual bool		FireEventClientSide(IGameEvent* Event) = 0;
	virtual IGameEvent* DuplicateEvent(IGameEvent* Event) = 0;
	virtual void		FreeEvent(IGameEvent* Event) = 0;
};