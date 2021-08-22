#include "HelpCommand.hpp"

HelpCommand::HelpCommand(string name) : Command(name) {}

HelpCommand::~HelpCommand() {}

void HelpCommand::execute(Server* server, User* sender, deque<string> args) {
	Command::execute(server, sender, args);

	if (args.size() > 1) {
		sender->getReply(server->getSign() + SPC + (ERR_TOOMANYPARAMS(sender->getName(), args[0])));
	} else {
		std::string	discribe[CMD_SIZE] = {
			HELP_DIS, NICK_DIS, JOIN_DIS, LEAVE_DIS, WHO_DIS, KICK_DIS
		};

		// sender->getReply(server->getSign() + SPC + HELP);

		for (int i = 0; i < CMD_SIZE; i++) {
			sender->getReply(discribe[i]);
		}
	}

}
