#include "NickCommand.hpp"


NickCommand::NickCommand() {
	_name = "NICK";
	_description = "NICK <nick> - сhange your nickname";
}

NickCommand::~NickCommand() {}

void NickCommand::execute() {

	if (!_sender->isAuthorized())
		throw ERR_RESTRICTED;

	string oldNick = _sender->getNick();
	if (_args.size() == 0) {
		_sender->getReply("Your nick is @" + oldNick);
		_sender->getReply("");
		return ;
	}

	if (_args.size() != 1)
		throw ERR_NEEDMOREPARAMS(_name);

	string newNick = _args[0];

	if (_server->getUser(newNick))
		throw ERR_NICKNAMEINUSE(newNick);

	_sender->setName(newNick);
	_sender->getReply("Your nick changed to @" + newNick);
	if (_sender->getChannel()) {
		_sender->sendMessageToChannel("@" + oldNick+ "set his nick to " + "@" + newNick);
	}
	_sender->getReply("");
}
