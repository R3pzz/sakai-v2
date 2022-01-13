#pragma once

class CVector3;

class ICollideable
{
public:
	// Here to align VMT
	virtual void _0() = 0;
	// Get mins and maxs:
	virtual const CVector3&		GetMins() const = 0;
	virtual const CVector3&		GetMaxs() const = 0;
};