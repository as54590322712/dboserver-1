#include "CharacterManager.h"
#include "GameNetwork.h"

CharacterManager::CharacterManager()
{
	pServer = (GameServer*)_GetApp();
}

CharacterManager::~CharacterManager()
{
	Release();
}

void CharacterManager::Init()
{
	CreateThread();
}

void CharacterManager::Release()
{
}


void CharacterManager::Run()
{
	while (IsRunnable())
	{
		// TODO CHARACTER IMPLEMENTATIONS
		Sleep(1000);
	}
}

void CharacterManager::CreateThread()
{
	pThread = ThreadFactory::CreateThread(this, "CharacterManagerThread");
	pThread->Start();
}

void CharacterManager::SpawnObjects()
{
	for (cliIt it = cList.begin(); it != cList.end(); ++it)
	{
		pServer->GetObjectManager()->SpawnToClient(it->second);
	}
}

bool CharacterManager::AddClient(GameClient* pClient)
{
	if (false == cList.insert(cliVal(pClient->GetHandle(), pClient)).second)
	{
		return false;
	}
	return true;
}

void CharacterManager::RemoveClient(GameClient* pClient)
{
	cliIt it = cList.find(pClient->GetHandle());
	if (it != cList.end())
	{
		if (pClient->GetHandle() == it->second->GetHandle())
		{
			cList.erase(it);
		}
	}
}

bool CharacterManager::FindClient(GameClient* pClient)
{
	for (cliIt it = cList.begin(); it != cList.end(); ++it)
	{
		if (pClient->GetHandle() == it->second->GetHandle())
			return true;
	}
	return false;
}

void CharacterManager::SendAll(void* pData, int nSize)
{
	for (cliIt it = cList.begin(); it != cList.end(); ++it)
	{
		it->second->PushPacket(pData, nSize);
	}
}

void CharacterManager::SendOthers(void* pData, int nSize, GameClient* pClient, bool distCheck)
{
	for (cliIt it = cList.begin(); it != cList.end(); ++it)
	{
		if (pClient->GetHandle() != it->second->GetHandle())
			it->second->PushPacket(pData, nSize);
	}
}

void CharacterManager::RecvOthers(eOPCODE_GU Opcode, GameClient* pClient, bool distCheck)
{
	for (cliIt it = cList.begin(); it != cList.end(); ++it)
	{
		if (pClient->GetHandle() != it->second->GetHandle())
		{
			switch (Opcode)
			{
			case GU_OBJECT_CREATE:
				{
					sGU_OBJECT_CREATE pSpawn = it->second->GetCharSpawnData();
					pSpawn.handle = it->second->GetCharSerialID();
					pClient->PushPacket(&pSpawn, sizeof(pSpawn));
				} break;
			}
		}
	}
}