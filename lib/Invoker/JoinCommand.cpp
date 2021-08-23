#include "JoinCommand.hpp"

JoinCommand::JoinCommand(string name) : Command(name) {}

JoinCommand::~JoinCommand() {}

void JoinCommand::execute() {

	if (_args.size() < 1) {
		_sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), "/join")));
	} else if (_args.size() > 1) {
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), "/join")));
	} else if (_sender->getChannel() != nullptr) {
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYCHANNELS(_sender->getName(), "/join", _args[0])));
	} else if (_args[0].size() < 2 || _args[0][0] != '#') {
		_sender->getReply(_server->getSign() + SPC + (ERR_BADCHANMASK(_sender->getName(), "/join", _args[0])));
	} else {
		Channel *existingChan = _server->getChannel(_args[0]);
		if (existingChan != nullptr) {
			_sender->setChannel(existingChan);
			existingChan->addUser(_sender);
			// existingChan->setOperator(_sender);
		} else {
			Channel	*newChannel = _server->addChannel(_args[0], _sender);
			_sender->setChannel(newChannel);
			_sender->getChannel()->sendServiceMessageToChannel(_sender->getName() + " join to channel " + newChannel->getName());
			newChannel->addUser(_sender);
		}
	}
	_sender->getReply("");
}
