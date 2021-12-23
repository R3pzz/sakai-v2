#include "matrix.h"

// Include M::SinCos
#include "../../cheat/core/math.h"

/*
* InitFromQAngles implementation with a given position.
*/
m3x4_t& m3x4_t::InitFromQAngles(const ang_t& Angle, const vec3d_t& Pos) {
	InitFromQAngles(Angle);

	mat[0][3] = Pos.x;
	mat[1][3] = Pos.y;
	mat[2][3] = Pos.z;

	return *this;
}

/*
* InitFromQAngles implementation.
*/
m3x4_t& m3x4_t::InitFromQAngles(const ang_t& Angle) {
	float sr, sp, sy, cr, cp, cy;

	M::SinCos(DEG2RAD(Angle[YAW]), &sy, &cy);
	M::SinCos(DEG2RAD(Angle[PITCH]), &sp, &cp);
	M::SinCos(DEG2RAD(Angle[ROLL]), &sr, &cr);

	mat[0][0] = cp * cy;
	mat[1][0] = cp * sy;
	mat[2][0] = -sp;

	mat[0][1] = sr * sp * cy + cr * -sy;
	mat[1][1] = sr * sp * sy + cr * cy;
	mat[2][1] = sr * cp;
	mat[0][2] = (cr * sp * cy + -sr * -sy);
	mat[1][2] = (cr * sp * sy + -sr * cy);
	mat[2][2] = cr * cp;

	mat[0][3] = 0.0f;
	mat[1][3] = 0.0f;
	mat[2][3] = 0.0f;

	return *this;
}