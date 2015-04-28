#include "GameNetwork.h"

GameClient::GameClient(bool IsAliveCheck, bool IsOpcodeCheck)
	:Session(SESSION_CLIENT)
{
	SetControlFlag(CONTROL_FLAG_USE_SEND_QUEUE);

	if (IsAliveCheck)
	{
		SetControlFlag(CONTROL_FLAG_CHECK_ALIVE);
	}
	if (IsOpcodeCheck)
	{
		SetControlFlag(CONTROL_FLAG_CHECK_OPCODE);
	}

	SetPacketEncoder(&_packetEncoder);
	pServer = (GameServer*)_GetApp();
	pProfile = new CharacterProfile();
}

GameClient::~GameClient()
{
	OnClose();
}

int	GameClient::OnAccept()
{
	return 0;
}

void GameClient::OnClose()
{
	if (false == bIsClosed)
	{
		if (goCharServer) pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '2' WHERE `ID` = '%d';", pProfile->GetAccountid());
		else pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '0' WHERE `ID` = '%d';", pProfile->GetAccountid());
		if (pServer->GetClientManager()->FindClient(this))
			pServer->GetClientManager()->RemoveClient(this);
		if (pServer->GetObjectManager()->FindObject(pProfile->GetSerialID(), OBJTYPE_PC))
		{
			pServer->GetObjectManager()->RemoveObject(pProfile->GetSerialID(), OBJTYPE_PC);
			sGU_OBJECT_DESTROY obDes;
			memset(&obDes, 0, sizeof(obDes));
			obDes.wOpCode = GU_OBJECT_DESTROY;
			obDes.handle = pProfile->GetSerialID();
			pServer->GetClientManager()->SendOthers(&obDes, sizeof(obDes), this);
		}
		pProfile->RemoveOnlineData();
		bIsClosed = true;
	}
}

int GameClient::OnDispatch(Packet* pPacket)
{
	PacketControl(pPacket);
	return 0;
}

void GameClient::Send(void* pData, int nSize)
{
	Send(pData, nSize, this->GetHandle());
}

void GameClient::Send(void* pData, int nSize, int nHandle)
{
	Packet* packet = new Packet((unsigned char*)pData, nSize);
	int rc = pServer->Send(nHandle, packet);
	if (0 != rc)
	{
		Logger::Log("Failed to send packet %d\n", rc);
	}
}

void GameClient::AddSpawn(unsigned int nHandle, BYTE byType)
{
	objSpawn.insert(std::make_pair(nHandle, byType));
}

void GameClient::RemoveSpawn(unsigned int nHandle)
{
	objSpawn.erase(nHandle);
}

bool GameClient::FindSpawn(unsigned int nHandle, BYTE byType)
{
	for each (objSp var in objSpawn)
	{
		if (var.first == nHandle && var.second == byType)
			return true;
	}
	return false;
}

