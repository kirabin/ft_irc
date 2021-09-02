#include "NickCommand.hpp"


NickCommand::NickCommand() {
	_name = "NICK";
	_description = "NICK <nick> - сhange your nickname";
}

NickCommand::~NickCommand() {}

void NickCommand::execute() {

	if (_args.size() < 1)
		throw ERR_NEEDMOREPARAMS(_name);
	// TODO: check for allowed characters in nick

	string oldNick = _sender->getNick();
	string newNick = _args[0];

	if (_server->getUser(newNick))
		throw ERR_NICKNAMEINUSE(newNick);

	if (oldNick != "") {
		_sender->sendMessage(_sender, "NICK " + newNick.substr(0, 9));
	}
	_sender->setNick(newNick);
	_sender->doRegister();
}
