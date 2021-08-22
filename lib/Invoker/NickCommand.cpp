#include "NickCommand.hpp"

NickCommand::NickCommand(string name) : Command(name) {}

NickCommand::~NickCommand() {}

void NickCommand::execute() {

    if (_args.size() < 1) {
        _sender->getReply(_server->getSign() + SPC + (ERR_NEEDMOREPARAMS(_sender->getName(), _args[0])));
    } else if (_args.size() > 1) {
        _sender->getReply(_server->getSign() + SPC + (ERR_TOOMANYPARAMS(_sender->getName(), _args[0])));
    } else {
        std::string newName = _args[0];
        std::string oldName = _sender->getName();

        _sender->setName(newName);
        // _sender->sendMessageToChannel(_msg);
		if (_sender->getChannel()) {
			_sender->getChannel()->sendServiceMessageToChannel(oldName + " change name to " + newName);
		}
    }
}
