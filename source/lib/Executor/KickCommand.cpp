#include "KickCommand.hpp"

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
