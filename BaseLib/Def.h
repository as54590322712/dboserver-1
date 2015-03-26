#ifndef _DEF_H
#define _DEF_H

#pragma once

#include "Base.h"
#include "Vector.h"

typedef char SBYTE;
typedef unsigned char BYTE;
typedef short SWORD;
typedef unsigned short WORD;
typedef long SDWORD;
typedef unsigned long DWORD;
typedef long long SQWORD;
typedef unsigned long long QWORD;
#define pi 3.1415926535897932384626433832795
#define r2d pi/180

#define SERVER_PORT 50200
#define MAX_BUFFER_SIZE 7048

#define MAX_USERNAME_SIZE (12)
#define MAX_PASSWORD_SIZE (12)
#define MAX_AUTHKEY_SIZE (16)
#define MAX_SRVADDR_SIZE (64)
#define MAX_CHARSRV_COUNT (10)
#define MAX_MAC_ADDR_SIZE (6)
#define INVALID_SERVERID (0xFF)
#define INVALID_SLOTID (0xFF)
#define MAX_SERVERNAME_SIZE (32)
#define MAX_CHANNEL_COUNT (10)
#define MAX_CHARNAME_SIZE (16)
#define MAX_PARTYNAME_SIZE (16)
#define MAX_ITEM_OPTION (2)
#define INVALID_MARKING_TYPE (0xffui8)
#define MAX_CHARSLOT_COUNT (8)
#define ALLRACES (0xFF)
#define MAX_CHATMESSAGE_USIZE (256)
#define MAX_CHATMESSAGE_SIZE (256)
#define MAX_CHATMESSAGE_SIZE_MBUFFER (1024)
#define SHORTCUT_MAX_COUNT (100)
#define MAX_SKILL_TARGET (8)
#define MAX_SHOPCART (12)
#define MAX_GUILDNAME_USIZE (32)
#define MAX_DRAGONBALLS (7)
#define MAX_PRIVATESHOPNAME_USIZE (32)
#define MAX_PRIVATESHOPNOTICE_USIZE (64)
#define MAX_MAILMESSAGE_SIZE (128)
#define MAX_MAILSLOT_COUNT (30)
#define MAX_MULTIDEL_COUNT (6)
#define MAX_BUDOKAITEAMNAME_USIZE (20)
#define MAX_HLSSHOP_CART (10)
#define GMT_MAX_EFFECT_LIST_SIZE (5)
#define GMT_MAX_TIME_SLOT_SIZE (3)
#define MAX_HTBSKILL_COUNT (10)
#define MAX_NEXTDESTLOC_COUNT (10)
#define MAX_EFFECTSKILL (2)
#define MAX_INVEN_ITEMCOUNT (128)
#define MAX_PCHARSKILLS_COUNT (120)
#define MAX_PCHARHTBSKILLS_COUNT (30)
#define MAX_PCHARBUFF_COUNT (8)
#define MAX_PCHARDEBUFF_COUNT (8)
#define MAX_WOLDDOJO_COUNT (7)
#define MAX_NEXT_DEST_LOC_COUNT (10)
#define MAX_SIZE_CP_COOKIE (1024 * 2)
#define MAX_SIZE_CJI_KOR_UNI_ID (12)
#define NEWBIE_ITEM_MAX (8)
#define NEWBIE_SKILL_MAX (3)
#define NEWBIE_MAX_QUICKSLOT_COUNT (5)
#define INVALID_OBJECT 0xFFFFFFFF
#define MAX_OBJECT 0x0FFFFFFF
#define MAX_COUNT_USER_HAVE_INVEN_ITEM (128)
#define MAX_COUNT_USER_HAVE_NORMAL_BANK_ITEM (52)
#define MAX_COUNT_USER_HAVE_PUBLIC_BANK_ITEM (16)
#define MAX_COUNT_USER_HAVE_BANK_ITEM (MAX_COUNT_USER_HAVE_NORMAL_BANK_ITEM + MAX_COUNT_USER_HAVE_PUBLIC_BANK_ITEM)
#define MAX_COUNT_USER_HAVE_TOTAL_ITEM (MAX_COUNT_USER_HAVE_INVEN_ITEM + MAX_COUNT_USER_HAVE_BANK_ITEM)
#define CHAR_QUICK_SLOT_MAX_COUNT 48
#define MAX_NPC_HAVE_SKILL 7
#define MAX_COUNT_WAR_FOG (80)
#define MAX_SIZE_WAR_FOG (int)(( MAX_COUNT_WAR_FOG - 1) / 8 + 1)
#define ITEM_UPGRADE_EQUIP_COUNT 5
#define MAX_BANK_ITEM_SLOT 16
#define	MAX_MINORMATCH_TEAM_COUNT 32
#define MAX_MATCH_EXTENDED_STAGE_COUNT 3
#define MAX_MATCH_STAGE_COUNT (5 + MAX_MATCH_EXTENDED_STAGE_COUNT)
#define MAX_MAJORMATCH_EXTENDED_STAGE_COUNT 1
#define	MAX_BUDOKAI_MATCH_REWARD_ITEM_COUNT 3
#define MAX_SIZE_QUESTION_CONTENT_UNICODE (256)
#define ITEM_RECIPE_MAX_COUNT 100
#define MAX_COUNT_DOJO_BANK_HISTORY 40
#define MAX_LENGTH_OF_DOJO_NOTICE_UNICODE (64)

// macro bit flag
#define BIT_FLAG_CLEAR(b)		( (b) = 0 )
#define BIT_FLAG_FLIP(b)		( (b) ^= (b) )
#define BIT_FLAG_SET(b, f)		( (b) |= (f) )
#define BIT_FLAG_UNSET(b, f)	( (b) &= ~(f) )
#define BIT_FLAG_TEST(b, f)		( (b) & (f) ? true : false ) 
#define BIT_FLAG_TOGGLE(b, f)	( (b) ^= (f) )
#define MAKE_BIT_FLAG(x)		( 0x01 << (x) )
#define MAKE_BIT_FLAG64(x)		( DWORD64(0x01) << (x) )

static wchar_t* charToWChar(const char* text)
{
	size_t conv, size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs_s(&conv, wa, size, text, size);
	return wa;
}

enum ResultCodes
{
	// BASE
	RESULT_SUCCESS = 0,
	RESULT_FAIL,
	// AUTHSERVER
	AUTH_SUCCESS = 100,
	AUTH_FAIL,
	AUTH_VERSION_FAIL,
	AUTH_TOO_LONG_ACCOUNT,
	AUTH_TOO_LONG_PASSWORD,
	AUTH_AUTHKEY_FAIL,
	AUTH_USER_SAMENAME_EXIST,
	AUTH_WRONG_PASSWORD,
	AUTH_USER_NOT_FOUND,
	AUTH_USER_EXIST,
	AUTH_USER_EXIST_IN_CHARACTER_SERVER,
	AUTH_DB_FAIL,
	AUTH_NO_AVAILABLE_CHARACTER_SERVER,
	AUTH_USER_BLOCK,
	AUTH_USER_TEMPORARY_BLOCK,
	AUTH_SERVER_LOCKED,
	AUTH_COMMON_CANT_DO_THAT_FOR_SOME_REASON,
	AUTH_INVALID_CJI_KOR_COOKIE,
	AUTH_IP_BLOCK,
	AUTH_USER_KICKOUT_WAIT_PLZ,
	// CHARSERVER
	CHARACTER_SUCCESS = 200,
	CHARACTER_FAIL,
	CHARACTER_AUTHKEY_FAIL,
	CHARACTER_TOO_LONG_NAME,
	CHARACTER_TOO_SHORT_NAME,
	CHARACTER_SAMENAME_EXIST,
	CHARACTER_COUNT_OVER,
	CHARACTER_NAME_NOT_EXIST,
	CHARACTER_CREATE_VALUE_FAIL,
	CHARACTER_USER_EXIST,
	CHARACTER_USER_EXIST_IN_GAME_SERVER,
	CHARACTER_USER_ITEM_CREATE_FAIL,
	CHARACTER_USER_SKILL_CREATE_FAIL,
	CHARACTER_USER_QUICK_SLOT_CREATE_FAIL,
	CHARACTER_DB_QUERY_FAIL,
	CHARACTER_WRONG_SERVER_FARM_SELECTED,
	CHARACTER_USER_BLOCK,
	CHARACTER_BLOCK_STRING_INCLUDED,
	CHARACTER_TEMPORARY_BLOCK,
	CHARACTER_AUTHKEY_MISMATCH,
	CHARACTER_AUTHKEY_CREATE_FAIL,
	CHARACTER_AUTHKEY_NOT_FOUND,
	CHARACTER_DELETE_GUILD_LEADER_FAIL,
	CHARACTER_DELETE_BUDOKAI_REGISTER_FAIL,
	CHARACTER_SERVER_LOCKED,
	CHARACTER_DISCONNECTED_FORCEDLY,
	CHARACTER_DISCONNECTED_TEMPORARILY,
	CHARACTER_RACE_NOT_ALLOWED,
	CHARACTER_COMMON_CANT_DO_THAT_FOR_SOME_REASON,
	CHARACTER_USER_SHOULD_WAIT_FOR_CONNECT,
	CHARACTER_SERVER_IS_UNDER_CONSTRUCTION,
	CHARACTER_DELETE_CHAR_FAIL,
	// COMMUNITY SERVER
	CHAT_SUCCESS = 300,
	COMMUNITY_FAIL,
	COMMUNITY_INVALID_AUTH_KEY,
	COMMUNITY_ALREADY_IN_SERVER,
	COMMUNITY_DISCONNECTED_FORCEDLY,
	COMMUNITY_DISCONNECTED_TEMPORARILY,
	COMMUNITY_COMMON_SYSTEM_ERROR,
	COMMUNITY_COMMON_NO_SUCH_A_TARGET,
	COMMUNITY_COMMON_TARGET_IS_NOT_YOUR_GUILD_MEMBER,
	COMMUNITY_COMMON_NEED_MORE_TIME_TO_DO_IT,
	COMMUNITY_PARTY_LEADER_DOESNT_EXIST,
	COMMUNITY_PARTY_SAME_PARTYID_ALREADY_EXIST,
	COMMUNITY_PARTY_NO_SUCH_A_PARTY,
	COMMUNITY_PARTY_MEMBER_ALREADY_EXIST,
	COMMUNITY_PARTY_NO_SUCH_A_MEMBER,
	COMMUNITY_GUILD_CREATOR_NOT_FOUND,
	COMMUNITY_GUILD_GUILD_MEMBER_CANT_HAVE_MORE_GUILD,
	COMMUNITY_GUILD_NEED_MORE_PARTY_MEMBER_FOR_NEW_GUILD,
	COMMUNITY_GUILD_YOU_DONT_BELONG_TO_GUILD,
	COMMUNITY_GUILD_YOU_ARE_NOT_GUILD_MASTER,
	COMMUNITY_GUILD_GUILD_IS_BEING_DISBANDED,
	COMMUNITY_GUILD_GUILD_IS_NOT_BEING_DISBANDED,
	COMMUNITY_GUILD_YOU_DONT_HAVE_RIGHT_TO_INVITE,
	COMMUNITY_GUILD_TARGET_IS_ALREADY_IN_A_GUILD,
	COMMUNITY_GUILD_TARGET_ALREADY_HAS_INVITATION,
	COMMUNITY_GUILD_YOU_HAVE_NO_INVITATION,
	COMMUNITY_COMMON_NO_SUCH_A_GUILD,
	COMMUNITY_GUILD_YOU_ARE_ALREADY_IN_A_GUILD,
	COMMUNITY_GUILD_MAX_NUMBER_OF_MEMBERS,
	COMMUNITY_GUILD_LEADER_CANT_LEAVE,
	COMMUNITY_GUILD_YOU_DONT_HAVE_RIGHT_TO_KICK_OUT,
	COMMUNITY_GUILD_CANT_KICK_YOURSELF_OUT,
	COMMUNITY_GUILD_TRIED_TO_APPOINT_YOURSELF,
	COMMUNITY_GUILD_TARGET_IS_ALREADY_SECOND_MASTER,
	COMMUNITY_GUILD_MAX_NUMBER_OF_SECOND_MASTERS,
	COMMUNITY_GUILD_TARGET_IS_NOT_SECOND_MASTER,
	COMMUNITY_GUILD_FUNCTION_NOT_FOUND,
	COMMUNITY_GUILD_BANK_USING_NOW,
	COMMUNITY_FRIEND_CHAR_NOT_FOUND,
	COMMUNITY_FRIEND_CHAR_ARLEADY_ADDED,
	COMMUNITY_FRIEND_MAX_COUNT_OVER,
	COMMUNITY_FRIEND_CHAR_EXIST,
	COMMUNITY_FRIEND_BLACK_CHAR_EXIST,
	COMMUNITY_FRIEND_SELF_FAIL,
	COMMUNITY_RANK_BATTLE_LIST_NOT_FOUND,
	COMMUNITY_GUILD_BANK_QUERY,
	COMMUNITY_GUILD_BANK_CLOSED,
	COMMUNITY_GUILD_KICKOUT,
	COMMUNITY_GUILD_LEAVE,
	COMMUNITY_TMQ_CHAR_NOT_FOUND,
	COMMUNITY_TMQ_DATA_NOT_FOUND,
	COMMUNITY_DOJO_MAKE_FAIL,
	COMMUNITY_DOJO_DEL_FAIL,
	COMMUNITY_DOJO_FIND_FAIL,
	COMMUNITY_DOJO_SCRAMBLE_ARLEADY_HAVE,
	COMMUNITY_DOJO_SCRAMBLE_WAIT,
	COMMUNITY_DOJO_SCRAMBLE_REJECT_FAIL_FOR_BANK_USE,
	COMMUNITY_DOJO_SCRAMBLE_REJECT_FAIL_SECOND,
	COMMUNITY_DOJO_SEED_ALREADY_SETTING,
	COMMUNITY_DOJO_SEED_NAME_FAIL,
	COMMUNITY_DOJO_SEED_NOT_SET,
	COMMUNITY_DOJO_NON_EXISTING_FUNCTION,
	COMMUNITY_DOJO_YOU_ARE_NOT_OWNNER,
	COMMUNITY_GUILD_FIND_FAIL,
	COMMUNITY_DOJO_BANK_ZENNY_NOT_ENOUGH,
	COMMUNITY_GUILD_DISBANDE_FAIL_FOR_DOJO,
	COMMUNITY_DOJO_SCRAMBLE_FAIL_FOR_BEING_DISBANDED,
	// GAME SERVER
	GAME_SUCCESS = 500,				// 게임서버 상의 모든 성공
	GAME_FAIL,						// 게임서버 상의 전반적인 실패

	GAME_DB_CHAR_DATA_LOAD_FAIL,	// 캐릭터 데이타 로딩에 실패하였습니다.
	GAME_DB_CHAR_NOT_FOUND,			// 해당하는 캐릭타 데이타가 존재하지 않습니다.

	GAME_INVALID_AUTH_KEY,			// 인증키 인증이 실패하였습니다.
	GAME_USER_EXIST,				// 이미 접속중입니다.
	GAME_SERVER_LOCKED,				// 현재 서버가 잠긴 상태여서 접속할 수 없습니다.
	GAME_WRONG_SERVER_CHANNEL_HAS_BEEN_SPECIFIED,			// 잘못된 서버 채널을 선택하였습니다.

	GAME_CHAR_IS_WRONG_STATE,		// 지금은 할 수 없습니다
	GAME_INPUT_PARAMETER_WRONG,		// 올바르지 않은 입력 입니다.

	GAME_TARGET_IS_WRONG_STATE,		// 대상이 적절한 상태가 아닙니다.
	GAME_TARGET_NOT_FOUND,			// 대상을 찾을 수 없습니다.
	GAME_TARGET_TOO_FAR,			// 대상과의 거리가 너무 멉니다.
	GAME_TARGET_TOO_CLOSE,			// 대상과의 거리가 너무 가깝습니다.
	GAME_TARGET_HAS_NOT_FUNCTION,	// 대상은 해당 기능을 지원하지 않습니다.

	GAME_DISCONNECTED_FORCEDLY,							// 제재로 인해 강제로 접속이 종료되었습니다.
	GAME_DISCONNECTED_TEMPORARILY,						// 운영자에 의하여 일시적으로 로그아웃 처리가 되었습니다.

	GAME_COMMON_YOU_ARE_NOT_IN_A_PARTY,					// 파티에 속해 있지 않습니다.
	GAME_COMMON_YOU_ARE_NOT_A_PARTY_LEADER,				// 파티 리더가 아닙니다.
	GAME_COMMON_ZENNY_CANT_BE_USED_RIGHT_NOW,			// 일시적으로 제니를 사용할 수 없는 상황입니다. 잠시 후 다시 시도하세요.
	GAME_COMMON_CANT_DO_THAT_FOR_SOME_REASON,			// 시스템 문제로 작업을 처리할 수 없습니다.
	GAME_COMMON_NON_EXISTING_PET_SPECIFIED,				// 존재하지 않는 펫을 지정하였습니다.

	GAME_COMMON_CANT_DO_THAT_IN_SPAWNING_STATE,				// 월드 진입 도중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_STANDING_STATE,				// 서 있을 때에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_STANDING_JUMPING_STATE,		// 제자리 점프 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_JUMPING_STATE,				// 점프 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_NON_JUMPING_STATE,			// 점프 중이 아닐 때에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_SITTING_STATE,				// 앉아 있을 때에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_FAINTING_STATE,				// 실신한 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_CAMPING_STATE,				// 캠핑 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_LEAVING_STATE,				// 리빙 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_MOVING_STATE,				// 이동 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_MOVING_JUMPING_STATE,		// 점프 이동 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_DESTMOVING_STATE,			// 이동 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_FOLLOWING_STATE,			// 이동 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_FALLING_STATE,				// 떨어지는 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_DASH_STATE,					// 대쉬 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_TELEPORTING_STATE,			// 텔레포트 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_SLIDING_STATE,				// 슬라이딩 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_KNOCKDOWN_STATE,			// 넉다운 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_FOCUSING_STATE,				// 집중 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_CASTING_STATE,				// 스킬 시전 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_AFFECTING_STATE,			// 스킬 시전 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_KEEPING_EFFECT_STATE,		// 효과 유지 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_CASTING_ITEM_STATE,			// 아이템 사용 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_STUNNED_STATE,				// 기절 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_SLEEPING_STATE,				// 수면 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_PARALYZED_STATE,			// 마비 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_HTB_STATE,					// HTB 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_SANDBAG_STATE,				// HTB 스킬에 걸린 상태에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_CHARGING_STATE,				// 기를 모으는 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_BLOCKING_STATE,				// Block 모드에서는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_DESPAWNING_STATE,			// 월드에서 벗어나는 도중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_PRIVATESHOP_STATE,			// 개인 상점을 열고 있을 때에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_DIRECT_PLAY_STATE,			// 연출 중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_OPERATING_STATE,			// 오브젝트 동작중에는 사용할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_RIDEON_STATE,				// 탈것을 탄상태에서는 할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_TURNING_STATE,				// 턴상태에서는 할 수 없는 명령입니다.

	GAME_COMMON_CANT_DO_THAT_IN_INVISIBLE_CONDITION,		// 투명 상태에서는 사용 할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_HIDING_KI_CONDITION,		// 기 숨기기 상태에서는 사용 할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_TRANSPARENT_CONDITION,		// GM 투명 상태에서는 사용 할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_TERROR_CONDITION,			// 공포에 걸린 상태에서는 사용 할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_AFTEREFFECT_CONDITION,		// 후유증 상태에서는 사용 할 수 없는 명령입니다.
	GAME_COMMON_CANT_DO_THAT_IN_CHARGING_BLOCKED_CONDITION,		// 기 모으기가 불가능한 상태입니다.

	GAME_GAMERULE_REG_CANT_PLAY_IN_FREEBATTLE,				// 프리배틀 중에는 할 수 없습니다.
	GAME_GAMERULE_REG_CANT_PLAY_IN_RANKBATTLE,				// 랭크배틀 중에는 할 수 없습니다.
	GAME_GAMERULE_REG_CANT_PLAY_IN_TMQ,						// 타임머신 퀘스트 중에는 할 수 없습니다.
	GAME_GAMERULE_REG_CANT_PLAY_IN_SUMMON_DRAGONBALL,		// 드래곤볼 소환 중에는 할 수 없습니다.
	GAME_GAMERULE_REG_CANT_PLAY_IN_PRIVATE_SHOP,			// 개인상정 중에는 할 수 없습니다.
	GAME_GAMERULE_REG_CANT_PLAY_IN_BUDOKAI,					// 천하제일무도회 중에는 할 수 없습니다.

	GAME_GAMERULE_REG_ALREADY_JOINED_IN_FREEBATTLE,			// 이미 프리배틀 참가 중입니다.
	GAME_GAMERULE_REG_ALREADY_JOINED_IN_RANKBATTLE,			// 이미 랭크배틀 참가 중입니다.
	GAME_GAMERULE_REG_ALREADY_JOINED_IN_TMQ,				// 이미 타임머신 퀘스트 참가 중입니다.
	GAME_GAMERULE_REG_ALREADY_SUMMON_DRAGONBALL,			// 이미 드래곤볼 소환 중입니다.
	GAME_GAMERULE_REG_ALREADY_OPENED_PRIVATE_SHOP,			// 이미 개인상점 개설 중입니다.
	GAME_GAMERULE_REG_ALREADY_JOINED_BUDOKAI,				// 이미 천하제일무도회 참가 중입니다.

	GAME_CONTENTS_LOCK,										// 현재 잠겨있는 컨텐츠입니다.
	GAME_CONTENTS_CAN_NOT_PLAY_IN_BUDOKAI_REGISTER_STATE,	// 천하제일무도회 등록기간 중에는 이용할 수 없습니다.

	GAME_WORLD_CAN_NOT_CREATE_DYNAMIC_WORLD,			// 월드를 생성할 수 없습니다.
	GAME_WORLD_NOW_CREATING,							// 잠시 후 다시 시도하십시오.
	GAME_WORLD_ALREADY_WORLD_ENTERED,					// 이미 월드에 진입해 있습니다.
	GAME_WORLD_CANT_ENTER_WORLD,						// 진입할 수 있는 월드가 없습니다.
	GAME_WORLD_ALREADY_WORLD_AREA_ENTERED,				// 이미 월드 영역에 진입해 있습니다.
	GAME_WORLD_CANT_FIND_WORLD_AREA,					// 진입할 월드영역을 찾을 수 없습니다.
	GAME_WORLD_CANT_ENTER_WORLD_AREA,					// 진입할 수 있는월드영역이 없습니다.

	GAME_SHORTCUT_KEY_ARLEADY_FOUND,					// 같은 키가 이미 지정되어 있습니다.
	GAME_SHORTCUT_KEY_DEL_NOT_FOUND,					// 삭제하려는 키가 없습니다.
	GAME_SHORTCUT_KEY_MODIFY_NOT_FOUND,					// 수정하려는 키가 없습니다.

	GAME_COMMON_CANT_DO_THAT_NOT_ALLOWED_TARGET,		// 명령 수행이 불가능한 유져 입니다.

	GAME_COMMON_CANT_FIND_OBJECT,						// 해당 오브젝트를 찾을 수 없습니다.

	GAME_CHAR_WRONG_REVIVAL_METHOD,						// 잘못된 부활 방법입니다.
	GAME_CANNOT_CONNECT_DUE_TO_TIMEOUT,					// 타임아웃되어 접속할 수 없습니다.
	GAME_CANNOT_CONNECT_TARGET_CHANNEL_FULL,			// 이동하려는 채널에 여유 공간이 없습니다.
	GAME_CANNOT_CONNECT_DUE_TO_INVAlID_CHARACTER,		// 정상적인 캐릭터가 아닙니다.
	GAME_TARGET_HAS_DIFFERENT_JOB,						// 대상의 직업이 올바르지 않습니다.

	GAME_GMT_NOT_ENOUGH_RESET_POINT,					// GMT 재설정 포인트가 부족합니다.

	//-----------------------------------------------------------------
	GAME_SKILL_NOT_ACTIVE_TYPE = 600,		// Active 타입의 스킬이 아닙니다.
	GAME_SKILL_YOU_DONT_HAVE_THE_SKILL,		// 가지고 있지 않은 스킬입니다.
	GAME_SKILL_NOT_EXISTING_SKILL,			// 존재하지 않는 스킬입니다.
	GAME_SKILL_CANT_CAST_NOW,				// 현재 스킬을 시전할 수 있는 상태가 아닙니다.
	GAME_SKILL_NO_TARGET_APPOINTED,				// 대상을 선택하셔야 합니다.
	GAME_SKILL_INVALID_TARGET_APPOINTED,		// 현재 타겟에 스킬을 사용할 수 없습니다.
	GAME_SKILL_NOT_READY_TO_BE_CAST,		// 스킬의 쿨타임을 기다려야 합니다.
	GAME_SKILL_NOT_ENOUGH_LP,				// LP가 충분하지 않습니다.
	GAME_SKILL_NOT_ENOUGH_EP,				// EP가 충분하지 않습니다.
	GAME_SKILL_NOT_ENOUGH_RP_BALL,						// RP 구슬이 충분하지 않습니다.

	GAME_SKILL_NO_REQUIRED_ITEM,			// 스킬을 사용하기 위해 필요한 아이템을 가지고 있지 않습니다.
	GAME_SKILL_TOO_MANY_LP_TO_USE_SKILL,				// LP가 50% 이하일 때에만 이 스킬을 사용할 수 있습니다.
	GAME_SKILL_TARGET_IS_NOT_KNOCKED_DOWN,				// 타겟이 knock down 상태가 아닙니다.
	GAME_SKILL_RESISTED,								// 스킬을 저항했습니다.
	GAME_SKILL_TRIED_TO_LEARN_AN_EXISTING_SKILL,		// 이미 가지고 있는 스킬은 배울 수 없습니다.
	GAME_SKILL_TRIED_TO_LEARN_WRONG_CLASS_SKILL,		// 직업에 맞지 않는 스킬은 배울 수 없습니다.
	GAME_SKILL_TOO_HIGH_LEVEL_TO_TRAIN,					// 레벨이 낮아서 아직 스킬을 배울 수 없습니다.
	GAME_SKILL_NOT_ENOUGH_ZENNY,						// Zenny가 모자라 스킬을 배울 수 없습니다.
	GAME_SKILL_NO_EMPTY_SKILL_SLOT,						// 빈 스킬 슬롯이 없습니다.
	GAME_SKILL_YOU_HAVE_NO_LOWER_LEVEL_SKILL,			// 업그레이드를 위해서는 선택한 스킬보다 한 단계 낮은 스킬을 가지고 있어야 합니다.

	GAME_SKILL_ALREADY_MASTERED_SKILL,					// 이미 궁극의 스킬을 습득한 상태입니다.
	GAME_SKILL_NO_PREREQUISITE_SKILLS_YOU_HAVE,			// 스킬 습득을 위해 이미 배우고 있어야 할 스킬을 가지고 있지 않습니다.
	GAME_SKILL_UPGRADE_ONLY_SKILL,		// 업그레이드로만 얻을 수 있는 스킬입니다.
	GAME_SKILL_SHOULD_BE_GAINED_BY_YOURSELF,			// 스스로 배워야 하는 스킬입니다.
	GAME_SKILL_CANT_BE_GAINED_BY_YOURSELF,				// 스스로 배울 수 없는 스킬입니다.
	GAME_SKILL_CANT_USE_FOR_SOME_REASON,		// 시스템 문제로 스킬을 사용할 수 없습니다.
	GAME_SKILL_TARGET_IS_NOT_IN_FRONT_SIDE,		// 타겟이 당신 앞에 위치해야 합니다.
	GAME_SKILL_YOU_ARE_NOT_IN_BACKSIDE_OF_TARGET,		// 대상의 뒤에서만 스킬을 사용할 수 있습니다.
	GAME_SKILL_TARGET_IS_IN_FAINT,		// 타겟이 실신한 상태입니다.
	GAME_SKILL_CAN_BE_CAST_ONLY_ON_PLAYER,		// 플레이어에게만 사용할 수 있는 스킬입니다.

	GAME_SKILL_TARGET_IS_NOT_FAINTING,					// 타겟이 실신한 상태가 아닙니다.
	GAME_SKILL_NOT_BATTLE_AVAILABLE_LOCATION,			// 스킬 사용자와 대상 모두 전투가 가능한 지역에 위치해야 합니다.
	GAME_SKILL_CASTING_CANCELED_BY_DAMAGE,				// 공격을 받아 스킬 시전이 취소되었습니다.
	GAME_SKILL_CANT_SET_THAT_RP_BONUS_IN_SKILL,			// 지정한 스킬에서는 설정할 수 없는 RP 보너스 타입입니다.
	GAME_SKILL_CANT_USE_THAT_RP_BONUS_IN_SKILL,			// 지정한 스킬에서는 사용할 수 없는 RP 보너스 타입입니다.
	GAME_SKILL_NO_BUFF_TO_DROP_FOUND,					// 해제될 수 있는 버프를 선택하여야 합니다.
	GAME_SKILL_ALREADY_TRANSFORMED,						// 현재의 변신 상태가 해제되어야 새로운 변신이 적용될 수 있습니다.
	GAME_SKILL_NOT_TRANSFORMED,							// 변신 상태가 아닙니다.
	GAME_SKILL_CANT_USE_SKILL_WHEN_SUPER_SAIYAN,		// 초사이어인 상태에서는 사용할 수 없는 스킬입니다.
	GAME_SKILL_CANT_USE_SKILL_WHEN_PURE_MAJIN,			// 순수 마인 상태에서는 사용할 수 없는 스킬입니다.

