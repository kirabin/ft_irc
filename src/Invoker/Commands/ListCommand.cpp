#include "ListCommand.hpp"

// TODO: numeric replies

ListCommand::ListCommand() {
	_name = "LIST";
	_description = "LIST - show channels on the server";
}

ListCommand::~ListCommand() {}

void ListCommand::execute() {
	if (!_sender->isAuthorized())
		throw "You're not authorized, use PASS";

	vector<Channel*> channels = _server->getChannels();
	vector<Channel*>::iterator it;

	_sender->getReply("Channels: " + std::to_string(channels.size()));

	for (it = channels.begin(); it != channels.end(); it++) {
		_sender->getReply((*it)->getName());
	}
	_sender->getReply("");
}
