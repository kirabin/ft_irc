#include "NickCommand.hpp"

NickCommand::NickCommand(string name) : Command(name) {}

NickCommand::~NickCommand() {}

void NickCommand::execute() {

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
