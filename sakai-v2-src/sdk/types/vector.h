#pragma once

// Include Valve QAngle for transitions between vector and angle
#include "angle.h"
// Used for align
#include "../platform.h"

// Placeholder for an empty vector
#define MATH_VEC_NAN (std::uint8_t)-1

class CVector2
{
public:
	// Destructor
	~CVector2() = default;

	// Constructors
	CVector2() { }
	CVector2(float X, float Y) : m_X(X), m_Y(Y) { }

public:
	/*
	* Operators.
	*/
	FORCEINLINE CVector2	operator+(const CVector2& Other) const { return CVector2(m_X + m_X, m_Y + m_Y); }
	FORCEINLINE CVector2	operator-(const CVector2& Other) const { return CVector2(m_X - m_X, m_Y - m_Y); }
	FORCEINLINE bool		operator==(const CVector2& Other) const { return (m_X == Other.m_X && m_Y == Other.m_Y); }
	FORCEINLINE bool		operator!=(const CVector2& Other) const { return (m_X != Other.m_X || m_Y != Other.m_Y); }
	FORCEINLINE CVector2&	operator=(const CVector2& Other) { this->m_X = Other.m_X; this->m_Y = Other.m_Y; }
	FORCEINLINE float		operator[](std::size_t Size) { return reinterpret_cast<float*>(this)[Size]; }

	/*
	* Is the vector valid?
	* @Basically checks if all the dimensions are MATH_VEC_NAN.
	*/
	FORCEINLINE bool		IsValid() const { return (m_X != MATH_VEC_NAN && m_Y != MATH_VEC_NAN); }

	/*
	* Invalidate the vector.
	*/
	FORCEINLINE CVector2&	Invalidate() { m_X = m_Y = MATH_VEC_NAN; return *this; }

	/*
	* Negate all vector dimensions.
	*/
	FORCEINLINE CVector2&	Negate() { m_X = -m_X; m_Y = -m_Y; return *this; }

	/*
	* Return the length of the vector (pethagorean I think).
	*/
	FORCEINLINE float		Length() const { return std::sqrtf(m_X * m_X + m_Y * m_Y); }

	/*
	* Return the sqared length of the vector.
	*/
	FORCEINLINE float		LengthSqr() const { return (m_X * m_X + m_Y * m_Y); }

	/*
	* Is our vector empty?
	*/
	FORCEINLINE bool		IsZero() const { return (m_X == 0 && m_Y == 0); }

	/*
	* Cross-vector multiplication.
	*/
	FORCEINLINE float		Dot(const CVector2& Other) const { return (this->m_X * Other.m_X + this->m_Y * Other.m_Y); }

	/*
	* Calc squared distance to other vector.
	*/
	FORCEINLINE float		DistTo(const CVector2& Other) const
	{
		float DifX = this->m_X - Other.m_X;
		float DifY = this->m_Y - Other.m_Y;

		return std::sqrtf(DifX * DifX + DifY * DifY);
	}

	/*
	* Calc linear distance to other vector.
	*/
	FORCEINLINE float		DistToSqr(const CVector2& Other) const
	{
		float DifX = this->m_X - Other.m_X;
		float DifY = this->m_Y - Other.m_Y;

		return (DifX * DifX + DifY * DifY);
	}

public:
	// Dimensions.
	float m_X = 0.f, m_Y = 0.f;
};

class CVector3
{
public:
	// Destructor
	~CVector3() { }

