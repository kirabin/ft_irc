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

	_sender->sendMessage(_sender, "NICK " + newNick.substr(0, 9));
	_sender->setNick(newNick);
	if (_sender->getChannel()) {
		_sender->sendMessage(_sender->getChannel(), "@" + oldNick+ "set his nick to " + "@" + newNick);
	}
	_sender->doRegister();
}
