#include "WhoCommand.hpp"


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
