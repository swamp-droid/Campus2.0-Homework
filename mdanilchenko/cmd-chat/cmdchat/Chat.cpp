#include "Chat.h"
#include <string>

const char START_COMMAND = '-';
const std::string CLOSE_APP = "-exit";
const std::string SEND_MESSAGE = "send ";
const std::string CHANGE_NAME = "name ";
const std::string NONE = "";

const std::string CONNECT_MESSAGE = "connect123kappa";

Chat::~Chat()
{
    Destroy();
}

bool Chat::Init()
{
    if (WSAStartup(MAKEWORD(2, 2), &wsaData))
    {
        std::cout << "WSAStartup failed\n";
        return false;
    }

    return m_Sender.Init(PORT) && m_Receiver.Init(PORT);
}

Buffer_t Chat::GetMessages()
{
    std::lock_guard<std::mutex> lock(m_MutexMessages);
    Buffer_t messages = m_Buffer;
    m_Buffer.clear();

    return messages;
}

void Chat::StartListeningMessages()
{
    m_Receiver.SetActive(true);
    std::thread th(&Chat::ListenToMessages, this);
    th.detach();
}

void Chat::HandleCommand(std::string msg)
{
    std::string command = GetCommand(msg, SEND_MESSAGE);
    if (command != NONE)
    {
        SendMessage("[ " + m_Name + " ] " + command);
    }

    command = GetCommand(msg, CHANGE_NAME);
    if(command != NONE)
    {
        m_Name = command;
    }
}

std::string Chat::GetCommand(const std::string& msg, const std::string& commandName)
{
    std::string command;
    if (msg.length() > 0 && msg[0] == START_COMMAND)
    {
        const int commandPos = commandName.length();
        if (msg.length() >= commandPos + 1 && msg.substr(1, commandPos) == commandName)
        {
            command = msg.substr(commandPos + 1, msg.length() - commandPos - 1);
            if (command.length() > 0)
            {
                return command;
            }
        }
    }
    return NONE;
}

void Chat::Destroy()
{
    m_Receiver.Destroy();
    m_Sender.Destroy();
}

void Chat::ListenToMessages()
{
    while (m_Receiver.IsActive())
    {
        const char* msg = m_Receiver.ReceiveMessage();
        if(msg > 0)
        {
            std::lock_guard<std::mutex> lock(m_MutexMessages);
            m_Buffer.push_back(msg);
        }
    }
}

void Chat::SendMessage(const std::string& msg)
{
    m_Sender.BroadcastMessage(msg.c_str());
}

