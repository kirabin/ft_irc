#ifndef WhoCommand_hpp
# define WhoCommand_hpp
# include "Command.hpp"
# include <deque>

using namespace std;

class WhoCommand: public Command {
	public:
		WhoCommand(string name);
		virtual ~WhoCommand();
		void execute(Server* server, User* user, deque<string> args);
};

#endif