	GAME_SKILL_CANT_USE_SKILL_WHEN_GREAT_NAMEK,			// 거대 나메크 상태에서는 사용할 수 없는 스킬입니다.
	GAME_SKILL_CANT_USE_SKILL_WHEN_KAIOKEN,				// 계왕권 상태에서는 사용할 수 없는 스킬입니다.
	GAME_SKILL_CANT_USE_SKILL_WHEN_SPINNING_ATTACK,		// 회전 공격 상태에서는 사용할 수 없는 스킬입니다.
	GAME_SKILL_CANT_USE_SKILL_WHEN_VEHICLE,				// 탈 것 상태에서는 사용할 수 없는 스킬입니다.
	GAME_SKILL_CANT_USE_SKILL_WHEN_NOT_TRANSFORMED,		// 변신하지 않은 상태에서는 사용할 수 없는 스킬입니다.
	GAME_SKILL_NOT_ENOUGH_SP_POINT,						// SP POINT 가 부족합니다.
	GAME_SKILL_ERASE_FAIL,								// 스킬을 지우다가 실패했습니다.
	GAME_BLOCK_ATTACK_NOW,								// 현재는 제재되어 사용할 수 없습니다. 
	GAME_SKILL_HAVE_UPGRADED_SKILL,						// 스킬중 업그레이드 된 스킬을 습득한 상태입니다.
	GAME_SKILL_CANT_BE_CAST_ON_YOURSELF,				// 자신을 선택하고 사용할 수 없는 스킬입니다.

	GAME_SKILL_CANT_USE_HTB_WHEN_TRANSFORMED,			// 변신 중에는 HTB를 사용할 수 없습니다.
	GAME_SKILL_CASTING_CANCELED_BY_TARGET_NEW_STATE,	// 651 // 대상의 상태가 바뀌어 시전이 취소되었습니다.
	GAME_SKILL_CASTING_CANCELED_OBJECT_OCCLUSION,       // 캐스팅중에 오브젝트에 가려서 취소되었습니다.
	GAME_SKILL_CANT_USE_VEHICLE_WHEN_TRANSFORMED,		// 변신 중에는 탈 것을 이용할 수 없습니다.
	GAME_SKILL_CANT_USE_WHEN_TRANSFORMED,				// 변신 중에는 이용할 수 없습니다.
	//-----------------------------------------------------------------
	GAME_CHAR_ONLY_ADULT_CAN_CHANGE_CLASS = 700,				// 어른 상태에서만 전직을 할 수 있습니다.
	GAME_CHAR_NO_AUTHORITY_FOR_CHANGING_CLASS,					// 전직할 수 있는 자격을 갖추고 있지 않습니다.
	GAME_GM_CANT_DO_THAT_WHEN_YOU_ARE_HIDING,					// 702 // 투명 상태에서는 쓸 수 없는 명령입니다.
	//-----------------------------------------------------------------
	GAME_ITEM_NUM_NULL = 800,		// 아이템 번호가 잘못되었습니다.
	GAME_ITEM_POSITION_FAIL,		// 아이템 위치값이 잘못되었습니다.	
	GAME_ITEM_OWNER_NOT_SAME,		// 아이템 소유주가 잘못되었습니다.	
	GAME_ITEM_NOT_SAME,             // 아이템이 잘못 되었습니다.
	GAME_ITEM_OWNER_NULL,			// 아이템 소유주가 없습니다.
	GAME_ITEM_STACK_FAIL,           // 아이템 스택이 잘못 되었습니다.
	GAME_ITEM_NOT_FOUND,			// 아이템을 찾을 수 없습니다.
	GAME_NEEDITEM_NOT_FOUND,		// 아이템 구매시 필요한 아이템을 Table에서 찾을 수 없습니다. [7/17/2008 SGpro]
	GAME_NEEDITEM_NOT_FOUND_INVANTORY,	// 아이템 구매시 필요한 교환아이템이 없습니다. [7/17/2008 SGpro]
	GAME_ITEM_BAG_IS_NOT_EMPTY,		// 가방을 비워야 이동이 가능합니다.

	GAME_ITEM_ALREADY_EXIST,        // 아이템이 존재하므로 이동이 불가 합니다.
	GAME_ITEM_MAX_COUNT_OVER,       // 아이템 갯수를 초과하였습니다.
	GAME_ITEM_STACK_FULL,           // 스택이 가득찼습니다.
	GAME_EQUIP_SLOT_NOT_EMPTY,		// 장비 슬롯이 비어있지 않습니다.
	GAME_ITEM_CLASS_FAIL,			// 아이템 착용 가능 클래스타입이 아닙니다.
	GAME_ITEM_NEED_MORE_LEVEL,		// 레벨 부족으로 아이템을 착용할 수 없습니다.
	GAME_ITEM_NEED_MORE_PARAMETER,  // 아이템 착용가능 능력치가 부족합니다.
	GAME_ITEM_MAX_WATT_OVER,		// Scouter 메인파츠의 Max Watt수를 초과하였습니다. 
	GAME_ITEM_INVEN_FULL,			// 가방이 가득찼습니다.
	GAME_ITEM_LOOTING,				// 아이템을 줍고 있습니다.

	GAME_ITEM_UNIDENTIFY,	        // 아이템 확인이 안되어있습니다.
	GAME_ITEM_UNIDENTIFY_FAIL,		// 아이템 확인 실패
	GAME_LOOTING_FAIL,			// 아이템 소유권이 없습니다.
	GAME_ZENNY_NOT_ENOUGH,			// 돈이 부족합니다.	
	GAME_ITEM_IS_LOCK,				// 아이템이 잠김 상태입니다.
	GAME_CHARM_POINT_IS_LOCKED,		// 이전의 부적 포인트에 대한 처리가 완료되지 않았습니다. 잠시 후에 다시 시도하여 주십시오.
	GAME_ZENNY_IS_LOCK,				// 제니의 잠김 상태입니다.
	GAME_REPAIR_VALUE_FAIL,			// 수리 가능한 아이템이 아닙니다.
	GAME_REPAIR_NOT_FOUND,			// 수리 가능한 아이템이 없습니다.
	GAME_ITEM_YOU_ARE_USING_AN_ITEM,				// 아이템을 사용하는 중입니다.

	GAME_ITEM_NOT_FOR_USE,			// 사용할 수 있는 아이템이 아닙니다.
	GAME_ITEM_NOT_BATTLE_AVAILABLE_LOCATION,		// 아이템 사용자와 대상 모두 전투가 가능한 지역에 위치해야 합니다.
	GAME_ITEM_CANT_USE_FOR_SOME_REASON,		// 시스템 문제로 아이템을 사용할 수 없습니다.
	GAME_ITEM_NOT_READY_TO_BE_USED,		// 아이템의 쿨타임을 기다려야 합니다.
	GAME_ITEM_TOO_LOW_LEVEL_TO_USE_ITEM,		// 레벨이 모자라 아이템을 사용할 수 없습니다.
	GAME_ITEM_NOT_ENOUGH_LP,		// LP가 충분하지 않습니다.
	GAME_ITEM_NOT_ENOUGH_EP,		// EP가 충분하지 않습니다.
	GAME_ITEM_NOT_ENOUGH_RP_BALL,						// RP 구슬이 충분하지 않습니다.
	GAME_ITEM_CASTING_CANCELED,							// 아이템 사용이 취소되었습니다.
	GAME_ITEM_CANT_USE_NOW,		// 현재 아이템을 사용할 수 있는 상태가 아닙니다.

	GAME_ITEM_DUR_ZERO,			// 내구도가 제로입니다.
	GAME_SCOUTER_MAX_OVER,		// 측정치가 오버 되어 스카우터 메인파츠가 고장났습니다.
	GAME_ITEM_NOT_ENOUGH,		// 아이템이 만족하지 않습니다.
	GAME_ITEM_UPGRADE_NO_SUBJECT_ITEM,			// 업그레이드할 장비 아이템을 넣어 주십시오.
	GAME_ITEM_UPGRADE_NO_HOIPOI_STONE,			// 조합을 하기 위해서는 호이포이스톤이 필요합니다.
	GAME_ITEM_UPGRADE_WRONG_ITEM_TYPE,			// 무기나 방어구만 업그레이드를 할 수 있습니다.
	GAME_ITEM_UPGRADE_ALREADY_MAX_GRADE,		// 더 이상 업그레이드를 할 수 없는 아이템입니다.
	GAME_ITEM_UPGRADE_FAIL,     // 아이템 업그레이드 실패
	GAME_ITEM_UPGRADE_FAIL_AND_DEL,     // 업그레이드 실패로 아이템이 파괴되었습니다.
	GAME_BANK_NOT_READY,		// 창고가 아직 열려있지 않습니다.

	GAME_BANK_ALREADY_EXIST,		// 창고가 이미 존재합니다.
	GAME_SCOUTER_PARTS_NOT_FOUND,	// 해당 스카우터 파츠를 찾지 못했습니다.
	GAME_SCOUTER_JAMMING,			// 전파방해로 인해 표시할 수 없습니다. 
	GAME_SCOUTER_TARGET_FAIL,	 // 표시 대상이 부적절합니다.
	GAME_CHAR_LEVEL_FAIL,		// 레벨이 맞지 않습니다.
	GAME_CHAR_CLASS_FAIL,		// 해당클래스가 맞지 않습니다.
	GAME_CHAR_RACE_FAIL,		// 해당 종족이 맞지 않습니다.
	GAME_ZENNY_OVER,			// 금액이 오버되었습니다.
	GAME_QUEST_ALREADY_EXIST,	// 이미 존재하는 퀘스트입니다.
	GAME_QUEST_COUNT_OVER,		// 수행가능한 퀘스트수가 초과되었습니다.

	GAME_QUEST_NOT_EXIST,		// 존재하지 않는 퀘스트입니다.
	GAME_ITEM_CREATE_COUNT_OVER,// 한번에 생성할 수 있는 갯수를 넘었다.
	GAME_ITEM_DELETE_COUNT_OVER,// 한번에 삭제할 수 있는 갯수를 넘었다.
	GAME_GM_LEVEL_NOT_FOUND,	// GM Level 이 없음
	GAME_GM_PUNISH_NOT_FOUND,	// Punish type error
	GAME_SCOUTER_BODY_IS_NOT_EMPTY, // 스카우터 파츠를 비워야 이동가능합니다.
	GAME_SCOUTER_PARTS_LEVEL_FAIL,	// 스카우터 파츠 레벨이 맞지 않습니다.
	GAME_TRADE_TARGET_WRONG_STATE,		// 상대방이 현재 트레이드를 할 수 없는 상태입니다.
	GAME_TRADE_ALREADY_USE,		// 트레이드 중입니다.
	GAME_TRADE_DENY_USE,		// 트레이드 거절 중입니다.

	GAME_TRADE_DENY,			// 트레이드를 거절하였습니다.
	GAME_TRADE_REPLY_WAIT_OVER,
	GAME_TRADE_WRONG_STATE,		// 트레이드하기에 적절한 상태가 아닙니다.
	GAME_TRADE_ITEM_INVALID,	// 트레이드 불가능한 아이템 입니다.
	GAME_TRADE_ALREADY_CLOSE,	// 트레이드가 이미 잠김상태 입니다.
	GAME_TRADE_ALREADY_OPEN,	// 트레이드가 이미 열림상태 입니다.
	GAME_TRADE_CHANGED_STATE,	// 트레이드 물품 정보가 바뀌었습니다.
	GAME_ITEM_NOT_GO_THERE,		// 옮길수 없는 위치입니다.
	GAME_DRAGONBALL_OBJECT_ARLEADY_USED, // 제단이 사용 중입니다.
	GAME_DRAGONBALL_NOT_FOUND,	 // 드래곤볼을 찾을수 없습니다.

	GAME_DRAGONBALL_REWARD_NOT_FOUND,   // 드래곤볼 보상을 찾을 수 없습니다.
	GAME_DRAGONBALL_TIME_OVER,	// 사용시간이 만료되었습니다.
	GAME_DRAGONBALL_SAME_EXIST,		// 동일 한 드래곤볼이 있습니다.
	GAME_QUSET_ITEM_CREATE_COUNT_OVER,// 퀘스트 인벤토리에서 동일한 아이템을 생성할 수 없습니다.
	GAME_ITEM_CANT_BE_USED_ON_YOURSELF,					// 자신을 선택하고 사용할 수 없는 아이템입니다.
	GAME_ITEM_TYPE_NOT_MISMATCHED,	// 아이템 타입이 맞지 않습니다.
	GAME_ITEM_RECIPE_ALREADY_EXIST,	// 같은 레시피가 이미 존재 합니다.	
	GAME_ITEM_RECIPE_NOT_FOUND,		// 해당 레시피가 존재 하지 않습니다 .	
	GAME_ITEM_RECIPE_REGISTER_PROFESSION,	// 해당 아이템 믹스 직업을 먼저 선택하여야 합니다.
	GAME_ITEM_RECIPE_LEVEL_MISMATCHED,	// 해당 아이템 레시피레벨이 맞지 않습니다.
	GAME_ITEM_RECIPE_TYPE_MISMATCHED,	// 해당 아이템 레시피 타입이 맞지 않습니다.
	GAME_ITEM_RECIPE_REGISTER_FAIL,		// 아이템 레시피 등록에 실패했습니다.
	GAME_ZENNY_LOOTING,					// 제니를 줍고 있습니다.
	GAME_ITEM_RECIPE_REGISTER_PROFESSION_FAIL,	// 아이템 믹스 직업이 잘못되었습니다.
	GAME_SCOUTER_MAIN_PARTS_NOT_FOUND,	// 스카우터 메인 파츠를 찾지 못했습니다.
	GAME_ITEM_HOIPOIMIX_FARE_NOT_SET,	// 호이포이머신사용료가 세팅되어있지 않습니다. 
	GAME_ITEM_HOIPOIMIX_FARE_CAN_NOT_SET,	// 호이포이머신사용료 세팅은 캐쉬머신만 가능합니다. 
	GAME_ITEM_HOIPOIMIX_FARE_RATE_FAIL,	// 호이포이머신사용료가 범위가 초과 되었습니다.
	GAME_ITEM_CANNOT_BUY_NOW,			// 구매할 수 있는 아이템이 아닙니다.
	// GAME GM TOOL
	GAME_GM_TOOL_SUCCESS = 900,			// GM TOOL 작업에 성공했습니다.
	GAME_GM_TOOL_FAIL,					// GM TOOL FAIL
	GAME_GM_TOOL_LOGIN_PASS_FAIL,		// GM TOOL LOGIN PASSWORD MISMATCHED
	GAME_GM_TOOL_ACCOUNT_EXIST,			// 이미 존재하는 아이디 입니다.
	GAME_GM_TOOL_PASS_NULL,				// 패스워드를 설정하지 않았습니다.
	GAME_GM_TOOL_GROUP_NOT_FOUND,		// 그룹이 없습니다 그룹을 먼저 만드십시요.
	GAME_GM_TOOL_GROUP_ALREADY_EXIST,	// 
	GAME_GM_TOOL_GROUP_NEED_ADMIN,
	GAME_GM_TOOL_USER_NOT_FOUND,		// 해당 계정이 존재하지 않습니다.
	GAME_GM_TOOL_LOGIN_DUPLICATE,		// 중복 로그인
	GAME_GM_TOOL_CHARACTER_IS_NOT_KICK,	// 킥 상태가 아니다.
	GAME_GM_TOOL_CHARACTER_EXIST,		// 캐릭터가 존재합니다.
	GAME_GM_TOOL_INVALID_TOOL_VERSION,	// 툴 버젼이 맞지 않습니다.
	GAME_GM_TOOL_INVALID_IP_ADDRESS,	// 인가되지 않은 IP입니다.
	GAME_GM_TOOL_NOTICE_OVER,			// 공지사항 최대갯수를 초과했습니다.
	GAME_GM_TOOL_GUILD_NOT_FOUND,		// 길드를 찾지 못했습니다.
	GAME_GM_TOOL_CHARACTER_NOT_EXIST,	// 캐릭터가 존재하지 않습니다.
	GAME_GM_TOOL_SERVER_CANT_BE_TURNED_ON_BY_GM_TOOL,		// GM Tool로 실행할 수 없는 서버입니다.
	GAME_GM_TOOL_SERVER_CANT_BE_TURNED_OFF_BY_GM_TOOL,		// GM Tool로 종료할 수 없는 서버입니다.
	GAME_GM_TOOL_WRONG_SERVER_TO_TURN_ON,					// 실행할 서버를 잘못 지정하였습니다.
	GAME_GM_TOOL_WRONG_SERVER_TO_TURN_OFF,					// 종료할 서버를 잘못 지정하였습니다.
	GAME_GM_TOOL_SERVERFARMID_INVALID,						// ServerFarmID가 Invalid입니다.
	GAME_GM_TOOL_AGENTSERVER_NORUN,
	GAME_GM_TOOL_RANK_BATTLE_POINT_NOT_FOUND, // 랭크 배틀 정보가 없는 캐릭터 입니다.
	GAME_GM_TOOL_ACCOUNT_NOT_EXIST,							// 존재하지 않는 아이디 입니다.

	//-----------------------------------------------------------------
	GAME_SKILL_SLOT_FAIL = 1000,
	GAME_SKILL_ID_NULL,
	GAME_SKILL_OWNER_NULL,
	GAME_SKILL_SAME_EXIST,
	GAME_SKILL_NOT_FOUND,
	GAME_ITEM_NOT_PROPER_PLACE_TO_USE,						// 아이템을 사용하기에 적절한 장소가 아닙니다.
	GAME_ITEM_YOU_HAVE_NO_RELATED_QUEST_TO_USE,				// 아이템과 관련된 퀘스트를 갖고 있지 않습니다.
	//-----------------------------------------------------------------
	GAME_SHOP_NOT_FOUND = 1100,
	GAME_SHOP_SO_FAR,
	GAME_SHOP_NOT_CLOSED,					// 상점이 열린상태입니다.
	GAME_SHOP_ITEM_INVALID,					// 팔수 없는 아이템 입니다.
	//-----------------------------------------------------------------
	GAME_MOVE_CANT_GO_THERE = 1200,		// 갈 수 없는 위치입니다
	GAME_WORLD_NOT_EXIST,				// 존재하지 않는 월드 입니다.
	GAME_MOVE_CANT_ALLOWED_ENTER,		// 진입이 허용되지 않습니다.
	GAME_WORLD_CANT_MOVE_AGAIN,								// 월드에 재진입 할 수 없는 상태입니다.
	//-----------------------------------------------------------------
	GAME_PARTY_ALREADY_IN_PARTY = 1300,						// 이미 파티에 속해 있습니다.
	GAME_PARTY_ANOTHER_PLAYER_IS_INVITING_YOU,				// 다른 플레이어가 이미 당신을 초대하고 있습니다.
	GAME_PARTY_ANOTHER_PARTY_IS_INVITING_YOU,				// 다른 파티가 이미 당신을 초대하고 있습니다.
	GAME_PARTY_NOT_PROPER_PARTY_NAME_LENGTH,				// 파티 이름 길이가 적절하지 않습니다.
	GAME_PARTY_PARTY_NAME_HAS_INVALID_CHARACTER,			// 파티 이름에 사용 불가능한 문자가 포함되어 있습니다.
	GAME_PARTY_NOT_CREATED_FOR_SOME_REASON,					// 시스템 문제로 파티가 생성되지 않았습니다.
	GAME_PARTY_YOU_ARE_NOT_IN_PARTY,						// 파티에 속해 있지 않습니다.
	GAME_PARTY_ONLY_ALLOWED_TO_PARTY_LEADER,				// 파티 리더만 사용할 수 있는 기능입니다.
	GAME_PARTY_NOT_AVAILABLE_OPERATION_RIGHT_NOW,			// 파티가 수행하고 있는 작업이 끝나야 가능합니다.
	GAME_PARTY_NO_SUCH_A_PLAYER,							// 존재하지 않는 플레이어입니다.

	GAME_PARTY_TARGET_ALREADY_IN_PARTY,						// 상대방이 이미 파티에 속해 있습니다.
	GAME_PARTY_TARGET_ALREADY_HAS_INVITATION,				// 상대방이 이미 파티 초대를 받은 상태입니다.
	GAME_PARTY_NO_ROOM_FOR_NEW_MEMBER,						// 더 이상 멤버를 받을 수 없습니다.
	GAME_PARTY_MEMBER_IS_ALREADY_REGISTERED_TIMEQUEST,		// 상대방이 타임머신 퀘스트에 이미 등록되어 있습니다.
	GAME_PARTY_YOU_HAVE_NO_INVITATION,						// 당신은 파티로부터 초대를 받은 상태가 아닙니다.
	GAME_PARTY_INVITOR_PLAYER_IS_IN_A_PARTY,				// 당신을 초대했던 플레이어를 찾을 수 없습니다.
	GAME_PARTY_NO_SUCH_A_PARTY,								// 파티가 존재하기 않습니다.
	GAME_PARTY_COULDNT_JOIN_FOR_SOME_REASON,				// 시스템 문제로 파티에 가입할 수 없었습니다.
	GAME_PARTY_NO_SUCH_A_PLAYER_IN_THE_PARTY,				// 파티에 존재하지 않는 플레이어입니다.
	GAME_PARTY_COULDNT_KICK_OUT_FOR_SOME_REASON,			// 시스템 문제로 멤버를 강제로 탈퇴시킬 수 없었습니다.

	GAME_PARTY_CANT_KICK_OUT_HIMSELF,						// 자기 자신을 강제로 탈퇴시킬 수 없습니다.
	GAME_PARTY_YOU_ARE_ALREADY_A_LEADER,					// 이미 자신이 파티 리더입니다.
	GAME_PARTY_COULDNT_ASSIGN_A_LEADER_FOR_SOME_REASON,		// 시스템 문제로 멤버를 리더로 변경할 수 없었습니다.
	GAME_PARTY_COULDNT_BE_DONE_FOR_SOME_REASON,				// 시스템 문제로 요청이 처리될 수 없었습니다.
	GAME_PARTY_WRONG_CHARM_INVENTORY_SPECIFIED,				// 부적 인벤토리가 잘못 지정되었습니다.
	GAME_PARTY_CHARM_INVENTORY_IS_OPEN,						// 부적 인벤토리가 열려 있습니다.
	GAME_PARTY_CHARM_INVENTORY_IS_CLOSED,					// 부적 인벤토리가 닫혀 있습니다.
	GAME_PARTY_CHARM_INVENTORY_SLOT_IS_NOT_EMPTY,			// 부적 인벤토리 슬롯이 비어 있지 않은 상태입니다.
	GAME_PARTY_CHARM_INVENTORY_SLOT_IS_EMPTY,				// 부적 인벤토리 슬롯이 비어 있는 상태입니다.
	GAME_PARTY_ZENNY_IS_LOCKED_RIGHT_NOW,					// 현재 인벤토리의 제니를 조작할 수 없는 상태입니다.

	GAME_PARTY_NO_SUCH_A_VICTIM_ITEM,						// 존재하지 않는 제물 아이템입니다.
	GAME_PARTY_UNIDENTIFIED_VICTIM_ITEM,					// 제물 아이템이 감정이 되지 않은 상태입니다.
	GAME_PARTY_THE_ITEM_IS_LOCKED,							// 아이템을 움직일 수 없습니다.
	GAME_PARTY_VICTIM_ITEM_IS_NOT_YOURS,					// 당신이 등록한 제물 아이템이 아닙니다.
	GAME_PARTY_CANT_UNREGISTER_CHARM_DUE_TO_VITIM,			// 이미 등록한 제물이 있어서 부적을 다시 가져올 수 없습니다.
	GAME_PARTY_YOU_DONT_BELONG_TO_THE_PARTY,				// 당신은 파티에 속해 있지 않은 것 같습니다.
	GAME_PARTY_VICTIM_ZENNY_HASNT_CHANGED,					// 부적 제물로 등록한 제니의 양이 바뀌지 않았습니다.
	GAME_PARTY_YOU_DONT_HAVE_THAT_MUCH_ZENNY,				// 그만큼의 제니를 가지고 있지 않습니다.
	GAME_PARTY_YOU_HAVENT_REGISTERED_VICTIM_ZENNY,			// 제니를 부적 제물로 등록한 적이 없습니다.
	GAME_PARTY_TOO_MUCH_VICTIM_ZENNY_TO_UNREGISTER,			// 등록한 제니의 양보다 많은 양의 제니를 가져오려고 했습니다.

	GAME_PARTY_ONLY_LEADER_CAN_REGISTER_CHARM,				// 부적은 파티 리더만 등록할 수 있습니다.
	GAME_PARTY_ONLY_CHARM_ITEM_AVAILABLE_IN_THAT_SLOT,		// 부적 아이템만 등록할 수 있는 슬롯입니다.
	GAME_PARTY_SAME_CHARM_ALREADY_HAS_BEEN_REGISTERED,		// 이미 활성화되어 있는 부적 아이템입니다.
	GAME_PARTY_ONLY_EQUIP_ITEM_AVAILABLE_IN_THAT_SLOT,		// 장착 가능한 아이템만 등록할 수 있는 슬롯입니다.
	GAME_PARTY_CHARM_ITEM_HASNT_BEEN_REGISTERED,			// 현재 부적이 등록되어 있지 않습니다.
	GAME_PARTY_CHARM_SLOT_HAS_AN_ITEM_OF_IMPROPER_TYPE,		// 부적 슬롯에 부적이 아닌 아이템이 등록되어 있습니다.
	GAME_PARTY_CHARM_SLOT_HAS_UNKNOWN_CHARM_ITEM,			// 부적 슬롯에 알 수 없는 부적이 등록되어 있습니다.
	GAME_PARTY_ITEMS_DONT_SATISFY_THE_CONDITION,			// 제물 아이템이 부적의 조건을 만족시키지 않습니다.
	GAME_PARTY_ZENNY_DOESNT_SATISFY_THE_CONDITION,			// 제니가 부적의 조건을 만족시키지 않습니다.
	GAME_PARTY_MEMBER_DOESNT_HAVE_ENOUGH_CHARM_POINT,		// 등록한 부적 포인트보다 적은 포인트를 가진 파티원이 있습니다.

	GAME_PARTY_MEMBER_DOESNT_HAVE_ENOUGH_ZENNY,				// 등록한 제니보다 적은 제니를 가진 파티원이 있습니다.
	GAME_PARTY_MEMBER_CHARM_POINT_IS_IN_TRANSACTION,		// 부적 포인트를 사용할 수 없는 상태의 파티원이 있습니다.
	GAME_PARTY_MEMBER_ZENNY_IS_IN_TRANSACTION,				// 제니를 사용할 수 없는 상태의 파티원이 있습니다.
	GAME_PARTY_MEMBER_DOESNT_SATISFY_THE_CONDITION,			// 부적 사용 조건을 만족시키지 못한 파티원이 있습니다.
	GAME_PARTY_CHARM_BUFF_REGISTERED_ALREADY,				// 이미 등록된 부적 버프가 있습니다.
	GAME_PARTY_NO_CHARM_BUFF_REGISTERED,					// 등록된 부적 버프가 없습니다.
	GAME_PARTY_UNKNOWN_ZENNY_LOOTING_METHOD,				// 잘못된 제니 분배 방식입니다.
	GAME_PARTY_UNKNOWN_ITEM_LOOTING_METHOD,					// 잘못된 아이템 분배 방식입니다.
	GAME_PARTY_CANT_CHANGE_LOOTING_METHOD_YET,				// 다시 전리품 분배 방식을 바꿀 수 있을 때까지 시간이 필요합니다.
	GAME_PARTY_INVALID_INVENTORY_SLOT_INDEX,				// 파티 인벤토리의 아이템 위치가 잘못 지정되었습니다.

	GAME_PARTY_TOO_MANY_CONTRIBUTION_POINTS_TO_INVEST,		// 투자할 수 있는 기여도의 범위를 넘었습니다.
	GAME_PARTY_NOBODY_CANT_RECEIVE_ITEM_RIGHT_NOW,			// 아이템을 가질 수 있는 멤버가 아무도 없습니다.
	GAME_PARTY_NO_EMPTY_SPACE_IN_INVENTORY,					// 인벤토리에 빈 공간이 없습니다.
	GAME_PARTY_NO_EMPTY_SPACE_IN_PARTY_INVENTORY,			// 파티 인벤토리에 빈 공간이 없습니다.
	GAME_PARTY_MEMBER_IS_TOO_FAR,							// 멤버가 너무 멀리 떨어져 있습니다. 퀘스트 공유 할때 사용 by niam
	GAME_PARTY_INVITING_IS_NOT_ALLOWED,						// 이 파티에서는 초대가 허용되지 않습니다.
	GAME_PARTY_LEAVING_IS_NOT_ALLOWED,						// 이 파티에서는 탈퇴가 허용되지 않습니다.
	GAME_PARTY_KICKING_OUT_IS_NOT_ALLOWED,					// 이 파티에서는 강제 탈퇴가 허용되지 않습니다.
	GAME_PARTY_APPOINTING_A_LEADER_IS_NOT_ALLOWED,			// 이 파티에서는 파티장 임명이 허용되지 않습니다.
	GAME_PARTY_SHARETARGET_NOTFINDOBJECT,					// 해당 오브젝트가 없습니다 [3/28/2008 SGpro]

