#ifndef JoinCommand_hpp
# define JoinCommand_hpp
# include "Command.hpp"
# include <deque>

using namespace std;

class JoinCommand: public Command {
	public:
		JoinCommand(string name);
		virtual ~JoinCommand();
		void execute(Server* server, User* user, deque<string> args);
};

#endif
