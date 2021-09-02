#include "NoticeCommand.hpp"

NoticeCommand::NoticeCommand() {
	_name = "NOTICE";
	_description = "NOTICE username message — sends message to user";
}

NoticeCommand::~NoticeCommand() {}

void NoticeCommand::execute() {
	if (!_sender->didRegister())
		return;
	if (_args.size() < 2)
		return;

	User* user = _server->getUser(_args[0]);
	if (!user || user == _sender)
		return;

	string message;
	deque<string>::iterator word;

	for (word = _args.begin() + 1; word != _args.end(); word++) {
		message += " " + *word;
	}

	_sender->sendMessage(user,"NOTICE " + user->getNick() +  " :"+ message);
}