	// Constructors
	CVector3() { }
	CVector3(float X, float Y, float Z) : m_X(X), m_Y(Y), m_Z(Z) { }

public:
	/*
	* Operators.
	*/
	FORCEINLINE CVector3	operator+(const CVector3& Other) const { return CVector3(m_X + m_X, m_Y + m_Y, m_Z + m_Z); }
	FORCEINLINE CVector3	operator-(const CVector3& Other) const { return CVector3(m_X - m_X, m_Y - m_Y, m_Z - m_Z); }
	FORCEINLINE bool		operator==(const CVector3& Other) const { return (m_X == Other.m_X && m_Y == Other.m_Y && m_Z == Other.m_Z); }
	FORCEINLINE bool		operator!=(const CVector3& Other) const { return (m_X != Other.m_X || m_Y != Other.m_Y || m_Z != Other.m_Z); }
	FORCEINLINE CVector3	operator=(const CVector3& Other) { m_X = Other.m_X; m_Y = Other.m_Y; m_Z = Other.m_Z; return *this; }
	FORCEINLINE float&		operator[](std::size_t Size) { return reinterpret_cast<float*>(this)[Size]; }
	FORCEINLINE const float& operator[](std::size_t Size) const { return reinterpret_cast<const float*>(this)[Size]; }
	FORCEINLINE CVector3	operator*=(const CVector3& Other) { m_X *= Other.m_X; m_Y *= Other.m_Y; m_Z *= Other.m_Z; return *this; }
	FORCEINLINE CVector3	operator*=(const float& Value) { m_X *= Value; m_Y *= Value; m_Z *= Value; return *this; }

	/*
	* Get address of our vector.
	*/
	FORCEINLINE float*		Base() { return reinterpret_cast<float*>(this); }
	FORCEINLINE const float* Base() const { return reinterpret_cast<const float*>(this); }

	/*
	* Is the vector valid?
	* @Basically checks if all the dimensions are MATH_VEC_NAN.
	*/
	FORCEINLINE bool		IsValid() const { return (m_X != MATH_VEC_NAN && m_Y != MATH_VEC_NAN && m_Z != MATH_VEC_NAN); }

	/*
	* Invalidate the vector.
	*/
	FORCEINLINE CVector3&	Invalidate() { m_X = m_Y = m_Z = MATH_VEC_NAN; return *this; }

	/*
	* Construct 2d vector from this vector.
	*/
	FORCEINLINE CVector2	AsVector2D() { return CVector2(m_X, m_Y); }
	FORCEINLINE const CVector2& AsVector2D() const { return CVector2(m_X, m_Y); }

	/*
	* Negate all vector dimensions.
	*/
	FORCEINLINE CVector3&	Negate() { m_X = -m_X; m_Y = -m_Y; m_Z = -m_Z; return *this; }

	/*
	* Return the length of the vector (pethagorean I think).
	*/
	FORCEINLINE float		Length() const { return std::sqrtf(m_X * m_X + m_Y * m_Y + m_Z * m_Z); }

	/*
	* Return the sqared length of the vector.
	*/
	FORCEINLINE float		LengthSqr() const { return (m_X * m_X + m_Y * m_Y + m_Z * m_Z); }

	/*
	* Is our vector empty?
	*/
	FORCEINLINE bool		IsZero() const { return (m_X == 0 && m_Y == 0 && m_Z == 0); }
	FORCEINLINE void		Zero() { m_X = m_Y = m_Z = 0.f; }
	
	/*
	* Cross-vector multiplication.
	*/
	FORCEINLINE float		Dot(const CVector3& Other) const { return (this->m_X * Other.m_X + this->m_Y * Other.m_Y + this->m_Z * Other.m_Z); }

	/*
	* Is our vector within a bounding box?
	*/
	FORCEINLINE bool		WithinBBox(CVector3 const& Mins, CVector3 const& Maxs)
	{

	}

	/*
	* Calc squared distance to other vector.
	*/
	FORCEINLINE float		DistTo(const CVector3& Other) const
	{
		float DifX = this->m_X - Other.m_X;
		float DifY = this->m_Y - Other.m_Y;
		float DifZ = this->m_Z - Other.m_Z;

		return std::sqrtf(DifX * DifX + DifY * DifY + DifZ * DifZ);
	}

	/*
	* Calc linear distance to other vector.
	*/
	FORCEINLINE float		DistToSqr(const CVector3& Other) const
	{
		float DifX = this->m_X - Other.m_X;
		float DifY = this->m_Y - Other.m_Y;
		float DifZ = this->m_Z - Other.m_Z;

		return (DifX * DifX + DifY * DifY + DifZ * DifZ);
	}

