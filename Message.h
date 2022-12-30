#pragma once
#include <string> 

class Message
{
	// TODO: for logs etc.
	// int messageID;
	const std::string fromUser_;
	const std::string toUser_;
	const std::string messageBody_;

public:
	Message(const std::string& fromUser, const std::string& toUser, const std::string messageBody)
		: fromUser_(fromUser), toUser_(toUser), messageBody_(messageBody) {};
	const std::string& getFromUser() { return fromUser_; };
	const std::string& getToUser() { return toUser_; };
	const std::string& getMessageBody() { return messageBody_; };
//  TODO: for message correction
//	void setMessageBody(const std::string& messageBody) { messageBody_ = messageBody; }; 

};

