#include "Executor.Class.hpp"

void			printLog(User *user, std::string cmd);

// * **************** Constructor & Destructor **************** * //

Executor::Executor(Server *server)
{
	_server = server;
	_commands.push_back(new HelpCommand("/help"));
	_commands.push_back(new NickCommand("/nick"));
	_commands.push_back(new JoinCommand("/join"));
	_commands.push_back(new LeaveCommand("/leave"));
	_commands.push_back(new WhoCommand("/who"));
	_commands.push_back(new KickCommand("/kick"));
}

// * **************** Standart Getter/Setter **************** * //

std::string		Executor::getMessage()const { return _msg; }
User			*Executor::getSender()const { return _sender; }

void			Executor::setServer(Server *server) { _server = server; }

void			Executor::processCommand()
{
	std::stringstream	ssMsg(_msg);
	std::string			av;

	while (getline(ssMsg, av, ' '))
	{
		av.erase(av.find_last_not_of(ENDL) + 1);
		_argv.push_back(av);
	}

	std::string		commandName = _argv[0];

	std::cout << commandName << std::endl;
	for (size_t i = 0; i < _commands.size(); i++) {
		if (commandName == _commands[i]->getName()) {
			_commands[i]->execute();
			break;
		}
	}
	clearArgv();
}

void			Executor::processData(User *sender, std::string data)
{
	_sender = sender;
	_msg = data;

	if (data[0] == '/') {  // data.isCommand()
		processCommand();
	} else {
		sender->sendMessageToChannel(data);
	}
}

// * **************** Other Class function **************** * //

void			printLog(User *user, std::string cmd)
{
	std::cout << SPC << user->getSign() << " call command " << cmd << SPC << std::endl;
}

void			Executor::help()
{
	printLog(_sender, HELP);

	if (_argv.size() > 1)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), _argv[0])));
		return ;
	}

	std::string		discribe[CMD_SIZE] = {
		HELP_DIS, NICK_DIS, JOIN_DIS, LEAVE_DIS, WHO_DIS, KICK_DIS
	};

	_sender->getReply(_server->getSign() + SPC + HELP);

	for (int i = 0; i < CMD_SIZE; i++) {
		_sender->getReply(discribe[i]);
	}
}

void			Executor::nick()
{
	printLog(_sender, NICK);

	if (_argv.size() < 2)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), _argv[0])));
		return ;
	}
	else if (_argv.size() > 2)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), _argv[0])));
		return ;
	}

	if (_server->getUser(_argv[1]) != nullptr)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_NICKNAMEINUSE(_sender->getName(), _argv[0])));
		return ;
	}

	std::string newName = _argv[1];
	std::string oldName = _sender->getName();

	_sender->setName(newName);
	_sender->sendMessageToChannel(_msg);
	_sender->getChannel()->sendServiceMessageToChannel(oldName + " change name to " + newName);
}

void			Executor::join()
{
	printLog(_sender, JOIN);

	if (_argv.size() < 2)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), _argv[0])));
		return ;
	}
	else if (_argv.size() > 2)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), _argv[0])));
		return ;
	}

	if (_sender->getChannel() != nullptr)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYCHANNELS(_sender->getName(), _argv[0], _argv[1])));
		return ;
	}

	if (_argv[1].size() < 2 || _argv[1][0] != '#')
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_BADCHANMASK(_sender->getName(), _argv[0], _argv[1])));
		return ;
	}

	Channel *existChan = _server->getChannel(_argv[1]);
	if (existChan != nullptr)
	{
		_sender->setChannel(existChan);
		existChan->addUser(_sender);
		return ;
	}

	Channel	*newChannel = _server->addChannel(_argv[1], _sender);
	_sender->setChannel(newChannel);
	_sender->getChannel()->sendServiceMessageToChannel(_sender->getName() + " join to channel " + newChannel->getName());
}

void			Executor::leave()
{
	printLog(_sender, LEAVE);

	if (_argv.size() < 2)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), _argv[0])));
		return ;
	}
	else if (_argv.size() > 2)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), _argv[0])));
		return ;
	}

	if (_sender->getChannel() == nullptr)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_NOTONCHANNEL(_sender->getName(), _argv[0], _argv[1])));
		return ;
	}
	if (_sender->getChannel()->getName() != _argv[1])
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_NOSUCHCHANNEL(_sender->getName(), _argv[0], _argv[1])));
		return ;
	}

	_sender->setChannel(nullptr);
	_sender->removeUserFromChannel();
}

void			Executor::who()
{
	printLog(_sender, WHO);

	if (_argv.size() < 2)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), _argv[0])));
		return ;
	}
	else if (_argv.size() > 2)
	{
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), _argv[0])));
		return ;
	}

    Channel *existChan = _server->getChannel(_argv[1]);
	if (existChan != nullptr)
	{
		existChan->printFullInfo();
		return ;
	}

	_sender->getReply(_server->getSign() + SPC + (ERR_NOSUCHCHANNEL(_sender->getName(), _argv[0], _argv[1])));
}

void			Executor::kick()
{
	printLog(_sender, KICK);

	Channel	*chan = _server->getChannel(_argv[0]);


	if (_argv.size() < 3)
		return sendErrorReply(ERR_NEEDMOREPARAMS(_sender->getName(), _argv[0]));
	else if (_argv.size() > 3)
		return sendErrorReply(ERR_TOOMANYPARAMS(_sender->getName(), _argv[0]));
	else if (chan == nullptr)
		return sendErrorReply(ERR_NOSUCHCHANNEL(_sender->getName(), _argv[0], _argv[0]));
	// else if (chan->getAdmin() != _sender)
	// 	return sendErrorReply(ERR_NOSUCHCHANNEL(_sender->getName(), _argv[0], _argv[0]));
	// else if (!chan->isUser(_sender))
	// 	return sendErrorReply(ERR_NOSUCHCHANNEL(_sender->getName(), _argv[0], _argv[0]));



}

void			Executor::sendErrorReply(std::string info)
{
	std::string	msgReply = _server->getSign() + SPC + info + ENDL;
	send(_sender->getSockFd(), msgReply.c_str(), msgReply.length(), SEND_OPT);
}

// * **************** Clear function **************** * //

void			Executor::clearArgv()
{
	_sender = nullptr;
	_msg.clear();
	_argv.clear();
}
