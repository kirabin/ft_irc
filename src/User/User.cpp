#include "User.hpp"

// * **************** Constructor & Destructor **************** * //

User::User(int sockFd, int port)
{
	_nick = nullptr;
	_sockFd = sockFd;
	_host = nullptr;
	_port = port;
	_channel = nullptr;
	_enter = false;
}

User::User(int sockFd, char *host, int port)
{
	_nick = "";
	_sockFd = sockFd;
	_host = host;
	_port = port;
	_channel = nullptr;
	_enter = false;
	_id =  get_id();
}

User::~User()
{ }

// * **************** Standart Getter/Setter **************** * //

bool 			User::isAuthorized()const { return _enter; }
int				User::getSockFd()const { return _sockFd; }
int				User::getPort()const { return _port; }
std::string		User::getName()const { return _nick; }
std::string		User::getHost()const { return _host; }
std::string		User::getNick()const { return _nick; }
std::string		User::getMessage() const { return _message; }
Channel			*User::getChannel()const { return _channel; }

std::string		User::getSign()const { return _nick + "@" + _host + ":" + std::to_string(_port); }

void			User::setName(std::string name) { _nick = name; }

void			User::setAuthorized(bool enter) { _enter = enter; }
void			User::setChannel(Channel *channel) { _channel = channel; }

// * **************** Class Function **************** * //

void			User::appendMessage(std::string message)
{
	_message.append(message);
	_message.erase(_message.find_last_not_of("\n\r") + 1);
	_message.append("\n");
}

void	User::clearMessage()
{
	_message.clear();
}

void	User::sendMessageToChannel(std::string message)
{
	if (!message.empty())
    {
        if (_channel != nullptr)
            _channel->sendMessageToChannel(this, message);
    }
}

void			User::getReply(std::string message)
{
	std::string	finalMessage;

	finalMessage = message + "\n\r";
	send(_sockFd, finalMessage.c_str(), finalMessage.length(), 0);
}

void			User::removeUserFromChannel()
{
	if (_channel != nullptr)
		this->_channel->removeUser(this);
}

// * **************** Extra Function **************** * //

void			User::printShortInfo()const
{
	std::cout << "Name: " << std::setw(10) << _nick << ", fd: " << _sockFd << std::endl;
}

std::string User::get_id() {

		std::string s;
		static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
		srand( time( 0 ) ); // автоматическая рандомизация
		for (int i = 0; i < 25; ++i) {
			s += alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		return s;

}

std::string User::getId() const{
	return _id;
}
