#pragma once
// Inlude CALL_VIRTUAL, std stuff etc
#include "../platform.h"

class ISteamClient;
class ISteamUser;
class ISteamGameServer;
class ISteamFriends;
class ISteamUtils;
class ISteamMatchmaking;
class ISteamGameSearch;
class ISteamContentServer;
class ISteamMatchmakingServers;
class ISteamUserStats;
class ISteamApps;
class ISteamNetworking;
class ISteamRemoteStorage;
class ISteamScreenshots;
class ISteamMusic;
class ISteamMusicRemote;
class ISteamGameServerStats;
class ISteamHTTP;
class ISteamUnifiedMessages;
class ISteamController;
class ISteamUGC;
class ISteamAppList;
class ISteamHTMLSurface;
class ISteamInventory;
class ISteamVideo;
class ISteamParentalSettings;
class ISteamInput;

namespace U
{
	/*
	* Handle to steam stream.
	*/
	using SteamPipe_t = std::int32_t;

	/*
	* Steam user id.
	*/
	using SteamUser_t = std::int32_t;

	/*
	* Steam api call handle.
	*/
	using SteamApiCall_t = std::int64_t;

	/*
	* User security ticket.
	*/
	using SteamTicket_t = std::uint32_t;
}

enum EAccountType : int
{
	ACC_INVALID = 0,
	ACC_INDIVIDUAL,
	ACC_MULTISEAT,
	ACC_GAME_SERVER,
	ACC_ANON_GAME_SERVER,
	ACC_PENDING,
	ACC_CONTENT_SERVER,
	ACC_CLAN,
	ACC_CHAT,
	ACC_CON_USR,
	ACC_ANON_USR,
	ACC_MAX
};

enum EUniverse : int
{
	U_INVALID = 0,
	U_PUBLIC = 1,
	U_BETA = 2,
	U_INTERN = 3,
	U_DEV = 4,
	U_MAX
};

enum EBeginAuthSessionResult : int
{
	RES_OK = 0,						// Ticket is valid for this game and this steamID.
	RES_INVALID_TICKET = 1,				// Ticket is not valid.
	RES_DUPLICATE_RQ = 2,			// A ticket has already been submitted for this steamID
	RES_INVALID_VER = 3,			// Ticket is from an incompatible interface version
	RES_GAME_MISMATCH = 4,				// Ticket is not for this game
	RES_EXPIRED = 5,				// Ticket has expired
};

struct SteamID_t
{
	std::uint32_t	m_unAccountID : 32;			// unique account identifier
	std::uint32_t	m_unAccountInstance : 20;	// dynamic instance ID
	std::uint32_t	m_EAccountType : 4;			// type of account - can't show as EAccountType, due to signed / unsigned difference
	EUniverse		m_EUniverse : 8;
	pad_t			_0[8];
};

class ISteamAPI
{
public:
	virtual U::SteamPipe_t		CreateSteamPipe() = 0;
	virtual bool				ReleaseSteamPipe(U::SteamPipe_t hSteamPipe) = 0;
	virtual U::SteamUser_t		ConnectToGlobalUser(U::SteamPipe_t hSteamPipe) = 0;
	virtual U::SteamUser_t		CreateLocalUser(U::SteamPipe_t* phSteamPipe, EAccountType eAccountType) = 0;
	virtual void				ReleaseUser(U::SteamPipe_t hSteamPipe, U::SteamUser_t hUser) = 0;
	virtual ISteamUser*			GetISteamUser(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamGameServer*	GetISteamGameServer(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual void				SetLocalIPBinding(uint32_t unIP, uint16_t usPort) = 0;
	virtual ISteamFriends*		GetISteamFriends(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamUtils*		GetISteamUtils(U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamMatchmaking*	GetISteamMatchmaking(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamMatchmakingServers* GetISteamMatchmakingServers(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual void*				GetISteamGenericInterface(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamUserStats*	GetISteamUserStats(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamGameServerStats* GetISteamGameServerStats(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamApps*			GetISteamApps(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamNetworking*	GetISteamNetworking(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamRemoteStorage* GetISteamRemoteStorage(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamScreenshots*	GetISteamScreenshots(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual void				RunFrame() = 0;
	virtual std::uint32_t		GetIPCCallCount() = 0;
	virtual void				_0();
	virtual bool				ShutdownIfAllPipesClosed() = 0;
	virtual ISteamHTTP*			GetISteamHTTP(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamUnifiedMessages* GetISteamUnifiedMessages(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamController*	GetISteamController(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamUGC*			GetISteamUGC(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamAppList*		GetISteamAppList(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamMusic*		GetISteamMusic(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamMusicRemote*	GetISteamMusicRemote(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamHTMLSurface*	GetISteamHTMLSurface(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual void				_1() = 0;
	virtual void				_2() = 0;
	virtual void				_3() = 0;
	virtual ISteamInventory*	GetISteamInventory(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
	virtual ISteamVideo*		GetISteamVideo(U::SteamUser_t hSteamUser, U::SteamPipe_t hSteamPipe, const char* pchVersion) = 0;
};

class ISteamUser
{
public:
	// General info:
	CALL_VIRTUAL(0U,	GetHSteamUser(),				U::SteamUser_t(__thiscall*)(void*));
	CALL_VIRTUAL(2U,	GetSteamID(),					SteamID_t(__thiscall*)(void*));
	CALL_VIRTUAL(1U,	IsLoggedOn(),					bool(__thiscall*)(void*));
	// Game connection:
	CALL_VIRTUAL(3U,	InitGameConnection(void* Blob, int MaxBlob, SteamID_t Server, std::uint32_t IP, std::uint16_t Port, bool Secure),
		int(__thiscall*)(void*, void*, int, SteamID_t, std::uint32_t, std::uint16_t, bool),	Blob, MaxBlob, Server, IP, Port, Secure);
	CALL_VIRTUAL(4U,	TermGameConnection(std::uint32_t IP, std::uint16_t Port),
		int(__thiscall*)(void*, std::uint32_t, std::uint16_t), IP, Port);
	CALL_VIRTUAL(13U,	GetSessionTicket(void* Ticket, int SzTicket, std::size_t LenTicket),
		U::SteamTicket_t(__thiscall*)(void*, void*, int, std::size_t), Ticket, SzTicket, LenTicket);
	CALL_VIRTUAL(14U,	BeginAuthSession(void* AuthTicket, int Size, SteamID_t ID),
		EBeginAuthSessionResult(__thiscall*)(void*, void*, int, SteamID_t), AuthTicket, Size, ID);
	CALL_VIRTUAL(15U,	EndAuthSession(SteamID_t ID),	void(__thiscall*)(void*, SteamID_t),	ID);
	CALL_VIRTUAL(16U,	CancelTicket(U::SteamTicket_t Ticket), void(__thiscall*)(void*, U::SteamTicket_t), Ticket);
	// Storage:
	CALL_VIRTUAL(6U,	GetUserFolder(char* Buf, int SzBuf), bool(__thiscall*)(void*, char*, int), Buf, SzBuf);
	// Steam info:
	CALL_VIRTUAL(23U,	GetSteamLevel(),				int(__thiscall*)(void*));
};

