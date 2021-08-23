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

User::User(std::string nick, int sockFd, char *host, int port)
{
	_nick = nick;
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
void			User::setSockFd(int fd) { _sockFd = fd; }
void			User::setMessage(std::string message) { _message = message; }
void			User::setAuthorized(bool enter) { _enter = enter; }
void			User::setChannel(Channel *channel) { _channel = channel; }

// * **************** Class Function **************** * //

void			User::appendMessage(std::string message)
{
	_message.append(message);
	_message.erase(_message.find_last_not_of(ENDL) + 1);
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

	finalMessage = message + ENDL;
	send(_sockFd, finalMessage.c_str(), finalMessage.length(), SEND_OPT);
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

void			User::printFullInfo()const
{
	std::ostringstream	out;

	out << std::endl;
	out << "**************** User info ****************" << std::endl;

	out << "Name: " << _nick << std::endl;
	out << "SockFf: " << _sockFd << std::endl;
	out << "Port: " << _port << std::endl;
	out << "Host: " << _host << std::endl;
	out << "Channel: " << _channel->getName() << std::endl;

	out << "**************** End  info ****************" << std::endl;
	out << std::endl;

	std::cout << out;
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
