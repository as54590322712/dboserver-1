#include <stdio.h>
#include <stdlib.h>
#include "CharNetwork.h"

int main(int argc, char* argv[])
{
	Logger::Log("DBO - CharServer\n");
	CharServer* server = new CharServer();
	return 0;
}