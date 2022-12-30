# ConsoleChat
A simple ConsoleChat as a Skillfactory homework

// This is a personal academic project. Dear Skillfactory, please check it. 

  Author      : Vladimir Lapshov
  Description : Simple console chat. Provides users registration 
                and messaging in common console.
		
                  Main menu: 
                1 - new user registration, 2 - login existing, 0 - exit
		
                  User menu: 
                1 - receive messages, 2 - new message, 3 - show users, 0 - exit 
![ChatDemo](ChatDemo.png)
Class Chat - main Class in the ConsoleChat. 
	Provides user registration, login/logout, massages reading and writing
	
	std::map<std::string, std::shared_ptr<User>> registeredUsersMap_; 
	std::shared_ptr<User> currentUser_;
	bool chatStarted_ = false;
	bool registerNewUser();
	const bool login(); 
	const void showAllRegisteredUsers() const;
	void sendMessage();
	std::shared_ptr<User> getUserByLogin(const std::string& login);

MyExceptions.h
A couple of useless exceptions redefined  here, 
just for show

class User
{
	std::string login_;
	std::string password_;
	std::string userName_;
	std::queue<Message> messagesList_; // Unread messages for the User
}  

Class Message
{
	const std::string fromUser_;
	const std::string toUser_;
	const std::string messageBody_;
  }
  
