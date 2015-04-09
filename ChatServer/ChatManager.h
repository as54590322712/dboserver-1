#ifndef _CHATMANAGER
#define _CHATMANAGER

#include <Base.h>
#include <Def.h>
#include <Thread.h>
#include <Mutex.h>

#include <iostream>
#include <memory>
#include <map>

class ChatServer;
class ChatClient;

class ChatLink
{
public:
	ChatLink(ChatClient* pClient) { m_pClient = pClient; }
	ChatLink(ChatLink* pLink) { (*this) = *pLink; }
	ChatClient* GetClient() { return m_pClient; }
private:
	ChatClient* m_pClient;
};

class ChatManager : public RunObject
{
public:
	ChatManager();
	~ChatManager();

	void Init();
	void Release();
	void CreateThread();
	void Run();

	bool AddClient(ChatClient* pClient);
	void RemoveClient(ChatClient* pClient);
	bool FindClient(ChatClient* pClient);
	void SendAll(void* pData, int nSize);
	void SendOthers(void* pData, int nSize, ChatClient* pClient, bool distCheck = false);
	void RecvOthers(eOPCODE_TU Opcode, ChatClient* pClient, bool distCheck = false);

private:
	Thread * pThread;
	ChatServer* pServer;
	typedef std::map<unsigned int, ChatLink*> clientList;
	typedef clientList::iterator cliIt;
	typedef clientList::value_type cliVal;
	clientList cList;
};

#endif