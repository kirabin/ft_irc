#ifndef WhoCommand_hpp
# define WhoCommand_hpp
# include "Command.hpp"

using namespace std;

class WhoCommand: public Command {
	public:
		WhoCommand(string name);
		virtual ~WhoCommand();
		void execute();
};

#endif
