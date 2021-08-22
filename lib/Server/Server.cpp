#include "Server.hpp"

int				createSocket(const char *port);

// * ************** Constructor & Destructor ************** * //

Server::Server(std::string host, std::string port, std::string password) : _host(host), _port(port), _password(password + "\n")
{
	_sock = createSocket();
//	_channels.push_back(new Channel("#room1", nullptr));
//	_channels.push_back(new Channel("#room2", nullptr));
	_servname = _host + ":" + _port;
}



Server::~Server() { }

// * ************** Getter & Setter ************** * //

int				Server::getSock()const { return _sock; }
std::string		Server::getHost()const { return _host; }
std::string		Server::getPort()const { return _port; }
std::string		Server::getSign()const { return _port; }
std::string		Server::getServname()const { return _servname; }

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

Channel			*Server::getChannel(std::string chanName)
{
	for (std::vector<Channel *>::iterator itUser = _channels.begin(); itUser != _channels.end(); itUser++)
	{
		std::string	curName = (*itUser)->getName();
		if (curName == chanName)
			return *itUser;
	}
	return nullptr;
}

// * ************** Main Server function ************** * //

void			Server::start()
{
	pollfd	newPollfd = {_sock, POLLIN, 0};
	if (fcntl(_sock, F_SETFL, O_NONBLOCK) == -1)
	 	throw std::runtime_error("error fcntl");

	std::vector<pollfd>::iterator	iter;
	_pollfds.push_back(newPollfd);
	_Invoker = new Invoker(this);

	std::cout << "server created!" << std::endl;
	while (true) {

		iter = _pollfds.begin();
		if (poll(&(*iter), _pollfds.size(), -1) == -1)
			throw std::runtime_error("error: poll");
		this->action();
	}
}

int				Server::acceptOK()
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

	static int	i;
	i++;

	User	*newUser = new User("user_example", client_d, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	_users.push_back(newUser);

// TODO Убрать добавление в рандомный чат
	//randChannel->addUser(newUser);

	std::cout << "New client " << newUser->getName() << "@" << newUser->getHost() << ":" << newUser->getPort() << std::endl;
	return client_d;
}

void			Server::greeting(int client_d)const
{
	std::string str((WELCOME_MSG(_servname)));

	if (send(client_d, str.c_str(), str.length(), SEND_OPT) == -1)
		throw std::runtime_error("error send");
	str = "Enter password: ";
	if (send(client_d, str.c_str(), str.length(), SEND_OPT) == -1)
		throw std::runtime_error("error send");
}

void			Server::action()
{
	pollfd curPollfd;

	for (std::vector<pollfd>::iterator itPollfd = _pollfds.begin(); itPollfd != _pollfds.end(); itPollfd++)
	{
		curPollfd = *itPollfd;
		if ((curPollfd.revents & POLLIN) == POLLIN)
		{
			if (curPollfd.fd == _sock)
			{
				this->greeting(acceptOK());
				break ;
			}
			else
			{
				std::vector<User *>::iterator	itUser = _users.begin();
				std::advance(itUser, std::distance(_pollfds.begin(), itPollfd) - 1);
				ssize_t byteRecved;
                byteRecved = recvMsg(*itUser);
                if ((*itUser)->isAuthorized())
                {
                    _Invoker->processData(*itUser, (*itUser)->getMessage());
                }
                else
                {
                    validEnter(*itUser);
                }

			}
		}



	}
}

int				Server::recvMsg(User *user) {
	ssize_t		byteRecved;
	char		message[100];

	user->clearMessage();
	memset(message, '\0', sizeof(message));
	while (!std::strstr(message, ENDL))
	{
		memset(message, '\0', sizeof(message));
		byteRecved = recv(user->getSockFd(), message, sizeof(message), RECV_FLAGS);
		if (byteRecved <= 0)
			break ;
		user->appendMessage(message);
	}
	return (byteRecved);
}

void			Server::validEnter(User *user)
{
	std::string str("Success\n");

	if (user->getMessage() == _password)
	{
		user->setEnter(true);
		if (send(user->getSockFd(), str.c_str(), str.length(), SEND_OPT) == -1)
			throw std::runtime_error("error send");
	}
	else
	{
		str = "Invalid password\n";
		if (send(user->getSockFd(), str.c_str(), str.length(), SEND_OPT) == -1)
			throw std::runtime_error("error send");
		str = "Enter password: ";
		if (send(user->getSockFd(), str.c_str(), str.length(), SEND_OPT) == -1)
			throw std::runtime_error("error send");
	}
}

// * ************** Added function ************** * //

void			Server::removeUser(int i)
{
	// remove User[i] - first
	std::vector<User *>::iterator iterUser = _users.begin();
	std::advance(iterUser, i - 1);

	(*iterUser)->removeUserFromChannel();
	_users.erase(iterUser);

	// remove Pollfd[i] - second
	std::vector<pollfd>::iterator iterPollfd = _pollfds.begin();
	std::advance(iterPollfd, i);

	_pollfds.erase(iterPollfd);
}

Channel			*Server::addChannel(std::string name, User *admin)
{
	Channel	*newChannel = new Channel(name, admin);
	_channels.push_back(newChannel);
	return newChannel;
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

void Server::log(std::string text) {
    std::cout << text << std::endl;
}

vector<Channel *> Server::getChannels() {
    return _channels;
}

