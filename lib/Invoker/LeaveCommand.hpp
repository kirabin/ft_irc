#ifndef LeaveCommand_hpp
# define LeaveCommand_hpp
# include "Command.hpp"
# include <deque>

using namespace std;

class LeaveCommand: public Command {
	public:
		LeaveCommand(string name);
		virtual ~LeaveCommand();
		void execute(Server* server, User* user, deque<string> args);
};

#endif
