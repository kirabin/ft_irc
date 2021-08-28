#ifndef NoticeCommand_hpp
# define NoticeCommand_hpp
# include "../Command.hpp"

using namespace std;

class NoticeCommand: public Command {
	public:
		NoticeCommand();
		virtual ~NoticeCommand();
		void execute();
};

#endif
