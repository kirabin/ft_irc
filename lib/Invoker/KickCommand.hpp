#ifndef KickCommand_hpp
# define KickCommand_hpp
# include "Command.hpp"

using namespace std;

class KickCommand: public Command {
	public:
		KickCommand(string name);
		virtual ~KickCommand();
		void execute();
};


#endif
