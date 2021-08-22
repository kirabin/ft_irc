#include "LeaveCommand.hpp"


LeaveCommand::LeaveCommand(string name) : Command(name) {}
LeaveCommand::~LeaveCommand() {}
void LeaveCommand::execute(Server* server, User* sender, deque<string> args) {
	Command::execute(server, sender, args);

	if (args.size() < 1) {
		sender->getReply(server->getSign() + SPC + (ERR_NEEDMOREPARAMS(sender->getName(), this->_name)));
	} else if (args.size() > 1) {
		sender->getReply(server->getSign() + SPC + (ERR_TOOMANYPARAMS(sender->getName(), this->_name)));
	} else if (sender->getChannel() == nullptr) {
		sender->getReply(server->getSign() + SPC + (ERR_NOTONCHANNEL(sender->getName(), this->_name, args[0])));
	} else if (sender->getChannel()->getName() != args[0]) {
		sender->getReply(server->getSign() + SPC + (ERR_NOSUCHCHANNEL(sender->getName(), this->_name, args[0])));
	} else {
		sender->setChannel(nullptr);
		sender->removeUserFromChannel();
	}
}
