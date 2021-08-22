#include "WhoCommand.hpp"

WhoCommand::WhoCommand(string name) : Command(name) {}

WhoCommand::~WhoCommand() {}

void WhoCommand::execute() {

	if (_args.size() < 1) {
		_sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), this->_name)));
	} else if (_args.size() > 1) {
		_sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), this->_name)));
	} else {
		Channel *existChan = _server->getChannel(_args[0]);
		if (existChan != nullptr) {
			existChan->printFullInfo();
		} else {
			_sender->getReply(_server->getSign() + SPC + (ERR_NOSUCHCHANNEL(_sender->getName(), this->_name, _args[0])));
		}
	}
}
