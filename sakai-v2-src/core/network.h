#pragma once
// Include std:: stuff...
#include "../includes.h"
// Include 
#include <wininet.h>

namespace NET
{
	/*
	* Get a server(profile) name for player's HWID.
	* @Note: you basically can do this from loader
	*	and just keep connection with it while
	*	initializing cheat so it can pass the username.
	*/
	std::string GetServerName();
}