	GAME_PARTY_SHARETARGET_SLOTID_FAIL,						// 공유타겟 슬롯ID가 잘못되었습니다[3/28/2008 SGpro]
	GAME_PARTY_ONLY_EQUIP_ITEM_ALLOWED_FOR_CHARM_POINT,		// 장착 아이템으로만 부적 포인트를 얻을 수 있습니다.
	GAME_PARTY_IDENTIFIED_ITEM_NEEDED_FOR_CHARM_POINT,		// 감정된 아이템으로만 부적 포인트를 얻을 수 있습니다.
	GAME_PARTY_DUNGEON_IN_PLAYER_FOUND,						// 1372 // 던전에 아직 남아있는 캐릭터가 있습니다. 
	GAME_PARTY_DICE_FAIL,									// 파티 주사위 결과 실패
	GAME_PARTY_INVEN_ITEM_EXIST,							// 파티인벤에 아이템이 남아있습니다.
	GAME_PARTY_INVEN_INVEST_ZENNY_NOT_ENOUGH,				// 파티인벤에 투자할 돈이 부족합니다.
	GAME_PARTY_INVEN_LOCKED,								// 파티인벤이 잠겼습니다.
	GAME_PARTY_ITEM_DICE_USING_NOW,							// 파티 아이템 다이스가 사용중입니다.
	GAME_PARTY_INVEN_ITEM_NON_EXIST,						// 파티인벤 해당 슬롯에 아이템 없습니다.

	GAME_PARTY_ITEM_DICE_NOT_USING_NOW,						// 파티 아이템 다이스가 안 사용중입니다.
	GAME_PARTY_DUNGEON_MIN_PLAYER_FAIL,						// 파티 던전의 최소인원이 부족합니다.
	GAME_PARTY_DUNGEON_OUT_RESERVED,						// 파티 던전 나가기 예약 NTL_MIN_DUNGEON_PARTYOUT_TIME 남았습니다..(정의된 값이 바뀌면 반드시 기획쪽 GUI 담당자에게 알려 주세요)
	GAME_PARTY_INVEN_DISTRIBUTE_METHOD_NOT_MATCH,			// 분배방식이 맞지 않습니다.
	GAME_PARTY_MEMBER_ZENNY_IS_LOCK,						// 파티 멤버중 제니가 잠긴 상태가 있습니다.
	GAME_PARTY_MEMBER_NOT_SAME,								// 파티인벤에 멤버가 다릅니다.
	GAME_PARTY_INVEN_LOCK_FIRST,							// 파티인벤이 열려있습니다. 먼저 닫아주십시요.
	GAME_PARTY_INVEN_UNDER_INVEST,							// 파티인벤에 투자된 최대금액 보다 높아야합니다.
	GAME_PARTY_DUNGEON_ENTER_PARTY_FAIL,					// 파티던전에 들어가시려면 파티를 생성하십시요.
	GAME_PARTY_DUNGEON_IN_CHANGE_DIFF_NOW,					// 파티던전안에선 난이도 변경이 불가능합니다.

	GAME_PARTY_CANT_INVITE_YOURSELF,						// 자기 자신을 파티에 초대할 수 없습니다.
	//-----------------------------------------------------------------
	GAME_HTB_NO_HTB_RESULT = 1400,							// 진행할 HTB가 없습니다
	GAME_HTB_CANT_FORWARD_ANYMORE,							// 더이상 진행할 HTB단계가 없습니다.
	GAME_HTB_NOT_ENOUGH_RP_BALL,							// RP 구슬이 충분하지 않습니다.
	GAME_HTB_YOU_ALREADY_USED_RP_BALL,						// 이미 RP 구슬을 사용한 상태입니다.
	GAME_HTB_YOU_HAVE_NO_RELATION_WITH_HTB,					// 1404 // HTB와 관련 없는 상태입니다.

	GAME_WORLD_ENTER_NEED_LOW_LEVEL, // 해당 지역에 진입하기에는 낮은 레벨입니다.
	GAME_WORLD_ENTER_NEED_HIGH_LEVEL, // 해당 지역에 진입하기에는 높은 레벨입니다.
	GAME_WORLD_ENTER_NEED_ITEM, // 해당 지역에 진입하기위한 필요  아이템이 없습니다.

	GAME_FREEBATTLE_TARGET_HAS_NO_MATCH, // 대상이 결투를 진행할 수 업습니다.
	GAME_FREEBATTLE_WRONG_PLACE, // 결투를 할 수 없는 지역입니다.
	GAME_FREEBATTLE_ALREADY_HAS_MATCH, // 이미 결투중입니다.
	GAME_FREEBATTLE_TARGET_ALREADY_HAS_MATCH, // 이미 결투중인 대상입니다.
	GAME_FREEBATTLE_CHALLENGE_TIME_REMAIN, // 아직 도전 대기 시간입니다.
	GAME_FREEBATTLE_CHALLENGE_ACCEPT_DENIED, // 결투 신청을 거절당했습니다.
	GAME_FREEBATTLE_CHALLENGE_ACCEPT_TIME_DENIED, // 결투 신청에 응답을 하지 않아 자동으로 거절되었습니다.
	GAME_FREEBATTLE_CHALLENGE_WAIT_TIME_DENIED, // 결투 신청에 대한 응답이 없어 자동으로 거절되었습니다.
	GAME_FREEBATTLE_ERROR_HAS_NO_MATCH, // 에러(에러코드) - 결투를 진행할 수 업습니다.
	GAME_FREEBATTLE_ERROR_TARGET_HAS_NO_MATCH, // 에러(에러코드)  - 대상이 결투를 진행할 수 업습니다.
	GAME_FREEBATTLE_ERROR_WRONG_PEER, // 에러(에러코드) - 잘못된 결투 대상을 가지고 있습니다.
	GAME_FREEBATTLE_ERROR_TARGET_WRONG_PEER, // 에러(에러코드) - 대상이 잘못된 결투 대상을 가지고 있습니다.
	//-----------------------------------------------------------------
	GAME_WORLD_ENTER_NEED_REPUTATION, // 해당 지역에 진입하기위한 필요 명성이 낮습니다.
	GAME_WORLD_NOT_FOUND,			  // 해당 지역을 찾을 수 없습니다.

	GAME_WORLD_ENTER_DISAPPROVAL,	 // 해당 지역에 진입할 수 없습니다.

	GAME_SCOUTER_TARGET_SELF_FAIL,	 // 자기 자신을 대상으로 불가능합니다.

	//////////////////////////////////////////////////////////////////////////
	//
	// Trigger system 관련 메시지들
	//
	//////////////////////////////////////////////////////////////////////////

	GAME_TS_WARNING_BEGIN = 1500,						// Trigger warning message 시작

	GAME_TS_WARNING_NOT_SATISFY_REWARD_CONDITIONS = 1500,	// 보상 받을 수 있는 조건을 만족하지 못합니다.
	GAME_TS_WARNING_MUST_SELECT_ONE_SEL_REWARD,		// 선택 보상이 존재합니다. 반드시 하나의 선택보상을 선택해야 합니다.
	GAME_TS_WARNING_PROCESSING_PRE_CONFIRM_REQ,		// 이전 진행 요청이 처리중입니다. (진행)
	GAME_TS_WARNING_NOW_TIME_WAIT,					// 이전 진행 요청이 처리중입니다. (시간)
	GAME_TS_WARNING_OVERFLOW_MAX_TS_NUM,			// 실행가능한 최대 트리거 개수가 넘었습니다.

	GAME_TS_WARNING_SYSTEM_WAIT,					// 다른 시스템과 충돌이 일어난 경우. 잠시 기다려 주세요.
	GAME_TS_WARNING_INVENTORY_IS_LOCK,				// 아이템 인벤토리가 lock이 걸려 있음
	GAME_TS_WARNING_INVENTORY_IS_FULL,				// 아이템 인벤토리가 가득찼음
	GAME_TS_WARNING_QUEST_INVENTORY_IS_FULL,		// 퀘스트 인벤토리가 가득 찼음
	GAME_TS_WARNING_INVALID_QUEST_ITEM_DELETE_COUNT,// 퀘스트 아이템의 삭제 요청 갯수가 틀림
	GAME_TS_WARNING_REWARD_FAIL,					// 보상을 하지 못함(아마 이 메시지가 갈일은 없을것임)
	GAME_TS_WARNING_EQUIP_SLOT_NOT_EMPTY,			// 장비 슬롯이 비어있지 않습니다.
	GAME_TS_WARNING_EQUIP_SLOT_LOCK,				// 장비 슬롯이 잠겨있습니다.
	GAME_TS_WARNING_CLASS_CHANGE_CLASS_FAIL,		// 전직 클래스가 다름
	GAME_TS_WARNING_CLASS_CHANGE_LEVEL_FAIL,		// 전직 레벨이 안됨
	GAME_TS_WARNING_NOT_YET_PROCESSED,				// 처리되지 않았음
	GAME_TS_WARNING_ROLLBACK,						// 정상 처리 하였으나 롤백시킴
	GAME_TS_WARNING_ROLLBACK_FAIL,					// 롤백을 실패함
	GAME_TS_WARNING_ESCORT_EXCEED_MEMBER,			// 멤버 초과
	GAME_TS_WARNING_ESCORT_NOT_SHARED,				// 공유 모드가 아님
	GAME_TS_WARNING_ESCORT_TRIGGER_TYPE_WRONG,		// 트리거 타입이 다름
	GAME_TS_WARNING_ESCORT_TRIGGER_ID_WRONG,		// 트리거 아이디가 다름
	GAME_TS_WARNING_ESCORT_PARTY_WRONG,				// 파티가 다름
	GAME_TS_WARNING_ESCORT_ALREADY_EXIST,			// 이미 등록되어 있음
	GAME_TS_WARNING_TMQ_COUPON_NOT_ENOUGH,			// TMQ에서 쿠폰이 부족함

	GAME_TS_WARNING_WPS_ALREDY_USED_BY_OTHER_PLAYER,// 이미 다른 유저가 수행중입니다.
	GAME_TS_WARNING_WPS_CAN_NOT_JOIN_NOW,			// 지금은 수행 할 수 없습니다.

	GAME_TS_WARNING_CAN_NOT_FIND_VISIT_EVT,			// 관련된 방문 이벤트가 없습니다. for visit event
	GAME_TS_WARNING_ALREADY_VISITED,				// 이미 완료했습니다. for visit event
	GAME_TS_WARNING_WRONG_CONDITION,				// 수행 조건이 맞지 않습니다.
	GAME_TS_WARNING_CANNOT_FIND_QUEST_ITEM,			// 퀘스트 아이템을 찾을 수 없습니다.
	GAME_TS_WARNING_DEL_FORBIDDENDEL_QUEST_ITEM,	// 지울수 없는 퀘스트 아이템입니다.
	//-----------------------------------------------------------------
	GAME_TS_WARNING_END = 1700,							// Trigger warning message 종료

	GAME_TS_ERROR_BEGIN = 1700,							// Trigger error message 시작

	GAME_TS_ERROR_RUN_ERROR = 1700,	// 트리거 진행 에러
	GAME_TS_ERROR_CS_SCRIPT_MISSMATCH,				// 다음에 진행해야할 컨테이너 타입이 CS 간에 일치하지 않습니다.
	GAME_TS_ERROR_NO_IMP_CONT_TYPE,					// 구현되지 않은 컨테이너 타입이 사용되었습니다.
	GAME_TS_ERROR_CANNOT_CREATE_TS_OBJECT,			// 트리거 오브젝트 생성 실패.
	GAME_TS_ERROR_CANNOT_FIND_TID,					// 트리거를 찾을 수 없습니다.
	GAME_TS_ERROR_CANNOT_FIND_TCID,					// 컨테이너를 찾을 수 없습니다.
	GAME_TS_ERROR_CANNOT_PROGRESS_REPEAT_QUEST,		// 반복 퀘스트는 오로지 한번만 진행할 수 있습니다


	GAME_TS_ERROR_SYSTEM,							// 일반적인 시스템상의 에러[버그]
	GAME_TS_ERROR_TRIGGER_SYSTEM,					// Trigger System 에서 에러가 난 경우
	GAME_TS_ERROR_QUERY_SERVER,						// 쿼리 서버 에러
	GAME_TS_ERROR_CANNOT_FIND_ITEM_HOBJECT,			// 테이블에서 아이템을 찾을수 없다
	GAME_TS_ERROR_CANNOT_FIND_SKILL_HOBJECT,			// 스킬을 찾을 수 없습니다.
	GAME_TS_ERROR_CANNOT_LEARN_SKILL,				// 스킬을 배울 수 없습니다.
	GAME_TS_ERROR_CANNOT_ADD_QUEST_EVENT_DATA,		// 이벤트 옵저버에 이벤트를 등록할 수 없습니다.
	GAME_TS_ERROR_CANNOT_FIND_QUEST_ITEM,			// 퀘스트 아이템을 찾을 수 없습니다.
	GAME_TS_ERROR_CREATE_ITEM_COUNT_OVER,			// 한번에 생성할 수 있는 제한 갯수를 넘었다.
	GAME_TS_ERROR_DELETE_ITEM_COUNT_OVER,			// 한번에 삭제할 수 있는 제한 갯수를 넘었다
	GAME_TS_ERROR_CANNOT_FIND_PC,					// PC를 찾을 수 없다
	GAME_TS_ERROR_TRIGGER_OBJECT_NOT_EXIST,			// 존재하지 않는 트리거 오브젝트 입니다.
	GAME_TS_ERROR_TRIGGER_OBJECT_INVALID_FUNCFLAG,	// 기능이 올바르지 않은 트리거 오브젝트입니다.
	//-----------------------------------------------------------------
	GAME_TS_ERROR_END = 1900,							// Trigger error message 종료
	//-----------------------------------------------------------------
	GAME_PET_CANT_MAKE_MORE_SUMMON_PET = 2000,			// 더 이상 소환펫을 부를 수 없습니다.
	GAME_PET_CANT_MAKE_MORE_ITEM_PET,					 // 더 이상 아이템 펫을 부를 수 없습니다.
	GAME_PET_COULDNT_BE_DONE_FOR_SOME_REASON,			// 시스템 문제로 요청을 처리할 수 없습니다.
	GAME_PET_TARGET_IS_NOT_SPAWNED,						// 대상이 소환되어 있지 않습니다.
	//-----------------------------------------------------------------
	GAME_GUILD_NO_GUILD_MANAGER_NPC_FOUND = 2100,			// 길드 매니저 NPC를 찾을 수 없습니다.
	GAME_GUILD_NOT_GUILD_MANAGER_NPC,						// 길드 매니저 NPC가 아닙니다.
	GAME_GUILD_GUILD_MANAGER_IS_TOO_FAR,					// 선택한 길드 매니저가 너무 멀어 대화를 할 수 없습니다.
	GAME_GUILD_NEED_MORE_ZENNY_FOR_NEW_GUILD,				// 길드 생성을 위해서는 제니가 더 필요합니다.
	GAME_GUILD_NOT_PROPER_GUILD_NAME_LENGTH,				// 길드 이름 길이가 적절하지 않습니다.
	GAME_GUILD_GUILD_NAME_HAS_INVALID_CHARACTER,			// 길드 이름에 사용 불가능한 문자가 포함되어 있습니다.
	GAME_GUILD_NOT_PROPER_GUILD_NAME,						// 길드 이름이 적절하지 않습니다.
	GAME_GUILD_SAME_GUILD_NAME_EXIST,						// 동일 길드 이름이 존재합니다.
	GAME_GUILD_NOT_EXIST,									// 해당 길드가 존재하지 않습니다.
	GAME_GUILD_NON_EXISTING_GUILD_FUNCTION,					// 알 수 없는 길드 기능입니다.

	GAME_GUILD_ALREADY_HAS_GUILD_FUNCTION,					// 이미 가지고 있는 길드 기능입니다.
	GAME_GUILD_NEED_PREREQUISITE_GUILD_FUNCTION,			// 한 단계 낮은 길드 기능을 획득한 상태여야 합니다.
	GAME_GUILD_NEED_MORE_GUILD_POINT,						// 더 많은 길드 포인트가 필요합니다.
	GAME_GUILD_NEED_MORE_ZENNY,								// 더 많은 제니가 필요합니다.
	GAME_GUILD_NEED_LEVEL_MORE,								// 레벨이 부족합니다.
	GAME_GUILD_GIVE_ZENNY_NOT_MATCHED,						// 길드 포인트를 얻기위해서는 1000으로 나누어 떨어지고 1000 이상이여야 합니다.
	GAME_GUILD_NO_GUILD_FOUND,								// 길드에 가입되어 있지 않습니다.
	GAME_GUILD_MARK_ARLEADY_CREATED,						// 길드마크가 이미 생성 되어 있습니다.
	GAME_GUILD_MARK_NOT_CREATED,							// 길드마크가 생성 되어 있지 않습니다.
	GAME_GUILD_NEED_DOJO_NOT_FOUND,							// 도장을 찾을 수 없습니다.

	GAME_GUILD_MAKE_DOJO_ALREADY_TAKEN,						// 이미 유파가 도장을 소유하고 있어 도장을 설립할 수 없습니다.
	GAME_GUILD_NEED_GUILD_FUNCTION,							// 길드의 기능이 없습니다. 기능획득을 먼저하십시요.
	GAME_GUILD_NO_DOJO_MANAGER_NPC_FOUND,					// 도장 매니저 NPC를 찾을 수 없습니다.
	GAME_GUILD_NOT_DOJO_MANAGER_NPC,						// 도장 매니저 NPC가 아닙니다.
	GAME_GUILD_DOJO_MANAGER_IS_TOO_FAR,						// 선택한 도장 매니저가 너무 멀어 대화를 할 수 없습니다.
	GAME_GUILD_NON_EXISTING_DOJO_FUNCTION,					// 알 수 없는 도장 기능입니다.
	GAME_GUILD_MAKE_DOJO_NOT_TAKEN,							// 도장의 주인이 없습니다.
	GAME_GUILD_DOGI_NOT_CREATED,							// 도복 생성 되어 있지 않습니다.
	GAME_GUILD_DOGI_ARLEADY_CREATED,						// 도복이 이미 생성 되어 있습니다.
	GAME_GUILD_ALREADY_HAS_DOJO_FUNCTION,					// 이미 가지고 있는 도장 기능입니다.

	GAME_GUILD_NEED_PREREQUISITE_DOJO_FUNCTION,				// 한 단계 낮은 도장 기능을 획득한 상태여야 합니다.
	GAME_GUILD_HOIPOIROCK_ITEM_NOT_FOUND,					// 호이포이락 아이템을 찾지 못했습니다.
	GAME_GUILD_HOIPOIROCK_ITEM_NOT_MATCHED,					// 호이포이락 아이템이 아닙니다.
	GAME_GUILD_HOIPOIROCK_ITEM_COUNT_FAIL,					// 호이포이락 아이템 갯수가 부족합니다.
	GAME_GUILD_DOJO_SCRAMBLE_CHALLENGE_HAVE,				// 도장 쟁탈 신청길드가 이미 있습니다.
	GAME_GUILD_DOJO_YOU_ARE_NOT_A_PARTY_LEADER,				// 도장의 설립은 유파 최고사범만이 가능합니다.
	GAME_GUILD_DOJO_YOU_ARE_NOT_OWNNER,						// 도장의 주인이 아닙니다.
	GAME_GUILD_DOJO_SCRAMBLE_CHALLENGE_STATUS_FAIL,			// 도장쟁탈전 신청가능 상태가 아닙니다. 
	GAME_GUILD_DOJO_SCRAMBLE_CHALLENGE_HAVE_DOJO,			// 도장을 소유한 유파는 쟁탈전을 신청할 수 없습니다.
	GAME_GUILD_DOJO_SCRAMBLE_REJECT_STATUS_FAIL,			// 도장쟁탈전 신청거부가능 상태가 아닙니다. 

	GAME_GUILD_DOJO_NOT_FOUND_TABLE,						// 도장테이블을 찾을수 없습니다. 
	GAME_GUILD_DOJO_NEED_FUNCTION,							// 도장설립 권한이 없습니다. 권한획득을 먼저하십시요.
	GAME_GUILD_DOJO_SCRAMBLE_MAX_COUNT_OVER,				// 도장쟁탈전에 들어갈수 있는 인원 수를 초과 했습니다.	
	GAME_GUILD_DOJO_NOT_FOUND,								// 해당 도장을 찾을 수 없습니다.	
	GAME_GUILD_DOJO_SELF_SCRAMBLE_FAIL,						// 자신이 속한 도장에 쟁탈전을 신청할수 없습니다.	
	GAME_GUILD_DOJO_SCRAMBLE_NOT_A_PARTY_LEADER,			// 쟁탈전의 신청은 최고사범만 할 수 있습니다.
	GAME_GUILD_DOJO_YOU_ARE_NOT_ENOUGH_REPUTATION,			// 쟁탈전을 신청하기에는 유파 포인트가 충분하지 않습니다. 
	GAME_GUILD_DOJO_YOU_ARE_NOT_ENOUGH_ZENNY,				// 쟁탈전을 신청하기에는 소지한 제니가 부족합니다. 
	GAME_GUILD_DOJO_YOU_ARE_ARLREADY_REJECT,				// 쟁탈전을 거부당해 신청할 수 없는 도장입니다. 다음 신청기간에 가능합니다. 
	GAME_GUILD_DOJO_YOU_DONT_BELONG_TO_ANY_DOJO,			// 도장에 속해 있지 않습니다.

	GAME_GUILD_DOJO_YOU_DONT_BELONG_TO_THAT_DOJO,			// 해당 도장에 속해 있지 않습니다.
	GAME_GUILD_DOJO_YOU_ARE_ARLREADY_REJECT_ONE_TIME,		// 쟁탈전 거부는 한번만 가능합니다.
	GAME_GUILD_DOJO_YOU_CANT_ATTACK_YOUR_TEAM_SEAL,			// 자신의 팀에 속한 인장을 공략할 수 없습니다.
	GAME_GUILD_DOJO_SEAL_CANT_BE_ATTACKED,					// 지금은 인장을 공략할 수 없습니다.
	GAME_GUILD_DOJO_TOO_MANY_ATTACKER_ON_SEAL,				// 이미 많은 플레이어가 인장을 공략하고 있습니다.
	GAME_GUILD_YOUR_GUILD_CANT_DO_DOJO_TELEPORT,			// 2155 // 텔레도장 기능을 사용할 수 없는 유파에 속해 있습니다.
	GAME_GUILD_DOJO_FUNCTION_ADD_FIRST,						// 도장의 기능을 먼저 습득하신 후 사용해 주세요. 
	//-----------------------------------------------------------------
	GAME_ROOM_ENTER_EXCEED_MAX_MEMBER_COUNT = 2200,			// 방에 인원이 가득 찼습니다.
	GAME_ROOM_ENTER_EXCEED_MAX_ROOM_COUNT,					// 더이상 방을 만들 수 없습니다.
	GAME_ROOM_ENTER_NEED_MORE_MEMBER,						// 방에 인원이 더 필요 합니다.
	GAME_ROOM_ENTER_TOO_LOW_LEVEL,							// 방에 진입하기에는 레벨이 너무 낮습니다
	GAME_ROOM_ENTER_TOO_HIGHTLEVEL,							// 방에 진입하기에는 레벨이 너무 높습니다
	GAME_ROOM_ENTER_MUST_HAVE_NEED_ITEM,					// 방에 진입하기위한 필요 아이템이 없습니다
	GAME_ROOM_ENTER_MUST_HAVE_NEED_ZENNY,					// 방에 진입하기위한 제니가 부족합니다.
	GAME_ROOM_ENTER_ROOM_NOT_EXIST,							// 방이 존재하지 않습니다.
	GAME_ROOM_ENTER_ROOMMANAGER_NOT_EXIST,					// 게시판이 존재하지 않습니다.
	GAME_ROOM_ENTER_NEED_MORE_PARTY_MEMEBER,				// 파티멤버가 더 필요합니다.
	GAME_ROOM_ENTER_NOT_MATCH_MEMBER,						// 대전 멤버가 아닙니다.
	GAME_ROOM_ENTER_NOT_WAIT_STATE,							// 대기 상태가 아닙니다.
	GAME_ROOM_ENTER_FAIL,									// 방진입 시도가 실패하였습니다
	GAME_ROOM_LEAVE_LIMIT_TIME_ELAPSED,						// 대기룸에서 나갈수 없는 시간 입니다
	GAME_ROOM_LEAVE_FAIL,									// 대기룸 나오기 실패
	GAME_ROOM_NOT_OWNER,									// 방의 소유자가 아닙니다.
	GAME_ROOM_CAN_NOT_FIND_PARTY_MEMBER,					// 파티멤버를 찾을 수 없습니다.

	GAME_RANKBATTLE_NOR_REGISTERED,							// 등록되어 있지 않습니다.
	GAME_RANKBATTLE_CANNOT_LEAVE_NOW,						// 취소 할 수 없습니다.
	GAME_RANKBATTLE_CANNOT_LEAVE_IN_MATCH,					// 경기중에는 취소할 수 없습니다.
	GAME_RANKBATTLE_CANNOT_FIND_ARENA,						// 경기장을 찾을 수 없습니다.
	GAME_RANKBATTLE_CANNOT_FIND_OPPONENT,					// 상대를 찾을 수 없습니다.
	GAME_RANKBATTLE_MEMBER_ALREADY_JOINED_RANKBATTLE,		// 파티원이 이미 랭크배틀 중입니다.
	GAME_RANKBATTLE_ARENA_IS_FULL,							// 비어있는 경기장이 없습니다.
	GAME_RANKBATTLE_OBJECT_IS_TOO_FAR,						// 너무 멀리 떨어져 있습니다.

	GAME_MATCH_CAN_NOT_USE_SKILL_IN_THIS_WORLD,				// 현재 월드에서는 사용할 수 없는 스킬입니다.
	GAME_MATCH_CAN_NOT_USE_SKILL_IN_OUTOFAREA,				// 장외일때는 스킬을 사용할 수 없습니다.
	GAME_TIMEQUEST_CANNOT_LEAVE_IN_PARTY_WHEN_PLAYING_RANKBATTLE,	// 랭크배틀 중일때에는 파티에서 나갈 수 없습니다.


	//-----------------------------------------------------------------
	GAME_TIMEQUEST_WORLD_NOT_FOUND = 2300,					// 타임머신 퀘스트에 해당하는 월드를 찾을 수 없습니다
	GAME_TIMEQUEST_ROOM_NOT_FOUND,							// 타임머신 퀘스트 대기방을 찾을 수 없습니다
	GAME_TIMEQUEST_ALREADY_JOINED,							// 타임머신 퀘스트 대기실에 이미 참여하고 있습니다
	GAME_TIMEQUEST_HAVE_NO_JOIN_ROOM,						// 타임머신 퀘스트 대기실에 참여하고 있지 않습니다
	GAME_TIMEQUEST_CANT_MAKE_PARTY,							// 타임머신 퀘스트에 자동 파티를 생성할 수 없습니다.
	GAME_TIMEQUEST_NEED_MORE_MEMBER,						// 타임머신 퀘스트를 할 인원이 충분하지 않습니다
	GAME_TIMEQUEST_NOT_ALLOWED_MEMBER,						// 타임머신 퀘스트에 진입이 허가되지 않은 멤버 입니다.
	GAME_TIMEQUEST_EXCEED_MAX_MEMBER_COUNT,					// 타임머신 퀘스트 진입최대 인원이 초과되었습니다.
	GAME_TIMEQUEST_TOO_LOW_LEVEL,							// 타임머신 퀘스트를 하기위한 레벨이 너무 낮습니다.
	GAME_TIMEQUEST_TOO_HIGH_LEVEL,							// 타임머신 퀘스트를 하기위한 레벨이 너무 높습니다.
	GAME_TIMEQUEST_MUST_HAVE_NEED_ITEM,						// 타임머신 퀘스트에 진입하기위한 아이템이 없습니다
	GAME_TIMEQUEST_MUST_HAVE_NEED_ZENNY,					// 타임머신 퀘스트에 진입하기위한 제니가 부족합니다.
	GAME_TIMEQUEST_ROOM_NOT_WAIT_STATE,						// 타임머신 퀘스트 대기실에 진입할 수 없습니다.
	GAME_TIMEQUEST_ROOM_PARTY_JOIN_FAIL,					// 타임머신 퀘스트 대기실에 파티등록을 할 수 없습니다.
	GAME_TIMEQUEST_ROOM_PARTY_ALREADY_JOINED,				// 타임머신 퀘스트 대기실에 이미 파티등록이 되어 있습니다.
	GAME_TIMEQUEST_ROOM_OUT_OF_ENTER_RANGE,					// 타임머신 퀘스트의 진입 영역을 벗어났습니다.
	GAME_TIMEQUEST_ROOM_CANNOT_TELEPORT_NOW,				// 지금은 타임머신의 위치로 이동할 수 없습니다.
	GAME_TIMEQUEST_DAYRECORD_IS_ALREADY_RESET,				// 데이레코드 리셋이 이미 처리되었습니다.
	GAME_TIMEQUEST_WORLD_ENTER_FAIL,						// 타임머신 퀘스트 진입이 실패하였습니다.
	GAME_TIMEQUEST_CANNOT_LEAVE_IN_PARTY_WHEN_PLAYING_TMQ,	// 타임머신 퀘스트를 수행 할 때에는 파티에서 나갈 수 없습니다.

	//-----------------------------------------------------------------
	GAME_TUTORIAL_CHAR_ALREADY_TUTORIAL_ACCOMPLISHED = 2350, // 캐릭터가 이미 튜토리얼을 수행했습니다
	GAME_TUTORIAL_CANT_FIND_TUTORIAL_WAIT_ROOM,				// 튜토리얼 대기룸이 존재 하지 않습니다
	GAME_TUTORIAL_CANT_ENTER_TUTORIAL_WAIT_ROOM,			// 튜토리얼 대기룸에 진입할 수 없습니다
	GAME_TUTORIAL_YOU_HAVE_NO_JOIN_ROOM,					// 튜토리얼 대기를 하고 있지 않습니다.


