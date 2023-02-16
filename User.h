/* регистрация пользователей - логин, пароль, имя */

#pragma once

#include <queue>
#include "Message.h" 
#include "Sha1.h"

class User
{
	std::string login_;
	//std::string password_; // was used before Sha1 hash implementation
	uint* passwordSha1Hash_;
	std::string userName_;
	std::queue<Message> messagesList_; // Unread messages for the User
	
public:
	User(const std::string& login, const std::string& password, const std::string& userName)
		: login_(login), passwordSha1Hash_(sha1(password, password.length())), userName_(userName) {}
	const bool checkPassword(const std::string& password) { return *passwordSha1Hash_ == *sha1(password, password.length()); }
	void setPassword(const std::string& password) { passwordSha1Hash_ = sha1(password, password.length()); }
	const std::string& getUserName() { return userName_; }
	void setUserName(const std::string& userName) { userName_ = userName; }
	const std::string& getUserLogin() { return login_; }
	void addNewMessage(const Message& message) { messagesList_.push(message); } // adds new offline message to queue
	void showNewMessages(); // shows and erases (pop) newMessages queue
};

