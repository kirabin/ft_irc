#include "NameCommand.hpp"

// TODO: numeric replies
// ERR_NEEDMOREPARAMS
// ERR_ALREADYREGISTRED

NameCommand::NameCommand() {
	_name = "/name";
	_description = "/user <username> <hostname> <servername> <realname> - used at the beginning of connection to specify you on server";
}

NameCommand::~NameCommand() {}

void NameCommand::execute() {


}
