#include "interfaces.h"

CClientState* g_pClientState = NULL;

namespace I
{
	bool Init()
	{
		m_pEngineClient = MEM::Interface<IEngine>(XOR("engine.dll"), XOR("VEngineClient014"));
		m_pTrace = MEM::Interface<IEngineTrace>(XOR("engine.dll"), XOR("EngineTraceClient004"));
		m_pSound = MEM::Interface<IEngineSound>(XOR("engine.dll"), XOR("IEngineSoundClient003"));
		m_pGlobalVars = **MEM::CallVirtual<MEM::Pointer_t>(m_pEngineClient, 11U).Get<CGlobalVarsBase***>(0xA);

		m_pClientDll = MEM::Interface<IClientDLL>(XOR("client.dll"), XOR("VClient018"));
		m_pEntityList = MEM::Interface<IClientEntityList>(XOR("client.dll"), XOR("VClientEntityList003"));
		m_pGameConsole = MEM::Interface<IGameConsole>(XOR("client.dll"), XOR("GameConsole004"));

		m_pGameEventManager = MEM::Interface<IGameEventManager>(XOR("engine.dll"), XOR("GAMEEVENTSMANAGER002"));
		m_pDebugOverlay = MEM::Interface<IDebugOverlay>(XOR("engine.dll"), XOR("VDebugOverlay004"));
		m_pEngineEffects = MEM::Interface<IEngineEffects>(XOR("engine.dll"), XOR("VEngineEffects001"));

		m_pEffects = MEM::Interface<IEffects>(XOR("client.dll"), XOR("IEffects001"));
		m_pModelRender = MEM::Interface<IVModelRender>(XOR("client.dll"), XOR("VEngineModel016"));

		m_pMatSystem = MEM::Interface<IMaterialSystem>(XOR("materialsystem.dll"), XOR("VMaterialSystem080"));

		if (auto ShaderDevice = MEM::Interface<std::uintptr_t*>(XOR("shaderapidx9.dll"), XOR("ShaderDevice001")))
		{
			if (auto DeviceTable = ShaderDevice[0])
			{
				if (auto ShutdownDevice = DeviceTable[37])
				{
					m_pDevice = **MEM::Pointer_t{ &ShutdownDevice }.Get<IDirect3DDevice9***>(0x2); /***reinterpret_cast<IDirect3DDevice9***>(ShutdownDevice + 0x2)*/;
				}
			}
		}

#ifdef _DEBUG
		assert(m_pEngineClient != nullptr);
#endif
		g_pClientState = **MEM::CallVirtual<MEM::Pointer_t>(m_pEngineClient, 12U).Get<CClientState***>(0x10);

		if (!m_pEngineClient
			|| !m_pTrace
			|| !m_pSound
			|| !m_pClientDll
			|| !m_pGameEventManager
			|| !m_pDebugOverlay
			|| !m_pEngineEffects
			|| !m_pEffects
			|| !g_pClientState)
			return false;

		return true;
	}
}