	/*
	* Add another vector but with a scalar.
	*/
	FORCEINLINE CVector3&	MulAdd(const CVector3& Vec1, const CVector3& Vec2, float Scalar)
	{
		m_X = Vec1.m_X + Vec2.m_X * Scalar;
		m_Y = Vec1.m_Y + Vec2.m_Y * Scalar;
		m_Z = Vec1.m_Z + Vec2.m_Z * Scalar;

		return *this;
	}

	/*
	* Get 2d length (squared and linear).
	*/
	FORCEINLINE float		Length2D() const { return std::sqrtf(m_X * m_X + m_Y * m_Y); }
	FORCEINLINE float		Length2DSqr() const { return (m_X * m_X + m_Y * m_Y); }

	/*
	* Cross-product.
	*/
	//FORCEINLINE CVector3&	Cross(const CVector3& Other) const;
public:
	// Dimensions
	float m_X = 0.f, m_Y = 0.f, m_Z = 0.f;
};

class ALIGN16 CVector3a : public CVector3
{
public:
	CVector3a() { }
	CVector3a(float X, float Y, float Z) { m_X = X; m_Y = Y; m_Z = Z; }
	CVector3a(const CVector3a& Value) { m_X = Value.m_X; m_Y = Value.m_Y; m_Z = Value.m_Z; }
	CVector3a(const CVector3& Value) { m_X = Value.m_X; m_Y = Value.m_Y; m_Z = Value.m_Z; }

public:
	FORCEINLINE void operator=(const CVector3a& Other) { _mm_store_ps(Base(), _mm_load_ps(Other.Base())); }
};

class CVector4 : public CVector3
{
public:
	~CVector4() { }

	CVector4() { }
	CVector4(float X, float Y, float Z, float W = 0.f) { m_X = X; m_Y = Y; m_Z = Z; m_W = W; }
	CVector4(const CVector3& Value) { m_X = Value.m_X; m_Y = Value.m_Y; m_Z = Value.m_Z; }
	CVector4(const CVector4& Value) { m_X = Value.m_X; m_Y = Value.m_Y; m_Z = Value.m_Z; m_W = Value.m_W; }

public:
	FORCEINLINE CVector4& operator=(const CVector3& Value)
	{
		m_X = Value.m_X;
		m_Y = Value.m_Y;
		m_Z = Value.m_Z;
		m_W = 0.f;

		return *this;
	}

	FORCEINLINE CVector4& operator=(const CVector4& Value)
	{
		m_X = Value.m_X;
		m_Y = Value.m_Y;
		m_Z = Value.m_Z;
		m_W = Value.m_W;

		return *this;
	}

	FORCEINLINE float& operator[](std::size_t Size) { return reinterpret_cast<float*>(this)[Size]; }
	FORCEINLINE const float& operator[](std::size_t Size) const { return reinterpret_cast<const float*>(this)[Size]; }

public:
	float m_W = 0.f;
};

class ALIGN16 CVector4a : public CVector4
{
public:
	~CVector4a() { }

	CVector4a() { }
	CVector4a(float X, float Y, float Z, float W = 0.f) { m_X = X; m_Y = Y; m_Z = Z; m_W = W; }
	CVector4a(const CVector3& Value) { m_X = Value.m_X; m_Y = Value.m_Y; m_Z = Value.m_Z; }
	CVector4a(const CVector4& Value) { m_X = Value.m_X; m_Y = Value.m_Y; m_Z = Value.m_Z; m_W = Value.m_W; }

public:
	FORCEINLINE CVector4a& operator=(const CVector3& Value)
	{
		m_X = Value.m_X;
		m_Y = Value.m_Y;
		m_Z = Value.m_Z;
		m_W = 0.f;

		return *this;
	}

	FORCEINLINE CVector4a& operator=(const CVector4a& Value)
	{
		m_X = Value.m_X;
		m_Y = Value.m_Y;
		m_Z = Value.m_Z;
		m_W = Value.m_W;

		return *this;
	}
};