#pragma once

//#include <vector> // TODO: for getUsersByName() function
#include <map> 
#include <memory> 
// #include <exception> 
#include "Message.h" 
#include "User.h"

// exceptions if need

class Chat
{
	//std::map<std::string, std::shared_ptr<User>> onlineUsersMap_; // TODO: For future use: active users 
	std::map<std::string, std::shared_ptr<User>> registeredUsersMap_; // all registered users. <login, User(login, name, password)>
	std::shared_ptr<User> currentUser_ = nullptr;
	bool chatStarted_ = false;

	bool registerNewUser();
	const bool login(); 

	void showAllRegisteredUsers() const;
	void sendMessage();
	std::shared_ptr<User> getUserByLogin(const std::string& loginName);

/*	** currently not used functions **
	std::vector<std::shared_ptr<User>> getUsersByName(const std::string& name); // ! name isn't a key in the chat book
	void showOnlineUsers() const; // show active users in multithread mode

    ** checkPassword() is now realised in class User **   
	const bool checkUserPassword(const std::string& loginName, const std::string& password) {return registeredUsersMap_[loginName]->getPassword() == password;};
*/

public:
	void showMainMenu();
	void showUserMenu();
	void startChat() { chatStarted_ = true; };
	bool getChatState() { return chatStarted_; };
	std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
};

