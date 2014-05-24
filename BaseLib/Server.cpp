#include "Network.h"

bool Server::Start()
{
	int rc;

	rc = WSAStartup(MAKEWORD(2, 2), &wsData);
	if (rc > 0)
	{
		perror("WSAStartup() error");
		return false;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
	{
		perror("socket() failed");
		return false;
	}

	rc = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&Opt, sizeof(Opt));
	if (rc < 0)
	{
		perror("setsockopt() failed");
		close(sock);
		return false;
	}

	rc = ioctlsocket(sock, FIONBIO, (u_long*)&Opt);
	if (rc < 0)
	{
		perror("ioctl() failed");
		close(sock);
		return false;
	}

	memset(&addrServer, 0, sizeof(addrServer));
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
	addrServer.sin_port = htons(SERVER_PORT);

	if (bind(sock, (const sockaddr*)&addrServer, sizeof(addrServer)))
	{
		perror("bind() failed");
		close(sock);
		sock = INVALID_SOCKET;
		return false;
	}

	rc = listen(sock, 32);
	if (rc < 0)
	{
		perror("listen() failed");
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
	int rc;
	sockaddr_in cAddr;
	SOCKET cSock;
	timeval timeout = { 0, 2000 };

	OnServerStep();

	do
	{
		FD_ZERO(&fds);
		CheckFDS(&fds);
		FD_SET(sock, &fds);

		rc = select(0, &fds, NULL, NULL, &timeout);

		if (rc == 0) continue;

		if (rc < 0 && errno == EINTR)
		{
			perror("select() failed");
			isActive = false;
		}

		if (FD_ISSET(sock, &fds))
		{
			int sSize = sizeof(sockaddr_in);
			cSock = accept(sock, (sockaddr*)&cAddr, (int *)&sSize);
			if (cSock != INVALID_SOCKET) { AddClient(cSock, &cAddr); }
		}
		HandleClients(&fds);
	}
	while (isActive);
}

void Server::AddClient(SOCKET sock, sockaddr_in* addr)
{
	Client* cli = CreateClient();
	cli->pServer = this;
	cli->sock = sock;
	cli->isActive = true;
	Clients.push_back(cli);
	OnConnect(cli);
}

void Server::CheckFDS(fd_set* fds)
{
	for each (Client* cli in Clients)
	{
		if (cli->isActive) FD_SET(cli->sock, fds);
		else Disconnect(cli);
	}
}

void Server::HandleClients(fd_set* fds)
{
	for each (Client* cli in Clients)
	{
		if (!cli->isActive) continue;
		if (FD_ISSET(cli->sock, fds))
		{
			if (!cli->ReceivingData()) Disconnect(cli);
		}
	}
}

void Server::Disconnect(Client* cli)
{
	OnDisconnect(cli);
	close(cli->sock);
	cli->sock = INVALID_SOCKET;
	cli->isActive = false;
	std::vector<Client*>::iterator cIt = Clients.begin();
	while (cIt != Clients.end())
	{
		Client* c = (*cIt);

		if (c == cli)
		{
			delete[] c;
			cIt = Clients.erase(cIt);
		}

		if (cIt == Clients.end() || Clients.size() == 0) break;
		++cIt;
	}
	DeleteClient(cli);
}