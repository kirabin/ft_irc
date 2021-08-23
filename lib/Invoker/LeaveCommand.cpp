#include "LeaveCommand.hpp"

LeaveCommand::LeaveCommand(string name) : Command(name) {}

LeaveCommand::~LeaveCommand() {}

void LeaveCommand::execute() {

	if (_args.size() != 0)
		throw "Arguments count error";
	if (_sender->getChannel() == nullptr)
		throw "You don't belong to any channel";

	_sender->removeUserFromChannel();
	_sender->setChannel(nullptr);
	_sender->getReply("");
}
