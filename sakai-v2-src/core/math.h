#pragma once

// Include core types
#include "../includes.h"
// Include Valve math types (vector, matrix, angle etc...)
#include "../sdk/types/vector.h"
// Include Valve math types (vector, matrix, angle etc...)
#include "../sdk/types/angle.h"
// Include Valve math types (vector, matrix, angle etc...)
#include "../sdk/types/matrix.h"

/*
* Here are functions specified on math operations.
*/
namespace M
{
	/*
	* Sets vector aligned to a matrix.
	*/
	CVector3 TransformVector(CVector3& Vector, CMatrix3x4& Matrix);

	/*
	* Implementation of 8 times faster std::clamp function.
	* @Also it is harder to recognize this clamp function.
	*/
	FORCEINLINE float Clamp(float Val, float Min, float Max)
	{
		_mm_store_ss(&Val, _mm_min_ss(_mm_max_ss(_mm_set_ss(Val), _mm_set_ss(Min)), _mm_set_ss(Max)));
		return Val;
	}

	/*
	* Writes sin and cos of Value into SinOut and CosOut.
	*/
	FORCEINLINE void SinCos(float Value, float* SinOut, float* CosOut)
	{
		*SinOut = std::sinf(Value);
		*CosOut = std::cosf(Value);
	}

	/*
	* Normalizes a vector so it does not exceed 180.f.
	*/
	FORCEINLINE void NormalizeVector(CVector3& Vector)
	{
		for (std::size_t Item = 0; Item < 2; Item++)
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
	FORCEINLINE void NormalizeAngle(QAngle& Angle)
	{
		for (std::size_t Item = 0; Item < 2; Item++)
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