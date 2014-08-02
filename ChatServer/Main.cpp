#include <stdio.h>
#include <stdlib.h>
#include "ChatNetwork.h"

int main(int argc, char* argv[])
{
	Logger::Log("DBO - ChatServer\n");
	ChatServer* server = new ChatServer();
	return 0;
}