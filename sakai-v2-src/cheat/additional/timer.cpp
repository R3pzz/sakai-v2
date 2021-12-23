#include "timer.h"



bool CTimer<>::SetUpReminder(TimeType_t When) {
	m_pNotify = std::make_unique<CTimerNotify<>>(new CTimerNotify<>(When));

	if (!m_pNotify)
		return false;

	return true;
}

CTimerNotify<>::CTimerNotify(TimeType_t When) {
	SetupNotify(When, true);
}

void CTimerNotify<>::SetupNotify(TimeType_t TimeWhenNotify, bool DeleteThisOnTimerSignal) {
	m_iTimeToNotify = TimeWhenNotify;
	
	if (TimeWhenNotify <= Iter_t::now()) {
		m_iTimeToNotify = TimeType_t( std::chrono::nanoseconds(-1) );
		m_iTimePassedAfterNotify = TimeType_t(TimeWhenNotify - Iter_t::now());

		if (DeleteThisOnTimerSignal)
			delete this;

		return;
	}

	m_bDeleteThisOnSignal = DeleteThisOnTimerSignal;

	return;
}

bool CTimerNotify<>::CheckNotify(TimeType_t Tolerance) {
	auto TimeElapsed = m_iTimeToNotify - Iter_t::now();

	if (TimeElapsed + Tolerance.time_since_epoch() > TimeType_t::duration(0)) {
		if (m_bDeleteThisOnSignal)
			delete this;

		return true;
	}
}