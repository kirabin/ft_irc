#ifndef JoinCommand_hpp
# define JoinCommand_hpp
# include "Command.hpp"

using namespace std;

class JoinCommand: public Command {
	public:
		JoinCommand(string name);
		virtual ~JoinCommand();
		void execute();
};

#endif
