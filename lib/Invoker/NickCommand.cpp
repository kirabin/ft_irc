#include "NickCommand.hpp"

NickCommand::NickCommand() {
	_name = "/nick";
	_description = "/nick <nick> - сhange your nickname";
}

NickCommand::~NickCommand() {}

void NickCommand::execute() {

	if (!_sender->isAuthorized())
		throw "You're not authorized, use /pass";
	if (_args.size() != 1)
		throw "Arguments count error";

	string newName = _args[0];
	string oldName = _sender->getName();

	// TODO
	// if (!isExistingName(newName))
		// throw "This name already in use";

	_sender->setName(newName);
	_sender->getReply("Your nick is @" + newName);
	if (_sender->getChannel()) {
		_sender->sendMessageToChannel("@" + oldName + "set his nick to " + "@" + newName);
	}
	_sender->getReply("");
}
