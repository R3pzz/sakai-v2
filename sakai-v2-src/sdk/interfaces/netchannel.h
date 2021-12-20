#pragma once
// Std includes, CALL_VIRTUAL
#include "../platform.h"
// Include BfRead_t, BfWrite_t
#include "../types/bitbuf.h"

class INetMessage;
class INetMessageBinder;

class INetChannel {
public:
	// Functions used for net messagee operations:
	CALL_VIRTUAL(29U,	RegisterMessage(INetMessageBinder* Msg), bool(__thiscall*)(void*, INetMessageBinder*), Msg);
	CALL_VIRTUAL(30U,	UnregisterMessage(INetMessageBinder* Msg), bool(__thiscall*)(void*, INetMessageBinder*), Msg);
	CALL_VIRTUAL(41U,	SendNetMessage(INetMessage* Msg, bool Voice), void(__thiscall*)(void*, INetMessage*, bool, bool), Msg, false, Voice);
	// Net channel operations:
	CALL_VIRTUAL(36U,	Reset(),						void(__thiscall*)(void*));
	CALL_VIRTUAL(37U,	Clear(),						void(__thiscall*)(void*));
	CALL_VIRTUAL(38U,	Shutdown(const char* Reason),	void(__thiscall*)(void*, const char*),	Reason);
	CALL_VIRTUAL(77U,	SetActiveChannel(INetChannel* NewChannel), bool(__thiscall*)(void*, INetChannel*), NewChannel);
	CALL_VIRTUAL(28U,	SetDataRate(float Rate),		void(__thiscall*)(void*, float), Rate);
	// Etc...:
	CALL_VIRTUAL(78U,	GetEncryptionKey(),				const unsigned char* (__thiscall*)(void*))
};

class INetChannelInfo {
public:
	// All functions are just for info here. Nothing to classify :smiling_face:
	virtual const char* GetName() const = 0;
	virtual const char* GetIPAddress() const = 0;
	virtual float		GetTime() const = 0;
	virtual float		GetTimeConnected() const = 0;
	virtual int			GetBufferSize() const = 0;
	virtual int			GetDataRate() const = 0;
	virtual bool		IsLoopback() const = 0;
	virtual bool		IsTimingOut() const = 0;
	virtual bool		IsPlayback() const = 0;
	virtual float		GetLatency(int DataFlow) const = 0;
	virtual float		GetAvgLatency(int DataFlow) const = 0;
	virtual float		GetAvgLoss(int DataFlow) const = 0;
	virtual float		GetAvgChoke(int DataFlow) const = 0;
	virtual float		GetAvgData(int DataFlow) const = 0;
	virtual float		GetAvgPackets(int DataFlow) const = 0;
	virtual int			GetTotalData(int DataFlow) const = 0;
	virtual int			GetTotalPackets(int DataFlow) const = 0;
	virtual int			GetSequenceNr(int DataFlow) const = 0;
	virtual bool		IsValidPacket(int DataFlow, int Frame) const = 0;
	virtual float		GetPacketTime(int DataFlow, int Frame) const = 0;
	virtual int			GetPacketBytes(int DataFlow, int Frame, int Group) const = 0;
	virtual bool		GetStreamProgress(int DataFlow, int* ReceivedPacketsOut, int* TotalPacketsOut) const = 0;
	virtual float		GetTimeSinceLastReceived() const = 0;
	virtual	float		GetCommandInterpolationAmount(int DataFlow, int Frame) const = 0;
	virtual void		GetPacketResponseLatency(int DataFlow, int Frame, int* LatencyMsecsOut, int* ChokeOut) const = 0;
	virtual void		GetRemoteFramerate(float* FrameTimeOut, float* FrameTimeStdDeviationOut, float* FrameStartTimeStdDeviationOut) const = 0;
	virtual float		GetTimeoutSeconds() const = 0;
};

class INetMessage {
public:
	// Net message processing operations:
	CALL_VIRTUAL(3U,	Process(),						bool(__thiscall*)(void*));
	CALL_VIRTUAL(4U,	ReadFromBuffer(BfRead_t& Buf),	bool(__thiscall*)(void*, BfRead_t&), Buf);
	CALL_VIRTUAL(5U,	WriteToBuffer(BfWrite_t& Buf),	bool(__thiscall*)(void*, BfWrite_t&), Buf);
	// Net message info:
	CALL_VIRTUAL(9U,	GetName(),						const char* (__thiscall*)(void*));
	CALL_VIRTUAL(10U,	GetNetChannel(),				INetChannel* (__thiscall*)(void*));
	// Net message content:
	CALL_VIRTUAL(11U,	AsString(),						const char* (__thiscall*)(void*));
	// Net channel operations:
	CALL_VIRTUAL(1U, SetNetChannel(INetChannel* Channel), void(__thiscall*)(void*, INetChannel*), Channel);
};

class INetMessageBinder {
public:
	virtual	~INetMessageBinder() {};
	virtual int			GetType() const = 0;
	virtual void		SetNetChannel(INetChannel* Channel) = 0;
	virtual INetMessage* CreateFromBuffer(BfRead_t& Buf) = 0;
	virtual bool		Process(const INetMessage& Src) = 0;
};