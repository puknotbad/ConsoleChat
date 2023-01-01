#include "User.h"
#include "MyExceptions.h"
#include <iostream>  

void User::showNewMessages()
{
	MessagesListException messagesListException;
	std::cout << "-------------------------" << std::endl;
	try {
		if (messagesList_.empty()) {
			throw messagesListException; // Exception throws when trying to read an empty message queue;
		}
		while (messagesList_.size() != 0) { 
			std::cout << "From " << (messagesList_.front()).getFromUser() << " message: " << (messagesList_.front()).getMessageBody() << std::endl;
			messagesList_.pop();
		}
		std::cout << "No more messages to read." << std::endl;	
	}
	catch (MessagesListException& excpt)
	{
		std::cout << excpt.what() << '\n';
	}
	
	std::cout << "-------------------------" << std::endl;
	return;
}
