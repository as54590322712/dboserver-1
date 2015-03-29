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