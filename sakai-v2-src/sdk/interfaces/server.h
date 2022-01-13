#pragma once
// Include std::uint64_t, std::uint16_t, std::uint32_t
#include <cstdint>

class IServerBrowser
{
public:
	// Draw the server browser window:
	virtual bool Activate() = 0;
	// Join game w/o opening browser:
	virtual bool JoinGame(std::uint32_t IP, std::uint16_t Port) = 0;
	virtual bool JoinGame(std::uint64_t FriendSteamID) = 0;
	// Show server info:
	virtual bool OpenGameInfoDialog(std::uint64_t ulSteamIDFriend) = 0;
	virtual void CloseGameInfoDialog(std::uint64_t ulSteamIDFriend) = 0;
	virtual void CloseAllGameInfoDialogs() = 0;
};