#include "PassCommand.hpp"

PassCommand::PassCommand() {
	_name = "PASS";
	_description = "PASS <passwordtoserver> - authorise on channel";
}

PassCommand::~PassCommand() {}

void PassCommand::execute() {

	if (_sender->isAuthorized())
		throw ERR_ALREADYREGISTRED;
	if (_args.size() != 1)
		throw ERR_NEEDMOREPARAMS(_name);

	string password = _args[0];
	if (!_server->checkPassword(password))
		throw ERR_PASSWDMISMATCH;

	_sender->setAuthorized(true);
	// TODO reply ?
	_sender->getReply("001 * :You're now authorized");
}

// TODO: segfault on lost connection from Lime chat
