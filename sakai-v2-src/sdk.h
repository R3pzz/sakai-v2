#pragma once

#include "includes.h"

#include "utils.h"

#include "sdk/classes.h"
#include "sdk/platform.h"
#include "sdk/interfaces.h"

#include "sdk/types/angle.h"
#include "sdk/types/bitbuf.h"
#include "sdk/types/recv.h"
#include "sdk/types/vector.h"
#include "sdk/types/matrix.h"
#include "sdk/types/clientclass.h"

/*
* Initialize our globals.
*/
void Globals_Init();
// Just a helper function...
HWND IO_GetHwnd();