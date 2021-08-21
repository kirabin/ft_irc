#include "LeaveCommand.hpp"


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
