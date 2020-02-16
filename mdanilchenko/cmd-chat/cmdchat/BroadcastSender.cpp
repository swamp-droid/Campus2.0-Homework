#include "BroadcastSender.h"

bool BroadcastSender::Init(int port)
{
    if (!InitSocket())
    {
        return false;
    }

    m_ReceiverAddress.sin_family = AF_INET;
    m_ReceiverAddress.sin_port = htons(port);
    m_ReceiverAddress.sin_addr.s_addr = INADDR_BROADCAST;

    return true;
}

int BroadcastSender::BroadcastMessage(const char* msg)
{
    m_SendMessage = msg;

    int sendResult = sendto(m_Sock, m_SendMessage, strlen(m_SendMessage) + 1, 0, (sockaddr*)&m_ReceiverAddress, sizeof(m_ReceiverAddress));
    if (sendResult <= 0)
    {
        std::cout << "Failed to send: " << WSAGetLastError() << " \n";
    }

    return sendResult;
}

bool BroadcastSender::InitSocket()
{
    m_Sock = socket(AF_INET, SOCK_DGRAM, 0);
    const char broadcast = '1';

    if (setsockopt(m_Sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast) < 0))
    {
        std::cout << "Error in setting Broadcast option! \n";
        closesocket(m_Sock);
        return false;
    }

    return true;
}
