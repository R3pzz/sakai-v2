#pragma once

#include "../utils.h"

#include "interfaces/engine.h"
#include "interfaces/events.h"
#include "interfaces/client.h"

/*
* The structure goes like this:
*	1. Base classes which rely on engine
*	2. Base classes which rely on client
*	3. Classes which rely on engine
*	4. Classes which rely on client
*	5. Classes for prediction, events etc...
*	6. Rendering interfaces
*	7. DirectX device
*/

namespace I
{
	bool Init();

	inline IEngine* m_pEngineClient = NULL;
	inline IEngineTrace* m_pTrace = NULL;
	inline IEngineSound* m_pSound = NULL;

	inline IClientDLL* m_pClientDll = NULL;

	inline IGameEventManager* m_pGameEventManager = NULL;
	inline IDebugOverlay* m_pDebugOverlay = NULL;
	inline IEngineEffects* m_pEngineEffects = NULL;
	inline IEffects* m_pEffects = NULL;

	inline IDirect3DDevice9* m_pDevice = NULL;
}