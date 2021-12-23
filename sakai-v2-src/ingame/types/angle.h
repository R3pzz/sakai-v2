#pragma once
// Common includes
#include "../../cheat/platform.h"

class ang_t
{
public:
	DEF_CTOR_SECT(ang_t, x = 0.f; y = 0.f; z = 0.f;);
	ang_t(
		const ang_t& _other
		)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
	}

public:
	/*operators section*/
	__forceinline float& operator[](unsigned _size)
	{
		return reinterpret_cast<float*>(this)[_size];
	}

	__forceinline const float& operator[](unsigned _size) const
	{ 
		return reinterpret_cast<const float*>(this)[_size];
	}
	/*end of operators section*/
public:
	float x, y, z;
};