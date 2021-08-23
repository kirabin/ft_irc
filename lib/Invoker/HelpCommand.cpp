#include "HelpCommand.hpp"

HelpCommand::HelpCommand(string name) : Command(name) {}

HelpCommand::~HelpCommand() {}

void HelpCommand::execute() {

	if (_args.size() > 1) {
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), _args[0])));
	} else {
		std::string	discribe[CMD_SIZE] = {
			HELP_DIS, NICK_DIS, JOIN_DIS, LEAVE_DIS, WHO_DIS, KICK_DIS
		};

		for (int i = 0; i < CMD_SIZE; i++) {
			_sender->getReply(discribe[i]);
		}
	}
	_sender->getReply("");
}
