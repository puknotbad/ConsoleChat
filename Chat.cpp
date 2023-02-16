#include "Chat.h"
#include "Message.h"
#include "MyExceptions.h"

#include <windows.h> // WinApi header for colored text
#include <conio.h> // used for _getch(): char input without enter
#include <iostream>  

const int YELLOW = 14; //"033[33m";
const int GREEN = 10;
const int WHITE = 15;
const int RED = 4;
const int CYAN = 11;
const int MAGENTA = 13;

void Chat::showMainMenu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	std::cout << " - Main menu -" << std::endl;
	std::cout << "Choose: 1 - new user registration, 2 - login existing, 0 - exit " << std::endl;
	char menuChoice = _getch(); // unbuffered single char input
	while (chatStarted_ && !currentUser_) // while nobody has loged in
	{
		switch (menuChoice)
		{
		case '0':
			chatStarted_ = false;
			break;
		case '1':
			// if unsuccessfull registration -> go to the main menu
			// if successfull -> set currentUser_ and go to the user menu on next while cicle
			if (!registerNewUser()) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
				std::cout << "Choose: 1 - new user registration, 2 - login existing, 0 - exit" << std::endl;
				menuChoice = _getch();
			}
			break;
		case '2':
			// if unsuccessfull login -> go to the main menu
			// if successfull login -> set currentUser_ and go to the user menu on next while cicle
			if (!login()) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
				std::cout << "Choose: 1 - new user registration, 2 - login existing, 0 - exit" << std::endl;
				menuChoice = _getch();
			}
			break;
		default:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			std::cout << "Incorrect Choice!" << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
			std::cout << "1 - new user registration, 2 - login existing, 0 - exit" << std::endl;
			menuChoice = _getch();
			break;
		}
	}
	return;
}

void Chat::showUserMenu()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	std::cout << "Hi, " << currentUser_->getUserName() << "!" << std::endl;
	while (1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "Choose: 1 - receive messages, 2 - new message, 3 - show users, 0 - exit to the main menu" << std::endl;
		char menuChoice = _getch();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
		switch (menuChoice)
		{
			case '0': // logout currentUser and return to main menu
				currentUser_ = nullptr;
				return;
			case '1':
				currentUser_->showNewMessages();
				break;
			case '2':
				sendMessage();
				break;
			case '3':
				showAllRegisteredUsers();
				break;
			default:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
				std::cout << "Incorrect Choice!" << std::endl;
				break;
		}
	}
}

bool Chat::registerNewUser()
{
	std::string loginName, password, name;
	std::cout << "-------------------------" << std::endl;
	std::cout << "Chose your login (\"all\" is reserved for group messages): "; 
	std::cin >> loginName;

	// NewUserLoginException
	// if login allready exists or reserved at registeredUsersMap_ -> throws
	NewUserLoginException newUserLoginException;
	try { 
		if (!registeredUsersMap_.empty() && (registeredUsersMap_.find(loginName) != registeredUsersMap_.end() || loginName == "all")) // std::map::contains() works since C ++ 20
		{
			throw newUserLoginException;
		};

		std::cout << "Enter your name: "; 
		std::cin >> name;
		std::cout << "Enter password: "; 
		std::cin >> password;
		std::cout << "-------------------------" << std::endl;
		currentUser_ = std::make_shared<User>(User(loginName, password, name)); // makes currentUser_ = new user
		registeredUsersMap_[loginName] = currentUser_; // and adds new user to the map
		return true;
	}

	catch (NewUserLoginException& excpt) // shows alert and returns to the user menu
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		std::cout << excpt.what() << '\n';
		return false;
	};

}

const bool Chat::login()
{	
	std::string loginName, password;
	std::cout << "Login: ";
	std::cin >> loginName;
	std::cout << "Password: ";
	std::cin >> password;

	if (registeredUsersMap_.find(loginName) == registeredUsersMap_.end() || // login is not registered           // std::map::contains() won't work before C++20
		!(registeredUsersMap_[loginName]->checkPassword(password))) // or password is incorrect
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		std::cout << "Wrong login / password!" << std::endl;
		return false;
	}
	currentUser_ = registeredUsersMap_[loginName]; // if login / password are OK -> set currentUser
	return true;
}

void Chat::showAllRegisteredUsers() const
{
	std::cout << "-------------------------" << std::endl;
	std::cout << "Registered users: " << std::endl;
	for (auto &user : registeredUsersMap_)
	{
		std::cout << "Name " << user.second->getUserName() << " | Nickname (login): " << user.first 
			<< (currentUser_ == user.second ? " *current" : "") << std::endl;
	}
	std::cout << "-------------------------" << std::endl;
	return;
}

void Chat::sendMessage()
{
	std::string toUser;
	std::string text;
	std::cout << "-------------------------" << std::endl;
	std::cout << "To whom? (nickname/login or \"all\") ? ";
	std::cin >> toUser;
	if (!getUserByLogin(toUser) && toUser != "all") {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		std::cout << "Oops 8O( ... the nickname is not registered..." << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CYAN);
		std::cout << "-------------------------" << std::endl;
		return;
	}
	std::cout << "Type your message: ";
	std::cin.clear(); std::cin.ignore(INT_MAX, '\n'); // clear buffer. Ununderstandable undefined behavioured dog shit.. 
	std::getline(std::cin, text);
	Message message(currentUser_->getUserLogin(), toUser, text);
	// private message
	if (toUser != "all") {
		registeredUsersMap_[toUser]->addNewMessage(message);
	}
	// group message
	else {
		for (auto &user : registeredUsersMap_) {
			user.second->addNewMessage(message);
		}
	}
	std::cout << "-------------------------" << std::endl;
	return;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login)// const
{	// if login exists - return user(login), else - nullptr
	return (registeredUsersMap_.find(login) != registeredUsersMap_.end() ? registeredUsersMap_[login] : nullptr);
}

/*    ** currently not used functions **
std::vector<std::shared_ptr<User>> Chat::getUsersByName(const std::string& name)
{
	std::vector<std::shared_ptr<User>> nameNamedUsers;
	for (auto &iter: registeredUsersMap_) 
	{
		if ((iter.second)->getUserName() == name)
		{
			nameNamedUsers.push_back(iter.second);
		}
	}
	return nameNamedUsers;
}
*/