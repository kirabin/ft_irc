#include "PassCommand.hpp"

PassCommand::PassCommand() {
	_name = "PASS";
	_description = "PASS <passwordtoserver> - authorise on channel";
}

PassCommand::~PassCommand() {}

void PassCommand::execute() {

	if (_sender->didEnter())
		throw ERR_ALREADYREGISTRED;
	if (_args.size() != 1)
		throw ERR_NEEDMOREPARAMS(_name);

	string password = _args[0];
	if (!_server->checkPassword(password))
		throw ERR_PASSWDMISMATCH;

	_server->sendMessage(_sender, "Correct password");
	_sender->setDidEnter(true);
	_sender->doRegister();
}
