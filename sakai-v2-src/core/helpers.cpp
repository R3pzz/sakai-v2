#include "helpers.h"

#include "logs.h"

#include "security.h"

namespace HLP
{
	// @TODO: Implement this for va_list.
	bool AreTypesSame(void* A, void* B)
	{
		try {
			return typeid(A).name() == typeid(B).name();
		}
		catch (std::bad_typeid::exception& Exception)
		{
			L::LogEvent(Exception.what(), true);
			return false;
		}
	}

	bool InitConsole(std::string Name)
	{
		const int ConsoleAllocCode = AllocConsole();

		if (ConsoleAllocCode == 0)
		{
			L::LogEvent(XOR("Error: console alloc failure! Continuing without console..."), true);
			L::m_bConsoleAttached = false;

			return false;
		}

		const int ConsoleAttachCode = AttachConsole(ATTACH_PARENT_PROCESS);

		if (ConsoleAttachCode == 0)
		{
			L::LogEvent(XOR("Error: console attach failure! Continuing without console..."), true);
			L::m_bConsoleAttached = false;

			return false;
		}

		SetConsoleTitleA(Name.c_str());

		return true;
	}
}