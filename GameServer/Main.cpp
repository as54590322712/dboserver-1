#include <stdio.h>
#include <stdlib.h>
#include "GameNetwork.h"

int main(int argc, char* argv[])
{
	Logger::Log("DBO - GameServer\n");
	GameServer* server = new GameServer();
	return 0;
}