#ifndef KickCommand_hpp
# define KickCommand_hpp
# include "Command.hpp"
# include <deque>

using namespace std;

class KickCommand: public Command {
	public:
		KickCommand(string name);
		virtual ~KickCommand();
		void execute(Server* server, User* user, deque<string> args);
};


#endif
