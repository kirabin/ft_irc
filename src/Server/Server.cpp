#include "Server.hpp"

// * ************** Constructor & Destructor ************** * //

Server::Server(std::string host, std::string port, std::string password) : _host(host), _port(port), _password(password)
{
	_sock = createSocket();
	_serverName = _host;
}

Server::~Server() { }

// * ************** Getter & Setter ************** * //

int				Server::getSock()const { return _sock; }
std::string		Server::getHost()const { return _host; }
std::string		Server::getPort()const { return _port; }
std::string		Server::getServerName()const { return _serverName; }

User			*Server::getUser(std::string userName)
{
	for (std::vector<User *>::iterator itUser = _users.begin(); itUser != _users.end(); itUser++)
	{
		std::string	curName = (*itUser)->getName();
		if (curName == userName)
			return *itUser;
	}
	return nullptr;
}

User			*Server::getUser(int sock)
{
	for (std::vector<User *>::iterator itUser = _users.begin(); itUser != _users.end(); itUser++)
	{
		int	curSock = (*itUser)->getSockFd();
		if (curSock == sock)
			return *itUser;
	}
	return nullptr;
}

Channel			*Server::getChannel(std::string name)
{
	std::vector<Channel *>::iterator channel;
    string tmp = name;
	if (name.empty())
        return nullptr;

    if (tmp.c_str()[0] == '#')
        tmp = tmp.substr(1, tmp.size());
	for (channel = _channels.begin(); channel != _channels.end(); channel++)
	{
		if ((*channel)->getName() == tmp)
			return *channel;
	}
	return nullptr;
}

// * ************** Main Server function ************** * //

void			Server::start()
{
	pollfd	newPollfd = {_sock, POLLIN, 0};
	if (fcntl(_sock, F_SETFL, O_NONBLOCK) == -1)
	 	throw std::runtime_error("Error: fcntl");

	std::vector<pollfd>::iterator	iter;
	_pollfds.push_back(newPollfd);
	_Invoker = new Invoker(this);

	std::cout << "Server created!" << std::endl;
	while (true) {

		iter = _pollfds.begin();
		if (poll(&(*iter), _pollfds.size(), -1) == -1)
			throw std::runtime_error("Error: poll");

		this->action();

	}
}

