#pragma once
// Include std::chrono::high_resolution_clock, std::chrono::time_point
#include <chrono>
// Include  macro
#include <windows.h>

class CTimer
{
public:
	CTimer() { m_iTimePoint = std::chrono::high_resolution_clock::now(); }
	~CTimer() = default;

public:
	/*
	* Get time elapsed from timer setup.
	*/
	 std::chrono::nanoseconds GetTimeElapsed() { return m_iTimePoint - std::chrono::high_resolution_clock::now(); }

	/*
	* Get current time.
	*/
	 std::chrono::time_point<std::chrono::steady_clock> GetCurTime() { return std::chrono::high_resolution_clock::now(); }
public:
	// Timer setup time;
	std::chrono::time_point<std::chrono::steady_clock> m_iTimePoint;
};