#include "KickCommand.hpp"

KickCommand::KickCommand(string name) : Command(name) {}

KickCommand::~KickCommand() {}

void KickCommand::execute(Server* server, User* sender, deque<string> args) {
	Command::execute(server, sender, args);

	// Channel	*chan = server->getChannel(args[1]);


	// if (args.size() < 2)
	// 	return sendErrorReply(ERR_NEEDMOREPARAMS(sender->getName(), args[0]));
	// else if (args.size() > 2)
	// 	return sendErrorReply(ERR_TOOMANYPARAMS(sender->getName(), args[0]));
	// else if (chan == nullptr)
	// 	return sendErrorReply(ERR_NOSUCHCHANNEL(sender->getName(), args[0], args[0]));
	// else if (chan->getAdmin() != sender)
	// 	return sendErrorReply(ERR_NOSUCHCHANNEL(sender->getName(), args[0], args[0]));
	// else if (!chan->isUser(sender))
	// 	return sendErrorReply(ERR_NOSUCHCHANNEL(sender->getName(), args[0], args[0]));

}
