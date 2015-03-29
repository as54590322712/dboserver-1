#ifndef _CHARACTERMANAGER
#define _CHARACTERMANAGER

#include <Base.h>
#include <Def.h>
#include <Thread.h>

class GameServer;

class CharacterManager : public RunObject
{
public:
	CharacterManager();
	~CharacterManager();

	void Init();
	void Release();
	void CreateThread();
	void Run();

private:
	Thread * pThread;
	GameServer* pServer;
};

#endif