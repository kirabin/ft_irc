#include "LeaveCommand.hpp"

// TODO: numeric replies

LeaveCommand::LeaveCommand() {
	_name = "LEAVE";
	_description = "LEAVE - leave channel";
}

LeaveCommand::~LeaveCommand() {}

void LeaveCommand::execute() {

	if (!_sender->isAuthorized())
		throw "You're not authorized, use PASS";
	if (_args.size() != 0)
		throw "Arguments count error";
	if (_sender->getChannel() == nullptr)
		throw "You don't belong to any channel";

	_sender->removeUserFromChannel();
	_sender->setChannel(nullptr);
	_sender->getReply("");
}
