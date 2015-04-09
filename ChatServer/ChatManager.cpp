#include "ChatManager.h"
#include "ChatNetwork.h"

ChatManager::ChatManager()
{
	pServer = (ChatServer*)_GetApp();
}

ChatManager::~ChatManager()
{
	Release();
}

void ChatManager::Init()
{
	CreateThread();
}

void ChatManager::Release()
{
}


void ChatManager::Run()
{
	while (IsRunnable())
	{
		Sleep(1000);
	}
}

void ChatManager::CreateThread()
{
	pThread = ThreadFactory::CreateThread(this, "ChatManagerThread");
	pThread->Start();
}

bool ChatManager::AddClient(ChatClient* pClient)
{
	if (false == cList.insert(cliVal(pClient->GetHandle(), new ChatLink(pClient))).second)
		return false;
	return true;
}

void ChatManager::RemoveClient(ChatClient* pClient)
{
	for (cliIt it = cList.begin(); it != cList.end(); ++it)
	{
		if (pClient == it->second->GetClient())
			cList.erase(it);
	}
}

bool ChatManager::FindClient(ChatClient* pClient)
{
	for (cliIt it = cList.begin(); it != cList.end(); ++it)
	{
		if (pClient == it->second->GetClient()) return true;
	}
	return false;
}

void ChatManager::SendAll(void* pData, int nSize)
{
	for (cliIt it = cList.begin(); it != cList.end(); ++it)
	{
		it->second->GetClient()->PushPacket(pData, nSize);
	}
}

void ChatManager::SendOthers(void* pData, int nSize, ChatClient* pClient, bool distCheck)
{
	for (cliIt it = cList.begin(); it != cList.end(); ++it)
	{
		if (pClient->GetHandle() != it->second->GetClient()->GetHandle())
			it->second->GetClient()->PushPacket(pData, nSize);
	}
}

void ChatManager::RecvOthers(eOPCODE_TU Opcode, ChatClient* pClient, bool distCheck)
{
	for (cliIt it = cList.begin(); it != cList.end(); ++it)
	{
		if (pClient->GetHandle() != it->second->GetClient()->GetHandle())
		{
			switch (Opcode)
			{
			case 0:
			{
			} break;
			}
		}
	}
}