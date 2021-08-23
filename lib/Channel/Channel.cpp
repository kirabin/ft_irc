#include "Channel.hpp"

Channel::Channel(std::string name, User* admin) : _name(name), _admin(admin) {}

Channel::~Channel() {}

// * **************** Standart Getter/Setter **************** * //

std::string			Channel::getName()const { return _name; }
User				*Channel::getAdmin()const { return _admin; }

// * **************** Class Function **************** * //

void				Channel::addUser(User *newUser) {
	_users.push_back(newUser);
}

void				Channel::removeUser(User *user)
{
	std::vector<User *>::iterator iter = _users.begin();
	User *tmp;

	for (; iter < _users.end(); iter++)
	{
		tmp = *iter;
		if (tmp == user)
		{
			std::cout << "The user *" << tmp->getName();
			std::cout << "* has been removed from the channel *" << this->_name << "*" << std::endl;
			_users.erase(iter);
			break ;
		}
	}
}

void	Channel::sendMessageToUser(User* user, std::string message) {
	send(user->getSockFd(), message.c_str(), message.length(), SEND_OPT);
}

void	Channel::sendMessageToChannel(User *sender, std::string message) {


	for (std::vector<User *>::iterator iter = _users.begin(); iter != _users.end(); iter++)
	{
		if (*iter != sender && (*iter)->isAuthorized())
			sendMessageToUser(*iter, sender->getSign() + " :" + message);
	}
}

void				Channel::sendServiceMessageToChannel(std::string message)
{
	std::string	fMessage = "* " + message + " *";

	for (std::vector<User *>::iterator iter = _users.begin(); iter != _users.end(); iter++) {
		send((*iter)->getSockFd(), fMessage.c_str(), fMessage.length(), SEND_OPT);
	}
}

// * **************** Extra Function **************** * //

void			Channel::printShortInfo()const
{
	std::ostringstream	out;

	out << "Name: " << std::setw(10) << _name << ", users: " << _users.size() << std::endl;
	std::cout << out;
}

void			Channel::printFullInfo()const
{
	std::cout << std::endl;
	std::cout << "**************** Channel info ****************" << std::endl;

	std::cout << "Name: " << std::setw(10) << _name << ", users: " << _users.size() << std::endl;
	if (_users.size() > 0) {
		std::cout << "User info: " << std::endl;
	}

	int i = 0;
	for (std::vector<User *>::const_iterator iter = _users.begin(); iter != _users.end(); iter++, i++)
	{
		std::cout << i << ") ";
		(*iter)->printShortInfo();
	}

	std::cout << std::endl << "**************** End    info ****************" << std::endl;

}

bool			Channel::isUser(User *user)const
{
	std::vector<User *>::const_iterator itUser;
	for (itUser = _users.begin(); itUser != _users.end(); itUser++)
	{
		if (*itUser == user)
			return true;
	}
	return false;
}

