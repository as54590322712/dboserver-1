#include "ObjectManager.h"
#include "GameNetwork.h"

ObjectManager::ObjectManager()
{
	pServer = (GameServer*)_GetApp();
}

ObjectManager::~ObjectManager()
{
	Release();
}

void ObjectManager::Init()
{
	CreateThread();
}

void ObjectManager::Release()
{
}


void ObjectManager::Run()
{
	while (IsRunnable())
	{
		pServer->GetClientManager()->SpawnObjects();
		Sleep(1000);
	}
}

void ObjectManager::CreateThread()
{
	pThread = ThreadFactory::CreateThread(this, "ObjectManagerThread");
	pThread->Start();
}

bool ObjectManager::AddObject(sGU_OBJECT_CREATE pObj)
{
	if (false == objList.insert(objVal(pObj.handle, pObj)).second)
	{
		return false;
	}
	return true;
}

void ObjectManager::RemoveObject(unsigned int nHandle, BYTE byType)
{
	objIt it = objList.find(nHandle);
	if (it != objList.end())
	{
		if ((nHandle == it->second.handle) &&
			(byType == it->second.sObjectInfo.objType))
		{
			objList.erase(it);
		}
	}
}

bool ObjectManager::FindObject(unsigned int nHandle, BYTE byType)
{
	for (objIt it = objList.begin(); it != objList.end(); ++it)
	{
		if ((nHandle == it->second.handle) &&
			(byType == it->second.sObjectInfo.objType))
			return true;
	}
	return false;
}

void ObjectManager::UpdatePcItemBrief(unsigned int nHandle, sITEM_BRIEF sBrief, BYTE byPos)
{
	for (objIt it = objList.begin(); it != objList.end(); it++)
	{
		if (nHandle == it->second.handle)
		{
			switch (it->second.sObjectInfo.objType)
			{
			case OBJTYPE_PC:
				memcpy(&it->second.sObjectInfo.pcBrief.sItemBrief[byPos], &sBrief, sizeof(sITEM_BRIEF));
				break;
			}
		}
	}
}

void ObjectManager::UpdateCharState(unsigned int nHandle, sCHARSTATE CharState)
{
	for (objIt it = objList.begin(); it != objList.end(); it++)
	{
		if (nHandle == it->second.handle)
		{
			switch (it->second.sObjectInfo.objType)
			{
			case OBJTYPE_PC:
				memcpy(&it->second.sObjectInfo.pcState, &CharState, sizeof(sCHARSTATE));
				break;
			case OBJTYPE_NPC:
				memcpy(&it->second.sObjectInfo.npcState, &CharState, sizeof(sCHARSTATE));
				break;
			case OBJTYPE_MOB:
				memcpy(&it->second.sObjectInfo.mobState, &CharState, sizeof(sCHARSTATE));
				break;
			}
		}
	}
}

void ObjectManager::SpawnToClient(GameClient* pClient)
{
	for (objIt it = objList.begin(); it != objList.end(); it++)
	{
		sGU_OBJECT_CREATE obj = it->second;

		if (pClient->GetCharSerialID() == obj.handle)
			continue;

		float x = 0.0f, z = 0.0f;
		switch (obj.sObjectInfo.objType)
		{
		case OBJTYPE_PC:
			x = obj.sObjectInfo.pcState.sCharStateBase.vCurLoc.x;
			z = obj.sObjectInfo.pcState.sCharStateBase.vCurLoc.z;
			break;
		case OBJTYPE_NPC:
			x = obj.sObjectInfo.npcState.sCharStateBase.vCurLoc.x;
			z = obj.sObjectInfo.npcState.sCharStateBase.vCurLoc.z;
			break;
		case OBJTYPE_MOB:
			x = obj.sObjectInfo.mobState.sCharStateBase.vCurLoc.x;
			z = obj.sObjectInfo.mobState.sCharStateBase.vCurLoc.z;
			break;
		}

		float dist = NtlGetDistance(pClient->CharState.sCharStateBase.vCurLoc.x, pClient->CharState.sCharStateBase.vCurLoc.z, x, z);

		if (dist < 150)
		{
			if (false == pClient->FindSpawn(obj.handle, obj.sObjectInfo.objType))
			{
				pClient->AddSpawn(obj.handle, obj.sObjectInfo.objType);
				pClient->PushPacket(&obj, sizeof(obj));
			}
		}
		else
		{
			if (pClient->FindSpawn(obj.handle, obj.sObjectInfo.objType))
			{
				pClient->RemoveSpawn(obj.handle);
				sGU_OBJECT_DESTROY obDes;
				memset(&obDes, 0, sizeof(obDes));
				obDes.wOpCode = GU_OBJECT_DESTROY;
				obDes.handle = obj.handle;
				pClient->PushPacket(&obDes, sizeof(obDes));
			}
		}
	}
}