	//-----------------------------------------------------------------
	GAME_PRIVATESHOP = 2400,
	GAME_PRIVATESHOP_NOTAUTH,												// 권한이 없습니다
	GAME_PRIVATESHOP_NOTRUNSTATE,											// 지금 상태에서는 실행 할 수 없습니다
	GAME_PRIVATESHOP_PRIVATESHOP_NOT_CREATE_PLACE,							// 개인 상점을 열수 없는 장소 입니다
	GAME_PRIVATESHOP_PRIVATESHOP_ANOTHER_PRIVATESHOP,						// 근처에 다른 개인상점이 있어서 개인상점을 열 수 없습니다
	GAME_PRIVATESHOP_PRIVATESHOP_NULL,										// 상점이 없습니다
	GAME_PRIVATESHOP_PRIVATESHOP_INVENTORY_SAVEITEM_OVER,					// 상점 인벤토리에 빈슬롯이 없습니다
	GAME_PRIVATESHOP_PRIVATESHOP_INVENTORY_SLOT_ALREADY_ITEM,				// 상점 인벤토리 슬롯에 이미 아이템이 있습니다
	GAME_PRIVATESHOP_ITEM_NULL,												// 아이템이 없습니다
	GAME_PRIVATESHOP_ITEM_NOTVALID,											// 팔수 없는 아이템입니다
	GAME_PRIVATESHOP_VISITOR_NULL,											// 손님이 없습니다
	GAME_PRIVATESHOP_VISITOR_NOT_MONEY,										// 손님에 돈이 모자릅니다
	GAME_PRIVATESHOP_VISITOR_NOT_INVENTORY_EMPTY,							// 손님에 인벤토리 슬롯에 아이템들이 꽉 차 있습니다
	GAME_PRIVATESHOP_VISITOR_ALREADYENTER,									// 손님이 이미 상점에 입장했습니다
	GAME_PRIVATESHOP_VISITOR_SELECTITEM_NULL,								// 손님이 찜한 아이템이 없습니다
	GAME_PRIVATESHOP_VISITOR_SELECTITEM_OVER,								// 더이상 아이템을 찜할 수 없습니다
	GAME_PRIVATESHOP_VISITOR_SELECTITEM_ALREADY,							// 이미 찜한 아이템입니다
	GAME_PRIVATESHOP_VISITOR_SELECTITEM_ALLSELL,							// 선택한 아이템들을 살수 없습니다
	GAME_PRIVATESHOP_VISITOR_SELECTITEM_INVENSOLT_SHORTOF,					// 인벤토리에 빈 슬롯이 부족합니다
	GAME_PRIVATESHOP_VISITOR_FULL,											// 상점에 손님이 들어갈 수 있는 빈자리가 없습니다
	GAME_PRIVATESHOP_OWNER_MONEY_FULL,										// 상점 주인 돈이 더이상 늘어날수 없습니다
	GAME_PRIVATESHOP_OWNER_THEREISNO,										// 상점 주인이 자리에 없습니다
	GAME_PRIVATESHOP_OWNER_BUSINESS_REFUSED,								// 주인이 흥정을 거부중이다
	GAME_PRIVATESHOP_INVENTORY_NOTINVENTTORY,								// 잘못된 인벤토리 입니다
	GAME_PRIVATESHOP_INVENTORY_SAVEITEM_OVER,								// Inventory에 빈 슬롯이 없습니다
	GAME_PRIVATESHOP_STOP_PROGRESS,											// 종료중입니다
	GAME_PRIVATESHOP_OWNER_BARGAINS,										// 주인이 다름사람과 흥정중입니다
	GAME_PRIVATESHOP_ITEM_TABLE_ITEMID_DIFFERENT,							// 아이템이 동일하지 않습니다
	GAME_PRIVATESHOP_ITEM_SELECTITEM_NOTBUSINESS,							// 이미 선택한 아이템은 흥정할 수 없습니다
	GAME_PRIVATESHOP_OWNER_BUSINESS_NOT_CONSENT,							// 상점 주인이 흥정을 거부했습니다
	GAME_PRIVATESHOP_SAMENOT_PRICEFLUCTUATIONSCOUNTER,						// 주인이 가격 조정한 횟수와 손님이 가격 조정 패킷을 받은 값이 다릅니다.
	GAME_PRIVATESHOP_ZENNY_LOCK,											// 다른 사람과 Item Buy중이여서 Zenny가 Lock이 되었습니다. 처리가 끝날때까지 기다려 주세요
	GAME_PRIVATESHOP_NOT_PROGRESS_COMPLETE,									// 이전 요청이 처리될때까지 끝날때까지 기다려 주세요 (패킷이 Qry Srv에 머물고 있다)
	GAME_PRIVATESHOP_VISITOR_SELECTITEM_ALREADYBUYANDBUSINESSITEM,			// 이미 다른 손님이 구매한 아이템입니다.
	GAME_PRIVATESHOP_PRIVATESHOP_ANOTHER_NPC,								// 근처에 NPC가 있어서 개인상점을 열 수 없습니다

	//-----------------------------------------------------------------
	GAME_MAIL_TARGET_AWAY_STATE = 2500,						// 메일 받는 사람은 부재중이라 수신불가능합니다.
	GAME_MAIL_NOT_FOUND,									// 메일 찾지 못했습니다.
	GAME_MAIL_ALREADY_READ,									// 메일을 이미 읽은 상태입니다.
	GAME_MAIL_INVALID_DEL,									// 해당메일은 지울 수 없습니다.
	GAME_MAIL_INVALID_RETURN,								// 해당메일은 리턴할 수 없습니다.
	GAME_MAIL_INVALID_ACCEPT,								// 해당메일을 받을 수 없는 상태입니다.
	GAME_MAIL_INVALID_LOCK,									// 해당메일을 잠금설정이 변경 불가능합니다.
	GAME_MAIL_INVALID_ZENNY,								// 보낼 수 있는 제니의 한도를 초과했습니다.
	GAME_MAIL_NOT_EXISTING_PLAYER,							// 해당 캐릭터는 생성되지 않은 캐릭터입니다.
	GAME_MAIL_CANT_SEND_MAIL_TO_YOURSELF,					// 자기 자신에게는 메일을 보낼 수 없습니다.
	GAME_MAIL_MAILING_PARTS_NOT_FOUND,						// 메일 전송칩이 없습니다.
	GAME_MAIL_TRANSMIT_PARTS_NOT_FOUND,						// 물질 전송칩이 없습니다.
	GAME_MAIL_SCOUTER_FAIL,									// 메일전송을 위한 스카우터를 사용할 수 없는 상태입니다.
	//-----------------------------------------------------------------
	GAME_PORTAL_ARLEADY_ADDED = 2600,						// 이미등록된 포탈입니다.
	GAME_PORTAL_NOT_EXIST,									// 미등록 포탈입니다. 

	GAME_WARFOG_ARLEADY_ADDED = 2610,						// 이미등록된 워포그입니다.
	//-----------------------------------------------------------------
	GAME_PROCESSING_DB = 2620,						// 디비처리중입니다.
	//-----------------------------------------------------------------
	GAME_RIDE_ON_STATE = 2630,						// 현재 타 있는 상태 입니다.
	GAME_VEHICLE_CANNOT_WHILE_DRIVING,						// 운전 중엔 할 수 없습니다.
	GAME_VEHICLE_ENGINE_ALREADY_STARTED,					// 이미 시동이 켜져 있습니다.
	GAME_VEHICLE_ENGINE_ALREADY_STOPED,						// 이미 시동이 꺼져 있습니다.
	GAME_VEHICLE_INVALID_FUEL_ITEM,							// 
	GAME_VEHICLE_FAIL_TO_USE_FUEL_ITEM,						// 연료 아이템 사용에 실패했습니다.
	GAME_VEHICLE_NO_FUEL_ITEM_REMAINING,					// 남은 연료 아이템이 없습니다.
	GAME_VEHICLE_END_BY_USER,								// 유저가 탈것에서 내리기를 요청했습니다.
	GAME_VEHICLE_END_BY_HIT,								// 피격 당했기 때문에 탈것에서 내립니다.
	GAME_VEHICLE_END_BY_CONVERTCLASS,						// 전직으로 인해 탈 것에서 내립니다.
	GAME_VEHICLE_END_BY_TELEPORT,							// 텔레포트로 인해 탈 것에서 내립니다.
	GAME_VEHICLE_END_BY_FORCED,								// 탈 것 상태가 강제로 풀렸습니다.
	GAME_VEHICLE_END_BY_TMQ,								// TMQ 상태에 진입하기 때문에 탈것에서 내립니다.
	GAME_VEHICLE_END_BY_FORBIDDEN_ZONE,						// 탈 것이 허용되지 않는 지역입니다.
	//-----------------------------------------------------------------
	GAME_PETITION_NOTAUTH = 2700,							//권한이 없습니다
	GAME_PETITION_TOO_LONG_NAME,							//캐릭터명의 길이가 초과되었습니다.
	GAME_PETITION_TOO_SHORT_NAME,							//캐릭터명의 길이가 너무 짧습니다.
	GAME_PETITION_TOO_LONG_QUESTION_CONTENT,				//진정 내용의 길이가 초과되었습니다.
	GAME_PETITION_TOO_SHORT_QUESTION_CONTENT,				//진정 내용의 길이가 너무 짧습니다.
	GAME_PETITION_CATEGORY_1_FAIL,							//카테고리 1의 값이 이상합니다.
	GAME_PETITION_CATEGORY_2_FAIL,							//카테고리 2의 값이 이상합니다.
	GAME_PETITION_CREATE_PETITION_FAILE,					//진정 생성을 실패했습니다
	GAME_PETITION_DELETE_FAILE_STARTED,					//이미 상담중에 보류한 진정이기에 삭제할 수 없습니다
	GAME_PETITION_ISNOT_STARTED,							//진정 상태가 시작이 아닙니다
	GAME_PETITION_ALREADYSTARTED,							//이미 시작중입니다
	GAME_PETITION_INSERT_ERROR_ZERO_ID,					//데이타 저장 실패 - ID가 0입니다
	GAME_PETITION_INSERT_FAILE,							//데이타 저장 실패 (std::map에서 오류를 통보, 알 수 없는 오류
	GAME_PETITION_INSERT_ALLREADY_ID,						//데이타 저장 실패 (이미 등록되어 있는 ID 입니다
	GAME_PETITION_CREATE_PETITION_ID_FAILE,				//Petition ID 생성 실패
	GAME_PETITION_NOTRUNSTATE,								//지금 상태에서는 실행 할 수 없습니다
	GAME_PETITION_ACCOUNTNOTPETITION,						//해당 계정에 진정이 없습니다
	GAME_PETITION_ALREADY_INSERT,							//이미 진정이 접수된 Account입니다.
	GAME_PETITION_LOCK,										// Petition이 Lock되어 있습니다
	GAME_PETITION_PETITIONID_INVALID,						// Petition ID가 invalid 입니다.
	GAME_PETITION_ALREADYFINISH,							//이미 완료된 진정입니다.

	//-----------------------------------------------------------------
	GAME_BUDOKAI_INVALID_TEAM_NAME = 2800,					// 팀의 이름이 올바르지 않습니다.
	GAME_BUDOKAI_TOO_LONG_TEAM_NAME,						// 팀의 이름이 너무 깁니다.
	GAME_BUDOKAI_TOO_SHORT_TEAM_NAME,						// 팀의 이름이 너무 짧습니다.
	GAME_BUDOKAI_NEED_MORE_MEMBER,							// 팀원이 너무 적습니다.
	GAME_BUDOKAI_NOT_REGISTER_PERIOD,						// 등록 기간이 아닙니다.
	GAME_BUDOKAI_OVER_COUNT,								// 참가인원이 초과되었습니다.
	GAME_BUDOKAI_CHARACTER_ALREADY_JOIN,					// 이미 신청된 상태입니다.
	GAME_BUDOKAI_CHARACTER_NOT_JOINED,						// 신청하지 않은 상태입니다.
	GAME_BUDOKAI_MEMBER_ALREADY_JOINED,						// 이미 신청된 멤버가 있습니다.
	GAME_BUDOKAI_YOU_ARE_NOT_A_TEAM_LEADER,					// 팀 리더가 아닙니다.
	GAME_BUDOKAI_NOT_MATCH_PLAYING,							// 진행중인 경기가 없습니다.
	GAME_BUDOKAI_NOT_OPENED,								// 오픈기간이 아닙니다.
	GAME_BUDOKAI_NOT_MATCH_WORLD,							// 천하제일무도회 경기장이 아닙니다.

	GAME_CAN_NOT_TELEPORT,									// 이동할 수 없습니다.
	GAME_CAN_NOT_TELEPORT_THIS_STATE,						// 이동할 수 없는 상태입니다. 잠시 후 다시 시도하세요.

	GAME_MUDOSA_NOT_OPEND,									// 오픈 기간이 아닙니다.
	GAME_MUDOSA_POINT_CANT_BE_USED_RIGHT_NOW,				// 일시적으로 무도사 포인트를 사용할 수 없는 상황입니다. 잠시 후 다시 시도하세요.
	GAME_MUDOSA_POINT_NOT_ENOUGH,							// 무도사 점수가 충분하지 않습니다.
	GAME_MUDOSA_POINT_MAX_OVER,								// 무도사 점수가 최대를 초과하였습니다.

	GAME_MINORMATCH_CANNOT_TELEPORT_THIS_STATE,				// 현재의 예선전 상테에서는 진입할 수 없습니다.

	GAME_NETP_POINT_CANT_BE_USED_RIGHT_NOW,					// 일시적으로 NetPY 포인트를 사용할 수 없는 상황입니다. 잠시 후 다시 시도하세요.
	GAME_NETP_POINT_MAX_OVER,								// NetPY Point가 최대를 초과하였습니다.
	GAME_NETP_POINT_NOT_ENOUGH,								// NetPY Point가 충분하지 않습니다.
	GAME_NETPY_IS_LOCK,										// NetPY가 잠김 상태입니다.
	GAME_NETPY_NOT_ENOUGH,									// NetPY가 부족합니다.	

	GAME_BUILDING_VERSION_IS_NOT_CJI_KOR,					// The Building Version is not CJI Kor

	GAME_NETMARBLEMEMBER_IS_NOT,							// Netmarble Member가 아닙니다.

	GAME_CASHITEM_CANT_MOVE,								// 해당 캐쉬아이템은 가져올 수 없습니다.
	GAME_CASHITEM_NOT_LOADED,								// 캐쉬아이템 로딩이 완료되지 않았습니다.
	GAME_CASHITEM_NOT_FOUND,								// 해당 캐쉬아이템을 찾을 수 없습니다.
	//-----------------------------------------------------------------
	// Game, Item 관련. 800번대에서 이어짐. ( 3000 ~ )
	//-----------------------------------------------------------------
	GAME_ITEM_UPGRADE_ITEM_IS_ZERO_GRADE = 3000,			// 블랙 호이포이 스톤을 사용할 수 없습니다.
	GAME_DRAGONBALL_NOT_SAME_EXIST,							// 다른 종류의 드래곤볼 입니다.
	GAME_ITEM_DURATIONTIME_ZERO,							// 사용 기간이 끝났습니다.
	GAME_ITEM_RECIPE_CANNOT_RESET_NORMAL_TYPE,				// 기본 제조 기술은 포기할 수 없습니다.
	GAME_ITEM_NOT_USE_THIS_PLACE,							// 여기서 사용할 수 없는 아이템입니다.
	GAME_ITEM_STACK_FAIL_ITEMTYPE_DURATION,					// 사용기간이 있는 아이템은 Stack할 수 없습니다.
	GAME_ITEM_RECIPE_NORMAL_RECIPE_ALREADY_STARTED,			// 기본 제조 기술은 이미 배운 상태입니다.
	GAME_ITEM_RECIPE_SPECIAL_RECIPE_ALREADY_STARTED,		// 특수 제조 기술은 이미 배운 상태입니다.
	GAME_ITEM_RECIPE_CANNOT_RESET_CAUSE_NOT_STARTED_YET,	// 아직 배우지 않은 기술은 초기화 할 수 없습니다.
	GAME_ITEM_RECIPE_CANNOT_SET_YOU_NEED_HIGHER_LEVEL,		// 레벨이 부족하기 때문에 제조기술을 배울 수 없습니다.
	GAME_ITEM_RECIPE_CANNOT_SET_YOU_NEED_MORE_ZENNY,		// 제니가 부족하기 때문에 제조기술을 배울 수 없습니다.
	GAME_ITEM_CANT_USE_CAUSE_CAPSULE_ITEM_ALREADY_IN_USE,	// 캡슐 아이템을 이미 사용중입니다.

	GAME_SCOUTER_CHIP_NOT_EXIST,							// 스카우터 칩이 존재하지 않습니다.

	//-----------------------------------------------------------------
	REPORT_SUCCESS = 6000,									// 리포팅 성공
	REPORT_FAIL,											// 리포팅 실패

	//-----------------------------------------------------------------
	// Petition System ( 10000 ~ )
	//-----------------------------------------------------------------
	PETITION_SUCCESS = 10000,								// Petition 성공
	PETITION_FAIL,											// Petition 실패

	PETITION_NOT_STARTED_CLEINT_GM_CHAT,					// 클라이언트의 GM 채팅이 시작되지 않았습니다
	PETITION_DIFFERENT_CHAATING_GM_ID,						// 클라이언트가 채팅중인 GM의 ID와 다른 GM ID이다.
	PETITION_NOT_YET_ENTER_WORLD,							// 유저가 월드에 들어가지 않았다
	PETITION_AREADY_GM_CHATTING,							// 유저가 이미 GM 채팅중이다
};

enum SERVERSTATUS
{
	SERVERSTATUS_UP = 0,
	SERVERSTATUS_DOWN,
	SERVERSTATUS_LOCKED
};

enum RACE
{
	RACE_HUMAN,
	RACE_NAMEK,
	RACE_MAJIN,

	RACE_COUNT,
	RACE_UNKNOWN = 0xFF,

	RACE_FIRST = RACE_HUMAN,
	RACE_LAST = RACE_MAJIN
};

enum RACE_FLAG
{
	RACE_HUMAN_FLAG = MAKE_BIT_FLAG(RACE_HUMAN),
	RACE_NAMEK_FLAG = MAKE_BIT_FLAG(RACE_NAMEK),
	RACE_MAJIN_FLAG = MAKE_BIT_FLAG(RACE_MAJIN),
};

enum GENDER
{
	GENDER_MALE,
	GENDER_FEMALE,
	GENDER_ONE_SEX,

	GENDER_COUNT,
	GENDER_UNKNOWN = 0xFF,

	GENDER_FIRST = GENDER_MALE,
	GENDER_LAST = GENDER_ONE_SEX
};

enum PC_CLASS
{
	PC_CLASS_HUMAN_FIGHTER,
	PC_CLASS_HUMAN_MYSTIC,
	PC_CLASS_HUMAN_ENGINEER, 
	PC_CLASS_NAMEK_FIGHTER,
	PC_CLASS_NAMEK_MYSTIC,
	PC_CLASS_MIGHTY_MAJIN,
	PC_CLASS_WONDER_MAJIN,
	PC_CLASS_STREET_FIGHTER,
	PC_CLASS_SWORD_MASTER, 
	PC_CLASS_CRANE_ROSHI, 
	PC_CLASS_TURTLE_ROSHI,
	PC_CLASS_GUN_MANIA, 
	PC_CLASS_MECH_MANIA,
	PC_CLASS_DARK_WARRIOR, 
	PC_CLASS_SHADOW_KNIGHT, 
	PC_CLASS_DENDEN_HEALER,
	PC_CLASS_POCO_SUMMONER,
	PC_CLASS_ULTI_MA, 
	PC_CLASS_GRAND_MA,
	PC_CLASS_PLAS_MA,
	PC_CLASS_KAR_MA,

	PC_CLASS_COUNT,
	PC_CLASS_UNKNOWN = 0xFF,

	PC_CLASS_1_FIRST = PC_CLASS_HUMAN_FIGHTER,
	PC_CLASS_1_LAST = PC_CLASS_WONDER_MAJIN,
	PC_CLASS_2_FIRST = PC_CLASS_STREET_FIGHTER,
	PC_CLASS_2_LAST = PC_CLASS_KAR_MA,

	PC_CLASS_FIRST = PC_CLASS_HUMAN_FIGHTER,
	PC_CLASS_LAST = PC_CLASS_COUNT - 1
};

enum PC_CLASS_FLAG
{
	PC_CLASS_FLAG_HUMAN_FIGHTER = (0x01 << PC_CLASS_HUMAN_FIGHTER),
	PC_CLASS_FLAG_HUMAN_MYSTIC = (0x01 << PC_CLASS_HUMAN_MYSTIC),
	PC_CLASS_FLAG_HUMAN_ENGINEER = (0x01 << PC_CLASS_HUMAN_ENGINEER),
	PC_CLASS_FLAG_NAMEK_FIGHTER = (0x01 << PC_CLASS_NAMEK_FIGHTER),
	PC_CLASS_FLAG_NAMEK_MYSTIC = (0x01 << PC_CLASS_NAMEK_MYSTIC),
	PC_CLASS_FLAG_MIGHTY_MAJIN = (0x01 << PC_CLASS_MIGHTY_MAJIN),
	PC_CLASS_FLAG_WONDER_MAJIN = (0x01 << PC_CLASS_WONDER_MAJIN),
	PC_CLASS_FLAG_STREET_FIGHTER = (0x01 << PC_CLASS_STREET_FIGHTER) | PC_CLASS_FLAG_HUMAN_FIGHTER,
	PC_CLASS_FLAG_SWORD_MASTER = (0x01 << PC_CLASS_SWORD_MASTER) | PC_CLASS_FLAG_HUMAN_FIGHTER,
	PC_CLASS_FLAG_CRANE_ROSHI = (0x01 << PC_CLASS_CRANE_ROSHI) | PC_CLASS_FLAG_HUMAN_MYSTIC,
	PC_CLASS_FLAG_TURTLE_ROSHI = (0x01 << PC_CLASS_TURTLE_ROSHI) | PC_CLASS_FLAG_HUMAN_MYSTIC,
	PC_CLASS_FLAG_GUN_MANIA = (0x01 << PC_CLASS_GUN_MANIA) | PC_CLASS_FLAG_HUMAN_ENGINEER,
	PC_CLASS_FLAG_MECH_MANIA = (0x01 << PC_CLASS_MECH_MANIA) | PC_CLASS_FLAG_HUMAN_ENGINEER,
	PC_CLASS_FLAG_DARK_WARRIOR = (0x01 << PC_CLASS_DARK_WARRIOR) | PC_CLASS_FLAG_NAMEK_FIGHTER,	
	PC_CLASS_FLAG_SHADOW_KNIGHT = (0x01 << PC_CLASS_SHADOW_KNIGHT) | PC_CLASS_FLAG_NAMEK_FIGHTER,
	PC_CLASS_FLAG_DENDEN_HEALER = (0x01 << PC_CLASS_DENDEN_HEALER) | PC_CLASS_FLAG_NAMEK_MYSTIC,
	PC_CLASS_FLAG_POCO_SUMMONER = (0x01 << PC_CLASS_POCO_SUMMONER) | PC_CLASS_FLAG_NAMEK_MYSTIC,
	PC_CLASS_FLAG_GRAND_MA = (0x01 << PC_CLASS_GRAND_MA) | PC_CLASS_FLAG_MIGHTY_MAJIN,
	PC_CLASS_FLAG_ULTI_MA = (0x01 << PC_CLASS_ULTI_MA) | PC_CLASS_FLAG_MIGHTY_MAJIN,
	PC_CLASS_FLAG_PLAS_MA = (0x01 << PC_CLASS_PLAS_MA) | PC_CLASS_FLAG_WONDER_MAJIN,
	PC_CLASS_FLAG_KAR_MA = (0x01 << PC_CLASS_KAR_MA) | PC_CLASS_FLAG_WONDER_MAJIN,
};

enum ZENNY_CHANGE_TYPE
{
	ZENNY_CHANGE_TYPE_ITEM_BUY = 0,
	ZENNY_CHANGE_TYPE_ITEM_SELL,
	ZENNY_CHANGE_TYPE_PICK,
	ZENNY_CHANGE_TYPE_TRADE,
	ZENNY_CHANGE_TYPE_REPAIR,
	ZENNY_CHANGE_TYPE_REWARD,
	ZENNY_CHANGE_TYPE_SKILL,
	ZENNY_CHANGE_TYPE_PARTY_VICTIM_ADD,
	ZENNY_CHANGE_TYPE_PARTY_VICTIM_DEL,
	ZENNY_CHANGE_TYPE_PARTY_VICTIM_RETURN,
	ZENNY_CHANGE_TYPE_CHEAT,
	ZENNY_CHANGE_TYPE_BANK_BUY,
	ZENNY_CHANGE_TYPE_PARTY_PICK,
	ZENNY_CHANGE_TYPE_GUILD_CREATE,
	ZENNY_CHANGE_TYPE_DB_REWARD,
	ZENNY_CHANGE_TYPE_PRIVATESHOP_ITEM_BUY,
	ZENNY_CHANGE_TYPE_MAIL_SEND,
	ZENNY_CHANGE_TYPE_MAIL_RECV,
	ZENNY_CHANGE_TYPE_RANKBATTLE,
	ZENNY_CHANGE_TYPE_PORTAL_ADD,

	ZENNY_CHANGE_TYPE_GUILD_FUNCTION_ADD,
	ZENNY_CHANGE_TYPE_GUILD_GIVE_ZENNY,
	ZENNY_CHANGE_TYPE_GUILD_MARK_CHANGE,
	ZENNY_CHANGE_TYPE_GUILD_NAME_CHANGE,
	ZENNY_CHANGE_TYPE_RIDE_ON_BUS,
	ZENNY_CHANGE_TYPE_ITEM_IDENTIFY,
	ZENNY_CHANGE_TYPE_SCOUTER_ITEM_SELL,
	ZENNY_CHANGE_TYPE_PARTY_ITEM_INVEST,
	ZENNY_CHANGE_TYPE_ITEM_MIX_MAKE,
	ZENNY_CHANGE_TYPE_ITEM_MIX_FARE,
	ZENNY_CHANGE_TYPE_DOJO_CHANGE,
	ZENNY_CHANGE_TYPE_BANK,
	ZENNY_CHANGE_TYPE_GUILD_BANK,
	ZENNY_CHANGE_TYPE_DOJO_SCRAMBLE_REQ,
	ZENNY_CHANGE_TYPE_DOJO_ANTI_SCRAMBLE_ADD,
	ZENNY_CHANGE_TYPE_DOJO_ANTI_SCRAMBLE_DEL,
	ZENNY_CHANGE_TYPE_ITEM_RECIPE_JOB_SET, 

	ZENNY_CHANGE_TYPE_COUNT,
	ZENNY_CHANGE_TYPE_INVALID = 0xFF
};

enum CONTAINER_TYPE
{
	CONTAINER_TYPE_BAGSLOT,
	CONTAINER_TYPE_BAG1,
	CONTAINER_TYPE_BAG2,
	CONTAINER_TYPE_BAG3,
	CONTAINER_TYPE_BAG4,
	CONTAINER_TYPE_BAG5,

	CONTAINER_TYPE_NETPYSTORE,

	CONTAINER_TYPE_EQUIP,
	CONTAINER_TYPE_SCOUT,

	CONTAINER_TYPE_BANKSLOT,
	CONTAINER_TYPE_BANK1,
	CONTAINER_TYPE_BANK2,
	CONTAINER_TYPE_BANK3,
	CONTAINER_TYPE_BANK4,

	CONTAINER_TYPE_GUILD1,
	CONTAINER_TYPE_GUILD2,
	CONTAINER_TYPE_GUILD3,

	CONTAINER_TYPE_COUNT,
	CONTAINER_TYPE_NONE = 0xFF,

	CONTAINER_TYPE_BAG_FIRST = CONTAINER_TYPE_BAG1,
	CONTAINER_TYPE_BAG_LAST = CONTAINER_TYPE_NETPYSTORE,

	CONTAINER_TYPE_INVEN_FIRST = CONTAINER_TYPE_BAGSLOT,
	CONTAINER_TYPE_INVEN_LAST = CONTAINER_TYPE_SCOUT,

	CONTAINER_TYPE_BANK_FIRST = CONTAINER_TYPE_BANKSLOT,
	CONTAINER_TYPE_BANK_LAST = CONTAINER_TYPE_BANK4,

	CONTAINER_TYPE_GUILD_FIRST = CONTAINER_TYPE_GUILD1,
	CONTAINER_TYPE_GUILD_LAST = CONTAINER_TYPE_GUILD3,

	CONTAINER_TYPE_FIRST = CONTAINER_TYPE_BAGSLOT,
	CONTAINER_TYPE_LAST = CONTAINER_TYPE_BANK4,
};

enum EQUIP_SLOTTYPE
{
	EQUIP_SLOT_TYPE_HAND,
	EQUIP_SLOT_TYPE_SUB_WEAPON,
	EQUIP_SLOT_TYPE_JACKET,
	EQUIP_SLOT_TYPE_PANTS,
	EQUIP_SLOT_TYPE_BOOTS,
	EQUIP_SLOT_TYPE_SCOUTER,
	EQUIP_SLOT_TYPE_COSTUME,
	EQUIP_SLOT_TYPE_NECKLACE,
	EQUIP_SLOT_TYPE_EARRING_1,
	EQUIP_SLOT_TYPE_EARRING_2,
	EQUIP_SLOT_TYPE_RING_1,
	EQUIP_SLOT_TYPE_RING_2,

