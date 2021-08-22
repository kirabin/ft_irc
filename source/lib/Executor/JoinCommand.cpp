#include "JoinCommand.hpp"

JoinCommand::JoinCommand(string name) : Command(name) {}
JoinCommand::~JoinCommand() {}
void JoinCommand::execute(Server* server, User* sender, deque<string> args) {
	Command::execute(server, sender, args);

	if (args.size() < 1) {
		sender->getReply(server->getSign() + SPC + (ERR_NEEDMOREPARAMS(sender->getName(), "/join")));
	} else if (args.size() > 1) {
		sender->getReply(server->getSign() + SPC + (ERR_TOOMANYPARAMS(sender->getName(), "/join")));
	} else if (sender->getChannel() != nullptr) {
		sender->getReply(server->getSign() + SPC + (ERR_TOOMANYCHANNELS(sender->getName(), "/join", args[0])));
	} else if (args[0].size() < 2 || args[0][0] != '#') {
		sender->getReply(server->getSign() + SPC + (ERR_BADCHANMASK(sender->getName(), "/join", args[0])));
	} else {
		Channel *existChan = server->getChannel(args[0]);
		if (existChan != nullptr) {
			sender->setChannel(existChan);
			existChan->addUser(sender);
		} else {
			Channel	*newChannel = server->addChannel(args[0], sender);
			sender->setChannel(newChannel);
			sender->getChannel()->sendServiceMessageToChannel(sender->getName() + " join to channel " + newChannel->getName());
		}

	}
}
