#include "Network.h"

bool Server::Start()
{
	int rc;

	rc = WSAStartup(MAKEWORD(2, 2), &wsData);
	if (rc > 0)
	{
		std::cout << "WSAStartup() error" << std::endl;
		return false;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		std::cout << "socket() failed" << std::endl;
		return false;
	}

	memset(&addrServer, 0, sizeof(addrServer));
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
	addrServer.sin_port = htons(sPort);
	memset(&(addrServer.sin_zero), '\0', 8);

	if (bind(sock, (const sockaddr*)&addrServer, sizeof(addrServer)))
	{
		std::cout << "bind() failed" << std::endl;
		close(sock);
		sock = INVALID_SOCKET;
		return false;
	}

	rc = listen(sock, 5);
	if (rc < 0)
	{
		std::cout << "listen() failed" << std::endl;
		close(sock);
		return false;
	}

	isActive = true;
	OnReady();
	Loop();
	return true;
}

void Server::Loop()
{
	fd_set fds;
	int activity;
	sockaddr_in ClientInfo;
	SOCKET NewSocket;
	timeval timeout = { 0, 2000 };
	OnServerStep();
	do
	{
		FD_ZERO(&fds);
		CheckFDS(&fds);
		FD_SET(sock, &fds);

		activity = select(0, &fds, NULL, NULL, &timeout);
		if (activity == 0)
		{
			continue;
		}

		if (activity < 0 && errno != EINTR) {
			std::cout << "Select command failed: " << WSAGetLastError() << std::endl;
			isActive = false;
		}
		if (FD_ISSET(sock, &fds))
		{
			int clientinfolen = sizeof(sockaddr_in);
			NewSocket = accept(sock, (sockaddr*)&ClientInfo, (int*)&clientinfolen);
			if (NewSocket != INVALID_SOCKET)
				AddClient(NewSocket, &ClientInfo);
			else
				std::cout << "Error accepting socket: " << WSAGetLastError() << std::endl;
		}
		HandleClients(&fds);
	} while (isActive);
}

void Server::AddClient(SOCKET sock, sockaddr_in* addr)
{
	Client* client = CreateClient();
	if (client == NULL)
	{
		close(client->sock);
		if (client != 0) delete client;
		client = 0;
		return;
	}


	client->pServer = this;
	client->sock = sock;
	client->isActive = true;
	client->addr = addr;

	if (!OnConnect(client)) {
		close(client->sock);
		if (client != 0) delete client;
		client = 0;
		return;
	}
	Logger::Log("Client connected %s (%d)\n", inet_ntoa(client->addr->sin_addr), client->sock);
	Clients.push_back(client);
}

void Server::CheckFDS(fd_set* fds)
{
	for (unsigned int i = 0; i < Clients.size(); i++)
	{
		Client* client = Clients.at(i);
		if (client->isActive)
		{
			FD_SET((unsigned)client->sock, fds);
		}
		else
		{
			Disconnect(client);
		}
	}
}

void Server::HandleClients(fd_set* fds)
{
	for (unsigned int i = 0; i < Clients.size(); i++)
	{
		Client* client = Clients.at(i);
		if (!client->isActive)
			continue;
		if (FD_ISSET((unsigned)client->sock, fds))
		{
			if (!client->ReceivingData())
			{
				Disconnect(client);
			}
		}
	}
}

void Server::Disconnect(Client* client)
{
	OnDisconnect(client);
	Logger::Log("Client disconnected %s (%d)\n", inet_ntoa(client->addr->sin_addr), client->sock);
	close(client->sock);
	client->sock = INVALID_SOCKET;
	client->isActive = false;
	for (unsigned int i = 0; i < Clients.size(); i++)
	{
		Client* c = Clients.at(i);
		if (c == client)
		{
			Clients.erase(Clients.begin() + i);
			break;
		}
	}
	DeleteClient(client);
}

Client* Server::CreateClient()
{
	return new Client();
}

void Server::DeleteClient(Client* client)
{
	delete client;
}