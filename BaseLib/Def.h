#ifndef _DEF
#define _DEF

#include "Base.h"
#include "GameLib\NtlActionPattern.h"
#include "GameLib\NtlAdmin.h"
#include "GameLib\NtlAvatar.h"
#include "GameLib\NtlBattle.h"
#include "GameLib\NtlBBox.h"
#include "GameLib\NtlBudokai.h"
#include "GameLib\NtlCharacter.h"
#include "GameLib\NtlCharacterState.h"
#include "GameLib\NtlChat.h"
#include "GameLib\NtlCSArchitecture.h"
#include "GameLib\NtlDirection.h"
#include "GameLib\NtlDojo.h"
#include "GameLib\NtlDragonBall.h"
#include "GameLib\NtlFriend.h"
#include "GameLib\NtlGuild.h"
#include "GameLib\NtlHlsItem.h"
#include "GameLib\NtlItem.h"
#include "GameLib\NtlLine.h"
#include "GameLib\NtlMail.h"
#include "GameLib\NtlMatch.h"
#include "GameLib\NtlMovement.h"
#include "GameLib\NtlNetP.h"
#include "GameLib\NtlObject.h"
#include "GameLib\NtlPacketAll.h"
#include "GameLib\NtlParty.h"
#include "GameLib\NtlPartyDungeon.h"
#include "GameLib\NtlPet.h"
#include "GameLib\NtlPetition.h"
#include "GameLib\NtlQuest.h"
#include "GameLib\NtlRandom.h"
#include "GameLib\NtlRankBattle.h"
#include "GameLib\NtlReport.h"
#include "GameLib\NtlResultCode.h"
#include "GameLib\NtlRide.h"
#include "GameLib\NtlServer.h"
#include "GameLib\NtlService.h"
#include "GameLib\NtlSharedBotSystemDef.h"
#include "GameLib\NtlSharedDef.h"
#include "GameLib\NtlSharedType.h"
#include "GameLib\NtlSkill.h"
#include "GameLib\NtlSphere.h"
#include "GameLib\NtlSvrMath.h"
#include "GameLib\NtlTeleport.h"
#include "GameLib\NtlTimeQuest.h"
#include "GameLib\NtlTLQ.h"
#include "GameLib\NtlVector.h"
#include "GameLib\NtlWorld.h"

static wchar_t* charToWChar(const char* text)
{
	size_t conv, size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs_s(&conv, wa, size, text, size);
	return wa;
}

#endif