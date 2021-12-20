#pragma once
// Include std::chrono::high_resolution_clock, std::chrono::time_point
#include <chrono>
// Include FORCEINLINE macroS
#include <winnt.h>

template <typename iterator_type = std::chrono::high_resolution_clock,
	typename time_type = std::chrono::time_point<std::chrono::steady_clock>>
class CTimerNotify;

template <typename iterator_type = std::chrono::high_resolution_clock,
	typename time_type = std::chrono::time_point<std::chrono::steady_clock>>
class CTimer {
	using Iter_t = iterator_type;
	using TimeType_t = time_type;

public:
	CTimer() { m_iTimePoint = Iter_t::now(); }
	~CTimer() = default;

public:
	/*
	* Get time elapsed from timer setup.
	*/
	FORCEINLINE TimeType_t GetTimeElapsed() { return m_iTimePoint - Iter_t::now(); }

	/*
	* Get current time.
	*/
	FORCEINLINE TimeType_t GetCurTime() { return Iter_t::now(); }

	/*
	* Sets up a reminder.
	*/
	bool SetUpReminder(TimeType_t When);
public:
	// Timer setup time;
	Iter_t m_iTimePoint;
	// This is a notify interface for using timer in functions.
	std::unique_ptr<CTimerNotify<Iter_t, TimeType_t>> m_pNotify;
};

template <typename iterator_type = std::chrono::high_resolution_clock,
	typename time_type = std::chrono::time_point<std::chrono::steady_clock>>
class CTimerNotify {
	using Iter_t = iterator_type;
	using TimeType_t = time_type;

public:
	CTimerNotify(TimeType_t When);
	~CTimerNotify() {}

public:
	/*
	* Setups a reminder for a specific time.
	*/
	void SetupNotify(TimeType_t TimeWhenNotify, bool DeleteThisOnTimerSignal);

	/*
	* Checks if curtime > time when notify.
	*/
	bool CheckNotify(TimeType_t Tolerance);

public:
	// Our actual timer
	TimeType_t m_iTimeToNotify;
	// Time passed since timer rang
	TimeType_t m_iTimePassedAfterNotify;

	bool m_bDeleteThisOnSignal = true;
};

