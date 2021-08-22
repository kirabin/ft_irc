#include "NickCommand.hpp"

NickCommand::NickCommand(string name) : Command(name) {}

NickCommand::~NickCommand() {}

void NickCommand::execute(Server* server, User* sender, deque<string> args) {
    Command::execute(server, sender, args);

    if (args.size() < 1) {
        sender->getReply(server->getSign() + SPC + (ERR_NEEDMOREPARAMS(sender->getName(), args[0])));
    } else if (args.size() > 1) {
        sender->getReply(server->getSign() + SPC + (ERR_TOOMANYPARAMS(sender->getName(), args[0])));
    } else if (server->getUser(args[0]) != nullptr) {
        sender->getReply(server->getSign() + SPC + (ERR_NICKNAMEINUSE(sender->getName(), args[0])));
    } else {
        std::string newName = args[0];
        std::string oldName = sender->getName();

        sender->setName(newName);
        // sender->sendMessageToChannel(_msg);
        sender->getChannel()->sendServiceMessageToChannel(oldName + " change name to " + newName);
    }
}
