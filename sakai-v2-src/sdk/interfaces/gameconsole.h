#pragma once

class IGameConsole
{
public:
	// Here to align VMT
	virtual void	_0() { }

	// Activate INGAME console:
	virtual void	Activate() = 0;
	virtual void	Initialize() = 0;
	// Hide:
	virtual void	Hide() = 0;
	// Clear:
	virtual void	Clear() = 0;
	// Is console in foreground:
	virtual bool	IsConsoleVisible() = 0;
	// Set window parent:
	virtual void	SetParent(int Parent) = 0;
	// Deallocate:
	virtual void	Shutdown() = 0;
};