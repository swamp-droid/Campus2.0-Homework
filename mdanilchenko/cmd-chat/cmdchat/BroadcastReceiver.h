#pragma once
#include <iostream>
#include <WinSock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 50

class BroadcastReceiver
{
public:
    bool Init(int port);
    const char* ReceiveMessage();
    void Destroy() { closesocket(m_Sock); m_IsActive = false; }

    void SetActive(bool active) { m_IsActive = active; }
    bool IsActive() const { return m_IsActive; }

private:
    bool InitSocket();

    SOCKET m_Sock;
    struct sockaddr_in m_ReceiverAddress;
    struct sockaddr_in m_SenderAddress;

    const char* m_SendMessage;
    char m_ReceiveBuffer[BUFFER_SIZE] = "";
    int m_ReceiveBufferLen = BUFFER_SIZE;

    bool m_IsActive = false;
};