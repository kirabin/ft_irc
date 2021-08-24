#include "UserCommand.hpp"

// TODO: numeric replies
// ERR_NEEDMOREPARAMS
// ERR_ALREADYREGISTRED

// TODO: https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.3

UserCommand::UserCommand() {
	_name = "/name";
	_description = "/user <username> <hostname> <servername> <realname> - used at the beginning of connection to specify you on server";
}

UserCommand::~UserCommand() {}

void UserCommand::execute() {

}
