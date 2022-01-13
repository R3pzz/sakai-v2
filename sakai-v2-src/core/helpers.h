#pragma once

// Include std::type_info
#include "../includes.h"

/*
* Some miscellaneous helpers.
*/
namespace HLP
{
	/*
	* This function compares two types and
	*	returns true if they are the same.
	*/
	bool AreTypesSame(void* A, void* B);

	/*
	* Allocate a debugger console for logging.
	*/
	bool InitConsole(std::string Name);
}