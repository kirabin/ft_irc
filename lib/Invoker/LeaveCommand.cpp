#include "LeaveCommand.hpp"

LeaveCommand::LeaveCommand(string name) : Command(name) {}

LeaveCommand::~LeaveCommand() {}

void LeaveCommand::execute() {

	if (_args.size() < 1) {
		_sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), this->_name)));
	} else if (_args.size() > 1) {
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), this->_name)));
	} else if (_sender->getChannel() == nullptr) {
		_sender->getReply(_server->getSign() + SPC + (ERR_NOTONCHANNEL(_sender->getName(), this->_name, _args[0])));
	} else if (_sender->getChannel()->getName() != _args[0]) {
		_sender->getReply(_server->getSign() + SPC + (ERR_NOSUCHCHANNEL(_sender->getName(), this->_name, _args[0])));
	} else {
		_sender->setChannel(nullptr);
		_sender->removeUserFromChannel();
	}
}
