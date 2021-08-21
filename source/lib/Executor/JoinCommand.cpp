#include "JoinCommand.hpp"

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