int				Server::acceptUser()
{
	int				client_d;
	sockaddr_in		client_addr;
	socklen_t		s_size;

	s_size = sizeof(client_addr);
	client_d = accept(_sock, (sockaddr *) &client_addr, &s_size);
	if (client_d == -1)
		throw std::runtime_error("error accept");


	pollfd	newPollfd = {client_d, POLLIN, 0};
	_pollfds.push_back(newPollfd);
	if (fcntl(client_d, F_SETFL, O_NONBLOCK) == -1)
	 	throw std::runtime_error("error fcntl");

	User	*newUser = new User(client_d, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	_users.push_back(newUser);

	std::cout << "New client " << newUser->getName() << "@" << newUser->getHost() << ":" << newUser->getPort() << std::endl;
	return client_d;
}

void			Server::greeting(int client_d)const
{
	std::string str("PASS NICK USER\n\r");
	if (send(client_d, str.c_str(), str.length(), 0) == -1)
		throw std::runtime_error("error send");
}

void			Server::action()
{
	pollfd curPollfd;

	for (std::vector<pollfd>::iterator itPollfd = _pollfds.begin(); itPollfd != _pollfds.end(); itPollfd++)
	{
		curPollfd = *itPollfd;

		 if ((curPollfd.revents & POLLHUP) == POLLHUP)
        {
            std::vector<User *>::iterator	itUser = _users.begin();
            std::advance(itUser, std::distance(_pollfds.begin(), itPollfd) - 1);

			if (_users.empty())
			{
				break;
			}

            if ((*itUser)->didRegister() && ((*itUser)->getName() != "user_example"))
            {
                std::cout << "disconnect @" << (*itUser)->getName() << std::endl;
                this->removeUser((*itUser)->getId());
            }
            else
            {
                std::cout << "disconnect not registered user" << std::endl;
                this->removeUser((*itUser)->getId());
            }

            break;

        }

		if ((curPollfd.revents & POLLIN) == POLLIN)
		{
			if (curPollfd.fd == _sock)
			{
				this->greeting(acceptUser());
				break ;
			}
			else
			{
				std::vector<User *>::iterator	itUser = _users.begin();
				std::advance(itUser, std::distance(_pollfds.begin(), itPollfd) - 1);
				ssize_t byteRecved;
				byteRecved = recvMsg(*itUser);
				_Invoker->processData(*itUser, (*itUser)->getMessage());

			}
		}


	}
}

int				Server::recvMsg(User *user) {
	ssize_t		byteRecved;
	char		message[100];

	user->clearMessage();
	memset(message, '\0', sizeof(message));
	while (!std::strstr(message, MSG_DELIMITER))
	{
		memset(message, '\0', sizeof(message));
		byteRecved = recv(user->getSockFd(), message, sizeof(message), RECV_FLAGS);
		if (byteRecved <= 0)
			break ;
		user->appendMessage(message);
	}
	return (byteRecved);
}

// * ************** Added function ************** * //

void			Server::removeUser(std::string id)
{
    std::cout << "id: " << id << " nickname: " << this->getUserById(id)->getNick() << std::endl;
    std::cout << "socket fd: " << this->getUserById(id)->getSockFd() << std::endl;
    this->removeUserFromPoll(id);
    this->removeUserFromUsers(id);
}

Channel		*Server::createChannel(std::string name, User *admin)
{
	Channel	*newChannel = new Channel(name, admin, this);
	_channels.push_back(newChannel);
	return newChannel;
}

void	Server::deleteChannel(Channel *channel) {
	std::vector<Channel *>::iterator it;

	for (it = _channels.begin(); it < _channels.end(); it++)
	{
		if (*it == channel)
		{
			_channels.erase(it);
			break ;
		}
	}
}

// * ************** Extra function ************** * //

int				Server::createSocket()
{
	addrinfo	hints;
	addrinfo	*servinfo;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags    = AI_PASSIVE;
	if (getaddrinfo(_host.c_str(), _port.c_str(), &hints, &servinfo) != 0)
		throw std::runtime_error("error: getaddrinfo");

	addrinfo	*p;
	int			sock;
	int			yes = 1;

	for (p = servinfo; p != nullptr; p = p->ai_next) {
		sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		if (sock == -1)
			continue;

		if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)	// Choose Socket option
		{
			close(sock);
			freeaddrinfo(servinfo);
			throw std::runtime_error("error: setsockopt");
		}

		if (bind(sock, p->ai_addr, p->ai_addrlen) == -1)		// Bind socket with some addr
		{
			close(sock);
			continue;
		}
		break;
	}

	freeaddrinfo(servinfo);
	if (p == nullptr)
		throw std::runtime_error("error: failed to find address");
	if (listen(sock, MAX_CONNECTION) == -1)						// Make listen socket
		throw std::runtime_error("error: listen");

	return sock;
}

void Server::log(std::string text) { std::cout << text << std::endl; }

vector<Channel *> Server::getChannels() { return _channels; }

void Server::removeUserFromChannel() {

}

void Server::removeUserFromUsers(std::string id) {
	std::vector<User *>::iterator	it = _users.begin();
	std::vector<User *>::iterator	ite = _users.end();
	for (; it != ite; it++ )
	{
		if ((*it)->getId() == id)
		{
			_users.erase(it);
			break ;
		}
	}
}

void Server::removeUserFromPoll(std::string id) {
	int socketUser = this->getUserById(id)->getSockFd();
	std::vector<pollfd>::iterator	it = _pollfds.begin();
	std::vector<pollfd>::iterator	ite = _pollfds.end();
	for (; it != ite; it++ )
	{
		if (socketUser == (*it).fd)
		{
			close((*it).fd);
			_pollfds.erase(it);
			break ;
		}
	}
}

void Server::show_pollfd() {
	std::vector<pollfd>::iterator	it = _pollfds.begin();
	std::vector<pollfd>::iterator	ite = _pollfds.end();
	for (; it != ite; it++ )
		std::cout << (*it).fd << std::endl;
}

User *Server::getUserById(std::string id) {
	for (std::vector<User *>::iterator itUser = _users.begin(); itUser != _users.end(); itUser++)
	{
		std::string	_id = (*itUser)->getId();
		if (_id == id)
			return *itUser;
	}
	return nullptr;
}

bool	Server::checkPassword(std::string userPassword) {
	if (userPassword == _password)
		return true;
	return false;
}


std::string		Server::getPrefix() const {
	return ":" + _serverName;
}

void	Server::sendMessage(User* to, std::string message) {
	to->getReply(getPrefix() + " " + message);
}