	EQUIP_SLOT_TYPE_COUNT,
	EQUIP_SLOT_TYPE_UNKNOWN = 0xFF,

	EQUIP_SLOT_TYPE_FIRST = EQUIP_SLOT_TYPE_HAND,
	EQUIP_SLOT_TYPE_LAST = EQUIP_SLOT_TYPE_RING_2,
};

enum AVATAR_TYPE
{
	AVATAR_TYPE_AVATAR = 0,
	AVATAR_TYPE_SUMMON_PET_1,
	AVATAR_TYPE_ITEM_PET_1,
	AVATAR_TYPE_COUNT,
	AVATAR_TYPE_INVALID = 0xFF,
	AVATAR_TYPE_PET_FIRST = AVATAR_TYPE_SUMMON_PET_1,
	AVATAR_TYPE_PET_LAST = AVATAR_TYPE_ITEM_PET_1,
	AVATAR_TYPE_SUMMON_PET_FIRST = AVATAR_TYPE_SUMMON_PET_1,
	AVATAR_TYPE_SUMMON_PET_LAST = AVATAR_TYPE_SUMMON_PET_1,
	AVATAR_TYPE_ITEM_PET_FIRST = AVATAR_TYPE_ITEM_PET_1,
	AVATAR_TYPE_ITEM_PET_LAST = AVATAR_TYPE_ITEM_PET_1,
	DAVATAR_TYPE_COUNT_SUMMON_PET = AVATAR_TYPE_SUMMON_PET_LAST - AVATAR_TYPE_SUMMON_PET_FIRST + 1,
	DAVATAR_TYPE_COUNT_ITEM_PET = AVATAR_TYPE_ITEM_PET_LAST - AVATAR_TYPE_ITEM_PET_FIRST + 1,
};

enum REVIVAL_REQUEST_TYPE
{
	REVIVAL_REQUEST_TYPE_TELEPORT_SOMEWHERE = 0,
	REVIVAL_REQUEST_TYPE_CURRENT_POSITION,
	REVIVAL_REQUEST_TYPE_COUNT,
	REVIVAL_REQUEST_TYPE_FIRST = REVIVAL_REQUEST_TYPE_TELEPORT_SOMEWHERE,
	REVIVAL_REQUEST_TYPE_LAST = REVIVAL_REQUEST_TYPE_COUNT - 1,
};

enum REVIVAL_TYPE
{
	REVIVAL_TYPE_CURRENT_POSITION = 0,
	REVIVAL_TYPE_BIND_POINT,
	REVIVAL_TYPE_RESCUED,
	REVIVAL_TYPE_SPECIFIED_POSITION,

	REVIVAL_TYPE_FIRST = REVIVAL_TYPE_CURRENT_POSITION,
	REVIVAL_TYPE_LAST = REVIVAL_TYPE_RESCUED,
	INVALID_REVIVAL_TYPE = 0xFF
};

enum SHORTCUT_CHANGE_TYPE
{
	SHORTCUT_CHANGE_TYPE_ADD = 0,
	SHORTCUT_CHANGE_TYPE_DEL,
	SHORTCUT_CHANGE_TYPE_UPDATE,
};

enum PARTYDUNGEON_STATE
{
	PARTY_DUNGEON_STATE_NORMAL,
	PARTY_DUNGEON_STATE_HARD,
	PARTY_DUNGEON_STATE_SUPER,
	PARTY_DUNGEON_STATE_HERO,
	PARTY_DUNGEON_STATE_FIRST = PARTY_DUNGEON_STATE_NORMAL,
	PARTY_DUNGEON_STATE_LAST = PARTY_DUNGEON_STATE_HERO,
};

enum SYSTEM_EFFECT_RESULT_TYPE
{
	SYSTEM_EFFECT_RESULT_TYPE_GENERAL = 0,
	SYSTEM_EFFECT_RESULT_TYPE_DH_HOT,
	SYSTEM_EFFECT_RESULT_TYPE_DD_DOT,
	DSYSTEM_EFFECT_RESULT_TYPE_LP_EP_STEAL,
	SYSTEM_EFFECT_RESULT_TYPE_COUNT,
	SYSTEM_EFFECT_RESULT_TYPE_UNKNOWN = 0xFFui8,
	SYSTEM_EFFECT_RESULT_TYPE_FIRST = SYSTEM_EFFECT_RESULT_TYPE_GENERAL,
	SYSTEM_EFFECT_RESULT_TYPE_LAST = SYSTEM_EFFECT_RESULT_TYPE_COUNT - 1
};

enum QUEST_ID_RANGE
{
	QUEST_ID_RANGE_GENERAL_QUEST_MIN = 0,
	QUEST_ID_RANGE_GENERAL_QUEST_MAX = 7000,
	QUEST_ID_RANGE_GENERAL_QUEST_COUNT = QUEST_ID_RANGE_GENERAL_QUEST_MAX - QUEST_ID_RANGE_GENERAL_QUEST_MIN,
	QUEST_ID_RANGE_RESERVE_QUEST_MIN = 7000,
	QUEST_ID_RANGE_RESERVE_QUEST_MAX = 11000,
	QUEST_ID_RANGE_RESERVE_QUEST_COUNT = QUEST_ID_RANGE_RESERVE_QUEST_MAX - QUEST_ID_RANGE_RESERVE_QUEST_MIN,
	QUEST_ID_RANGE_SPECIAL_QUEST_MIN = 11000,
	QUEST_ID_RANGE_SPECIAL_QUEST_MAX = 14000,
	QUEST_ID_RANGE_SPECIAL_QUEST_COUNT = QUEST_ID_RANGE_SPECIAL_QUEST_MAX - QUEST_ID_RANGE_SPECIAL_QUEST_MIN,
	QUEST_ID_RANGE_QUEST_MAX = 14000,
};

enum COMPLETE_QUEST_STATE
{
	COMPLETE_QUEST_STATE_CLEAR = 0x1,
	COMPLETE_QUEST_STATE_MAX = 1
};

enum
{
	COMPLETE_QUEST_QUEST_PER_BYTE = 8 / COMPLETE_QUEST_STATE_MAX
};

enum
{
	COMPLETE_QUEST_QUEST_PER_STRUCT = 1000
};

enum
{
	COMPLETE_QUEST_QUEST_STRUCT_COUNT = QUEST_ID_RANGE_QUEST_MAX / COMPLETE_QUEST_QUEST_PER_STRUCT
};

enum
{
	MAX_CAN_PROGRESS_QUEST_NUM = 20,
	MAX_CAN_PROGRESS_GENERAL_QUEST_NUM = 10,
	MAX_CAN_PROGRESS_SPECIAL_QUEST_NUM = 10,
};

enum
{
	MAX_CAN_PROGRESS_TRIGGER_NUM = 20
};

enum TS_SVR_STATE
{
	TS_SVR_STATE_ERROR = 0x0001,
	TS_SVR_STATE_FAILED = 0x0002,
	TS_SVR_STATE_ESCORT = 0x0004,
	TS_SVR_STATE_SVR_EVT_WORLD_RANGE = 0x0008,
	TS_SVR_STATE_WPS_MODE = 0x0010,
	TS_SVR_STATE_USER_OUT_FAILED_WPS = 0x0020,
};

enum GAMERULE_TYPE
{
	GAMERULE_NORMAL,		// 일반 필드
	GAMERULE_RANKBATTLE,	// 랭킹 배틀
	GAMERULE_MUDOSA,		// 천하제일무도회장
	GAMERULE_DOJO,			// 도장
	GAMERULE_RAID,			// 레이드
	GAMERULE_HUNT,			// 사냥 (개인/파티별 인스턴스)
	GAMERULE_TIMEQUEST,		// 타임머신 퀘스트
	GAMERULE_TUTORIAL,		// 튜토리얼
	GAMERULE_MINORMATCH,	// 천하제일무도회 예선
	GAMERULE_MAJORMATCH,	// 천하제일무도회 본선
	GAMERULE_FINALMATCH,	// 천하제일무도회 결선
	GAMERULE_TEINKAICHIBUDOKAI,	// 천하제일무도회
	GAMERULE_TLQ,			// 타임리프 퀘스트

	GAMERULE_TYPE_COUNT,
	INVALID_GAMERULE = 0xFFFFFFFF, // 없음
};

enum ITEM_RANK
{
	ITEM_RANK_NOTHING,
	ITEM_RANK_NORMAL,
	ITEM_RANK_SUPERIOR,
	ITEM_RANK_EXCELLENT,
	ITEM_RANK_RARE,
	ITEM_RANK_LEGENDARY,

	ITEM_RANK_COUNT,
	ITEM_RANK_UNKNOWN = 0xFF,

	ITEM_RANK_FIRST = ITEM_RANK_NOTHING,
	ITEM_RANK_LAST = ITEM_RANK_LEGENDARY
};

enum INVITATION_RESPONSE
{
	INVITATION_RESPONSE_ACCEPT = 0,	
	INVITATION_RESPONSE_DECLINE,
	INVITATION_RESPONSE_EXPIRE,

	INVITATION_RESPONSE_COUNT,

	INVITATION_RESPONSE_FIRST = INVITATION_RESPONSE_ACCEPT,
	INVITATION_RESPONSE_LAST = INVITATION_RESPONSE_EXPIRE
};

enum PARTY_ZENNY_LOOTING
{
	PARTY_ZENNY_LOOTING_GREEDILY = 0,
	PARTY_ZENNY_LOOTING_SHARED,

	PARTY_ZENNY_LOOTING_COUNT,

	PARTY_ZENNY_LOOTING_UNKNOWN = 0xFF,

	PARTY_ZENNY_LOOTING_FIRST = PARTY_ZENNY_LOOTING_GREEDILY,
	PARTY_ZENNY_LOOTING_LAST = PARTY_ZENNY_LOOTING_SHARED
};

enum PARTY_ITEM_LOOTING
{
	PARTY_ITEM_LOOTING_GREEDILY = 0,
	PARTY_ITEM_LOOTING_IN_ORDER,
	PARTY_ITEM_LOOTING_IN_ORDER_SEPERATELY,

	PARTY_ITEM_LOOTING_IN_LEADER,	
	PARTY_ITEM_LOOTING_BY_ZENNY,
	PARTY_ITEM_LOOTING_DICE,

	PARTY_ITEM_LOOTING_COUNT,

	PARTY_ITEM_LOOTING_UNKNOWN = 0xFF,

	PARTY_ITEM_LOOTING_FIRST = PARTY_ITEM_LOOTING_GREEDILY,
	PARTY_ITEM_LOOTING_LAST = PARTY_ITEM_LOOTING_DICE
};

enum PARTY_OPTION
{
	PARTY_OPTION_CANT_INVITE = 0,
	PARTY_OPTION_CANT_LEAVE,
	PARTY_OPTION_CANT_KICK_OUT,
	PARTY_OPTION_CANT_APPOINT_LEADER
};

enum PARTY_OPTION_FLAG
{
	PARTY_OPTION_FLAG_CANT_INVITE = 1 << PARTY_OPTION_CANT_INVITE,
	PARTY_OPTION_FLAG_CANT_LEAVE = 1 << PARTY_OPTION_CANT_LEAVE,
	PARTY_OPTION_FLAG_CANT_KICK_OUT = 1 << PARTY_OPTION_CANT_KICK_OUT,
	PARTY_OPTION_FLAG_CANT_APPOINT_LEADER = 1 << PARTY_OPTION_CANT_APPOINT_LEADER
};
// Basic Values
const DWORD MAX_PARTY_COUNT = 2000;

const DWORD MAX_MEMBER_IN_PARTY = 5;
const float VALID_DISTANCE_FOR_EXP_FROM_VICTIM = 100.0f;
const float VALID_DISTANCE_TO_GET_ZENNY_IN_PARTY = 100.0f;
const float VALID_DISTANCE_TO_GET_ITEM_IN_PARTY = 100.0f;

// Charm
const DWORD PARTY_CHARM_INVENTORY_COUNT = 2;
const DWORD SLOT_COUNT_IN_PARTY_CHARM_INVENTORY = 11;
const DWORD MAX_PARTY_BUFF = 2;

const DWORD TIME_PARTY_CHARM_DICE = 30000;		//30sec 
const DWORD TIME_PARTY_DICE_ITEM = 30000;		//30sec 
const BYTE	PARTY_INVEN_DEFAULT_ITEM_RANK = ITEM_RANK_SUPERIOR;
// Party Inventory
const DWORD PARTY_INVENTORY_SLOT_COUNT = 16;
// Party Option
const DWORD PARTY_OPTION_FLAG_DEFAULT = 0;
const DWORD PARTY_OPTION_FLAG_TMQ =
					PARTY_OPTION_FLAG_CANT_INVITE |
					PARTY_OPTION_FLAG_CANT_LEAVE |
					PARTY_OPTION_FLAG_CANT_KICK_OUT |
					PARTY_OPTION_FLAG_CANT_APPOINT_LEADER;
const DWORD PARTY_OPTION_FLAG_RANK_BATTLE =
					PARTY_OPTION_FLAG_CANT_INVITE |
					PARTY_OPTION_FLAG_CANT_LEAVE |
					PARTY_OPTION_FLAG_CANT_KICK_OUT |
					PARTY_OPTION_FLAG_CANT_APPOINT_LEADER;
const DWORD PARTY_OPTION_FLAG_BUDOKAI =
					PARTY_OPTION_FLAG_CANT_INVITE |
					PARTY_OPTION_FLAG_CANT_LEAVE |
					PARTY_OPTION_FLAG_CANT_KICK_OUT |
					PARTY_OPTION_FLAG_CANT_APPOINT_LEADER;
const DWORD MAX_SHARETARGET_COUNT = 5;

enum NPCCONV_TYPE
{
	NPCCONV_TYPE_DIALOGBOX,
	NPCCONV_TYPE_TOOLTIP,

	NPCCONV_TYPE_INVALID = 0xffffffff
};

enum STOC_EVT_DATA_TYPE
{
	STOC_EVT_DATA_TYPE_MOB_KILL_CNT,
	STOC_EVT_DATA_TYPE_MOB_KILL_ITEM_CNT,
	STOC_EVT_DATA_TYPE_DELIVERY_ITEM,
	STOC_EVT_DATA_TYPE_OBJECT_ITEM,
	STOC_EVT_DATA_TYPE_PUBLIC_MOB_ITEM_CNT,
	STOC_EVT_DATA_TYPE_CUSTOM_EVT_CNT,
	STOC_EVT_DATA_TYPE_VISIT,

	STOC_EVT_DATA_TYPE_MAX,
	STOC_EVT_DATA_TYPE_INVALID = 0xffffffff
};

enum FREEBATTLE_RESULT
{
	FREEBATTLE_RESULT_WIN,
	FREEBATTLE_RESULT_LOSE,
	FREEBATTLE_RESULT_DRAW,

	FREEBATTLE_RESULT_COUNT
};

enum ACCEPT_RES_TYPE
{
	ACCEPT_RES_TYPE_DENY = 0,
	ACCEPT_RES_TYPE_OK,
	ACCEPT_RES_TYPE_CANCEL,
};

enum OBJTYPE
{
	OBJTYPE_PC,
	OBJTYPE_NPC,
	OBJTYPE_MOB,
	OBJTYPE_SUMMON_PET,
	OBJTYPE_ITEM_PET,
	OBJTYPE_DROPMONEY,
	OBJTYPE_DROPITEM,
	OBJTYPE_TOBJECT,
	OBJTYPE_DYNAMIC,
	OBJTYPE_ITEM,

	MAX_OBJTYPE,
	MAX_SPAWNOBJTYPE = OBJTYPE_DYNAMIC,
	INVALID_OBJTYPE = 0xFF,

	OBJTYPE_FIRST = OBJTYPE_PC,
	OBJTYPE_LAST = MAX_OBJTYPE - 1,
};

enum OBJECT_SOURCE
{
	OBJECT_SOURCE_SKILL = 0,	
	OBJECT_SOURCE_ITEM,

	OBJECT_SOURCE_UNKNOWN = 0xFF,

	OBJECT_SOURCE_FIRST = OBJECT_SOURCE_SKILL,
	OBJECT_SOURCE_LAST = OBJECT_SOURCE_ITEM
};

enum TRIGGER_OBJECT_FUNC
{
	TRIGGER_OBJECT_FUNC_SELECTION = 0x1,
	TRIGGER_OBJECT_FUNC_PORTAL = 0x2,
	TRIGGER_OBJECT_FUNC_BIND = 0x4,
	TRIGGER_OBJECT_FUNC_SCOUTER = 0x8,
	TRIGGER_OBJECT_FUNC_RANK_BATTLE = 0x10,
	TRIGGER_OBJECT_FUNC_NORMAL_DRAGONBALL = 0x20,
	TRIGGER_OBJECT_FUNC_RAID_DRAGONBALL = 0x40,
	TRIGGER_OBJECT_FUNC_MAIL_BOX = 0x80,
	TRIGGER_OBJECT_FUNC_TIME_MACHINE = 0x100,
	TRIGGER_OBJECT_FUNC_NAMEKAN_SIGN = 0x200,
	TRIGGER_OBJECT_FUNC_PARTY_INSTANCE_DUNGEON = 0x400,
	TRIGGER_OBJECT_FUNC_TIME_LEAP_QUEST = 0x800,
	TRIGGER_OBJECT_FUNC_HOIPOIMIX = 0x1000,
	TRIGGER_OBJECT_FUNC_DOJO_WAREHOUSE = 0x2000,
	TRIGGER_OBJECT_FUNC_DOJO_SEAL = 0x4000,
};

enum DYNAMIC_OBJECT_STATES
{
	DYNAMIC_OBJECT_STATE_SPAWN,
	DYNAMIC_OBJECT_STATE_IDLE,
	DYNAMIC_OBJECT_STATE_DESPAWN,

	DYNAMIC_OBJECT_STATE_NUMS,
	DYNAMIC_OBJECT_STATE_INVALID = 0xFF
};

enum DYNAMIC_OBJECT_FUNCTION
{
	DYNAMIC_OBJECT_FUNCTION_HOIPOIMIX = 0x1,

	DYNAMIC_OBJECT_FUNCTION_NUMS,
	DYNAMIC_OBJECT_FUNCTION_INVALID = 0xFF
};

enum DYNAMIC_OBJECT_TYPE
{
	DYNAMIC_OBJECT_TYPE_HOIPOI_MIX_MACHINE = 1,
	DYNAMIC_OBJECT_TYPE_CAPSULE_HOUSE,

	DYNAMIC_OBJECT_TYPE_NONE = 0xFF,
};

enum DYNAMIC_OBJECT_SUBSTATE
{
	DYNAMIC_OBJECT_SUBSTATE_ALL_SHOW,
	DYNAMIC_OBJECT_SUBSTATE_ONLY_SPAWN_AVATAR_SHOW,
	DYNAMIC_OBJECT_SUBSTATE_ENEMY_HIDE,

	DYNAMIC_OBJECT_SUBSTATE_NUMS,
	DYNAMIC_OBJECT_SUBSTATE_INVALID = 0xFF
};

enum DYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE
{
	DYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_NORMAL = 1,
	DYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_RENTAL,
	DYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_NETP,
	DYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_CASH,

	DYNAMIC_OBJECT_HOIPOI_MACHINE_TYPE_NONE = 0xFF,
};

const unsigned int MAX_PC = 3000;
const unsigned int MAX_NPC = 3000;
const unsigned int MAX_MOB = 60000;
const unsigned int MAX_SUMMON_PET = MAX_PC;
const unsigned int MAX_ITEM_PET = MAX_PC;
const unsigned int MAX_DROP_ITEM = 3000;
const unsigned int MAX_DROP_MONEY = 3000;
const unsigned int MAX_PC_HAVE_ITEM = 200;
const unsigned int MAX_TRIGGER_OBJECT = 20000;
const unsigned int MAX_DYNAMIC_OBJECT = MAX_PC;
const unsigned int MAX_BOT = MAX_NPC + MAX_MOB + MAX_SUMMON_PET + MAX_ITEM_PET;
const unsigned int MAX_ITEM = MAX_PC * MAX_PC_HAVE_ITEM;
const unsigned int MAX_GAME_OBJECT = MAX_PC + MAX_BOT + MAX_ITEM + MAX_DROP_ITEM + MAX_DROP_MONEY + MAX_TRIGGER_OBJECT + MAX_DYNAMIC_OBJECT;
const float MAX_DISTANCE_OF_DYNAMIC_OBJECT = 20.0f;
const unsigned int DYNAMIC_OBJECT_CHECK_TERM = 1000;
const unsigned int DYNAMIC_OBJECT_DESPAWN_TERM = 1000;
const unsigned int DYNAMIC_OBJECT_SPAWN_TERM = 1000;

enum TIMEQUEST_TYPE
{
	TIMEQUEST_TYPE_TUTORIAL,
	TIMEQUEST_TYPE_PARTY,
	TIMEQUEST_TYPE_GROUP,

	MAX_TIMEQUEST_TYPE,
};

enum TIMEQUEST_MODE
{
	TIMEQUEST_MODE_INDIVIDUAL,
	TIMEQUEST_MODE_PARTY,

	MAX_TIMEQUEST_MODE,
	INVALID_TIMEQUEST_MODE = 0xFF,
};

enum TIMEQUEST_ROOM_STATE
{
	TIMEQUEST_ROOM_STATE_REGISTRAITION,
	TIMEQUEST_ROOM_STATE_WAITENTRY,	
	TIMEQUEST_ROOM_STATE_PC_DIRECTION,
	TIMEQUEST_ROOM_STATE_DAYRECORD_REQ,
	TIMEQUEST_ROOM_STATE_OBJECT_DIRECTION,
	TIMEQUEST_ROOM_STATE_PREPARE_WORLD,

	MAX_TIMEQUEST_ROOM_STATE,
	INVALID_TIMEQUEST_ROOM_STATE = 0xFF,
};

enum TIMEQUEST_GAME_STATE
{
	TIMEQUEST_GAME_STATE_WAIT,
	TIMEQUEST_GAME_STATE_PREPARE,
	TIMEQUEST_GAME_STATE_ARRIVE,
	TIMEQUEST_GAME_STATE_BEGIN,
	TIMEQUEST_GAME_STATE_STAGE_READY,
	TIMEQUEST_GAME_STATE_STAGE_START,
	TIMEQUEST_GAME_STATE_STAGE_FINISH,
	TIMEQUEST_GAME_STATE_END,
	TIMEQUEST_GAME_STATE_LEAVE,
	TIMEQUEST_GAME_STATE_FAIL,
	TIMEQUEST_GAME_STATE_CLOSE,

	MAX_TIMEQUEST_GAME_STATE
};

enum TIMEQUEST_STAGE_STATE
{
	MAX_TIMEQUEST_STAGE_STATE
};

enum TIMEQUEST_DIFFICULTY
{
	TIMEQUEST_DIFFICULTY_EASY,
	TIMEQUEST_DIFFICULTY_NORMAL,
	TIMEQUEST_DIFFICULTY_HARD,

	MAX_TIMEQUEST_DIFFICULTY,
	FIRST_TIMEQUEST_DIFFICULTY = TIMEQUEST_DIFFICULTY_EASY,
	INVALID_TIMEQUEST_DIFFICULTY = 0xFF,
};

enum TIMEQUEST_DIFFICULTY_FLAG
{
	TIMEQUEST_DIFFICULTY_FLAG_EASY = MAKE_BIT_FLAG(TIMEQUEST_DIFFICULTY_EASY),
	TIMEQUEST_DIFFICULTY_FLAG_NORMAL = MAKE_BIT_FLAG(TIMEQUEST_DIFFICULTY_NORMAL),
	TIMEQUEST_DIFFICULTY_FLAG_HARD = MAKE_BIT_FLAG(TIMEQUEST_DIFFICULTY_HARD),
};

enum TIMEQUEST_PROGRESS_MESSAGE_TYPE
{
	TIMEQUEST_PROGRESS_MESSAGE_TYPE_START,
	TIMEQUEST_PROGRESS_MESSAGE_TYPE_END,
	TIMEQUEST_PROGRESS_MESSAGE_TYPE_CLEAR,
	TIMEQUEST_PROGRESS_MESSAGE_TYPE_FAIL,

	MAX_TIMEQUEST_PROGRESS_MESSAGE_TYPE,
	INVALID_TIMEQUEST_PROGRESS_MESSAGE_TYPE = 0xFF,
};

enum TIMEQUEST_INFORMATION_TYPE
{
	TIMEQUEST_INFORMATION_TYPE_SCENARIO,
	TIMEQUEST_INFORMATION_TYPE_STAGE,

	MAX_TIMEQUEST_INFORMATION_TYPE,
	INVALID_TIMEQUEST_INFORMATION_TYPE = 0xFF,
};

const DWORD TIMEQUEST_MAX_ROOM_COUNT = 10; 
const DWORD TIMEQUEST_MAX_MEMBER_COUNT = MAX_MEMBER_IN_PARTY; 
const DWORD TIMEQUEST_ROOM_START_REPORT_TIME = 30000; 
const DWORD TIMEQUEST_ROOM_LEAVE_LIMIT_TIME = 60000;
const DWORD TIMEQUEST_MAX_STAGE_NUMBER = 64;
const DWORD TIMEQUEST_MAX_KILL_COUNT = 3;
const DWORD TIMEQUEST_ROOM_REFRESH_TIME = 10000;
const WORD TIMEQUEST_COUNPON_CHANGE_POINT = 1000;
const WORD TIMEQUEST_COUNPON_LIMIT_COUNT = 4;
const WORD TIMEQUEST_DEFAULT_DAYRECORD_RANK_COUNT = 5;
const WORD TIMEQUEST_DEFAULT_TOTAL_RANK_COUNT = TIMEQUEST_DEFAULT_DAYRECORD_RANK_COUNT + 1;

enum RANKBATTLE_ROOMSTATE
{
	RANKBATTLE_ROOMSTATE_NONE,
	RANKBATTLE_ROOMSTATE_WAIT,
	RANKBATTLE_ROOMSTATE_MATCH_READY,
	RANKBATTLE_ROOMSTATE_WAIT_MATCH_WORLD,
	RANKBATTLE_ROOMSTATE_MATCH_RUN,
	RANKBATTLE_ROOMSTATE_MATCH_END,

	RANKBATTLE_ROOMSTATE_COUNT,
	INVALID_RANKBATTLE_ROOMSTATE = INVALID_BYTE,
};

enum RANKBATTLE_MODE
{
	RANKBATTLE_MODE_INDIVIDUAL,
	RANKBATTLE_MODE_PARTY,

	MAX_RANKBATTLE_MODE,
	INVALID_RANKBATTLE_MODE = INVALID_BYTE
};

enum RANKBATTLE_TEAM_TYPE
{
	RANKBATTLE_TEAM_NONE = 0,
	RANKBATTLE_TEAM_OWNER = 0x01 << 0,
	RANKBATTLE_TEAM_CHALLENGER = 0x01 << 1,
	RANKBATTLE_TEAM_OTHER = 0x01 << 2,

	RANKBATTLE_TEAM_ALL = RANKBATTLE_TEAM_OWNER | RANKBATTLE_TEAM_CHALLENGER,
};

enum RANKBATTLE_BATTLESTATE
{
	RANKBATTLE_BATTLESTATE_NONE,
	RANKBATTLE_BATTLESTATE_WAIT,
	RANKBATTLE_BATTLESTATE_DIRECTION,
	RANKBATTLE_BATTLESTATE_STAGE_READY,
	RANKBATTLE_BATTLESTATE_STAGE_RUN,
	RANKBATTLE_BATTLESTATE_STAGE_FINISH,
	RANKBATTLE_BATTLESTATE_MATCH_FINISH,
	RANKBATTLE_BATTLESTATE_BOSS_DIRECTION,
	RANKBATTLE_BATTLESTATE_BOSS_READY,
	RANKBATTLE_BATTLESTATE_BOSS_RUN,
	RANKBATTLE_BATTLESTATE_BOSS_FINISH,	
	RANKBATTLE_BATTLESTATE_END,

	MAX_RANKBATTLE_BATTLESTATE,
	INVALID_RANKBATTLE_BATTLESTATE = INVALID_BYTE
};

enum RANKBATTLE_MEMBER_STATE
{
	RANKBATTLE_MEMBER_STATE_NONE,
	RANKBATTLE_MEMBER_STATE_NORMAL,	
	RANKBATTLE_MEMBER_STATE_FAINT,
	RANKBATTLE_MEMBER_STATE_OUTOFAREA,
	RANKBATTLE_MEMBER_STATE_GIVEUP,
	RANKBATTLE_MEMBER_STATE_NOAPPLY,
};

enum RANKBATTLE_MATCH_RESULT
{
	RANKBATTLE_MATCH_NONE,
	RANKBATTLE_MATCH_WIN_OWNER,
	RANKBATTLE_MATCH_WIN_CHALLENGER,
	RANKBATTLE_MATCH_DRAW,

	INVALID_RANKBATTLE_MATCH = INVALID_BYTE,
};

enum RANKBATTLE_QUERY_UPDATE_TYPE
{
	RANKBATTLE_QUERY_UPDATE_NONE,
	RANKBATTLE_QUERY_UPDATE_ADD,
	RANKBATTLE_QUERY_UPDATE_INIT,
};

