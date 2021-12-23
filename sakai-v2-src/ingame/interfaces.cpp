#include "interfaces.h"

namespace I {
	bool Init() {
		m_pEngineClient = MEM::Interface<IEngine>(XOR("engine.dll"), XOR("VEngineClient014"));
		m_pTrace = MEM::Interface<IEngineTrace>(XOR("engine.dll"), XOR("EngineTraceClient004"));
		m_pSound = MEM::Interface<IEngineSound>(XOR("engine.dll"), XOR("IEngineSoundClient003"));

		m_pClientDll = MEM::Interface<IClientDLL>(XOR("client.dll"), XOR("VClient018"));

		m_pGameEventManager = MEM::Interface<IGameEventManager>(XOR("engine.dll"), XOR("GAMEEVENTSMANAGER002"));
		m_pDebugOverlay = MEM::Interface<IDebugOverlay>(XOR("engine.dll"), XOR("VDebugOverlay004"));
		m_pEngineEffects = MEM::Interface<IEngineEffects>(XOR("engine.dll"), XOR("VEngineEffects001"));
		m_pEffects = MEM::Interface<IEffects>(XOR("client.dll"), XOR("IEffects001"));

#ifdef DEBUG
		assert(m_pEngineClient != nullptr);
#endif
		g_pClientState = **MEM::CallVirtual<MEM::ptr_t>(m_pEngineClient, 12U).Get<CClientState***>();

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