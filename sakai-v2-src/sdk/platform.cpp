#include "platform.h"

void CopyColor3(const Color3_t Src, void* Dst)
{
	std::memcpy(Dst, Src, sizeof(Color3_t));
}

void CopyColor4(const Color4_t Src, void* Dst)
{
	std::memcpy(Dst, Src, sizeof(Color4_t));
}