#pragma once
// Include std::iostream, std::ofstream
#include <cstdio>
// Include std::filesystem::path
#include <filesystem>
// Include IGameEvent, IGameEventListener, IGameEventManager
#include "../sdk/interfaces/events.h"

/*
* This is a better version of volvo's event manager.
*/
class CEventManager {
public:
	/*
	* Init our event manager (setup outfiles, event manager,
	*	planned events etc...).
	*/
	void Init();

	/*
	* Fire events to be fired in m_vecEventsPending.
	*/
	bool FirePendingEvents(bool Log = false);

	/*
	* Dump all events into outfile.
	*/
	bool DumpEvents();

	/*
	* This is a wrapper for 
	*/
	bool LoadEventsFromFile(std::string FileName);

	/*
	* Logs a special event into m_vecDumpedEvents.
	*/
	void LogEvent(IGameEvent* Event);

	/*
	* Return game's event manager.
	*/
	IGameEventManager* GetEventManager();

	/*
	* Setup a listener for a game event.
	*/
	IGameEventListener* SeteupListener(std::string Name, IGameEvent* EventToListen);

public:
	// Events recieved from game (updates on hooking firegameevent)
	std::vector<IGameEvent*> m_vecDumpedEvents;
	// Pending events to be fireed/processed
	std::deque<IGameEvent*> m_vecEventsPending;
	// All event listeners wi did setup with SeteupListener()
	std::vector<IGameEventListener*> m_vecListeners;
	// Pointer to game's event manager
	IGameEventManager* m_pEventManager;
	// Path to a file from which we'll load our events
	std::filesystem::path m_loadFilePath;
	// File from which we'll load our events
	std::FILE* m_pEventsFile;
	// File in which we'll dump events
	std::ofstream m_ofsDumpFile;
	// Is local logging enabled?
	bool m_bLoggingEnabled = false;
};