#pragma once
// Used for initializing matrix from vectors
#include "vector.h"
// Used for align
#include "../../cheat/platform.h"

class m3x4_t
{
public:
	DEF_CTOR_SECT(m3x4_t);
	m3x4_t(
		float _m00, float _m01, float _m02, float _m03,
		float _m10, float _m11, float _m12, float _m13,
		float _m20, float _m21, float _m22, float _m23
		)
	{
		mat[0][0] = _m00; mat[0][1] = _m01; mat[0][2] = _m02; mat[0][3] = _m03;
		mat[1][0] = _m10; mat[1][1] = _m11; mat[1][2] = _m12; mat[1][3] = _m13;
		mat[2][0] = _m20; mat[2][1] = _m21; mat[2][2] = _m22; mat[2][3] = _m23;
	}

	m3x4_t(
		const vec3d_t& _x,
		const vec3d_t& _y,
		const vec3d_t& _z,
		const vec3d_t& _org
		)
	{

	}

	m3x4_t(
		const ang_t& _ang
		)
	{
		_from_angle(_ang);
	}

	m3x4_t(
		const ang_t& _ang,
		const vec3d_t& _pos
		)
	{
		_from_angle(_ang, _pos);
	}

public:
	m3x4_t&	_from_angle(
		const ang_t& _ang,
		const vec3d_t& _pos
		);

	m3x4_t& _from_angle(
		const ang_t& _ang
		);

	__forceinline ang_t	_to_angle() const
	{
		ang_t _ang;
		const auto _dist = std::sqrtf(mat[0][0] * mat[0][0] + mat[1][0] * mat[1][0]);

		if (_dist > 0.001f)
		{
			_ang.x = RAD2DEG(std::atan2(-mat[2][0], _dist));
			_ang.y = RAD2DEG(std::atan2(mat[1][0], mat[0][0]));
			_ang.z = RAD2DEG(std::atan2(mat[2][1], mat[2][2]));
		}
		else
		{
			_ang.x = RAD2DEG(std::atan2(-mat[2][0], _dist));
			_ang.y = RAD2DEG(std::atan2(-mat[0][1], mat[1][1]));
			_ang.z = 0.f;
		}

		return _ang;
	}

	__forceinline m3x4_t& _set_org(const vec3d_t& _value)
	{
		mat[0][3] = _value.x;
		mat[1][3] = _value.y;
		mat[2][3] = _value.z;
	}

	__forceinline vec3d_t _get_org() const
	{
		return vec3d_t(mat[0][3], mat[1][3], mat[2][3]);
	}

	__forceinline bool operator==(const m3x4_t& _other) const
	{
		return memcmp(this, &_other, sizeof(m3x4_t)) == 0;
	}

	__forceinline bool operator!=(const m3x4_t& _other) const
	{
		return _memicmp(this, &_other, sizeof(m3x4_t)) == 0;
	}

	__forceinline float* operator[](unsigned _size)
	{
		return mat[_size];
	}

	__forceinline const float* operator[](unsigned _size) const
	{
		return mat[_size];
	}

	__forceinline bool _is_valid() const
	{
		for (unsigned i = 0; i < 3; i++)
		{
			for (unsigned j = 0; j < 4; j++)
			{
				if (!std::isfinite(mat[i][j]))
				{
					return false;
				}
			}
		}

		return true;
	}

	__forceinline void _invalidate()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat[i][j] = MATH_VEC_NAN;
			}
		}
	}

	__forceinline vec3d_t		_get_col(unsigned _row)
	{
		return vec3d_t(mat[0][_row], mat[1][_row], mat[2][_row]);
	}

	__forceinline void _set_col(unsigned _row, vec4d_t& _value)
	{
		mat[0][_row] = _value.x;
		mat[1][_row] = _value.y;
		mat[2][_row] = _value.z;
	}

	__forceinline vec4d_t _get_row(unsigned _row)
	{
		return *reinterpret_cast<vec4d_t*>(mat[_row]);
	}

	__forceinline void _set_row(unsigned _row, vec4d_t& _value)
	{
		mat[_row][0] = _value.x;
		mat[_row][1] = _value.y;
		mat[_row][2] = _value.z;
		mat[_row][3] = _value.w;
	}

public:
	float mat[3][4];
};

/*
* I think it is used for SIMD.
*/
class ALIGN16 m3x4a_t : public m3x4_t {
public:

};

class VMatrix {
public:
	~VMatrix() = default;

	VMatrix() {}
	VMatrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) {

		mat[0][0] = m00;
		mat[0][1] = m00;
		mat[0][2] = m00;
		mat[0][3] = m00;

		mat[1][0] = m00;
		mat[1][1] = m00;
		mat[1][2] = m00;
		mat[1][3] = m00;

		mat[2][0] = m00;
		mat[2][1] = m00;
		mat[2][2] = m00;
		mat[2][3] = m00;

		mat[3][0] = m00;
		mat[3][1] = m00;
		mat[3][2] = m00;
		mat[3][3] = m00;
	}

	__forceinline m3x4_t&		As3x4() { return *reinterpret_cast<m3x4_t*>(this); }

	__forceinline bool			operator==(const VMatrix& src) const { return !std::memcmp(mat, src.mat, 64); }
	__forceinline bool			operator!=(const VMatrix& src) const { return std::memcmp(mat, src.mat, 64); }

	__forceinline float*			operator[](unsigned Index) { return mat[Index]; }
	__forceinline const float*	operator[](unsigned Index) const { return mat[Index]; }

	float mat[4][4];
};