#include "stdafx.h"
#include "NetworkProcessor.h"

#include "Network.h"
#include "Session.h"
#include "Packet.h"
#include "Logger.h"

const ULONG_PTR THREAD_CLOSE = (ULONG_PTR)(-1);	// thread terminate value

NetworkProcessor::NetworkProcessor(Network* pNetwork)
	:_hEventIOCP(0)
{
	SetArg(pNetwork);
}

NetworkProcessor::~NetworkProcessor()
{
	Destroy();
}

int NetworkProcessor::Create()
{
	if (NULL != _hEventIOCP)
	{
		Logger::Log("(NULL != m_hEventIOCP) m_hEventIOCP = %016x\n", _hEventIOCP);
	}

	_hEventIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 1);
	if (NULL == _hEventIOCP)
	{
		return GetLastError();
	}

	return 0;
}

void NetworkProcessor::Destroy()
{
	if (NULL != _hEventIOCP)
	{
		CloseHandle(_hEventIOCP);
	}
}

void NetworkProcessor::Run()
{
	Network* pNetwork = (Network*)GetArg();
	if (NULL == pNetwork)
	{
		Logger::Log("(NULL == pNetwork)\n");
		return;
	}


	BOOL Result = FALSE;
	DWORD BytesTransferred = 0;
	ULONG_PTR netEvent = INVALID_NETEVENT;
	Session* pSession = NULL;

	while (IsRunnable())
	{
		Result = GetQueuedCompletionStatus(_hEventIOCP,
			&BytesTransferred,
			(ULONG_PTR*)&netEvent,
			(LPOVERLAPPED*)&pSession,
			INFINITE);


		if (THREAD_CLOSE == (ULONG_PTR)netEvent)
		{
			Logger::Log("Thread Close\n");
			break;
		}

		if (FALSE == Result)
		{
			int rc = GetLastError();
			Logger::Log("Dispatcher\tGQCS Failed : Err:%d\n", rc);
			continue;
		}

		if (NULL == pSession)
		{
			continue;
		}

		switch (netEvent)
		{
		case NETEVENT_ACCEPT:
		{
			int rc = pSession->OnAccept();
			if (0 != rc)
			{
				pSession->Disconnect(false);
			}

		}
		break;

		case NETEVENT_CONNECT:
		{
			int rc = pSession->OnConnect();
			if (0 != rc)
			{
				pSession->Disconnect(false);
			}
		}
		break;

		case NETEVENT_CLOSE:
		{
			static int nCount = 0;
			Logger::Log("Client disconnected %s:%d [%d]\n", pSession->GetRemoteIP(), pSession->GetRemotePort(), pSession);
			pSession->OnClose();
			RELEASE_SESSION(pSession);
		}
		break;

		case NETEVENT_RECV:
		{
			int rc = 0;
			Packet packet;
			if (pSession->PopPacket(&packet))
			{
				rc = pSession->OnDispatch(&packet);

				int PacketLen = pSession->GetPacketLen((BYTE*)(packet.GetPacketHeader()));
				pSession->GetRecvBuffer()->IncreasePopPos(pSession->GetHeaderSize() + PacketLen);

				if (pSession->IsSetControlFlag(CONTROL_FLAG_CHECK_OPCODE))
				{
					if (0 != rc)
					{
						pSession->Disconnect(false);
						break;
					}
				}
			}
		}
		break;

		default:
			Logger::Log("netEvent is not valid. netEvent = %d\n", netEvent);
			break;

		}

	}
}

int NetworkProcessor::PostNetEvent(WPARAM wParam, LPARAM lParam)
{
	if (NULL == _hEventIOCP)
	{
		Logger::Log("(NULL == m_hEventIOCP)\n");
	}

	if (0 == PostQueuedCompletionStatus(_hEventIOCP, 0, (ULONG_PTR)wParam, (LPOVERLAPPED)lParam))
	{
		return GetLastError();
	}

	return 0;
}

void NetworkProcessor::Close()
{
	PostQueuedCompletionStatus(_hEventIOCP, 0, THREAD_CLOSE, NULL);
	RunObject::Close();
}
