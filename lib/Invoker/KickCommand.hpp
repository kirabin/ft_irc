#ifndef KickCommand_hpp
# define KickCommand_hpp
# include "Command.hpp"

using namespace std;

class KickCommand: public Command {
	public:
		KickCommand();
		virtual ~KickCommand();
		void execute();
};


#endif
