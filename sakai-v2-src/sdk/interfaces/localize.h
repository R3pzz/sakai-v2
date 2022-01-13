#pragma once
// Include IAppSystem for vtable alignment
#include "../platform.h"

// Invalid lookup string index.
enum { LOCALIZE_INVALID_STRING_INDEX = static_cast<std::uint32_t>(-1), };

class ILocalize : public IAppSystem
{
public:
	virtual bool			AddFile(const char* File, const char* PathID = NULL, bool IncludeFallbackPaths = false) = 0;
	virtual void			RemoveAll() = 0;
	virtual wchar_t*		Find(const char* TokenName) = 0;
	virtual const wchar_t*	FindSafe(const char* TokenName) = 0;
};