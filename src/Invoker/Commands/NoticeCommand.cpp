#include "NoticeCommand.hpp"

NoticeCommand::NoticeCommand() {
	_name = "NOTICE";
	_description = "";
}

NoticeCommand::~NoticeCommand() {}

void NoticeCommand::execute() {
	if (!_sender->didRegister())
		throw ERR_RESTRICTED;

	// TODO: Notice command
}
