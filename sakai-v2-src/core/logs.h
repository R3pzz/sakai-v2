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

/*
* Here are all logging utilities.
*/
namespace L
{
	/*
	* Log an event to file or console.
	*/
	bool LogEvent(std::string Name, bool ShowTimestamp);

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
	void PushFontColor(std::uint16_t Color);

	/*
	* Remove a font color in the debugger console.
	*/
	void PopFontColor();

	/*
	* Initialize m_oLogsFile, check for console.
	*/
	void Init();

	// Is a console attached?
	extern bool m_bConsoleAttached;

	// Is file logging enabled?
	inline bool m_bFileLogging = true;

	// Console text color.
	inline std::uint16_t m_uConsoleColor = FOREGROUND_BLUE;

	// A file in which we will log our events.
	inline std::fstream m_fLogsFile;

	// Path to logs file
	inline std::filesystem::path m_fLogsPath;
}