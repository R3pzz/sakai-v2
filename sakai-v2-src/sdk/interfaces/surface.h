#pragma once
// Include CRT lib and CALL_VIRTUAL macro
#include "../platform.h"

// This is here for some screen and cursor metrics
class ISurface
{
public:
	CALL_VIRTUAL(44U,	GetScreenSize(int& Width, int& Height),		void(__thiscall*)(void*, int&, int&),	Width, Height);
	// I think u understand what this does...
	CALL_VIRTUAL(66U,	UnlockCursor(),								void(__thiscall*)(void*));
	CALL_VIRTUAL(67U,	LockCursor(),								void(__thiscall*)(void*));
};