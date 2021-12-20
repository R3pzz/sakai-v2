#pragma once
// Include std::ofstream
#include <fstream>
// Include std::deque
#include <deque>
// Include std::counting_semaphore
#include <semaphore>
// Include XOR()
#include "security.h"
// Include H::ConsolePrint()
#include "helpers.h"

std::string UTIL_DispatchFmtString(const char* Fmt, ...);

/*
* Here are all logging utilities.
*/
namespace L
{
	/*
	* Type of a logged event.
	*/
	enum EEventType : int
	{
		LOG_EVENT_FAILURE = 0x9,
		LOG_EVENT_WARNING = 0x10,
		LOG_EVENT_ABORT = 0x11,
		LOG_EVENT_SUCCESS = 0x12,
		LOG_EVENT_NONE = 0x13
	};

	/*
	* A special log event class for logging special events
	*	fired by the exception handlers.
	*/
	class CLogEvent
	{
		EEventType m_nType;
	public:
		~CLogEvent() = default;

		CLogEvent() : m_nType(LOG_EVENT_NONE) {}
		CLogEvent(const EEventType Type) : m_nType(Type), m_szName(XOR("Dummy event!")) {}
		CLogEvent(std::string Name, const EEventType Type) : m_nType(Type), m_szName(Name) {}

		FORCEINLINE std::string What()
		{
			char* Buf = new char;

			std::strcat(Buf, XOR("["));
			std::strcat(Buf, XOR(std::to_string(m_nType).c_str()));
			std::strcat(Buf, XOR("] "));
			std::strcat(Buf, XOR(m_szName.c_str()));

			return Buf;
		}

		FORCEINLINE bool IsDummy() { return (m_szName.find(XOR("Dummy event!")) == std::string::npos || m_nType == LOG_EVENT_NONE); }

		FORCEINLINE CLogEvent& operator=(CLogEvent Other) { m_szName = Other.m_szName; m_nType = Other.m_nType; return *this; }

		std::string m_szName;
	};

	/*
	* Log an event to a queue of events for write.
	*/
	bool LogEvent(std::string Name, EEventType Type);
	bool LogEvent(EEventType Type, const char* Fmt, ...);

	/*
	* Print events from events queue.
	*/
	bool PrintEvents();

	/*
	* Just a basic color pallette for debugger console.
	*/
	enum EConsoleColor : std::uint8_t
	{
		CONSOLE_TEXT_BLUE = 0x0001,
		CONSOLE_TEXT_GREEN = 0x0002,
		CONSOLE_TEXT_RED = 0x0004,
		CONSOLE_TEXT_INTENSE_BLUE = (0x0001 | 0x0008),
		CONSOLE_TEXT_INTENSE_GREEN = (0x0002 | 0x0008),
		CONSOLE_TEXT_INTENSE_RED = (0x0004 | 0x0008),
		CONSOLE_TEXT_WHITE = (0x0001 | 0x0002 | 0x0004),
		CONSOLE_TEXT_BLACK = ~(0x0001 | 0x0002 | 0x0004),
	};

	/*
	* Set a font color in the debugger console.
	*/
	void PushFontColor(std::uint16_t& Color);

	/*
	* Remove a font color in the debugger console.
	*/
	void PopFontColor();

	// Is a console attached?
	extern bool m_bConsoleAttached;

	// Is file logging enabled?
	inline bool m_bFileLogging = false;

	// Console text color.
	inline std::uint16_t m_uConsoleColor = FOREGROUND_BLUE;

	// A path to a file in which we will log our events.
	inline std::ofstream m_oLogsFile;

	// A queue for events to be logged.
	inline std::vector<CLogEvent> m_vecEvents;
}