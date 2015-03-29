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
		pServer->SpawnObjects();
		Sleep(1000);
	}
}

void ObjectManager::CreateThread()
{
	pThread = ThreadFactory::CreateThread(this, "ObjectManagerThread");
	pThread->Start();
}

void ObjectManager::AddObject(sGU_OBJECT_CREATE pObj)
{
	objList.push_back(new ObjectLink(pObj));
}

void ObjectManager::RemoveObject(unsigned int nHandle, BYTE byType)
{
	for (unsigned int i = 0; i < objList.size(); ++i)
	{
		if ((nHandle == objList.at(i)->GetObj()->handle) &&
			(byType == objList.at(i)->GetObj()->sObjectInfo.objType))
			objList.erase(objList.begin() + i);
	}
}

bool ObjectManager::FindObject(unsigned int nHandle, BYTE byType)
{
	for (unsigned int i = 0; i < objList.size(); ++i)
	{
		if ((nHandle == objList.at(i)->GetObj()->handle) &&
			(byType == objList.at(i)->GetObj()->sObjectInfo.objType))
			return true;
	}
	return false;
}

void ObjectManager::SpawnToClient(GameClient* pClient)
{
	for (unsigned int x = 0; x < objList.size(); ++x)
	{
		sGU_OBJECT_CREATE obj = *objList.at(x)->GetObj();

		if (pClient->GetCharSerialID() == obj.handle)
			continue;

		if (pClient->FindSpawn(obj.handle, obj.sObjectInfo.objType))
			continue;

		pClient->AddSpawn(obj.handle, obj.sObjectInfo.objType);
		pClient->PushPacket(&obj, sizeof(obj));
	}
}