#pragma once

// Used for initializing matrix from vectors
#include "vector.h"
// Used for align
#include "../platform.h"

class CMatrix3x4
{
public:
	~CMatrix3x4() = default;

	CMatrix3x4() {}

	CMatrix3x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23)
	{
		m_Matrix[0][0] = m00; m_Matrix[0][1] = m01; m_Matrix[0][2] = m02; m_Matrix[0][3] = m03;
		m_Matrix[1][0] = m10; m_Matrix[1][1] = m11; m_Matrix[1][2] = m12; m_Matrix[1][3] = m13;
		m_Matrix[2][0] = m20; m_Matrix[2][1] = m21; m_Matrix[2][2] = m22; m_Matrix[2][3] = m23;
	}

	CMatrix3x4(const CVector3& xAxis, const CVector3& yAxis, const CVector3& zAxis, const CVector3& vecOrigin) { }

	CMatrix3x4(const QAngle& Angle) { InitFromQAngles(Angle); }

	CMatrix3x4(const QAngle& Angle, const CVector3& Pos) { InitFromQAngles(Angle, Pos); }

public:
	CMatrix3x4&		InitFromQAngles(const QAngle& Angle, const CVector3& Pos);

	CMatrix3x4&		InitFromQAngles(const QAngle& Angle);

	FORCEINLINE QAngle			ToQAngle() const
	{
		QAngle Angle;

		const float Dst = std::sqrtf(m_Matrix[0][0] * m_Matrix[0][0] + m_Matrix[1][0] * m_Matrix[1][0]);

		if (Dst > 0.001f) {
			Angle.m_X = RAD2DEG(std::atan2(-m_Matrix[2][0], Dst));
			Angle.m_Y = RAD2DEG(std::atan2(m_Matrix[1][0], m_Matrix[0][0]));
			Angle.m_Z = RAD2DEG(std::atan2(m_Matrix[2][1], m_Matrix[2][2]));
		}
		else {
			Angle.m_X = RAD2DEG(std::atan2(-m_Matrix[2][0], Dst));
			Angle.m_Y = RAD2DEG(std::atan2(-m_Matrix[0][1], m_Matrix[1][1]));
			Angle.m_Z = 0.f;
		}

		return Angle;
	}

	/*
	* Set the matrix bottom row.
	*/
	FORCEINLINE CMatrix3x4&		SetOrigin(const CVector3& Value) {
		m_Matrix[0][3] = Value.m_X;
		m_Matrix[1][3] = Value.m_Y;
		m_Matrix[2][3] = Value.m_Z;
	}

	/*
	* Get the matrix bottom row.
	*/
	FORCEINLINE CVector3		GetOrigin() const { return CVector3(m_Matrix[0][3], m_Matrix[1][3], m_Matrix[2][3]); }

	/*
	* Equality operators.
	*/
	FORCEINLINE bool			operator==(const CMatrix3x4& other) const { return memcmp(this, &other, sizeof(CMatrix3x4)) == 0; }
	FORCEINLINE bool			operator!=(const CMatrix3x4& other) const { return _memicmp(this, &other, sizeof(CMatrix3x4)) == 0; }

	/*
	* Array access.
	*/
	FORCEINLINE float*			operator[](std::size_t Size) { return m_Matrix[Size]; }
	FORCEINLINE const float*	operator[](std::size_t Size) const { return m_Matrix[Size]; }

	/*
	* Validation.
	*/
	FORCEINLINE bool			IsValid() const
	{
		// Go through all columns
		for (std::size_t i = 0; i < 3; i++) {
			// Go through all rows
			for (std::size_t j = 0; j < 4; j++) {
				// Check for infinite values
				if (!std::isfinite(m_Matrix[i][j]))
					return false;
			}
		}

		return true;
	}

	FORCEINLINE CMatrix3x4&		Invalidate()
	{
		// Go through all columns
		for (int i = 0; i < 3; i++){
			// Go through all rows
			for (int j = 0; j < 4; j++) {
				// Set to infinite
				m_Matrix[i][j] = MATH_VEC_NAN;
			}
		}

		return *this;
	}

	/*
	* Columns operations.
	*/
	FORCEINLINE CVector3		GetColumn(std::size_t Row) { return CVector3(m_Matrix[0][Row], m_Matrix[1][Row], m_Matrix[2][Row]); }
	FORCEINLINE CMatrix3x4&		SetColumn(std::size_t Row, CVector4& Value) { m_Matrix[0][Row] = Value.m_X; m_Matrix[1][Row] = Value.m_Y; m_Matrix[2][Row] = Value.m_Z; return *this; }

	/*
	* Rows operations.
	*/
	FORCEINLINE CVector4		GetRow(std::size_t Row) { return *reinterpret_cast<CVector4*>(m_Matrix[Row]); }
	FORCEINLINE CMatrix3x4&		SetRow(std::size_t Row, CVector4& Value) { m_Matrix[Row][0] = Value.m_X; m_Matrix[Row][1] = Value.m_Y; m_Matrix[Row][2] = Value.m_Z; m_Matrix[Row][3] = Value.m_W; return *this; }

public:
	float m_Matrix[3][4];
};

/*
* I think it is used for SIMD.
*/
class ALIGN16 CMatrix3x4a : public CMatrix3x4
{
public:

};

class VMatrix
{
public:
	~VMatrix() = default;

	VMatrix() { }

	VMatrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		m_Matrix[0][0] = m00;
		m_Matrix[0][1] = m00;
		m_Matrix[0][2] = m00;
		m_Matrix[0][3] = m00;

		m_Matrix[1][0] = m00;
		m_Matrix[1][1] = m00;
		m_Matrix[1][2] = m00;
		m_Matrix[1][3] = m00;

		m_Matrix[2][0] = m00;
		m_Matrix[2][1] = m00;
		m_Matrix[2][2] = m00;
		m_Matrix[2][3] = m00;

		m_Matrix[3][0] = m00;
		m_Matrix[3][1] = m00;
		m_Matrix[3][2] = m00;
		m_Matrix[3][3] = m00;
	}

	FORCEINLINE CMatrix3x4&		As3x4() { return *reinterpret_cast<CMatrix3x4*>(this); }

	FORCEINLINE bool			operator==(const VMatrix& src) const { return !std::memcmp(m_Matrix, src.m_Matrix, 64); }
	FORCEINLINE bool			operator!=(const VMatrix& src) const { return std::memcmp(m_Matrix, src.m_Matrix, 64); }

	FORCEINLINE float*			operator[](std::size_t Index) { return m_Matrix[Index]; }
	FORCEINLINE const float*	operator[](std::size_t Index) const { return m_Matrix[Index]; }

public:
	float m_Matrix[4][4];
};