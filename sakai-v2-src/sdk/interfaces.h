#pragma once

#include "../utils.h"

#include "interfaces/engine.h"
#include "interfaces/events.h"
#include "interfaces/client.h"
#include "interfaces/entitylist.h"
#include "interfaces/gameconsole.h"
#include "interfaces/globalvars.h"
#include "interfaces/glowmanager.h"
#include "interfaces/input.h"
#include "interfaces/localize.h"
#include "interfaces/materialsystem.h"
#include "interfaces/modelrender.h"
#include "interfaces/prediction.h"
#include "interfaces/server.h"
#include "interfaces/steamapi.h"
#include "interfaces/studiorender.h"
#include "interfaces/surface.h"
#include "interfaces/vphysics.h"

/*
* The structure goes like this:
*	1. Base classes which rely on engine
*	2. Base classes which rely on client
*	3. Classes which rely on engine
*	4. Classes which rely on client
*	5. Other classes
*	7. DirectX device
*/

namespace I
{
	bool Init();

	inline IEngine*				m_pEngineClient		= NULL;
	inline IEngineTrace*		m_pTrace			= NULL;
	inline IEngineSound*		m_pSound			= NULL;
	inline CGlobalVarsBase*		m_pGlobalVars		= NULL;

	inline IClientDLL*			m_pClientDll		= NULL;
	inline IClientEntityList*	m_pEntityList		= NULL;
	inline IGameConsole*		m_pGameConsole		= NULL;

	inline IGameEventManager*	m_pGameEventManager	= NULL;
	inline IDebugOverlay*		m_pDebugOverlay		= NULL;
	inline IEngineEffects*		m_pEngineEffects	= NULL;

	inline IGlowObjectManager*	m_pGlowManager		= NULL;
	inline IEffects*			m_pEffects			= NULL;
	inline IInputStackSystem*	m_pInputStackSystem = NULL;
	inline IInputSystem*		m_pInputSystem		= NULL;
	inline CInput*				m_pInput			= NULL;
	inline IVModelRender*		m_pModelRender		= NULL;
	inline IVRenderView*		m_pRenderView		= NULL;

	inline IMaterialSystem*		m_pMatSystem		= NULL;
	inline IStudioRender*		m_pStudioRender		= NULL;
	inline ISurface*			m_pSurface			= NULL;
	inline ILocalize*			m_pLocalize			= NULL;
	inline IPhysicsSurfaceProps* m_pPhysSurface		= NULL;

	inline IDirect3DDevice9*	m_pDevice			= NULL;
}