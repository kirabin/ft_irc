#include "User.hpp"

// * **************** Constructor & Destructor **************** * //

size_t User::_maxChannels = 1;

User::User(int sockFd, int port) {
	_nick = "";
	_sockFd = sockFd;
	_host = nullptr;
	_port = port;
	_channel = nullptr;
	_didEnter = false;
    _didEnter = false;
}

User::User(int sockFd, char *host, int port) {
	_nick = "";
	_sockFd = sockFd;
	_host = host;
	_port = port;
	_channel = nullptr;
	_didEnter = false;
	_id =  get_id();
    _didEnter = false;
}

User::~User() { }

// * **************** Standart Getter/Setter **************** * //

bool 			User::didEnter() const { return _didEnter; }
void			User::setDidEnter(bool value) { _didEnter = value; }
bool			User::didRegister() const { return _didRegister; }
int				User::getSockFd() const { return _sockFd; }
int				User::getPort() const { return _port; }
std::string		User::getName() const { return _nick; }
std::string		User::getHost() const { return _host; }
std::string		User::getNick() const { return _nick; }
std::string		User::getMessage() const { return _message; }
Channel			*User::getChannel() const { return _channel; }

std::string		User::getSign() const { return _nick + "@" + _host + ":" + std::to_string(_port); }

void			User::setNick(std::string nick) { _nick = nick.substr(0, 9); }
void			User::setUsername(std::string username) { _username = username; }
void			User::setRealname(std::string realname) { _realname = realname; }

void			User::setChannel(Channel *channel) { _channel = channel; }

// * **************** Class Function **************** * //

void			User::appendMessage(std::string message)
{
	_message.append(message);
	_message.erase(_message.find_last_not_of(MSG_DELIMITER) + 1);
	_message.append("\n");
}

void	User::clearMessage() { _message.clear(); }

string	User::getPrefix() const {
	return ":" + _nick;
}

void	User::sendMessage(User *to, std::string message) {
	to->getReply(this->getPrefix() + " " + message);
}

void			User::getReply(std::string message)
{
	std::string	finalMessage;

	finalMessage = message + MSG_DELIMITER;
	send(_sockFd, finalMessage.c_str(), finalMessage.length(), 0);
}

void			User::removeUserFromChannel()
{
	if (_channel != nullptr)
		this->_channel->removeUser(this);
}

// * **************** Extra Function **************** * //

void			User::printShortInfo() const { std::cout << "Name: " << std::setw(10) << _nick << ", fd: " << _sockFd << std::endl; }

std::string User::get_id() {
		std::string s;

		static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
		srand( time( 0 ) ); // автоматическая рандомизация
		for (int i = 0; i < 10; ++i) {
			s += alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		return s;
}

std::string User::getId() const { return _id; }

void	User::doRegister() {
	if (_didEnter && _nick != "" && _username != "") {
		this->getReply(RPL_WELCOME(_nick, _username, _host));
		_didRegister = true;
	}
}
