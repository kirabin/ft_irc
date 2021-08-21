#ifndef NickCommand_hpp
# define NickCommand_hpp

# include "Command.hpp"
# include <deque>

using namespace std;

class NickCommand: public Command {
    public:
        NickCommand(string name);
        virtual ~NickCommand();
        void execute(Server* server, User* user, deque<string> args);
};




#endif
