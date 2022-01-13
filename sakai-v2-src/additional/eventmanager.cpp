#include "eventmanager.h"

#include "../utils.h"

#include "../sdk/interfaces.h"

void CEventManager::Init()
{
	m_pEventManager = I::m_pGameEventManager;
}

bool CEventManager::FirePendingEvents(bool Log)
{
	for (auto& Event : m_vecEventsPending)
	{
		if (Event->IsEmpty())
			continue;

		if (Log)
			L::LogEvent("Successfully dumped event", true);

		if (!GetEventManager()->FireEvent(Event))
			L::LogEvent("Couldn't fire event", true);
	}

	return true;
}

bool CEventManager::DumpEvents()
{
	m_ofsDumpFile.open(XOR("events.sl"));

	if (m_ofsDumpFile.bad())
	{
		L::LogEvent(XOR("Events dump error, corrupted file!"), true);
		return false;
	}

	if (m_vecDumpedEvents.empty())
		return true;

	for (auto& Event : m_vecDumpedEvents)
	{
		if (Event->IsEmpty())
			continue;

		m_ofsDumpFile << Event->GetName();
	}

	m_ofsDumpFile.close();

	return true;
}

bool CEventManager::LoadEventsFromFile(std::string FileName)
{
	if (m_pEventsFile)
		fclose(m_pEventsFile);

	m_loadFilePath = FileName;
	m_pEventsFile = std::fopen(reinterpret_cast<const char*>(m_loadFilePath.c_str()), "rb");

	if (!m_pEventsFile)
		return false;

	auto Size = std::ftell(m_pEventsFile);
	auto* Buf = static_cast<char*>(_malloca(sizeof(char) * Size));

	if (Buf == NULL)
		return false;

	std::fread(Buf, 1, Size, m_pEventsFile);
	I::m_pGameEventManager->LoadEventsFromFile(Buf);
	std::free(Buf);

	return true;
}

IGameEventManager* CEventManager::GetEventManager()
{
	if (!m_pEventManager)
		return NULL;

	return m_pEventManager;
}

void CEventManager::LogEvent(IGameEvent* Event)
{

}

IGameEventListener* CEventManager::SeteupListener(std::string Name, IGameEvent* EventToListen)
{
	if (!EventToListen)
		return NULL;

	auto* pListener = static_cast<IGameEventListener*>(_malloca(sizeof(IGameEventListener)));

	GetEventManager()->AddListener(pListener, Name.c_str(), false);
}