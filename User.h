/* регистрация пользователей - логин, пароль, имя */

#pragma once

//#include <string> 
#include <queue>
#include "Message.h" 

class User
{
	std::string login_;
	std::string password_;
	std::string userName_;
	std::queue<Message> messagesList_; // Unread messages for the User
	
public:
	User(const std::string& login, const std::string& password, const std::string& userName)
		: login_(login), password_(password), userName_(userName) {}
	//const std::string& getPassword() { return password_; };
	bool checkPassword(const std::string& password) { return password_==password; }
	void setPassword(const std::string& password) { password_ = password; }
	const std::string& getUserName() { return userName_; }
	void setUserName(const std::string& userName) { userName_ = userName; }
	const std::string& getUserLogin() { return login_; }
	void addNewMessage(const Message& message) { messagesList_.push(message); } // adds new offline message to queue
	void showNewMessages(); // shows and erases (pop) newMessages queue
};

