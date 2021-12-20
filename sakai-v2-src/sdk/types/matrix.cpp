#include "matrix.h"

// Include M::SinCos
#include "../../core/math.h"

/*
* InitFromQAngles implementation with a given position.
*/
CMatrix3x4& CMatrix3x4::InitFromQAngles(const QAngle& Angle, const CVector3& Pos) {
	InitFromQAngles(Angle);

	m_Matrix[0][3] = Pos.m_X;
	m_Matrix[1][3] = Pos.m_Y;
	m_Matrix[2][3] = Pos.m_Z;

	return *this;
}

/*
* InitFromQAngles implementation.
*/
CMatrix3x4& CMatrix3x4::InitFromQAngles(const QAngle& Angle) {
	float sr, sp, sy, cr, cp, cy;

	M::SinCos(DEG2RAD(Angle[YAW]), &sy, &cy);
	M::SinCos(DEG2RAD(Angle[PITCH]), &sp, &cp);
	M::SinCos(DEG2RAD(Angle[ROLL]), &sr, &cr);

	m_Matrix[0][0] = cp * cy;
	m_Matrix[1][0] = cp * sy;
	m_Matrix[2][0] = -sp;

	m_Matrix[0][1] = sr * sp * cy + cr * -sy;
	m_Matrix[1][1] = sr * sp * sy + cr * cy;
	m_Matrix[2][1] = sr * cp;
	m_Matrix[0][2] = (cr * sp * cy + -sr * -sy);
	m_Matrix[1][2] = (cr * sp * sy + -sr * cy);
	m_Matrix[2][2] = cr * cp;

	m_Matrix[0][3] = 0.0f;
	m_Matrix[1][3] = 0.0f;
	m_Matrix[2][3] = 0.0f;

	return *this;
}