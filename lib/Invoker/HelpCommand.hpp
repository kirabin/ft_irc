#ifndef HelpCommand_hpp
# define HelpCommand_hpp
# include "Command.hpp"

using namespace std;

class HelpCommand: public Command {

	public:
		HelpCommand(string name);
		virtual ~HelpCommand();
		void execute();
};

#endif
