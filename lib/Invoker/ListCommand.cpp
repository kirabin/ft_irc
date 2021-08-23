#include "ListCommand.hpp"

ListCommand::ListCommand() {
	_name = "/list";
	_description = "/list - show channels on the server";
}

ListCommand::~ListCommand() {}

void ListCommand::execute() {
	vector<Channel*> channels = _server->getChannels();
	vector<Channel*>::iterator it;

	_sender->getReply("Channels: " + std::to_string(channels.size()));

	for (it = channels.begin(); it != channels.end(); it++) {
		_sender->getReply((*it)->getName());
	}
	_sender->getReply("");
}
