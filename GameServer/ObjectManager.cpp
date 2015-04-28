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

bool ObjectManager::AddObject(ObjectInfo pObj)
{
	if (false == objList.insert(objVal(pObj.ObjData.handle, pObj)).second)
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
		if ((nHandle == it->second.ObjData.handle) &&
			(byType == it->second.ObjData.sObjectInfo.objType))
		{
			objList.erase(it);
		}
	}
}

bool ObjectManager::FindObject(unsigned int nHandle, BYTE byType)
{
	for (objIt it = objList.begin(); it != objList.end(); ++it)
	{
		if ((nHandle == it->second.ObjData.handle) &&
			(byType == it->second.ObjData.sObjectInfo.objType))
			return true;
	}
	return false;
}

void ObjectManager::UpdatePcItemBrief(unsigned int nHandle, sITEM_BRIEF sBrief, BYTE byPos)
{
	for (objIt it = objList.begin(); it != objList.end(); it++)
	{
		if (nHandle == it->second.ObjData.handle)
		{
			switch (it->second.ObjData.sObjectInfo.objType)
			{
			case OBJTYPE_PC:
				memcpy(&it->second.ObjData.sObjectInfo.pcBrief.sItemBrief[byPos], &sBrief, sizeof(sITEM_BRIEF));
				break;
			}
		}
	}
}

void ObjectManager::UpdateCharState(unsigned int nHandle, sCHARSTATE CharState)
{
	for (objIt it = objList.begin(); it != objList.end(); it++)
	{
		if (nHandle == it->second.ObjData.handle)
		{
			switch (it->second.ObjData.sObjectInfo.objType)
			{
			case OBJTYPE_PC:
				memcpy(&it->second.ObjData.sObjectInfo.pcState, &CharState, sizeof(sCHARSTATE));
				break;
			case OBJTYPE_NPC:
				memcpy(&it->second.ObjData.sObjectInfo.npcState, &CharState, sizeof(sCHARSTATE));
				break;
			case OBJTYPE_MOB:
				memcpy(&it->second.ObjData.sObjectInfo.mobState, &CharState, sizeof(sCHARSTATE));
				break;
			}
		}
	}
}

void ObjectManager::SpawnToClient(GameClient* pClient)
{
	for (objIt it = objList.begin(); it != objList.end(); it++)
	{
		ObjectInfo obj = it->second;

		if (pClient->GetCharSerialID() == obj.ObjData.handle)
			continue;

		if (pClient->worldInfo.tblidx != obj.worldTblIdx)
			continue;

		float x = 0.0f, z = 0.0f;
		switch (obj.ObjData.sObjectInfo.objType)
		{
		case OBJTYPE_PC:
			x = obj.ObjData.sObjectInfo.pcState.sCharStateBase.vCurLoc.x;
			z = obj.ObjData.sObjectInfo.pcState.sCharStateBase.vCurLoc.z;
			break;
		case OBJTYPE_NPC:
			x = obj.ObjData.sObjectInfo.npcState.sCharStateBase.vCurLoc.x;
			z = obj.ObjData.sObjectInfo.npcState.sCharStateBase.vCurLoc.z;
			break;
		case OBJTYPE_MOB:
			x = obj.ObjData.sObjectInfo.mobState.sCharStateBase.vCurLoc.x;
			z = obj.ObjData.sObjectInfo.mobState.sCharStateBase.vCurLoc.z;
			break;
		}

		float dist = NtlGetDistance(pClient->CharState.sCharStateBase.vCurLoc.x, pClient->CharState.sCharStateBase.vCurLoc.z, x, z);

		if (dist < 150)
		{
			if (false == pClient->FindSpawn(obj.ObjData.handle, obj.ObjData.sObjectInfo.objType))
			{
				pClient->AddSpawn(obj.ObjData.handle, obj.ObjData.sObjectInfo.objType);
				pClient->PushPacket(&obj.ObjData, sizeof(obj.ObjData));
			}
		}
		else
		{
			if (pClient->FindSpawn(obj.ObjData.handle, obj.ObjData.sObjectInfo.objType))
			{
				pClient->RemoveSpawn(obj.ObjData.handle);
				sGU_OBJECT_DESTROY obDes;
				memset(&obDes, 0, sizeof(obDes));
				obDes.wOpCode = GU_OBJECT_DESTROY;
				obDes.handle = obj.ObjData.handle;
				pClient->PushPacket(&obDes, sizeof(obDes));
			}
		}
	}
}