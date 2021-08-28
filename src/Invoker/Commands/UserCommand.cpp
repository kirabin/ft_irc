#include "UserCommand.hpp"

// TODO: numeric replies
// ERR_NEEDMOREPARAMS
// ERR_ALREADYREGISTRED

// TODO: https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.3

UserCommand::UserCommand() {
	_name = "USER";
	_description = "USER <username> <hostname> <servername> <realname> - used at the beginning of connection to specify you on server";
}

UserCommand::~UserCommand() {}

void UserCommand::execute() {

	if (_args.size() < 4)
		throw ERR_NEEDMOREPARAMS(_name);

	// _sender.setUsername();
	// _sender.setRealname();
}
