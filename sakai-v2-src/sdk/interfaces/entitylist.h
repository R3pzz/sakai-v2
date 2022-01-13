#pragma once
// Include CBaseHandle
#include "../types/handle.h"

class IClientNetworkable;
class IClientUnknown;
class IClientEntity;

class IClientEntityList
{
public:
	virtual IClientNetworkable* GetClientNetworkable(int entnum) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle(CBaseHandle hEnt) = 0;
	virtual IClientUnknown*		GetClientUnknownFromHandle(CBaseHandle hEnt) = 0;
	virtual IClientEntity*		GetClientEntity(int entnum) = 0;
	virtual IClientEntity*		GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int					GetHighestEntityIndex() = 0;
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
	virtual void*				GetClientNetworkableArray() = 0;
};