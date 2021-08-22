#ifndef HelpCommand_hpp
# define HelpCommand_hpp
# include "Command.hpp"
# include <deque>

using namespace std;

class HelpCommand: public Command {

	public:
		HelpCommand(string name);
		virtual ~HelpCommand();
		void execute(Server* server, User* user, deque<string> args);
};

#endif
