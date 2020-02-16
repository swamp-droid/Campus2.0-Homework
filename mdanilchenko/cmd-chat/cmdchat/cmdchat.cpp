#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include "Chat.h"
#include <string>

const std::string CLOSE_APP = "-exit";
bool g_IsActive = true;
Chat chat;

void PrintMessages(std::vector<std::string> messages);
void GetMessages();

int main(int argc, char *argv[])
{
    if (chat.Init())
    {
        std::cout << "[ LOG ] Initialization successful!\n";
        std::cout << "[ LOG ] \"-exit\" to close the program\n";
        std::cout << "[ LOG ] \"-send <msg>\" to broadcast <msg>\n";
        std::cout << "[ LOG ] \"-name <name>\" to change name to <name>\n";
    }

    chat.StartListeningMessages();
    std::thread th(GetMessages);
    th.detach();

    std::string consoleText;
    while (consoleText != CLOSE_APP)
    {
        std::getline(std::cin, consoleText);
        chat.HandleCommand(consoleText);
    }

    g_IsActive = false;
}

void PrintMessages(std::vector<std::string> messages)
{
    for (const auto& msg : messages)
    {
        std::cout << msg << "\n";
    }
}

void GetMessages()
{
    while (g_IsActive)
    {
        PrintMessages(chat.GetMessages());
        Sleep(1000);
    }
}