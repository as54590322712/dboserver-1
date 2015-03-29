#ifndef _OBJECTMANAGER
#define _OBJECTMANAGER

#include <Base.h>
#include <Def.h>
#include <Thread.h>

#include <boost\container\vector.hpp>

#include "GameProtocol.h"

using namespace boost::container;

class GameServer;
class GameClient;

class ObjectLink
{
public:
	ObjectLink(sGU_OBJECT_CREATE sObj) { memcpy(&m_sObj, &sObj, sizeof(sObj)); }
	sGU_OBJECT_CREATE* GetObj() { return &m_sObj; }
private:
	sGU_OBJECT_CREATE m_sObj;
};

class ObjectManager : public RunObject
{
public:
	ObjectManager();
	~ObjectManager();

	void Init();
	void Release();
	void CreateThread();
	void Run();

	void AddObject(sGU_OBJECT_CREATE pObj);
	void RemoveObject(unsigned int nHandle, BYTE byType);
	bool FindObject(unsigned int nHandle, BYTE byType);

	void SpawnToClient(GameClient* pClient);

	vector<ObjectLink*> objList;

private:
	Thread * pThread;
	GameServer* pServer;
};

#endif