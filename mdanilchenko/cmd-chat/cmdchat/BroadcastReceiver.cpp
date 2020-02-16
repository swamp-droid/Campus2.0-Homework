#include "BroadcastReceiver.h"

bool BroadcastReceiver::Init(int port)
{
    if (!InitSocket())
    {
        return false;
    }

    m_ReceiverAddress.sin_family = AF_INET;
    m_ReceiverAddress.sin_port = htons(port);
    m_ReceiverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_Sock, (sockaddr*)&m_ReceiverAddress, sizeof(m_ReceiverAddress)) < 0)
    {
        std::cout << "Error in BINDING: " << WSAGetLastError();
        return false;
    }

    return true;
}

const char* BroadcastReceiver::ReceiveMessage()
{
    int len = sizeof(struct sockaddr_in);
    recvfrom(m_Sock, m_ReceiveBuffer, m_ReceiveBufferLen, 0, (sockaddr*)&m_SenderAddress, &len);

    return m_ReceiveBuffer;
}

bool BroadcastReceiver::InitSocket()
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
