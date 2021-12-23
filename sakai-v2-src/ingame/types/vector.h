#pragma once

// Include Valve ang_t for transitions between vector and angle
#include "angle.h"
// Used for align
#include "../../cheat/platform.h"

// Placeholder for an empty vector
#define MATH_VEC_NAN (std::uint8_t)-1

class vec2d_t
{
public:
	DEF_CTOR_SECT(vec2d_t, x = 0.f; y = 0.f;);

	vec2d_t(
		float _x,
		float _y
		) :
		x(_x),
		y(_y)
	{
	}

public:
	/*operators section*/
	__forceinline vec2d_t operator+(const vec2d_t& _other) const
	{
		return vec2d_t(x + _other.x, y + _other.y);
	}

	__forceinline vec2d_t operator-(const vec2d_t& _other) const
	{
		return vec2d_t(x - _other.x, y - _other.y);
	}

	__forceinline bool operator==(const vec2d_t& _other) const
	{
		return (x == _other.x && y == _other.y);
	}

	__forceinline bool operator!=(const vec2d_t& _other) const
	{
		return (x != _other.x || y != _other.y);
	}

	__forceinline vec2d_t& operator=(const vec2d_t& _other)
	{
		x = _other.x;
		y = _other.y;
	}

	__forceinline float operator[](unsigned _size)
	{
		return reinterpret_cast<float*>(this)[_size];
	}
	/*end of operators section*/
public:
	/*is valid*/
	__forceinline bool _is_valid() const
	{
		return (x != MATH_VEC_NAN && y != MATH_VEC_NAN);
	}
	/*invalidate*/
	__forceinline void _make_invalid()
	{
		x = y = MATH_VEC_NAN;
	}
	/*negate*/
	__forceinline void _negate()
	{
		x = -x;
		y = -y;
	}

	/*unsquared length*/
	__forceinline float _length() const
	{
		return std::sqrtf(x * x + y * y);
	}
	/*squared length*/
	__forceinline float _length_sqr() const { return (x * x + y * y); }
	/*is empty*/
	__forceinline bool _is_zero() const
	{
		return (x == 0 && y == 0);
	}
	/*mult of two vectors*/
	__forceinline float _dot_prod(const vec2d_t& _other) const
	{
		return (x * _other.x + y * _other.y);
	}
	/*calc distance to other vector*/
	__forceinline float _dist_to(const vec2d_t& _other) const
	{
		float _diff_x = x - _other.x;
		float _diff_y = y - _other.y;
		return std::sqrtf(_diff_x * _diff_x + _diff_y * _diff_y);
	}
	/*squared distance to other vector*/
	__forceinline float _dist_to_sqr(const vec2d_t& _other) const
	{
		float _diff_x = x - _other.x;
		float _diff_y = y - _other.y;
		return (_diff_x * _diff_x + _diff_y * _diff_y);
	}

public:
	/*dimensions*/
	float x, y;
};

class vec3d_t
{
public:
	DEF_CTOR_SECT(vec3d_t, x = 0.f; y = 0.f; z = 0.f;);

	vec3d_t(
		float _x,
		float _y,
		float _z
		) :
		x(_x),
		y(_y),
		z(_z)
	{
	}

public:
	/*operators section*/
	__forceinline vec3d_t operator+(const vec3d_t& _other) const
	{
		return vec3d_t(x + _other.x, y + _other.y, z + _other.z);
	}

	__forceinline vec3d_t operator-(const vec3d_t& _other) const
	{
		return vec3d_t(x - _other.x, y - _other.y, z - _other.z);
	}

	__forceinline bool operator==(const vec3d_t& _other) const
	{
		return (x == _other.x && y == _other.y && z == _other.z);
	}

	__forceinline bool operator!=(const vec3d_t& _other) const
	{
		return (x != _other.x || y != _other.y || z != _other.z);
	}

	__forceinline vec3d_t& operator=(const vec3d_t& _other)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
	}

	__forceinline float operator[](unsigned _size)
	{
		return reinterpret_cast<float*>(this)[_size];
	}
	/*end of operators section*/