const DWORD RANKBATTLE_MAX_ROOM_COUNT = 100;
const DWORD RANKBATTLE_MAX_ROOM_COUNT_PER_PAGE = 10;
const DWORD RANKBATTLE_USER_WAIT_TIME = 60000;
const DWORD RANKBATTLE_NAME_LENGTH = 128;
const BYTE RANKBATTLE_PARTY_MEMBER_RESTRICTION = 1;
const DWORD RANKBATTLE_ROOM_READY_TIME = 10000;
const DWORD RANKBATTLE_ENDSTAGE_WAIT_TIME = 5000;
const BYTE RANKBATTLE_MAX_RANK_BOARD_RECORD_COUNT = 10;
const BYTE RANKBATTLE_MAX_COMPARE_DAY = 7;
const DWORD RANKBATTLE_RANK_REQUEST_TERM = 500;
const BYTE _RANKBATTLE_RANK_BACKUP_TIME = 6;
const WORD RANKBATTLE_MAX_ARENA_TYPE = 10;
const DWORD	 RANKBATTLE_MATCH_START_TERM = 60;
const BYTE RANKBATTLE_MAX_MATCHING_LEVEL = 1;

enum PRIVATESHOP_STATE
{
	PRIVATESHOP_STATE_CLOSE = 0,
	PRIVATESHOP_STATE_OPEN,
	PRIVATESHOP_STATE_BUSINESS_WAIT,
	PRIVATESHOP_STATE_BUSINESS,
	PRIVATESHOP_STATE_NONE,
	PRIVATESHOP_STATE_NULL,
	PRIVATESHOP_STATE_DATALOADING
};

const BYTE MAX_PRIVATESHOP_INVENTORY = 36;
const int MAX_PRIVATESHOP_BUY_SHOPPING_CART = 12;
const BYTE PRIVATESHOP_ITEMPOS_INVALID = 0xFF;
const DWORD PRIVATESHOP_ITEM_BUY_ZENNY_DEFAULT = 1;

const DWORD MAX_BASIC_MAIL_SEND_ZENNY = 10;
const DWORD MAX_ATTACH_MAIL_SEND_ZENNY = 10;
const DWORD MAX_MAIL_SEND_ZENNY_AMOUNTS = 100000;
const DWORD MAX_MAIL_SLOT_COUNT = 30;
const DWORD MAIL_RELOAD_TIME = 1 * 60 * 1000;
const DWORD MAIL_DISTANCE_CHECK_TIME = 3 * 1000;
const BYTE DEFAULT_MAIL_KEEPING_PERIOD = 10;
const DWORD MAX_COUNT_OF_MULTI_DEL = 6;
const BYTE MAX_COUNT_MULTI_MAIL = 50;

enum MAIL_TYPE
{
	MAIL_TYPE_NONE,
	MAIL_TYPE_BASIC,
	MAIL_TYPE_ITEM,
	MAIL_TYPE_ZENNY,
	MAIL_TYPE_ITEM_ZENNY,
	MAIL_TYPE_ITEM_ZENNY_REQ, 
	MAIL_TYPE_ZENNY_REQ,
	MAIL_COUNT,
};

enum MAIL_SENDER_TYPE
{
	MAIL_SENDER_TYPE_BASIC,
	MAIL_SENDER_TYPE_REPLY,
	MAIL_SENDER_TYPE_RETURN,
	MAIL_SENDER_TYPE_SYSTEM,
	MAIL_SENDER_TYPE_GM,

};

enum TELEPORT_TYPE
{
	TELEPORT_TYPE_DEFAULT,
	TELEPORT_TYPE_GAME_IN,
	TELEPORT_TYPE_GAME_OUT,
	TELEPORT_TYPE_TELEPOPO,
	TELEPORT_TYPE_SKILL,
	TELEPORT_TYPE_NPC_PORTAL,
	TELEPORT_TYPE_POPOSTONE,
	TELEPORT_TYPE_WORLD_MOVE,
	TELEPORT_TYPE_TMQ_WORLD_MOVE,
	TELEPORT_TYPE_TMQ_PORTAL,

	TELEPORT_TYPE_RANKBATTLE,
	TELEPORT_TYPE_TIMEQUEST,
	TELEPORT_TYPE_TUTORIAL,
	TELEPORT_TYPE_BUDOKAI,
	TELEPORT_TYPE_MATCH,
	TELEPORT_TYPE_MINORMATCH,
	TELEPORT_TYPE_MAJORMATCH,
	TELEPORT_TYPE_FINALMATCH,

	TELEPORT_TYPE_COMMAND,
	TELEPORT_TYPE_GM,
	TELEPORT_TYPE_DUNGEON,
	TELEPORT_TYPE_DOJO,

	TELEPORT_TYPE_COUNT,

	TELEPORT_TYPE_INVALID = 0xFFui8,

	TELEPORT_TYPE_FIRST = TELEPORT_TYPE_GAME_IN,
	TELEPORT_TYPE_LAST = TELEPORT_TYPE_DUNGEON,
};

enum BIND_TYPE
{
	BIND_TYPE_INITIAL_LOCATION = 0,
	BIND_TYPE_POPO_STONE,
	BIND_TYPE_GM_TOOL,
	BIND_TYPE_SKILL,

	BIND_TYPE_FIRST = BIND_TYPE_INITIAL_LOCATION,
	BIND_TYPE_LAST = BIND_TYPE_SKILL,
	BIND_TYPE_INVALID = 0xFF
};

const int PORTAL_MAX_COUNT = 100;
const DWORD TELEPORT_PROPOSAL_WAIT_TIME = 120;

enum MATCHWORLD_TYPE
{
	MATCHWORLD_TYPE_MINOR_MATCH,
	MATCHWORLD_TYPE_MAJOR_MATCH,
	MATCHWORLD_TYPE_FINAL_MATCH,

	MAX_MATCHWORLD_TYPE,
	INVALID_MATCHWORLD_TYPE = 0xff
};

enum eMATCH_MEMBER_STATE
{
	MATCH_MEMBER_STATE_NONE,
	MATCH_MEMBER_STATE_NORMAL,	
	MATCH_MEMBER_STATE_FAINT,
	MATCH_MEMBER_STATE_OUTOFAREA,
	MATCH_MEMBER_STATE_GIVEUP,
	MATCH_MEMBER_STATE_NOAPPLY,
	MATCH_MEMBER_STATE_TELEPORTING,
	MATCH_MEMBER_STATE_BE_LATE,	
	MATCH_MEMBER_STATE_RESCUE,
};


enum MATCH_TEAM_TYPE
{
	MATCH_TEAM_TYPE_TEAM1,
	MATCH_TEAM_TYPE_TEAM2,

	MAX_MATCH_TEAM_TYPE_COUNT,
	INVALID_MATCH_TEAM_TYPE = 0xffff
};

enum MATCH_RESULT
{
	MATCH_RESULT_SUCCESS,
	MATCH_RESULT_DRAW,
	MATCH_RESULT_WIN,
	MATCH_RESULT_TIMEOVER,
	MATCH_RESULT_DOJO_RECOMMENDER,
	MATCH_RESULT_UNEARNED_WIN,

	INVALID_MATCH_RESULT = 0xff,
};

enum BUDOKAI_MINORMATCH_STATE
{
	BUDOKAI_MINORMATCH_STATE_NONE,
	BUDOKAI_MINORMATCH_STATE_WAIT_MINORMATCH,
	BUDOKAI_MINORMATCH_STATE_WAIT,
	BUDOKAI_MINORMATCH_STATE_DIRECTION,
	BUDOKAI_MINORMATCH_STATE_MATCH_READY,
	BUDOKAI_MINORMATCH_STATE_STAGE_READY,
	BUDOKAI_MINORMATCH_STATE_STAGE_RUN,
	BUDOKAI_MINORMATCH_STATE_STAGE_SELECTION,
	BUDOKAI_MINORMATCH_STATE_STAGE_FINISH,
	BUDOKAI_MINORMATCH_STATE_MATCH_FINISH,
	BUDOKAI_MINORMATCH_STATE_END,

	MAX_BUDOKAI_MINORMATCH_STATE,
	INVALID_BUDOKAI_MINORMATCH_STATE = INVALID_BYTE
};

enum BUDOKAI_MAJORMATCH_STATE
{
	BUDOKAI_MAJORMATCH_STATE_NONE,
	BUDOKAI_MAJORMATCH_STATE_WAIT,
	BUDOKAI_MAJORMATCH_STATE_DIRECTION,
	BUDOKAI_MAJORMATCH_STATE_MATCH_READY,
	BUDOKAI_MAJORMATCH_STATE_STAGE_READY,
	BUDOKAI_MAJORMATCH_STATE_STAGE_RUN,
	BUDOKAI_MAJORMATCH_STATE_STAGE_FINISH,
	BUDOKAI_MAJORMATCH_STATE_MATCH_FINISH,
	BUDOKAI_MAJORMATCH_STATE_END,

	MAX_BUDOKAI_MAJORMATCH_STATE,
	INVALID_BUDOKAI_MAJORMATCH_STATE = INVALID_BYTE
};

enum BUDOKAI_FINALMATCH_STATE
{
	BUDOKAI_FINALMATCH_STATE_NONE,
	BUDOKAI_FINALMATCH_STATE_WAIT,
	BUDOKAI_FINALMATCH_STATE_DIRECTION,
	BUDOKAI_FINALMATCH_STATE_MATCH_READY,
	BUDOKAI_FINALMATCH_STATE_STAGE_READY,
	BUDOKAI_FINALMATCH_STATE_STAGE_RUN,
	BUDOKAI_FINALMATCH_STATE_STAGE_FINISH,
	BUDOKAI_FINALMATCH_STATE_MATCH_FINISH,
	BUDOKAI_FINALMATCH_STATE_FINALDIRECTION,
	BUDOKAI_FINALMATCH_STATE_AWARDING,
	BUDOKAI_FINALMATCH_STATE_END,

	MAX_BUDOKAI_FINALMATCH_STATE,
	INVALID_BUDOKAI_FINALMATCH_STATE = INVALID_BYTE
};

enum FINALMATCH_TYPE
{
	FINALMATCH_TYPE_SEMIFINAL_1 = 0,
	FINALMATCH_TYPE_SEMIFINAL_2,
	FINALMATCH_TYPE_FINAL,

	FINALMATCH_TYPE_COUNT,
	INVALID_FINALMATCH_TYPE = 0xFF,
};

enum FINALMATCH_RESULT
{
	FINALMATCH_RESULT_WINNER,
	FINALMATCH_RESULT_SEMIWINNER,
	FINALMATCH_RESULT_MATCH1_LOSER,
	FINALMATCH_RESULT_MATCH2_LOSER,

	MAX_FINALMATCH_RESULT,
};

enum BUDOKAI_TYPE
{
	BUDOKAI_TYPE_JUNIOR,
	BUDOKAI_TYPE_ADULT,

	INVALID_BUDOKAI_TYPE = 0xff
};


enum BUDOKAI_MATCH_TYPE
{
	BUDOKAI_MATCH_TYPE_INDIVIDIAUL,
	BUDOKAI_MATCH_TYPE_TEAM,

	MAX_BUDOKAI_MATCH_TYPE,
	INVALID_BUDOKAI_MATCH_TYPE = 0xff,
};

enum BUDOKAI_NOTICE_TYPE
{
	BUDOKAI_NOTICE_SYSTEM,
	BUDOKAI_NOTICE_GM,
	BUDOKAI_NOTICE_ONLY_CLIENT,

	INVALID_BUDOKAI_NOTICE_TYPE = 0xff,
};

enum BUDOKAI_STATE
{
	BUDOKAI_STATE_JUNIOR_CLOSE,
	BUDOKAI_STATE_JUNIOR_OPEN_NOTICE,
	BUDOKAI_STATE_JUNIOR_DOJO_RECOMMEND,
	BUDOKAI_STATE_JUNIOR_OPEN,
	BUDOKAI_STATE_JUNIOR_CLEAR,

	BUDOKAI_STATE_CLOSE,
	BUDOKAI_STATE_OPEN_NOTICE,
	BUDOKAI_STATE_DOJO_RECOMMEND,
	BUDOKAI_STATE_OPEN,
	BUDOKAI_STATE_CLEAR,

	MAX_BUDOKAI_STATE,
	BUDOKAI_STATE_JUNIOR_FIRST = BUDOKAI_STATE_JUNIOR_CLOSE,
	BUDOKAI_STATE_JUNIOR_LAST = BUDOKAI_STATE_JUNIOR_CLEAR,
	BUDOKAI_STATE_ADULT_FIRST = BUDOKAI_STATE_CLOSE,
	BUDOKAI_STATE_ADULT_LAST = BUDOKAI_STATE_CLEAR,
	BUDOKAI_STATE_FIRST = BUDOKAI_STATE_JUNIOR_CLOSE,
	BUDOKAI_STATE_LAST = BUDOKAI_STATE_CLEAR,
	INVALID_BUDOKAI_STATE = 0xff,
};

enum BUDOKAI_MATCHSTATE
{
	BUDOKAI_MATCHSTATE_REGISTER,
	BUDOKAI_MATCHSTATE_WAIT_MINOR_MATCH,
	BUDOKAI_MATCHSTATE_MINOR_MATCH,
	BUDOKAI_MATCHSTATE_WAIT_MAJORMATCH_32,
	BUDOKAI_MATCHSTATE_MAJORMATCH_32,
	BUDOKAI_MATCHSTATE_WAIT_MAJORMATCH_16,
	BUDOKAI_MATCHSTATE_MAJORMATCH_16,
	BUDOKAI_MATCHSTATE_WAIT_MAJORMATCH_08,
	BUDOKAI_MATCHSTATE_MAJORMATCH_08,
	BUDOKAI_MATCHSTATE_WAIT_SEMIFINAL_MATCH,
	BUDOKAI_MATCHSTATE_SEMIFINAL_MATCH,
	BUDOKAI_MATCHSTATE_WAIT_FINAL_MATCH,
	BUDOKAI_MATCHSTATE_FINAL_MATCH,
	BUDOKAI_MATCHSTATE_MATCH_END,

	MAX_BUDOKAI_MATCHSTATE,
	INVALID_BUDOKAI_MATCHSTATE = 0xff,
};

enum BUDOKAI_JOIN_STATE
{
	BUDOKAI_JOIN_STATE_PLAY = 0,
	BUDOKAI_JOIN_STATE_DROPOUT,	

	INVALID_BUDOKAI_JOIN_STATE = 0xff,
};

enum BUDOKAI_JOIN_RESULT
{
	BUDOKAI_JOIN_RESULT_REGISTER = 0,
	BUDOKAI_JOIN_RESULT_MINORMATCH,
	BUDOKAI_JOIN_RESULT_ENTER_32,
	BUDOKAI_JOIN_RESULT_ENTER_16,
	BUDOKAI_JOIN_RESULT_ENTER_8,
	BUDOKAI_JOIN_RESULT_ENTER_4,
	BUDOKAI_JOIN_RESULT_ENTER_2,
	BUDOKAI_JOIN_RESULT_WINNER,

	INVALID_BUDOKAI_JOIN_RESULT = 0xff
};


enum BUDOKAI_MATCH_DEPTH
{
	BUDOKAI_MATCH_DEPTH_2 = 0,	// 1	2^0
	BUDOKAI_MATCH_DEPTH_4,		// 2	2^1
	BUDOKAI_MATCH_DEPTH_8,		// 4	2^2
	BUDOKAI_MATCH_DEPTH_16,		// 8	2^3
	BUDOKAI_MATCH_DEPTH_32,		// 16	2^4

	BUDOKAI_MATCH_DEPTH_COUNT,
	MAX_BUDOKAI_MATCH_DEPTH_INDIVIDUAL = BUDOKAI_MATCH_DEPTH_32,
	MAX_BUDOKAI_MATCH_DEPTH_TEAM = BUDOKAI_MATCH_DEPTH_16,
	INVALID_BUDOKAI_MATCH_DEPTH = 0xff,
};

enum BUDOKAI_PROGRESS_MESSAGE
{
	BUDOKAI_PROGRESS_MESSAGE_START = 0,

	BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_ENTERING,
	BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_BEFORE_1MIN,
	BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_WINNER,
	BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_LOSER,
	BUDOKAI_PROGRESS_MESSAGE_MINORMATCH_ALL_FINISHED,

	BUDOKAI_PROGRESS_MESSAGE_DEPTH_32_BEFORE_10SEC,
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_32_WINNER,
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_32_LOSER,
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_32_ALL_FINISHED,

	BUDOKAI_PROGRESS_MESSAGE_DEPTH_16_BEFORE_10SEC,
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_16_WINNER,
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_16_LOSER,
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_16_ALL_FINISHED,

	BUDOKAI_PROGRESS_MESSAGE_DEPTH_08_BEFORE_10SEC,
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_08_WINNER,
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_08_LOSER,
	BUDOKAI_PROGRESS_MESSAGE_DEPTH_08_ALL_FINISHED,

	BUDOKAI_PROGRESS_MESSAGE_SEMI_FINAL_BEFORE_10SEC,
	BUDOkAI_PROGRESS_MESSAGE_SEMI_FINAL_RUNNING,
	BUDOkAI_PROGRESS_MESSAGE_FINAL_WAIT_LOSER,

	BUDOkAI_PROGRESS_MESSAGE_END,

	INVALID_BUDOKAI_PROGRESS_MESSAGE = 0xff,
};

#define INVALID_MUDOSAPOINT INVALID_DWORD
#define MAX_MUDOSA_POINT (500000)
#define BUDOKAI_SERVER_INDEX 0
#define BUDOKAI_MAX_NOTICE_LENGTH 255
#define BUDOKAI_MAX_INDIVIDUAL_DB_DATA_PACKET_COUNT	20
#define BUDOKAI_MAX_TEAM_DB_DATA_PACKET_COUNT (int)(BUDOKAI_MAX_INDIVIDUAL_DB_DATA_PACKET_COUNT / MAX_MEMBER_IN_PARTY)
#define	BUDOKAI_MAX_TOURNAMENT_INDIVIDUAL_ENTRY_PACKET_COUNT (MAX_MEMBER_IN_PARTY * 4)
#define	BUDOKAI_MAX_TOURNAMENT_TEAM_ENTRY_PACKET_COUNT 4
#define BUDOKAI_MAX_INDIVIDUAL_REGISTER_COUNT 10000
#define BUDOKAI_MAX_TEAM_REGISTER_COUNT 2000
#define BUDOKAI_MIN_TEAM_MEMBER_COUNT 1
#define BUDOKAI_MAX_TEAM_MEMBER_COUNT MAX_MEMBER_IN_PARTY;
#define	BUDOKAI_MAX_INDIVIDUAL_MATCH_COUNT 32
#define	BUDOKAI_MAX_TEAM_MATCH_COUNT 16
#if BUDOKAI_MAX_INDIVIDUAL_MATCH_COUNT > BUDOKAI_MAX_TEAM_MATCH_COUNT
#define BUDOKAI_MAX_MATCH_COUNT BUDOKAI_MAX_INDIVIDUAL_MATCH_COUNT
#else
#define BUDOKAI_MAX_MATCH_COUNT BUDOKAI_MAX_TEAM_MATCH_COUNT
#endif
#define BUDOKAI_MINOR_MATCH_INDIVIDUAL_COUNT 15
#define BUDOKAI_MINOR_MATCH_TEAM_COUNT 5
#if BUDOKAI_MINOR_MATCH_INDIVIDUAL_COUNT > BUDOKAI_MINOR_MATCH_TEAM_COUNT
#define BUDOKAI_MAX_MINORMATCH_TEAM_COUNT BUDOKAI_MINOR_MATCH_INDIVIDUAL_COUNT
#else
#define BUDOKAI_MAX_MINORMATCH_TEAM_COUNT BUDOKAI_MINOR_MATCH_TEAM_COUNT
#endif
#define BUDOKAI_MINOR_MATCH_MAX_INDIVIDUAL_COUNT (BUDOKAI_MINOR_MATCH_INDIVIDUAL_COUNT * BUDOKAI_MAX_INDIVIDUAL_MATCH_COUNT)
#define BUDOKAI_MINOR_MATCH_MAX_TEAM_COUNT (BUDOKAI_MINOR_MATCH_TEAM_COUNT * BUDOKAI_MAX_TEAM_MATCH_COUNT)
#define BUDOKAI_MINOR_MATCH_MAX_TEAM_MEMBER_COUNT (BUDOKAI_MINOR_MATCH_MAX_TEAM_COUNT * MAX_MEMBER_IN_PARTY)
#define BUDOKAI_MAJOR_MATCH_PLAYER_NUMBER (BUDOKAI_MAX_INDIVIDUAL_MATCH_COUNT)
#define BUDOKAI_MAJOR_MATCH_TEAM_NUMBER (BUDOKAI_MAX_TEAM_MATCH_COUNT)
#define BUDOKAI_MINORMATCH_RESCUE_TIME 10
#define BUDOKAI_MINORMATCH_SELECTION_STATE_TIME 20
#define BUDOKAI_MINORMATCH_SELECTION_NUMBER 100
#define BUDOKAI_MAX_MUDOSA_INFO_COUNT 5
#define BUDOKAI_MAX_MUDOSA_PLAYER_COUNT 200
#define BUDOKAI_MAX_MUDOSA_NAME_IN_UNICODE 32
#define BUDOKAI_MAX_TOURNAMENT_INDIVIDUAL_MATCH_COUNT (BUDOKAI_MAJOR_MATCH_PLAYER_NUMBER - 1)
#define BUDOKAI_MAX_TOURNAMENT_TEAM_MATCH_COUNT (BUDOKAI_MAJOR_MATCH_TEAM_NUMBER - 1)
#define BUDOKAI_MAX_FINALMATCH_TEAM_COUNT 4
#define BUDOKAI_MAX_TOURNAMENT_INDIVIDUAL_MATCH_RECORD_COUNT (BUDOKAI_MAJOR_MATCH_PLAYER_NUMBER * 2)
#define BUDOKAI_MAX_TOURNAMENT_TEAM_MATCH_RECORD_COUNT (BUDOKAI_MAJOR_MATCH_TEAM_NUMBER * 2)
#define	BUDOKAI_MAX_SEASON_HISTORY_INDIVIAUL_WINNER_COUNT (4)
#define	BUDOKAI_MAX_SEASON_HISTORY_TEAM_WINNER_COUNT (MAX_MEMBER_IN_PARTY * 4)
#define	BUDOKAI_MAX_SEASON_HISTORY_WINNER_PLAYER_COUNT (BUDOKAI_MAX_SEASON_HISTORY_INDIVIAUL_WINNER_COUNT + BUDOKAI_MAX_SEASON_HISTORY_TEAM_WINNER_COUNT)
const BYTE BUDOkAI_MAX_PLAYER_JOIN_STATE_DATA_COUNT = 100;

enum ITEM_MIX_RESULT_TYPE
{
	ITEM_MIX_RESULT_TYPE_FAIL,
	ITEM_MIX_RESULT_TYPE_SUCCESS,
	ITEM_MIX_RESULT_TYPE_GREAT_SUCCESS,

	ITEM_MIX_RESULT_TYPE_NUMS
};

enum RECIPE_TYPE
{
	RECIPE_NORMAL,
	RECIPE_MAINWEAPON,
	RECIPE_ARMOR,
	RECIPE_ACCESSORY,
	RECIPE_SCOUTER,
	RECIPE_SUBWEAPON,

	RECIPE_INVALID = 0xFF,
};

#pragma pack(1)

struct TIME
{
	TIME()
	{
		minute = 0;
		second = 0;
	};
	WORD year;
	BYTE month;
	BYTE day;
	BYTE hour;
	BYTE minute;
	BYTE second;
};

struct SRVINFO
{
	BYTE CharServerIP[MAX_SRVADDR_SIZE + 1];
	WORD CharServerPort;
	DWORD Load;
};

struct GAMESERVER_INFO
{
	GAMESERVER_INFO() :
		serverId(INVALID_SERVERID),
		ServerStatus(SERVERSTATUS_DOWN),
		MaxLoad(0),
		Load(0)
	{
		::ZeroMemory(ServerName, sizeof(ServerName));
	};

	BYTE serverId;
	WCHAR ServerName[MAX_SERVERNAME_SIZE + 1];
	BYTE ServerStatus;
	DWORD MaxLoad;
	DWORD Load;
};

struct GAMECHANNEL_INFO
{
	GAMECHANNEL_INFO() :
		serverId(INVALID_SERVERID),
		ChannelId(INVALID_SLOTID),
		IsVisible(true),
		ServerStatus(SERVERSTATUS_DOWN),
		MaxLoad(0),
		Load(0)
	{
	};

	BYTE serverId;
	BYTE ChannelId;
	bool IsVisible;
	BYTE ServerStatus;
	DWORD MaxLoad;
	DWORD Load;
};

struct ITEMDATA
{
	unsigned int tblidx;
	BYTE Rank;
	BYTE Grade;
	BYTE BattleAttribute;
	unsigned int OptionTblidx[MAX_ITEM_OPTION];
};

struct MARKING
{
	BYTE Code;
public:
	MARKING()
		: Code(INVALID_MARKING_TYPE)
	{
	}
};

struct DOGIDATA
{
	bool IsIntialized;
	int guildId;
	BYTE Type;
	BYTE GuildColor;
	BYTE DojoColor;
};

struct CHARDATA
{
	unsigned int charId;
	WCHAR Name[MAX_CHARNAME_SIZE + 1];
	BYTE Race;
	BYTE Class;
	bool IsAdult;
	BYTE Gender;
	BYTE Face;
	BYTE Hair;
	BYTE HairColor;
	BYTE SkinColor;
	BYTE Level;
	unsigned int worldTblidx;
	unsigned int worldId;
	float PositionX;
	float PositionY;
	float PositionZ;
	DWORD Money;
	DWORD MoneyBank;
	ITEMDATA Item[EQUIP_SLOT_TYPE_COUNT];
	DWORD MapInfoId;
	bool TutorialFlag;
	MARKING Marking;
	bool NeedNameChange;
	DOGIDATA Dogi;
};

struct TODEL_CHARINFO
{
	int charId;
	DWORD PastTick;
};

struct SHORTCUT_UPDATE_DATA
{
	BYTE Type;
	WORD ActionID;
	WORD Key;
};

struct SHORTCUT_DATA
{
	WORD ActionID;
	WORD Key;
};

struct SHOP_BUYCART
{
	BYTE MerchantTab;
	BYTE ItemPos;
	BYTE Stack;
};

struct SHOP_SELLCART
{
	BYTE Place;
	BYTE Pos;
	BYTE Stack;
};

struct EMPTY_INVEN
{
	BYTE Place;
	BYTE Pos;
};

struct ITEMPOS_DATA
{
	unsigned int Item;
	BYTE Place;
	BYTE Pos;
};

struct GUILD_MARK
{
	bool IsIntialized;
	BYTE MarkMain;
	BYTE MarkMainColor;
	BYTE MarkInLine;
	BYTE MarkInColor;
	BYTE MarkOutLine;
	BYTE MarkOutColor;
};

struct GAMEMANIA_TIME_DATA
{
	DWORD SetTime;
	BYTE TimeSlot[GMT_MAX_EFFECT_LIST_SIZE][GMT_MAX_TIME_SLOT_SIZE];
};

struct GAMEMANIA_TIME
{
	BYTE TimeSlot[GMT_MAX_EFFECT_LIST_SIZE][GMT_MAX_TIME_SLOT_SIZE];
};

struct PCHAR_SHAPE
{
	BYTE Face;
	BYTE Hair;
	BYTE HairColor;
	BYTE SkinColor;
};

struct AVATAR_ATTRIBUTE
{
	BYTE BaseStr;
	BYTE LastStr;
	BYTE BaseCon;
	BYTE LastCon;
	BYTE BaseFoc;
	BYTE LastFoc;
	BYTE BaseDex;
	BYTE LastDex;
	BYTE BaseSol;
	BYTE LastSol;
	BYTE BaseEng;
	BYTE LastEng;
	WORD BaseMaxLP;
	WORD LastMaxLP;
	WORD BaseMaxEP;
	WORD LastMaxEP;
	WORD BaseMaxRP;
	WORD LastMaxRP;
	WORD BaseLpRegen;
	WORD LastLpRegen;
	WORD BaseLpSitdownRegen;
	WORD LastLpSitdownRegen;
	WORD BaseLpBattleRegen;
	WORD LastLpBattleRegen;
	WORD BaseEpRegen;
	WORD LastEpRegen;
	WORD BaseEpSitdownRegen;
	WORD LastEpSitdownRegen;
	WORD BaseEpBattleRegen;
	WORD LastEpBattleRegen;
	WORD BaseRpRegen;
	WORD LastRpRegen;
	WORD LastRpDimimutionRate;
	WORD BasePhysicalOffence;
	WORD LastPhysicalOffence;
	WORD BasePhysicalDefence;
	WORD LastPhysicalDefence;
	WORD BaseEnergyOffence;
	WORD LastEnergyOffence;
	WORD BaseEnergyDefence;
	WORD LastEnergyDefence;
	WORD BaseAttackRate;
	WORD LastAttackRate;
	WORD BaseDodgeRate;
	WORD LastDodgeRate;
	WORD BaseBlockRate;
	WORD LastBlockRate;
	WORD BaseCurseSuccessRate;
	WORD LastCurseSuccessRate;
	WORD BaseCurseToleranceRate;
	WORD LastCurseToleranceRate;
	WORD BasePhysicalCriticalRate;
	WORD LastPhysicalCriticalRate;
	WORD BaseEnergyCriticalRate;
	WORD LastEnergyCriticalRate;
	float LastRunSpeed;
	WORD BaseAttackSpeedRate;
	WORD LastAttackSpeedRate;
	float BaseAttackRange;
	float LastAttackRange;
	float CastingTimeChangePercent;
	float CoolTimeChangePercent;
	float KeepTimeChangePercent;
	float DotValueChangePercent;
	float DotTimeChangeAbsolute;
	float RequiredEpChangePercent;
	float HonestOffence;
	float HonestDefence;
	float StrangeOffence;
	float StrangeDefence;
	float WildOffence;
	float WildDefence;
	float EleganceOffence;
	float EleganceDefence;
	float FunnyOffence;
	float FunnyDefence;
	WORD ParalyzeToleranceRate;
	WORD TerrorToleranceRate;
	WORD ConfuseToleranceRate;
	WORD StoneToleranceRate;
	WORD CandyToleranceRate;
	float ParalyzeKeepTimeDown;
	float TerrorKeepTimeDown;
	float ConfuseKeepTimeDown;
	float StoneKeepTimeDown;
	float CandyKeepTimeDown;
	float BleedingKeepTimeDown;
	float PoisonKeepTimeDown;
	float StomachacheKeepTimeDown;
	float CriticalBlockSuccessRate;
	WORD GuardRate;
	float SkillDamageBlockModeSuccessRate;
	float CurseBlockModeSuccessRate;
	float KnockdownBlockModeSuccessRate;
	float HtbBlockModeSuccessRate;
	float SitDownLpRegenBonusRate;
	float SitDownEpRegenBonusRate;
	float PhysicalCriticalDamageBonusRate;
	float EnergyCriticalDamageBonusRate;
	float ItemUpgradeBonusRate;
	float ItemUpgradeBreakBonusRate;
};

