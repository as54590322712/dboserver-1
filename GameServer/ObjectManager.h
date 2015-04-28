#ifndef _OBJECTMANAGER
#define _OBJECTMANAGER

#include <Base.h>
#include <Def.h>
#include <Thread.h>

#include <iostream>
#include <memory>
#include <map>

#include "GameProtocol.h"

typedef struct _Object {
	TBLIDX worldTblIdx;
	sGU_OBJECT_CREATE ObjData;
} ObjectInfo;

class GameServer;
class GameClient;

class ObjectManager : public RunObject
{
public:
	ObjectManager();
	~ObjectManager();

	void Init();
	void Release();
	void CreateThread();
	void Run();

	bool AddObject(ObjectInfo pObj);
	void RemoveObject(unsigned int nHandle, BYTE byType);
	bool FindObject(unsigned int nHandle, BYTE byType);

	void UpdatePcItemBrief(unsigned int nHandle, sITEM_BRIEF sBrief, BYTE byPos);
	void UpdateCharState(unsigned int nHandle, sCHARSTATE CharState);
	void SpawnToClient(GameClient* pClient);

	typedef std::map<HOBJECT, ObjectInfo> objectList;
	typedef objectList::iterator objIt;
	typedef objectList::value_type objVal;

	objectList objList;

private:
	Thread* pThread;
	GameServer* pServer;
};

#endif