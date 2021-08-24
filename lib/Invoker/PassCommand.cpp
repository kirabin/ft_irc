#include "PassCommand.hpp"

PassCommand::PassCommand() {
	_name = "/pass";
	_description = "/pass <passwordtoserver> - authorise on channel";
}

PassCommand::~PassCommand() {}

void PassCommand::execute() {

	if (_args.size() != 1)
		throw "Arguments count error";

	string password = _args[0];

	if (!_server->checkPassword(password))
		throw "Invalid Password";

	_sender->setAuthorized(true);
	_sender->getReply("You're now authorized");
	_sender->getReply("");
}