struct HOIPOIMIX_DATA
{
	bool NormalStart;
	bool SpecialStart;
	BYTE SpecialType;
	BYTE MixLevel;
	DWORD MixExp;
};

struct PC_PROFILE_LOCALIZE_DEV
{
};

struct PC_PROFILE_LOCALIZE_CJIKOR
{
	DWORD netP;
};

struct PC_PROFILE_LOCALIZE
{
	BYTE type;
	union
	{
		PC_PROFILE_LOCALIZE_DEV pcProfileDev;
		PC_PROFILE_LOCALIZE_CJIKOR pcProfileCJKor;
	};
};

struct PCHAR_PROFILE
{
	unsigned int tblidx;
	bool IsAdult;
	bool ChangeClass;
	unsigned int charId;
	WCHAR Name[MAX_CHARNAME_SIZE + 1];
	PCHAR_SHAPE CharShape;
	AVATAR_ATTRIBUTE avatarAttribute;
	WORD CurLP;
	WORD CurEP;
	WORD CurRP;
	BYTE Level;
	DWORD CurExp;
	DWORD MaxExpInThisLevel;
	DWORD Zenny;
	DWORD TutorialHint;
	BYTE BindType;
	unsigned int bindWorldId;
	unsigned int bindObjectTblidx;
	DWORD Reputation;
	DWORD MudosaPoint;
	DWORD SpPoint;
	MARKING	Marking;
	HOIPOIMIX_DATA MixData;
	bool IsGameMaster;
	unsigned int guildId;
	PC_PROFILE_LOCALIZE Localize;
};

struct CHARSTATE_SPAWNING
{
	BYTE TeleportType;
};

struct CHARSTATE_DESPAWNING
{
	BYTE TeleportType;
};

struct CHARSTATE_STANDING
{
};

struct CHARSTATE_SITTING
{
};

struct CHARSTATE_FAINTING
{
	BYTE Reason;
};

struct CHARSTATE_CAMPING
{
};

struct CHARSTATE_LEAVING
{
	BYTE LeavingType;
};

struct CHARSTATE_MOVING
{
	DWORD TimeStamp;
	BYTE MoveFlag;
	BYTE MoveDirection;
};

struct CHARSTATE_DESTMOVE
{
	DWORD TimeStamp;
	BYTE MoveFlag;
	bool HaveSecondDestLoc;
	VECTORXYZ SecondDestLoc;
	BYTE DestLocCount;
	VECTORXYZ DestLoc[MAX_NEXTDESTLOC_COUNT];
};

struct CHARSTATE_FOLLOWING
{
	DWORD TimeStamp;
	BYTE MoveFlag;
	unsigned int Target;
	float Distance;
	BYTE MovementReason;
};

struct CHARSTATE_FALLING
{
	BYTE MoveDirection;
};

struct CHARSTATE_DASH_PASSIVE
{
	DWORD TimeStamp;
	BYTE MoveDirection;
	VECTORXYZ DestLoc;
};

struct CHARSTATE_TELEPORTING
{
	BYTE TeleportType;
};

struct CHARSTATE_SLIDING
{
	VECTORXYZ Shift;
};

struct CHARSTATE_KNOCKDOWN
{
	VECTORXYZ Shift;
};

struct CHARSTATE_FOCUSING
{
};

struct CHARSTATE_CASTING
{
	unsigned int skillId;
	unsigned int Target;
	DWORD CastingTime;
	DWORD CastingTimeRemaining;
};

struct CHARSTATE_SKILL_AFFECTING
{
	unsigned int skillId;
	unsigned int Target;
};

struct CHARSTATE_KEEPING_EFFECT
{
};

struct CHARSTATE_CASTING_ITEM
{
	unsigned int itemTblidx;
	unsigned int Target;
	DWORD CastingTime;
	DWORD CastingTimeRemaining;
};

struct CHARSTATE_STUNNED
{
	BYTE StunType;
};

struct CHARSTATE_SLEEPING
{
};

struct CHARSTATE_PARALYZED
{
};

struct SKILL_DATA
{
	BYTE Slot;
	unsigned int skillId;
	int RemainSec;
	int Exp;
	BYTE yRpBonusType;
	bool IsRpBonusAuto;
};

struct BUFF_DATA
{
	unsigned int sourceTblidx;
	BYTE SourceType;
	DWORD InitialDuration;
	DWORD TimeRemaining;
	int Argument1;
	int Argument2;
	float EffectValue1;
	float EffectValue2;
	BYTE BuffGroup;
};


struct PET_BUFF_DATA
{
	BYTE AvatarType;
	BYTE SourceType;
	unsigned int sourceTblidx;
	DWORD InitialDuration;
	DWORD TimeRemaining;
	int Argument1;
	int Argument2;
	float EffectValue1;
	float EffectValue2;
};

struct HTB_SKILL_DATA
{
	unsigned int skillId;
	int SkillTime;
};

struct SKILL_INFO
{
	unsigned int tblidx;
	DWORD TimeRemaining;
	int Exp;
	BYTE SlotId;
	BYTE RpBonusType;
	bool IsRpBonusAuto;
};

struct SKILL_INFO_PET
{
	unsigned int tblidx;
	BYTE SlotIndex;
};


struct BUFF_INFO
{
	unsigned int sourceTblidx;
	BYTE SourceType;
	DWORD InitialDuration;
	DWORD TimeRemaining;
	float EffectValue[MAX_EFFECTSKILL];
};

struct HTB_SKILL_INFO
{
	unsigned int skillId;
	BYTE SlotId;
	DWORD TimeRemaining;
};

struct SYSTEM_EFFECT_RESULT
{
	SYSTEM_EFFECT_RESULT_TYPE ResultType;
	union
	{
		float ResultValue;

		// DH/HOT
		struct
		{
			float DH_HOT_fHealAmount;
		};

		// DD/DOT
		struct
		{
			float DD_DOT_fDamage;
			float DD_DOT_fAbsorbedDamage;
			float DD_DOT_fReflectedDamage;
		};

		// ACTIVE_LP_STEAL, ACTIVE_EP_STEAL, ACTIVE_LP_STEAL_OVER_TIME, ACTIVE_EP_STEAL_OVER_TIME
		struct
		{
			float LP_EP_STEAL_fLpDamage;
			float LP_EP_STEAL_fEpDamage;
			float LP_EP_STEAL_fAbsorbedDamage;
			float LP_EP_STEAL_fReflectedDamage;
			float LP_EP_STEAL_fLpGained;
			float LP_EP_STEAL_fEpGained;
		};
	};
};

struct SKILL_RESULT
{
	unsigned int Target;
	BYTE AttackResult;
	SYSTEM_EFFECT_RESULT effectResult1;
	SYSTEM_EFFECT_RESULT effectResult2;
	BYTE BlockedAction;
	VECTORXYZ Shift;
};

struct HTBSKILL_RESULT
{
	BYTE Step;
	SKILL_RESULT SkillResult;
};

struct CHARSTATE_HTB
{
	unsigned int HTBId;
	unsigned int Target;
	BYTE StepCount;
	BYTE CurStep;
	BYTE ResultCount;
	HTBSKILL_RESULT	HTBSkillResult[MAX_HTBSKILL_COUNT];
};

struct CHARSTATE_SANDBAG
{
};

struct CHARSTATE_CHARGING
{
};

struct CHARSTATE_BLOCKING
{
};

struct SUMMARY_PRIVATESHOP_DATA
{
	bool IsOwnerEmpty;
	BYTE  ShopState;
	WCHAR PrivateShopName[MAX_PRIVATESHOPNAME_USIZE + 1];
};

struct CHARSTATE_PRIVATESHOP
{
	SUMMARY_PRIVATESHOP_DATA SummaryPrivateShopData;
};

struct CHARSTATE_DIRECT_PLAY
{
	BYTE DirectPlayType;
	unsigned int directTblidx;
};

struct CHARSTATE_OPERATING
{
	unsigned int TargetObject;
	DWORD OperateTime;
	unsigned int directTblidx;
};

struct CHARSTATE_RIDEON
{
	unsigned int Target;
};

struct CHARSTATE_TURNING
{
	unsigned int directTblidx;
	VECTORXYZ DestDir;
};

struct ASPECTSTATE_SUPER_SAIYAN
{
	BYTE SourceGrade;
};

struct ASPECTSTATE_PURE_MAJIN
{
	BYTE SourceGrade;
};

struct ASPECTSTATE_GREAT_NAMEK
{
	BYTE SourceGrade;
};

struct ASPECTSTATE_KAIOKEN
{
	BYTE SourceGrade;
	BYTE RepeatingCount;
};

struct ASPECTSTATE_SPINNING_ATTACK
{
};

struct ASPECTSTATE_VEHICLE
{
	unsigned int idVehicleTblidx;
	bool IsEngineOn;
};

struct ASPECTSTATE_BASE
{
	BYTE AspectStateId;
};

union ASPECTSTATE_DETAIL
{
	ASPECTSTATE_SUPER_SAIYAN SuperSaiyan;
	ASPECTSTATE_PURE_MAJIN PureMajin;
	ASPECTSTATE_GREAT_NAMEK GreatNamek;
	ASPECTSTATE_KAIOKEN Kaioken;
	ASPECTSTATE_SPINNING_ATTACK SpinningAttack;
	ASPECTSTATE_VEHICLE Vehicle;
};

struct ASPECTSTATE
{
	ASPECTSTATE_BASE AspectStateBase;
	ASPECTSTATE_DETAIL AspectStateDetail;
};

struct CHARSTATE_BASE
{
	BYTE StateID;
	DWORD StateTime;
	DWORD ConditionFlag;
	ASPECTSTATE	aspectState;
	bool FightMode : 1;
	VECTORXYZ CurLoc;
	VECTORXYZ CurDir;
};

union CHARSTATE_DETAIL
{
	CHARSTATE_SPAWNING CharStateSpawning;
	CHARSTATE_DESPAWNING CharStateDespawning;
	CHARSTATE_STANDING CharStateStanding;
	CHARSTATE_SITTING CharStateSitting;
	CHARSTATE_FAINTING CharStateFainting;
	CHARSTATE_CAMPING CharStateCamping;
	CHARSTATE_LEAVING CharStateLeaving;
	CHARSTATE_MOVING CharStateMoving;
	CHARSTATE_DESTMOVE CharStateDestMove;
	CHARSTATE_FOLLOWING	CharStateFollwing;
	CHARSTATE_FALLING CharStateFalling;
	CHARSTATE_DASH_PASSIVE CharStateDashPassive;
	CHARSTATE_TELEPORTING CharStateTeleporting;
	CHARSTATE_SLIDING CharStateSliding;
	CHARSTATE_KNOCKDOWN CharStateKnockdown;
	CHARSTATE_FOCUSING CharStateFocusing;
	CHARSTATE_CASTING CharStateCasting;
	CHARSTATE_SKILL_AFFECTING CharStateSkillAffecting;
	CHARSTATE_KEEPING_EFFECT CharStateKeepingEffect;
	CHARSTATE_CASTING_ITEM CharStateCastingItem;
	CHARSTATE_STUNNED CharStateStunned;
	CHARSTATE_SLEEPING CharStateSleeping;
	CHARSTATE_PARALYZED CharStateParalyzed;
	CHARSTATE_HTB CharStateHTB;
	CHARSTATE_SANDBAG CharStateSandBag;
	CHARSTATE_CHARGING CharStateCharging;
	CHARSTATE_PRIVATESHOP CharStatePrivateShop;
	CHARSTATE_DIRECT_PLAY CharStateDirectPlay;
	CHARSTATE_OPERATING CharStateOperating;
	CHARSTATE_RIDEON CharStateRideOn;
	CHARSTATE_TURNING CharStateTurning;
};

struct CHARSTATE
{
	CHARSTATE_BASE CharStateBase;
	CHARSTATE_DETAIL CharStateDetail;
};

struct ITEM_PROFILE
{
	unsigned int handle;
	unsigned int tblidx;
	BYTE Place;
	BYTE Pos;
	BYTE Stackcount;
	BYTE Rank;
	BYTE CurDur;
	bool NeedToIdentify;
	BYTE Grade;
	BYTE BattleAttribute;
	BYTE RestrictType;
	WCHAR Maker[MAX_CHARNAME_SIZE + 1];
	unsigned int OptionTblidx[MAX_ITEM_OPTION];
	BYTE DurationType;
	time_t UseStartTime;
	time_t UseEndTime;
};

struct TIMEQUEST_STAGE
{
	BYTE StageNumber;
};

struct TIMEQUEST_STATE
{
	BYTE GameState;
	TIMEQUEST_STAGE TimeQuestStage;
};

struct TIMEQUEST_RULE_INFO
{
	unsigned int timeQuestTblidx;
	BYTE StartHour;
	BYTE StartMin;
	BYTE TimeQuestMode;
	BYTE Difficulty;
	bool CountDown;
	DWORD LimitTime;
	DWORD BonusTime;
	DWORD DayRecord; 
	TIMEQUEST_STATE TimeQuestState;
};

struct GAME_RULE_INFO
{
	BYTE RuleType;
	union
	{
		TIMEQUEST_RULE_INFO	TimeQuestRuleInfo;
	};
};


struct WORLD_INFO
{
	unsigned int worldID;
	unsigned int tblidx;
	unsigned int TriggerObjectOffset;
	GAME_RULE_INFO RuleInfo;
};

struct WORLD_ZONE_INFO
{
	unsigned int zoneId;
	bool IsDark;
};

struct DOJO_BRIEF
{
	unsigned int guildId;
	unsigned int dojoTblidx;
	BYTE Level;
	GUILD_MARK Mark;
};

struct COMPLETE_QUEST_INFO
{
	BYTE QCInfo[QUEST_ID_RANGE_QUEST_MAX / COMPLETE_QUEST_QUEST_PER_BYTE];
};

struct COMPLETE_QUEST_BIT_INFO
{
	BYTE QCBitInfo[COMPLETE_QUEST_QUEST_PER_STRUCT / COMPLETE_QUEST_QUEST_PER_BYTE];
};

struct COMPLETE_QUEST_TOTAL_BIT_INFO
{
	COMPLETE_QUEST_BIT_INFO QCBitInfo[COMPLETE_QUEST_QUEST_STRUCT_COUNT]; 
};

struct MAIN_TSP
{
	BYTE CurId;
	BYTE PreId;
};

struct EXCEPT_TIMER
{
	BYTE tcId;
	BYTE taId;
	unsigned int uiRemainTime;
};

struct EXCEPT_TIMER_SLOT
{
	EXCEPT_TIMER ExceptTimer[4];
};

struct STORAGE_SLOT_MEMORY
{
	unsigned int uiSSM[8];
};

struct STOC_EVT_DB_DATA
{
	BYTE tcId;
	BYTE taId;
	unsigned int m_aUserData[4];
	void Init(void)
	{
		tcId = taId = 0xFF;
		memset(m_aUserData, 0, sizeof(m_aUserData));
	}
};

struct PROGRESS_QUEST_INFO
{
	PROGRESS_QUEST_INFO(void)
	{
		Ver = 0;
		Id = 0xFF;
		memset(&Data.QInfoV0, 0xff, sizeof(Data.QInfoV0));
		Data.QInfoV0.QState = 0;
		Data.QInfoV0.tcQuestInfo = 0xFF;
		Data.QInfoV0.taQuestInfo = 0xFF;
	}
	BYTE Ver;
	BYTE Id;
	union DATA
	{
		struct EXTENDED_POSSIBLE_V0
		{
			WORD QState;
			MAIN_TSP MainTSP;
			EXCEPT_TIMER_SLOT ETSlot;
			STORAGE_SLOT_MEMORY SSM;
			STOC_EVT_DB_DATA SToCEvtData;
			BYTE tgExcCGroup;
			BYTE tcQuestInfo;
			BYTE taQuestInfo;
		};
		EXTENDED_POSSIBLE_V0 QInfoV0;
	};
	DATA Data;
};

struct QUESTITEM_DATA
{
	unsigned int tblidx;
	BYTE CurStackCount;
	BYTE Pos;
};

struct PCHAR_BRIEF
{
	unsigned int charId;
	unsigned int tblidx;
	bool IsAdult;
	WCHAR Name[MAX_CHARNAME_SIZE + 1];
	WCHAR GuildName[MAX_GUILDNAME_USIZE + 1];
	PCHAR_SHAPE PcShape;
	WORD CurLP;
	WORD MaxLP;
	WORD CurEP;
	WORD MaxEP;
	BYTE Level;
	float Speed;
	ITEMDATA ItemBrief[EQUIP_SLOT_TYPE_COUNT];
	WORD AttackSpeedRate;
	GUILD_MARK Mark;
	MARKING Marking;
	DOGIDATA Dogi;
};

struct BOT_DATA
{
	unsigned int tblidx;
	unsigned int worldID;
	VECTORXYZ CurLoc;
	VECTORXYZ CurDir;
	VECTORXYZ SpawnLoc;
	VECTORXYZ SpawnDir;
	BYTE SpawnRange;
	WORD SpawnTime;
	BYTE SpawnFuncFlag;
	BYTE MoveType; 
	BYTE WanderRange;
	BYTE MoveRange;
	BYTE MoveDelayTime;
	unsigned int actionpatternTblIdx;
	unsigned int pathTblidx;
	unsigned int playScript;
	unsigned int playScriptScene;
	unsigned int tblidxAiScript;
	unsigned int tblidxAiScriptScene;
	unsigned int partyID;
	bool PartyLeader;
	VECTORXYZ PartyLeaderDistance;
	DWORD CharConditionFlag;
};

struct BOT_BRIEF
{
	unsigned int tblidx;
	WORD CurLP;
	WORD CurEP;
	WORD MaxLP;
	WORD MaxEP;
	float LastWalkingSpeed;
	float LastRunningSpeed;
	WORD AttackSpeedRate;
	unsigned int actionpatternTblIdx;
};

struct BOT_PROFILE
{
	unsigned int tblidx;
	unsigned int worldID;
	VECTORXYZ SpawnLoc;
	VECTORXYZ SpawnDir;
	BYTE SpawnRange;
	WORD SpawnTime;
	BYTE SpawnFuncFlag;
	BYTE MoveType;
	BYTE WanderRange;
	BYTE MoveRange;
	BYTE MoveDelayTime;
	unsigned int actionpatternTblIdx;
	unsigned int pathTblidx;
	unsigned int playScript;
	unsigned int playScriptScene;
	unsigned int tblidxAiScript;
	unsigned int tblidxAiScriptScene;
	unsigned int partyID;
	bool PartyLeader;
	VECTORXYZ PartyLeaderDistance;
	WORD CurLP;
	WORD MaxLP;
	float LastWalkingSpeed;
	float LastRunningSpeed;
};

struct NPC_DATA : public BOT_DATA
{
};

struct NPC_BRIEF : public BOT_BRIEF
{
	unsigned int nicknameTblidx;
};

struct NPC_PROFILE : public BOT_PROFILE
{
};

struct MOB_DATA : public BOT_DATA
{
	unsigned int spawnGroupId;
};

struct MOB_BRIEF : public BOT_BRIEF
{
	BYTE BallType;
};

struct MOB_PROFILE : public BOT_PROFILE
{
	unsigned int spawnGroupId;
};

struct PET_DATA
{
	BYTE PetIndex;
	BYTE SourceType;
	unsigned int sourceTblidx;
};

struct PET_BRIEF
{
	BYTE SourceType;
	unsigned int sourceTblidx;
	unsigned int npcTblidx;
	unsigned int Owner;
	float LastRunningSpeed;
};

struct PET_PROFILE
{
	BYTE SourceType;
	unsigned int sourceTblidx;
	unsigned int npcTblidx;
	unsigned int Owner;
	BYTE AvatarType;
	AVATAR_ATTRIBUTE attribute;
};

struct SUMMON_PET_DATA : public PET_DATA
{
	WORD CurLP;
	WORD CurEP;
};

struct SUMMON_PET_BRIEF : public PET_BRIEF
{
	WORD CurLP;
	WORD CurEP;
	WORD MaxLP;
	WORD MaxEP;
	WORD AttackSpeedRate;
};

struct SUMMON_PET_PROFILE : public PET_PROFILE
{
	WORD CurLP;
	WORD CurEP;
};

struct ITEM_PET_DATA : public PET_DATA
{
	unsigned int itemId;
};

struct ITEM_PET_BRIEF : public PET_BRIEF
{
};

struct ITEM_PET_PROFILE : public PET_PROFILE
{
};

struct ITEM_DATA
{
	unsigned int itemId;
	unsigned int itemNo;
	unsigned int charId;
	BYTE Place;
	BYTE Position;
	BYTE Stackcount;
	BYTE Rank;
	BYTE CurrentDurability;
	bool NeedToIdentify;
	BYTE Grade;
	BYTE BattleAttribute;
	BYTE RestrictType;
	WCHAR Maker[MAX_CHARNAME_SIZE + 1];
	unsigned int aOptionTblidx[MAX_ITEM_OPTION];
	BYTE DurationType;
	time_t UseStartTime;
	time_t UseEndTime;

};

struct ITEM_DURATION
{
	unsigned int itemID;
	BYTE Place;
	BYTE Position;
	time_t UseEndTime;
};

struct ITEM_BRIEF
{
	unsigned int tblidx;
	BYTE Rank;
	BYTE Grade;
	BYTE BattleAttribute;
	unsigned int aOptionTblidx[MAX_ITEM_OPTION];
};

struct ITEM_SUMMARY
{
	unsigned int tblidx;
	BYTE Rank;
	BYTE Grade;
	BYTE BattleAttribute;
	unsigned int aOptionTblidx[MAX_ITEM_OPTION];
};

struct ITEM_STATE
{
	VECTORXYZ CurLoc;
	bool NeedToIdentify;
	bool IsNew;
};

struct MONEY_BRIEF
{
	DWORD Zenny;
};

struct MONEY_STATE
{
	VECTORXYZ CurLoc;
	bool IsNew;
};

struct ITEM_DELETE_DATA
{
	BYTE Place;
	BYTE Pos;
	unsigned int Item;
	unsigned int itemId;
	unsigned int tblidx;	
};

struct TOBJECT_BRIEF
{
	unsigned int objectID;
};

struct TOBJECT_STATE
{
	BYTE State;
	BYTE SubStateFlag;
	DWORD StateTime;	
};

struct DYNAMIC_OBJECT_BRIEF
{
	BYTE ObjectType;
	unsigned int idObjectTblidx;
	unsigned int Owner;
};


struct DYNAMIC_OBJECT_STATE
{
	BYTE State;
	VECTORXYZ CurLoc;
};

struct OBJECT_INFO
{
	BYTE objType;
	union
	{
		struct // pc
		{
			PCHAR_BRIEF pcBrief;
			CHARSTATE pcState;
		};
		struct // npc
		{
			NPC_BRIEF npcBrief;
			CHARSTATE npcState;
		};
		struct // mob
		{
			MOB_BRIEF mobBrief;
			CHARSTATE mobState;
		};
		struct // summon pet
		{
			SUMMON_PET_BRIEF summonPetBrief;
			CHARSTATE summonPetState;
		};
		struct // item pet
		{
			ITEM_PET_BRIEF itemPetBrief;
			CHARSTATE itemPetState;
		};
		struct // item
		{
			ITEMDATA itemBrief;
			ITEM_STATE itemState;
		};
		struct // money
		{
			MONEY_BRIEF	moneyBrief;
			MONEY_STATE	moneyState;
		};
		struct // trigger object
		{
			TOBJECT_BRIEF tobjectBrief;
			TOBJECT_STATE tobjectState;
		};
		struct // dynamic object
		{
			DYNAMIC_OBJECT_BRIEF dynamicObjBrief;
			DYNAMIC_OBJECT_STATE dynamicObjState;
		};
	};
};

struct NEWBIE_QUICKSLOT_DATA
{
	unsigned int tblidx;
	BYTE Type;
	BYTE QuickSlot;
};

struct RANKBATTLE_SCORE_INFO
{
	WORD MaxStraightWin;
	WORD StraightWin;
	WORD MaxStraightKOWin;
	WORD StraightKOWin;
	DWORD Win;
	DWORD Draw;	
	DWORD Lose;
	float Point;
};

struct PARTY_MEMBER_INFO
{
	unsigned int Handle;
	WCHAR MemberName[MAX_CHARNAME_SIZE + 1];
	BYTE Race;
	BYTE Class;
	BYTE Level;
	WORD CurLP;
	WORD MaxLP;
	WORD CurEP;
	WORD MaxEP;
	DWORD Zenny;
	unsigned int worldTblidx;
	unsigned int worldId;
	VECTORXYZ CurLoc;
};

struct VICTIM_ITEM_DATA
{
	unsigned int charId;
	BYTE Place;
	BYTE Pos;
	unsigned int Item;
	unsigned int itemId;
};

struct PARTY_VICTIM_ITEM_INFO
{
	BYTE SlotIndex;
	unsigned int itemTblidx;
};

struct ZENNY_DATA
{
	unsigned int memberCharId;
	DWORD Zenny;
};

struct INVEST_ZENNY_INFO
{
	unsigned int Member;
	DWORD Zenny;
};

struct PARTY_INVENTORY_ITEM_INFO
{
	unsigned int tblidx;
	// byStackCount, byRank, byGrade and option's values are meaningless if bNeedToIdentify is true.
	BYTE StackCount;
	BYTE Rank;
	BYTE Grade;
	bool NeedToIdentify;
	BYTE BattleAttribute;
	unsigned int OptionTblidx[MAX_ITEM_OPTION];
};

struct PARTY_INVENTORY_SLOT_INFO
{
	BYTE SlotIndex;
	PARTY_INVENTORY_ITEM_INFO itemInfo;
};

struct VICTIM_INFO
{
	unsigned int Member;
	DWORD Zenny;
};

struct sDBO_VICTIM_DATA
{
	unsigned int charId;
	DWORD Zenny;
};

struct ZENNY_INFO
{
	unsigned int charId;
	DWORD Zenny; // dwOrgZenny + dwBonusZenny
	DWORD OrgZenny;
	DWORD BonusZenny;
};

struct SHARETARGET_INFO
{
	unsigned int Target;
	public:
	SHARETARGET_INFO() : Target(INVALID_OBJECT){}
};

union STOC_EVT_UPDATE_DATA
{
	struct MOB_KILL_CNT
	{
		int CurMobCnt;
	};

	struct MOB_KILL_ITEM_CNT
	{
		int CurMobLICnt;
	};

	struct DELIVERY_ITEM
	{
		int CurItemCnt;
	};

	struct OBJECT_ITEM
	{
		int CurItemCnt;
	};

	struct PUBLIC_MOB_ITEM_CNT
	{
		int CurItemCnt;
	};

	struct CUSTOM_EVT_CNT
	{
		int CurCnt;
	};

	struct VISIT_EVT
	{
		bool Completed;
	};


	MOB_KILL_CNT MobKillCnt;
	MOB_KILL_ITEM_CNT MobKillItemCnt;
	DELIVERY_ITEM DeliveryItemCnt;
	OBJECT_ITEM	ObjectItemCnt;
	PUBLIC_MOB_ITEM_CNT PublicMobItemCnt;
	CUSTOM_EVT_CNT CustomEvtCnt;
	VISIT_EVT VisitEvt;
};

struct QUICK_SLOT_DATA
{
	unsigned int tblidx;
	BYTE Slot;
	BYTE Type;
	unsigned int itemID;
	unsigned int Item;
};

struct QUICK_SLOT_PROFILE
{
	unsigned int tblidx;
	BYTE Slot;
	BYTE Type;
	unsigned int Item;
};

struct TIMEQUEST_ROOM_MEMBER
{
	unsigned int handle;
	WCHAR Name[MAX_CHARNAME_SIZE + 1];
	BYTE Class;
};

struct TIMEQUEST_ROOM_MEMBER_INFO
{
	BYTE MemberCount;
	TIMEQUEST_ROOM_MEMBER RoomMember[TIMEQUEST_MAX_MEMBER_COUNT];
};

struct TIMEQUEST_ROOM_PARTY_INFO
{
	WCHAR Name[MAX_PARTYNAME_SIZE + 1];
};

struct TIMEQUEST_ROOM
{
	unsigned int roomID;
	unsigned int timeQuestTblidx;
	DWORD RemainSec;
	BYTE StartHour;
	BYTE StartMin;
	BYTE RoomMode;
	BYTE Difficulty; 
	BYTE RoomState; 	
};

