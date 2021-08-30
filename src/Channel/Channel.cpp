#include "Channel.hpp"

Channel::Channel(std::string name, User* admin, Server *server) :
 _admin(admin), _server(server) {
	setName(name);
}

Channel::~Channel() {}

// * **************** Standart Getter/Setter **************** * //

std::string			Channel::getName()const { return _name; }
User				*Channel::getAdmin()const { return _admin; }

void				Channel::setName(std::string name) {
	size_t maxNameLenght = 200;
	_name = name.substr(1, maxNameLenght);
}

// * **************** Class Function **************** * //

void				Channel::addUser(User *newUser) {
	_users.push_back(newUser);
}

void				Channel::removeUser(User *user)
{
	std::vector<User *>::iterator it;

	for (it = _users.begin(); it < _users.end(); it++)
	{
		if (*it == user)
		{
			std::cout << "The user *" << (*it)->getName();
			std::cout << "* has been removed from the channel *" << this->_name << "*" << std::endl;
			_users.erase(it);
			break ;
		}
	}
	if (_users.empty()) {
		_server->deleteChannel(this);
	}
}

void	Channel::sendMessageToUser(User* user, std::string message) {
	send(user->getSockFd(), message.c_str(), message.length(), 0);
}

void	Channel::sendMessageToChannel(User *sender, std::string message) {

	for (std::vector<User *>::iterator iter = _users.begin(); iter != _users.end(); iter++)
	{
		if (*iter != sender)
			sendMessageToUser(*iter, sender->getNick() + " " + message + "\n");
	}
}

void				Channel::sendServiceMessageToChannel(std::string message)
{
	std::string	fMessage = "* " + message + " *";

	for (std::vector<User *>::iterator iter = _users.begin(); iter != _users.end(); iter++) {
		send((*iter)->getSockFd(), fMessage.c_str(), fMessage.length(), 0);
	}
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

User			*Channel::getUser(std::string userName)
{
	for (std::vector<User *>::iterator itUser = _users.begin(); itUser != _users.end(); itUser++)
	{
		std::string	curName = (*itUser)->getName();
		if (curName == userName)
			return *itUser;
	}
	return nullptr;
}

std::vector<User *> Channel::getUsers() const {
	return _users;
}

bool	isAllowedChannelName(std::string channelName) {
	if (channelName.empty()) {
		std::cout << "1";
		return false;
	}
	if (channelName[0] != '#' && channelName[0] != '&') {
		std::cout << "2";
		return false;
	}

	for (size_t i = 0; i < channelName.size(); i++) {
		if (channelName[i] == ' ' || channelName[i] == 7 || channelName[i] == ',') {
			std::cout << "3";
			return false;
		}
	}
	return true;
}
