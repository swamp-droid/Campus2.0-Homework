#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include "BroadcastSender.h"
#include "BroadcastReceiver.h"
#include <vector>
#include <mutex>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

#define PORT 27016
#define IP "10.41.255.255"
#define BUFFER_SIZE 50
using Buffer_t = std::vector<std::string>;

class Chat
{
public:
    ~Chat();

    bool Init();
    Buffer_t GetMessages();
    void StartListeningMessages();

    void HandleCommand(std::string msg);

private:
    std::string GetCommand(const std::string& text, const std::string& commandName);

    void Destroy();
    void ListenToMessages();
    void SendMessage(const std::string& msg);

    WSADATA wsaData;
    BroadcastSender m_Sender;
    BroadcastReceiver m_Receiver;

    Buffer_t m_Buffer;
    std::mutex m_MutexMessages;

    std::string m_Name = "ANONYMOUS";
};