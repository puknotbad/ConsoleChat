//-----------------------------------------------------------------------
//  Header      : -
//  Created     : 28.12.2022
//  Updated     : 16.02.2023
//  Author      : Vladimir Lapshov
//  Description : Simple console chat. Provides users registration 
//                and messaging in common console.
//                  Main menu: 
//                1 - new user registration, 2 - login existing, 0 - exit
//                  User menu: 
//                1 - receive messages, 2 - new message, 3 - show users, 0 - exit 
// 
//                Sha1 hash function provides password storage/check safe.
//                std::queue<Message> is used for unread user messages storage;
//                std::map<std::string, std::shared_ptr<User>> stores all registered users
//-----------------------------------------------------------------------
 
#include "Chat.h"  
#include <windows.h> 
#include <iostream>  

int main(int argc, char const* argv[])
{
    // set RU if need:
    //setlocale(LC_ALL, "Russian"); 
    //SetConsoleOutputCP(1251);
    //SetConsoleCP(1251);

   std::cout << "\t" << "* C++ simple console chat *" << std::endl;
   std::cout << "\t\t" << "Hello, World!" << std::endl;
 
    Chat chat;
    chat.startChat();
    while (chat.getChatState()) {
        chat.showMainMenu();
        while (chat.getCurrentUser()) {
            chat.showUserMenu();
        }
    }
    return 0;
}
