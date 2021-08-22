#include "ListCommand.hpp"


ListCommand::ListCommand(string name) : Command(name) {}

ListCommand::~ListCommand() {}

void ListCommand::execute() {
	vector<Channel*> channels = _server->getChannels();
	vector<Channel*>::iterator it;

	for (it = channels.begin(); it != channels.end(); it++) {
		_sender->getReply((*it)->getName());
	}
}
