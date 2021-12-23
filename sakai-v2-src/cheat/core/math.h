#pragma once
// Include Valve math types (vector, matrix, angle etc...)
#include "../../ingame/types/vector.h"
// Include Valve math types (vector, matrix, angle etc...)
#include "../../ingame/types/angle.h"
// Include Valve math types (vector, matrix, angle etc...)
#include "../../ingame/types/matrix.h"

/*
* Here are functions specified on math operations.
*/
namespace math
{
	vec3d_t vec_by_mat(vec3d_t& Vector, m3x4_t& Matrix);

	__forceinline float Clamp(float Val, float Min, float Max)
	{
		_mm_store_ss(&Val, _mm_min_ss(_mm_max_ss(_mm_set_ss(Val), _mm_set_ss(Min)), _mm_set_ss(Max)));
		return Val;
	}

	/*
	* Writes sin and cos of Value into SinOut and CosOut.
	*/
	__forceinline void SinCos(float Value, float* SinOut, float* CosOut)
	{
		*SinOut = std::sinf(Value);
		*CosOut = std::cosf(Value);
	}

	/*
	* Normalizes a vector so it does not exceed 180.f.
	*/
	__forceinline void NormalizeVector(vec3d_t& Vector)
	{
		for (unsigned Item = 0; Item < 2; Item++)
		{
			if (Vector[Item] < -180.f)
				Vector[Item] += 360.f;

			if (Vector[Item] > 180.f)
				Vector[Item] -= 360.f;

			if (Vector[Item] < -180.f || Vector[Item] > 180.f)
				NormalizeVector(Vector);
		}
	}

	/*
	* Same but for angle.
	*/
	__forceinline void NormalizeAngle(ang_t& Angle)
	{
		for (unsigned Item = 0; Item < 2; Item++)
		{
			if (Angle[Item] < -180.f)
				Angle[Item] += 360.f;

			if (Angle[Item] > 180.f)
				Angle[Item] -= 360.f;

			if (Angle[Item] < -180.f || Angle[Item] > 180.f)
				NormalizeAngle(Angle);
		}
	}
}