#include "WhoCommand.hpp"


WhoCommand::WhoCommand(string name) : Command(name) {}
WhoCommand::~WhoCommand() {}
void WhoCommand::execute(Server* server, User* sender, deque<string> args) {
	Command::execute(server, sender, args);

	if (args.size() < 1) {
		sender->getReply(server->getSign() + SPC + (ERR_NEEDMOREPARAMS(sender->getName(), this->_name)));
	} else if (args.size() > 1) {
		sender->getReply(server->getSign() + SPC + (ERR_TOOMANYPARAMS(sender->getName(), this->_name)));
	} else {
		Channel *existChan = server->getChannel(args[0]);
		if (existChan != nullptr) {
			existChan->printFullInfo();
		} else {
			sender->getReply(server->getSign() + SPC + (ERR_NOSUCHCHANNEL(sender->getName(), this->_name, args[0])));
		}
	}
}
