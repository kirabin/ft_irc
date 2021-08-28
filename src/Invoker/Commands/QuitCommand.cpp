#include "QuitCommand.hpp"

QuitCommand::QuitCommand() {
	_name = "QUIT";
	_description = "QUIT [ <Quit Message> ] — quit server [and leave a message]";
}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute() {

	
}
