#include "logs.h"
// Include GetLocalTime
#include "../utils.h"

std::string UTIL_DispatchFmtString(const char* Fmt, ...)
{
	char chRetStr[1024];

	va_list args;
	va_start(args, Fmt);
	const char* pOccurs = std::strstr(Fmt, "%");
	va_end(args);

	switch (Fmt[reinterpret_cast<unsigned>(pOccurs) + 1])
	{
	case 's': 
	case 'd':
	case 'p':
	case 'f':
	case 'l':
	case 'u':
	default:
		return XOR("");
	}
}

namespace L {
	bool m_bConsoleAttached = false;

	bool LogEvent(std::string Name, EEventType Type)
	{
		// Check for event validity
		if (Name.empty()
			// If event type equals none
			|| Type == EEventType::LOG_EVENT_NONE)
			// Exit function so we don't waste time
			return false;

		if (std::strstr(Name.c_str(), XOR("Dummy event!")) != 0)
			// If this event is dummy, then exit this function.
			// @Note: if you want to mark your event as dummy,
			//	use ONLY "Dummy event!".
			return false;

		// Form our log event
		const CLogEvent Event = CLogEvent(Name, Type);
		// Put our event into a queue
		m_vecEvents.push_back(Event);

		return true;
	}

	bool LogEvent(EEventType Type, const char* Fmt, ...)
	{
		// Parse event name with format
		va_list fmtstr;
		va_start(fmtstr, Fmt);
		std::string Name = UTIL_DispatchFmtString(Fmt, fmtstr);
		va_end(fmtstr);

		// Check for event validity
		if (Name.empty()
			// If event type equals none
			|| Type == EEventType::LOG_EVENT_NONE)
			// Exit function so we don't waste time
			return false;

		if (std::strstr(Name.c_str(), XOR("Dummy event!")) != 0)
			// If this event is dummy, then exit this function.
			// @Note: if you want to mark your event as dummy,
			//	use ONLY "Dummy event!".
			return false;

		// Form our log event
		const CLogEvent Event = CLogEvent(Name, Type);
		// Put our event into a queue
		m_vecEvents.push_back(Event);

		return true;
	}

	bool PrintEvents()
	{
		// Check for queue validity not to waste much time on printing
		if (m_vecEvents.empty())
			return false;
			
		// Go through all our present events
		for (unsigned Index = 0U; Index < m_vecEvents.size(); Index++)
		{
			// Pick up an event.
			CLogEvent& Event = m_vecEvents.at(Index);
			// If our event is dummy, then continue
			if (Event.IsDummy())
				continue;

			// If file logging is enabled, then log event into a file
			if (m_bFileLogging)
			{
				// Output file is not opened, then log a warning
				if (!m_oLogsFile.is_open())
				{
					m_vecEvents.push_back(CLogEvent(XOR("Warning! Unable to open log output file, printing to console only..."), EEventType::LOG_EVENT_WARNING));
					std::printf("%s\n", m_vecEvents.back().What().c_str());
					m_vecEvents.pop_back();
				}
				// Otherwise output our event and time it was registered
				else
				{
					m_oLogsFile << U::DATE::GetLocalTime() << Event.What();
				}
			}

			std::printf("%s\n", Event.What().c_str());

			m_vecEvents.erase(m_vecEvents.cbegin() + Index);
		}

		return true;
	}

	void PushFontColor(std::uint16_t& Color)
	{
		m_uConsoleColor = Color;
	}

	void PopFontColor()
	{
		// Set the console color to black (black is excluding r, g, b).
		m_uConsoleColor &= EConsoleColor::CONSOLE_TEXT_BLACK;
	}
}