#pragma once
// Common includes
#include "../../includes.h"

class QAngle {
public:
	~QAngle() = default;

	QAngle() : m_X(0.f), m_Y(0.f), m_Z(0.f) {}

	FORCEINLINE float&			operator[](std::size_t Size) { return reinterpret_cast<float*>(this)[Size]; }
	FORCEINLINE const float&	operator[](std::size_t Size) const { return reinterpret_cast<const float*>(this)[Size]; }

	float m_X = 0.f, m_Y = 0.f, m_Z = 0.f;
};