public:
	/*address in vmem*/
	__forceinline float* _get_thisptr()
	{
		return reinterpret_cast<float*>(this);
	}

	__forceinline const float* _get_thisptr() const
	{
		return reinterpret_cast<const float*>(this);
	}
	/*is valid*/
	__forceinline bool _is_valid() const
	{
		return (x != MATH_VEC_NAN && y != MATH_VEC_NAN && z != MATH_VEC_NAN);
	}
	/*invalidate*/
	__forceinline void _invalidate()
	{ 
		x = y = z = MATH_VEC_NAN;
	}
	/*project onto a plane*/
	__forceinline vec2d_t _project_on_2d()
	{
		return vec2d_t(x, y);
	}
	__forceinline const vec2d_t& _project_on_2d() const
	{
		return vec2d_t(x, y);
	}
	/*negate*/
	__forceinline void _negate()
	{
		x = -x;
		y = -y;
		z = -z;
	}
	/*desquared length*/
	__forceinline float	_length() const
	{
		return std::sqrtf(x * x + y * y + z * z);
	}
	/*squared length*/
	__forceinline float _length_sqr() const
	{
		return (x * x + y * y + z * z);
	}
	/*is empty*/
	__forceinline bool _is_zero() const
	{
		return (x == 0 && y == 0 && z == 0);
	}
	__forceinline void _make_zero()
	{
		x = y = z = 0.f;
	}
	/*mult of two vectors*/
	__forceinline float	_dot_prod(const vec3d_t& _other) const
	{
		return (x * _other.x + y * _other.y + z * _other.z);
	}
	/*does vector lay inside a box*/
	__forceinline bool _in_box(vec3d_t const& _mins, vec3d_t const& _maxs)
	{
		auto _x_valid_v = (x >= _mins.x && x <= _maxs.x);
		auto _y_valid_v = (y >= _mins.y && y <= _maxs.y);
		auto _z_valid_v = (z >= _mins.z && z <= _maxs.z);
		auto _all_valid_v = (_x_valid_v && _y_valid_v && _z_valid_v);
		SAPI_BOOL_RET(_all_valid_v);
	}
	/*calc distance to other vector*/
	__forceinline float	_dist_to(const vec3d_t& _other) const
	{
		float _diff_x = x - _other.x;
		float _diff_y = y - _other.y;
		float _diff_z = z - _other.z;
		return std::sqrtf(_diff_x * _diff_x + _diff_y * _diff_y + _diff_z * _diff_z);
	}
	/*squared distance to other vector*/
	__forceinline float	_dist_to_sqr(const vec3d_t& _other) const
	{
		float _diff_x = x - _other.x;
		float _diff_y = y - _other.y;
		float _diff_z = z - _other.z;
		return (_diff_x * _diff_x + _diff_y * _diff_y + _diff_z * _diff_z);
	}
	/*add two vectors with scalar*/
	__forceinline void _scale(const vec3d_t& _other1, const vec3d_t& _other2, float _scalar)
	{
		x = _other1.x + _other2.x * _scalar;
		y = _other1.y + _other2.y * _scalar;
		z = _other1.z + _other2.z * _scalar;
	}
	/*project onto a plane and calc distance*/
	__forceinline float _length_projected() const
	{
		return std::sqrtf(x * x + y * y);
	}
	__forceinline float	_length_projected_sqr() const
	{
		return (x * x + y * y);
	}

public:
	// Dimensions
	float x , y , z;
};

class ALIGN16 vec3a_t
	: public vec3d_t
{
public:
	DEF_CTOR_SECT(vec3a_t, x = 0.f; y = 0.f; z = 0.f;);

	vec3a_t(
		float _x,
		float _y,
		float _z
		)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	vec3a_t(
		const vec3a_t& _other
		)
	{
		x = _other.x;
		y = _other.y;
		z = _other.z;
	}

public:
	__forceinline void operator=(const vec3a_t& _other)
	{
		_mm_store_ps(_get_thisptr(), _mm_load_ps(_other._get_thisptr()));
	}
};

class vec4d_t : public vec3d_t {
public:
	DEF_CTOR_SECT(vec4d_t, x = 0.f; y = 0.f; z = 0.f; w = 0.f;);
	vec4d_t(
		float _x,
		float _y,
		float _z,
		float _w
		)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	vec4d_t(
		const vec3d_t& _value
		)
	{
		x = _value.x;
		y = _value.y;
		z = _value.z;
	}

	vec4d_t(
		const vec4d_t& _value
		)
	{
		x = _value.x;
		y = _value.y;
		z = _value.z;
		w = _value.w;
	}

public:
	/*operators section*/
	__forceinline vec4d_t& operator=(const vec3d_t& _value)
	{
		x = _value.x;
		y = _value.y;
		z = _value.z;
		w = 0.f;
	}

	__forceinline vec4d_t& operator=(const vec4d_t& _value)
	{
		x = _value.x;
		y = _value.y;
		z = _value.z;
		w = _value.w;
	}

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
	float w;
};

class ALIGN16 vec4a_t
	: public vec4d_t
{
public:
	DEF_CTOR_SECT(vec4a_t, x = 0.f; y = 0.f; z = 0.f; w = 0.f;);
	vec4a_t(
		float _x,
		float _y,
		float _z,
		float _w
		)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	vec4a_t(
		const vec3d_t& _value
		)
	{
		x = _value.x;
		y = _value.y;
		z = _value.z;
	}

	vec4a_t(
		const vec4a_t& _value
		)
	{
		x = _value.x;
		y = _value.y;
		z = _value.z;
		w = _value.w;
	}

public:
	/*operators section*/
	__forceinline vec4a_t& operator=(const vec3d_t& _value)
	{
		x = _value.x;
		y = _value.y;
		z = _value.z;
		w = 0.f;
	}

	__forceinline vec4a_t& operator=(const vec4a_t& _value)
	{
		x = _value.x;
		y = _value.y;
		z = _value.z;
		w = _value.w;
	}
	/*end of operators section*/
};