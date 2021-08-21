#include "Command.hpp"

Command::Command(string name) : _name(name) {}
Command::~Command() {}

void Command::execute(Server* server, User* user, deque<string> args) {
	cout << "Executing " << _name << endl;
}

string Command::getName() {
	return _name;
}

HelpCommand::HelpCommand(string name) : Command(name) {}
HelpCommand::~HelpCommand() {}
void HelpCommand::execute(Server* server, User* user, deque<string> args) {
	Command::execute(server, user, args);
}



JoinCommand::JoinCommand(string name) : Command(name) {}
JoinCommand::~JoinCommand() {}
void JoinCommand::execute(Server* server, User* user, deque<string> args) {
	Command::execute(server, user, args);

	// if (args.size() < 1)
	// {
	// 	_sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), "/join")));
	// 	return ;
	// }
	// else if (args.size() > 1)
	// {
	// 	_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), "/join")));
	// 	return ;
	// }

	// if (_sender->getChannel() != nullptr)
	// {
	// 	_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYCHANNELS(_sender->getName(), "/join", args[0])));
	// 	return ;
	// }

	// if (args[0].size() < 2 || args[0][0] != '#')
	// {
	// 	_sender->getReply(_server->getSign() + SPC + (ERR_BADCHANMASK(_sender->getName(), "/join", args[0])));
	// 	return ;
	// }

	// Channel *existChan = _server->getChannel(args[0]);
	// if (existChan != nullptr)
	// {
	// 	_sender->setChannel(existChan);
	// 	existChan->addUser(_sender);
	// 	return ;
	// }

	// Channel	*newChannel = _server->addChannel(args[0], _sender);
	// _sender->setChannel(newChannel);
	// _sender->getChannel()->sendServiceMessageToChannel(_sender->getName() + " join to channel " + newChannel->getName());

}

LeaveCommand::LeaveCommand(string name) : Command(name) {}
LeaveCommand::~LeaveCommand() {}
void LeaveCommand::execute(Server* server, User* user, deque<string> args) {
	Command::execute(server, user, args);

	// 	if (_argv.size() < 2)
// 	{
// 		_sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), _argv[0])));
// 		return ;
// 	}
// 	else if (_argv.size() > 2)
// 	{
// 		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), _argv[0])));
// 		return ;
// 	}

// 	if (_sender->getChannel() == nullptr)
// 	{
// 		_sender->getReply(_server->getSign() + SPC + (ERR_NOTONCHANNEL(_sender->getName(), _argv[0], _argv[1])));
// 		return ;
// 	}
// 	if (_sender->getChannel()->getName() != _argv[1])
// 	{
// 		_sender->getReply(_server->getSign() + SPC + (ERR_NOSUCHCHANNEL(_sender->getName(), _argv[0], _argv[1])));
// 		return ;
// 	}

// 	_sender->setChannel(nullptr);
// 	_sender->removeUserFromChannel();
}


WhoCommand::WhoCommand(string name) : Command(name) {}
WhoCommand::~WhoCommand() {}
void WhoCommand::execute(Server* server, User* user, deque<string> args) {
	Command::execute(server, user, args);

	// 	if (_argv.size() < 2)
	// 	{
	// 		_sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), _argv[0])));
	// 		return ;
	// 	}
	// 	else if (_argv.size() > 2)
	// 	{
	// 		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), _argv[0])));
	// 		return ;
	// 	}

	//     Channel *existChan = _server->getChannel(_argv[1]);
	// 	if (existChan != nullptr)
	// 	{
	// 		existChan->printFullInfo();
	// 		return ;
	// 	}

	// 	_sender->getReply(_server->getSign() + SPC + (ERR_NOSUCHCHANNEL(_sender->getName(), _argv[0], _argv[1])));
	//
}


KickCommand::KickCommand(string name) : Command(name) {}
KickCommand::~KickCommand() {}
void KickCommand::execute(Server* server, User* user, deque<string> args) {
	Command::execute(server, user, args);

	// 	Channel	*chan = _server->getChannel(_argv[0]);


// 	if (_argv.size() < 3)
// 		return sendErrorReply(ERR_NEEDMOREPARAMS(_sender->getName(), _argv[0]));
// 	else if (_argv.size() > 3)
// 		return sendErrorReply(ERR_TOOMANYPARAMS(_sender->getName(), _argv[0]));
// 	else if (chan == nullptr)
// 		return sendErrorReply(ERR_NOSUCHCHANNEL(_sender->getName(), _argv[0], _argv[0]));
// 	// else if (chan->getAdmin() != _sender)
// 	// 	return sendErrorReply(ERR_NOSUCHCHANNEL(_sender->getName(), _argv[0], _argv[0]));
// 	// else if (!chan->isUser(_sender))
// 	// 	return sendErrorReply(ERR_NOSUCHCHANNEL(_sender->getName(), _argv[0], _argv[0]));

}