struct TIMEQUEST_TIME
{
	void NextTime(BYTE TermMinute)
	{
		Hour = Hour + (BYTE)(TermMinute / 60);
		Minute += TermMinute % 60;

		if (60 <= Minute)
		{
			Minute -= 60;
			Hour++;
		}

		if (24 < Hour)
		{
			Hour -= 24;
		}
	}

	void NextBySec(DWORD TermSec)
	{
		NextTime((BYTE)(TermSec / 60));
	}

	BYTE Hour;
	BYTE Minute;
};

struct TIMEQUEST_ROOM_TMQ_INFO
{
	unsigned int tmqTblidx;
	BYTE Difficult;	
	TIMEQUEST_TIME CurTime;
	TIMEQUEST_TIME NextEnterTime;
	WORD WaitPartyCount;
	WORD WaitIndividualCount;
};

struct TIMEQUEST_ROOM_JOIN_INFO
{
	unsigned int tmqTblidx;
	unsigned int roomId;
	BYTE RoomState;
	BYTE TimeQuestMode;	
	DWORD RemainTime;
	BYTE Difficult;	
	WORD WaitPartyCount;
	WORD WaitIndividualCount;
};

struct TIMEQUEST_ROOM_REGISTRATION_ICON_INFO
{
	WORD WaitPartyCount;
	WORD WaitIndividualCount;
};

struct TIMEQUEST_ROOM_WAITENTRY_ICON_INFO
{
	BYTE HaveItem;
};

union TIMEQUEST_ROOM_ICON_INFO
{
	TIMEQUEST_ROOM_REGISTRATION_ICON_INFO RegistrationInfo;	// eTIMEQUEST_ROOM_STATE == TIMEQUEST_ROOM_STATE_REGISTRAITION
	TIMEQUEST_ROOM_WAITENTRY_ICON_INFO WaitEntryInfo;		// eTIMEQUEST_ROOM_STATE == TIMEQUEST_ROOM_STATE_WAITENTRY
};

struct TIMEQUEST_ROOM_ENTRY_INFO
{
	DWORD ReaminEntryTime;
	bool HaveItem;
};

struct TIMEQUEST_ROOM_NEXT_TMQ_INFO
{
	unsigned int tmqTblidx;
	TIMEQUEST_TIME NextTMQTime;
};

union TIMEQUEST_ROOM_SELECTION_INFO
{
	TIMEQUEST_ROOM_ENTRY_INFO EntryInfo;
	TIMEQUEST_ROOM_NEXT_TMQ_INFO NextTmqInfo;
};

struct TIMEQUEST_DAYRECORD_DATA
{
	BYTE Difficult;
	DWORD ClearTime;
	BYTE MemberCount;
	unsigned int MemberCharId[MAX_MEMBER_IN_PARTY];
};

struct RANKBATTLE_ARENA_INFO
{
	unsigned int rankBattleTblidx;
	WORD RegisterCount;
};

struct RANKBATTLE_ROOMLIST_INDIVIDUAL
{
	unsigned int roomId;
	WCHAR OwnerPc[MAX_CHARNAME_SIZE + 1];
	WORD WinCounter;
};

struct RANKBATTLE_ROOMLIST_PARTY
{
	unsigned int roomId;
	WCHAR OwnerParty[MAX_PARTYNAME_SIZE + 1];
	WORD WinCounter;
};

struct RANKBATTLE_ROOMINFO_MEMBER
{
	WCHAR Name[MAX_CHARNAME_SIZE + 1];
	BYTE Class;
	BYTE Level;
};

struct RANKBATTLE_ROOMINFO_INDIVIDUAL
{
	unsigned int rankBattleTblidx;
	unsigned int roomId;
	WORD WinCount;
	RANKBATTLE_ROOMINFO_MEMBER Member;
};

struct RANKBATTLE_ROOMINFO_PARTY
{
	unsigned int rankBattleTblidx;
	unsigned int roomId;
	WORD WinCount;
	WCHAR PartyName[MAX_PARTYNAME_SIZE + 1];
	BYTE MemberCount;
	RANKBATTLE_ROOMINFO_MEMBER	Member[MAX_MEMBER_IN_PARTY];
};

union RANKBATTLE_ROOMINFO
{
	RANKBATTLE_ROOMINFO_INDIVIDUAL Individual;
	RANKBATTLE_ROOMINFO_PARTY Party;
};

union RANKBATTLE_ROOMINFO_LIST
{
	RANKBATTLE_ROOMLIST_INDIVIDUAL IndividualRoom[RANKBATTLE_MAX_ROOM_COUNT_PER_PAGE];
	RANKBATTLE_ROOMLIST_PARTY PartyRoom[RANKBATTLE_MAX_ROOM_COUNT_PER_PAGE];
};

struct RANKBATTLE_MEMBER_RESULT
{
	unsigned int Pc;
	WORD ResultCode;
};

struct RANKBATTLE_MATCH_MEMBER_INFO
{
	unsigned int Pc;
	BYTE Team;
	BYTE State;
};

struct RANKBATTLE_SCORE
{
	BYTE Owner;
	BYTE Challenger;
};

struct RANKBATTLE_POINT
{
	float Owner;
	float Challenger;
};

struct RANKBATTLE_MATCH_FINISH_INFO
{
	struct WINER_RECORD
	{
		WORD StraightKOWinCount;
		WORD StraightWinCount;
	};

	struct TEAM_MATCH_FINISH_INFO
	{
		BYTE Score;
		float Point;
		float BonusPoint;
		WORD WinCount;
		WORD DrawCount;
		WORD LoseCount;
	};
	BYTE MatchWinner;
	WINER_RECORD WinerRecord;
	TEAM_MATCH_FINISH_INFO OwnerInfo;
	TEAM_MATCH_FINISH_INFO ChallengerInfo;
};

struct RANKBATTLE_RANK_DATA
{
	WCHAR CharName[MAX_CHARNAME_SIZE];
	BYTE Level;
	BYTE Class;
	WCHAR GuildName[MAX_GUILDNAME_USIZE];
	int Point;
	WORD StraightWinCount;
	DWORD CompareRank[RANKBATTLE_MAX_COMPARE_DAY];
};

struct RANKBATTLE_RANK_INFO
{
	WORD CharName; 
	BYTE yLevel;
	BYTE Class;
	WORD GuildName;
	int Point;
	WORD StraightWinCount;
	DWORD CompareRank;
};

struct sVARIABLE_DATA
{
protected:
	WORD	wReserveSize;
	WORD	wOffset;
	BYTE	abyData[1];
public:
	sVARIABLE_DATA() : wOffset(0), wReserveSize(1){}
	sVARIABLE_DATA(WORD wReserve) : wOffset(0)
	{
		Init(wReserve);
	}
	void Init(WORD wReserve)
	{
		wOffset = 0;
		if (wReserve >= 4096/*PACKET_MAX_SIZE*/)
		{
			_ASSERT(0);

			wReserveSize = 0;
			return;
		}
		wReserveSize = wReserve;
		::memset(abyData, 0xff, sizeof(BYTE) * wReserve);
	}
	void InitPacketSize(WORD wDefaultPacketSize)
	{
		wOffset = 0;
		wReserveSize = 4096 - wDefaultPacketSize + sizeof(BYTE);
		if (wReserveSize >= 4096)
		{
			_ASSERT(0);

			wReserveSize = 0;
			return;
		}
		::memset(abyData, 0xff, sizeof(BYTE) * wReserveSize);
	}
	WORD GetPacketSize(WORD wDefaultPacketSize) { return wDefaultPacketSize - sizeof(BYTE) + GetDataSize(); }
	WORD GetTotalSize() { return wOffset + sizeof(sVARIABLE_DATA) - sizeof(BYTE); }
	WORD GetDataSize() { return wOffset; }
	void WriteLock() { wReserveSize = GetDataSize(); }
	void __SetData(WORD wOff, BYTE * pData)
	{
		wOffset = wOff;
		::memcpy(abyData, pData, wOff);
	}
	bool CopyTo(sVARIABLE_DATA * pData, WORD wReserve)
	{
		if (NULL == pData)
		{
			return false;
		}
		if (wReserve < GetDataSize())
		{
			return false;
		}
		pData->__SetData(wOffset, abyData);
		pData->WriteLock();
		return true;
	}
	WORD Write(WORD wSize, void * pData)
	{
		WORD wTemp = wOffset;

		if (127 >= wSize)
		{
			if (wOffset + wSize + 1 > wReserveSize)
			{
				return INVALID_WORD;
			}
			abyData[wOffset] = (BYTE)wSize;
			::memcpy(&(abyData[wOffset + 1]), pData, wSize);
			wOffset += wSize + 1;
		}
		else
		{
			if (wOffset + wSize + 2 > wReserveSize)
			{
				return INVALID_WORD;
			}
			abyData[wOffset] = (BYTE)((wSize % 0x80) | 0x80);
			abyData[wOffset + 1] = (BYTE)(wSize >> 7);	
			::memcpy(&(abyData[wOffset + 2]), pData, wSize);
			wOffset += wSize + 2;
		}

		return wTemp;
	}
	WORD Malloc(WORD wSize)
	{
		WORD wTemp = wOffset;
		if (127 >= wSize)
		{
			if (wOffset + wSize + 1 > wReserveSize)
			{
				return INVALID_WORD;
			}
			abyData[wOffset] = (BYTE)wSize;
			wOffset += wSize + 1;
		}
		else	
		{
			if (wOffset + wSize + 2 > wReserveSize)
			{
				return INVALID_WORD;
			}
			abyData[wOffset] = (BYTE)((wSize % 0x80) | 0x80);
			abyData[wOffset + 1] = (BYTE)(wSize >> 7);
			wOffset += wSize + 2;
		}
		return wTemp;
	}
	WORD GetSize(WORD wReadLoc)
	{
		if (wReadLoc >= wOffset)
		{
			return 0;
		}
		if (0x80 & abyData[wReadLoc])
		{
			if (wReadLoc + 1 >= wOffset)
			{
				return 0;
			}
			WORD wSize = (abyData[wReadLoc] & 0x7f) + (abyData[wReadLoc + 1] << 7);
			if (wReadLoc + wSize + 2 > wOffset)
			{
				return 0;
			}

			return wSize;
		}
		else
		{
			if (wReadLoc + abyData[wReadLoc] + 1 > wOffset)
			{
				return 0;
			}

			return abyData[wReadLoc];
		}
	}
	bool Read(WORD wReadLoc, void * pData)
	{
		if (wReadLoc >= wOffset)
		{
			return false;
		}
		if (0x80 & abyData[wReadLoc])
		{
			if (wReadLoc + 1 >= wOffset)
			{
				return false;
			}
			WORD wSize = (abyData[wReadLoc] & 0x7f) + (abyData[wReadLoc + 1] << 7);
			if (wReadLoc + wSize + 2 > wOffset)
			{
				return false;
			}
			::memcpy(pData, &(abyData[wReadLoc + 2]), wSize);
		}
		else
		{
			if (wReadLoc + abyData[wReadLoc] + 1 > wOffset)
			{
				return false;
			}
			::memcpy(pData, &(abyData[wReadLoc + 1]), abyData[wReadLoc]);
		}

		return true;
	}
	void * Read(WORD wReadLoc)
	{
		if (wReadLoc >= wOffset)
		{
			return NULL;
		}
		if (0x80 & abyData[wReadLoc])
		{
			if (wReadLoc + 1 >= wOffset)
			{
				return NULL;
			}
			WORD wSize = (abyData[wReadLoc] & 0x7f) + (abyData[wReadLoc + 1] << 7);
			if (wReadLoc + wSize + 2 > wOffset)
			{
				return NULL;
			}
			return &(abyData[wReadLoc + 2]);
		}
		else
		{
			if (wReadLoc + abyData[wReadLoc] + 1 > wOffset)
			{
				return NULL;
			}
			return &(abyData[wReadLoc + 1]);
		} 
	}
};

struct SUMMARY_PRIVATESHOP_SHOP_DATA
{
	bool IsOwnerEmpty;
	BYTE ShopState; 
	WCHAR PrivateShopName[MAX_PRIVATESHOPNAME_USIZE + 1];
};

struct PRIVATESHOP_SHOP_DATA
{
	unsigned int Owner;	
	long long waittimeCashShopStart;
	long long waittimeCashShopEnd;
	SUMMARY_PRIVATESHOP_SHOP_DATA SummaryPrivateShopData;
	WCHAR Notice[MAX_PRIVATESHOPNOTICE_USIZE + 1];

public:
	PRIVATESHOP_SHOP_DATA()
		: Owner(INVALID_OBJECT)
		, waittimeCashShopStart(0)
		, waittimeCashShopEnd(0)
	{
		SummaryPrivateShopData.IsOwnerEmpty = false;
		SummaryPrivateShopData.ShopState = PRIVATESHOP_STATE_NULL;
		ZeroMemory(SummaryPrivateShopData.PrivateShopName, sizeof(WCHAR) * (MAX_PRIVATESHOPNAME_USIZE + 1));
		ZeroMemory(Notice, sizeof(WCHAR) * (MAX_PRIVATESHOPNOTICE_USIZE + 1));
	}
};

struct PACKET_PRIVATESHOP_SHOP_DATA
{
	unsigned int Owner;
	long long waittimeCashShopStart;
	long long waittimeCashShopEnd;
	SUMMARY_PRIVATESHOP_SHOP_DATA SummaryPrivateShopData;
	BYTE NoticeSize;
	WCHAR Notice[MAX_PRIVATESHOPNOTICE_USIZE + 1];

public:
	PACKET_PRIVATESHOP_SHOP_DATA()
		: Owner(INVALID_OBJECT)
		, waittimeCashShopStart(0)
		, waittimeCashShopEnd(0)
		, NoticeSize(0)
	{
		SummaryPrivateShopData.IsOwnerEmpty = false;
		SummaryPrivateShopData.ShopState = PRIVATESHOP_STATE_NONE;
		ZeroMemory(SummaryPrivateShopData.PrivateShopName, sizeof(WCHAR) * (MAX_PRIVATESHOPNAME_USIZE + 1));
		ZeroMemory(Notice, sizeof(WCHAR) * (MAX_PRIVATESHOPNOTICE_USIZE + 1));
	}
};

struct PRIVATESHOP_ITEM_DATA
{
	enum ITEMSTATE
	{
		PRIVATESHOP_GENERAL = 0,
		PRIVATESHOP_BUSINESS_ITEM = 1,
		PRIVATESHOP_VISITOR_SELECT_ITEM = 2,
		PRIVATESHOP_VISITOR_UNSELECT_ITEM = 3,
		PRIVATESHOP_INVALID = 0xFF,
	};

	unsigned int ItemObj;
	BYTE PrivateShopInventorySlotPos;
	bool IsSaveItem;
	ITEM_DATA Item;
	DWORD Zenny;
	BYTE ItemState;

	PRIVATESHOP_ITEM_DATA()
		: ItemObj(INVALID_OBJECT)
		, PrivateShopInventorySlotPos(PRIVATESHOP_ITEMPOS_INVALID)
		, Zenny(PRIVATESHOP_ITEM_BUY_ZENNY_DEFAULT)
		, ItemState(PRIVATESHOP_INVALID)
		, IsSaveItem(false)
	{
		ZeroMemory(&Item, sizeof(Item));
	}
};

struct MAIL_SLOT
{
	unsigned int MailID[MAX_MAIL_SLOT_COUNT];
};

struct MAIL_BRIEF
{
	BYTE MailType;
	DWORD Zenny;
	bool IsRead;
	bool IsAccept;
	bool IsLock;
	BYTE SenderType;
	time_t endTime;
};

struct MAIL_DATA
{
	unsigned int mailID;
	bool IsRead;
	bool IsAccept;
	bool IsLock;
	BYTE MailType;
	BYTE SenderType;
	DWORD Zenny;
	BYTE Expired;
	ITEM_DATA ItemData;
	TIME CreateTime;
	WCHAR FromName[MAX_CHARNAME_SIZE + 1];
	BYTE TextSize;
	WCHAR Text[MAX_MAILMESSAGE_SIZE + 1];
	time_t endTime;
};

struct MAIL_GM_DATA
{
	unsigned int mailID;
	bool IsRead;
	bool IsAccept;
	bool IsLock;
	BYTE MailType;
	BYTE SenderType;
	DWORD Zenny;
	BYTE Expired;
	ITEM_DATA ItemData;	
	TIME CreateTime;
	unsigned int FromCharID;
	WCHAR FromName[MAX_CHARNAME_SIZE + 1];
	BYTE TextSize;
	WCHAR Text[MAX_MAILMESSAGE_SIZE + 1];
	bool IsTemp;
};

struct MAIL_PROFILE
{
	unsigned int mailID;
	bool IsRead;
	bool IsAccept;
	bool IsLock;
	BYTE MailType;
	BYTE SenderType;
	DWORD Zenny;
	BYTE Expired;
	ITEM_PROFILE ItemProfile;	
	TIME CreateTime;
	WCHAR FromName[MAX_CHARNAME_SIZE + 1];
	WCHAR Text[MAX_MAILMESSAGE_SIZE + 1];
	time_t endTime;
};

struct MAIL_NEW_PROFILE
{
	unsigned int mailID;
	bool IsRead;
	bool IsAccept;
	bool IsLock;
	BYTE MailType;
	BYTE SenderType;
	DWORD Zenny;
	BYTE Expired;
	ITEM_PROFILE ItemProfile;
	TIME CreateTime;
	WCHAR FromName[MAX_CHARNAME_SIZE + 1];
	time_t endTime;
};

struct MAIL_NEW_GM_PROFILE
{
	unsigned int mailID;
	bool IsRead;
	bool IsAccept;
	bool IsLock;
	BYTE MailType;
	BYTE SenderType;
	DWORD Zenny;
	BYTE Expired;
	ITEM_PROFILE ItemProfile;	
	TIME CreateTime;
	unsigned int FromCharID;
	WCHAR FromName[MAX_CHARNAME_SIZE + 1];
	bool IsTemp;
};

struct MAIL_NEW_BREIF
{
	BYTE MailCount;
	BYTE UnReadManager;
	BYTE UnReadNormal;
};

struct MATCH_SCORE
{
	BYTE Team1;
	BYTE Team2;
};

struct MATCH_MEMBER_STATE_INFO
{
	unsigned int handle;
	BYTE State;
	BYTE Level;
	BYTE Class;
	WORD GuildName;
	WORD WinCount;
	WORD DrawCount;
	WORD LoseCount;
	WORD CharName;
};

struct MATCH_MINORMATCH_TEAM_INFO
{
	WORD TeamType;
	WCHAR TeamName[MAX_BUDOKAITEAMNAME_USIZE + 1];
	bool DojoRecommender;
	BYTE MemberCount;
	MATCH_MEMBER_STATE_INFO	Members[MAX_MEMBER_IN_PARTY];
};

struct MATCH_MINORMATCH_TEAM_INFO_VAR
{
	WORD TeamType;
	WORD TeamName_var;
	bool DojoRecommender;
	BYTE MemberCount;
	WORD Members_var;
};

typedef	MATCH_MINORMATCH_TEAM_INFO MATCH_MAJORMATCH_TEAM_INFO;
typedef MATCH_MINORMATCH_TEAM_INFO_VAR MATCH_MAJORMATCH_TEAM_INFO_VAR;

typedef	MATCH_MINORMATCH_TEAM_INFO MATCH_FINALMATCH_TEAM_INFO;
typedef MATCH_MINORMATCH_TEAM_INFO_VAR MATCH_FINALMATCH_TEAM_INFO_VAR;

struct MATCH_MINORMATCH_TEAM_SCORE
{
	WORD teamType;
	BYTE Score;
};

struct BUDOKAI_STATE_DATA
{
	BYTE State;
	DWORD NextStepTime;
};

#define BUDOKAI_MATCHSTATE_DATA BUDOKAI_STATE_DATA	

struct BUDOKAI_UPDATEDB_INITIALIZE
{
	WORD SeasonCount;
	DWORD DefaultOpenTime;
	bool RankPointInitialized;
	BUDOKAI_STATE_DATA StateData;
	BUDOKAI_MATCHSTATE_DATA	IndividualStateData;
	BUDOKAI_MATCHSTATE_DATA	TeamStateData;
};

struct BUDOKAI_STATE_INFO
{
	BUDOKAI_STATE State;
	DWORD NextStepTime;
};

struct BUDOKAI_MATCHSTATE_INFO
{
	BUDOKAI_MATCHSTATE State;
	DWORD NextStepTime;
};

struct BUDOKAI_PLAYER_DATA
{
	unsigned int charId;
	BYTE Class;
	BYTE Level;
	float Point;
	WCHAR Name[MAX_CHARNAME_SIZE + 1];
};

struct BUDOKAI_REGISTER_DATA
{
	WORD JoinId;
	WORD Ranking;
	BYTE MinorMatch_MatchIndex;
	float Point;
};

struct BUDOKAI_REGISTER_INDIVIDUAL_DATA : public BUDOKAI_REGISTER_DATA
{
	unsigned int charId;
	bool DojoRecommender;
};

struct BUDOKAI_REGISTER_TEAM_DATA : public BUDOKAI_REGISTER_DATA
{
	WCHAR TeamName[MAX_BUDOKAITEAMNAME_USIZE + 1];
	unsigned int Members[MAX_MEMBER_IN_PARTY];
};

struct BUDOKAI_TOURNAMENT_ENTRY_DATA
{
	WORD JoinId;
	BYTE MinorMatch_MatchIndex;
};

struct BUDOKAI_TOURNAMENT_INDIVIDUAL_ENTRY_DATA : public BUDOKAI_TOURNAMENT_ENTRY_DATA
{
	unsigned int charId;
	WCHAR CharName[MAX_CHARNAME_SIZE + 1];
	BYTE Class;
	BYTE Level;
	float RankPoint;
	bool DojoRecommender;
	WORD RankBattleWinCount;
	WORD RankBattleDrawCount;
	WORD RankBattleLoseCount;
	WCHAR GuildName[MAX_GUILDNAME_USIZE + 1];
};


struct BUDOKAI_TOURNAMENT_TEAM_ENTRY_MEMBER_DATA
{
	unsigned int charId;
	WCHAR CharName[MAX_CHARNAME_SIZE + 1];
	BYTE Class;
	BYTE Level;
	float RankPoint;
};

struct BUDOKAI_TOURNAMENT_TEAM_ENTRY_DATA : public BUDOKAI_TOURNAMENT_ENTRY_DATA
{
	WCHAR TeamName[MAX_BUDOKAITEAMNAME_USIZE + 1];
	BYTE MemberCount;
	BUDOKAI_TOURNAMENT_TEAM_ENTRY_MEMBER_DATA Members[MAX_MEMBER_IN_PARTY];
};

struct BUDOKAI_TOURNAMENT_INDIVIDUAL_ENTRY_DATA_VAR : BUDOKAI_TOURNAMENT_ENTRY_DATA
{
	unsigned int charId;
	WORD CharName;
	BYTE Class;
	BYTE Level;
	float RankPoint;
	bool DojoRecommender;
	WORD RankBattleWinCount;
	WORD RankBattleDrawCount;
	WORD RankBattleLoseCount;
	WORD GuildName;
};


struct BUDOKAI_TOURNAMENT_TEAM_ENTRY_MEMBER_DATA_VAR
{
	unsigned int charId;
	WORD CharName;
	BYTE Class;
	BYTE Level;
	float RankPoint;
};

struct BUDOKAI_TOURNAMENT_TEAM_ENTRY_DATA_VAR : public BUDOKAI_TOURNAMENT_ENTRY_DATA
{
	WORD TeamName;
	BYTE MemberCount;
	WORD Members;
};

struct BUDOKAI_TEAM_POINT_INFO
{
	BYTE Class;
	WCHAR Name[MAX_CHARNAME_SIZE + 1];
	BYTE Level;
	float Point;
};

struct BUDOKAI_REGISTER_INDIVIDUAL_INFO
{
	bool DojoRecommender;
	WORD JoinId;
	WCHAR CharName[MAX_CHARNAME_SIZE + 1];
};

struct BUDOKAI_REGISTER_TEAM_INFO
{
	WORD JoinId;
	WCHAR TeamName[MAX_BUDOKAITEAMNAME_USIZE + 1];
	BUDOKAI_TEAM_POINT_INFO MemberInfo[MAX_MEMBER_IN_PARTY];
};

struct BUDOKAI_JOIN_INFO
{
	BYTE MatchType;
	BYTE JoinState;	
	BYTE JoinResult;
	union
	{
		BUDOKAI_REGISTER_INDIVIDUAL_INFO IndividualInfo;
		BUDOKAI_REGISTER_TEAM_INFO TeamInfo;
	};
};

struct BUDOKAI_TOURNAMENT_ENTRY_TEAM_INFO
{
	WORD JoinId;
	bool DojoRecommender;
	WCHAR TeamName[MAX_BUDOKAITEAMNAME_USIZE + 1];
};

struct BUDOKAI_TOURNAMENT_ENTRY_TEAM_INFO_VAR
{
	WORD JoinId;
	bool DojoRecommender;
	WORD TeamName;
};

struct BUDOKAI_TOURNAMENT_MATCH_DATA
{
	BYTE Depth;
	BYTE MatchNumber;
	BYTE MatchResult;
	WORD WinnerTeam;
	WORD JoinId1;
	WORD JoinId2;
	BYTE Score1;
	BYTE Score2;
};

struct BUDOKAI_UPDATE_STATE_INFO
{
	BYTE State;
	DWORD NextStepTime;
	DWORD RemainTime;
	WORD SeasonCount;
};

struct BUDOKAI_UPDATE_MATCH_STATE_INFO
{
	BYTE State;
	DWORD NextStepTime;
	DWORD RemainTime;
};

struct BUDOKAI_MUDOSA_INFO
{
	WCHAR MudosaName[BUDOKAI_MAX_MUDOSA_NAME_IN_UNICODE + 1];
	WORD CurrentUserCount;
};

struct BUDOKAI_PREV_SEASON_PLAYER_INFO
{
	BYTE MatchType;
	unsigned int charId;
	WCHAR Name[MAX_CHARNAME_SIZE + 1];
	BYTE Class;
	BYTE Level;
	BYTE JoinResult;
};

struct MINORMATCH_TELEPORT_INDIVIDUAL_DATA
{
	unsigned int worldId;
	unsigned int worldTblidx;
	BYTE PlayerCount;
	unsigned int Players[BUDOKAI_MINOR_MATCH_INDIVIDUAL_COUNT];
};

struct MINORMATCH_TELEPORT_TEAM_MEMBER_LIST
{
	BYTE Count;
	unsigned int charId[MAX_MEMBER_IN_PARTY];
};

struct MINORMATCH_TELEPORT_TEAM_DATA
{
	unsigned int worldId;
	unsigned int worldTblidx;
	BYTE TeamCount;
	MINORMATCH_TELEPORT_TEAM_MEMBER_LIST TeamList[BUDOKAI_MINOR_MATCH_TEAM_COUNT];
};

enum BUDOKAI_GM_MATCH_PROGRESS_STATES
{
	BUDOKAI_GM_MATCH_PROGRESS_STATE_READY,
	BUDOKAI_GM_MATCH_PROGRESS_STATE_RUN,
	BUDOKAI_GM_MATCH_PROGRESS_STATE_FINISHED,
};

struct BUDOKAI_GM_MATCH_PROGRESS_STATE
{
	BYTE MatchIndex;
	BYTE ProgressState;
	BYTE MatchResult;
	WORD winnerTeamType;
	WCHAR TeamName1[MAX_BUDOKAITEAMNAME_USIZE + 1];
	BYTE Score1;
	WCHAR TeamName2[MAX_BUDOKAITEAMNAME_USIZE + 1];
	BYTE Score2;
};

struct MINORMATCH_SELECTION_DATA
{
	WORD teamType;
	BYTE Number;
};


struct BUDOKAI_JOIN_STATE_DATA
{
	unsigned int charId;
	WORD joinId;
	BYTE JoinState;
	BYTE JoinResult;
};

struct RECIPE_DATA
{
	unsigned int recipeTblidx;
	BYTE RecipeType;
};

struct UPDATED_SKILL_DATA
{
	BYTE SkillPassiveEffect;
	union
	{
		float Casting_Time;
		WORD Cool_Time;
		float Skill_Effect_Value[MAX_EFFECTSKILL];
		WORD Keep_Time;
		WORD Require_EP;
		BYTE Apply_Range;
		struct
		{
			BYTE Apply_Area_Size_1;
			BYTE Apply_Area_Size_2;
		};
		BYTE Use_Range_Max;
	};
};

struct DOJO_BANK_HISTORY_INFO
{
	TIME Time;
	BYTE Type;
	DWORD Amount;
	bool IsSave;
};

struct DOJO_NPC_INFO
{
	unsigned int dojoTblidx;
	WCHAR Name[MAX_GUILDNAME_USIZE + 1];
	BYTE Level;
	DWORD GuildReputation;
	DWORD MaxGuildPointEver;
	BYTE PeaceStatus;
	WCHAR SeedCharName[MAX_CHARNAME_SIZE + 1];
	WCHAR LeaderName[MAX_CHARNAME_SIZE + 1];
	WCHAR Notice[MAX_LENGTH_OF_DOJO_NOTICE_UNICODE + 1];
	WCHAR ChallengeName[MAX_GUILDNAME_USIZE + 1];
	WCHAR ChallengeLeaderName[MAX_CHARNAME_SIZE + 1];
};

struct CASHITEM_BRIEF
{
	DWORD ProductId;
	unsigned int HLSitemTblidx;
	BYTE StackCount;
};

#pragma pack()
#endif