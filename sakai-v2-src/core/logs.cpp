#include "logs.h"
// Include GetLocalTime
#include "../utils.h"
// Include SHGetKnownFolderPath
#include <shlobj.h>

namespace L {
	bool m_bConsoleAttached = false;

	bool LogEvent(std::string Name, bool ShowTimestamp)
	{	
		auto Time = U::DATE::GetLocalTime();

#ifdef _DEBUG
		PushFontColor(EConsoleColor::CONSOLE_TEXT_INTENSE_GREEN);
		if (ShowTimestamp)
			std::printf(Time.c_str());
		PushFontColor(m_uConsoleColor);
		std::printf("%s\n", Name.c_str());
		PopFontColor();

		if (m_bFileLogging)
		{
			auto Path = m_fLogsPath;
			// Mavigate to dump file
			Path.append(XOR("logs.sl"));

			// Check for file opened
			if (!m_fLogsFile.is_open())
				m_fLogsFile.open(Path, std::ios::out);

			m_fLogsFile << Time;
			m_fLogsFile << Name << std::endl;

			m_fLogsFile.close();
		}
#endif

		return true;
	}

	void PushFontColor(std::uint16_t Color)
	{
		m_uConsoleColor = Color;
	}

	void PopFontColor()
	{
		// Set the console color to black (black is excluding r, g, b).
		m_uConsoleColor &= EConsoleColor::CONSOLE_TEXT_BLACK;
	}

	void Init()
	{
		// Query documents folder
		PWSTR Folder;
		SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &Folder);
		// Navigate to cheat's folder
		m_fLogsPath.append(Folder);
		m_fLogsPath.append(XOR("sakai"));
	}
}