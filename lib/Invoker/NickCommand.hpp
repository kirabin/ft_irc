#ifndef NickCommand_hpp
# define NickCommand_hpp
# include "Command.hpp"

using namespace std;

class NickCommand: public Command {
	public:
		NickCommand();
		virtual ~NickCommand();
		void execute();
};

#endif
