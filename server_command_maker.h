#ifndef __SERVER_COMMAND_MAKER_H__
#define __SERVER_COMMAND_MAKER_H__

#include "server_command.h"
#include "server_help_command.h"
#include "server_surrender_command.h"
#include "server_number_command.h"
#include "server_protocol.h"

class CommandMaker {
    private:
        Command *command;
        
    public:
        CommandMaker(char aChar, ServerProtocol &sp, bool &aWin, int &att, 
                    int aNum);
        ~CommandMaker();
        Command* getCommand();
};

#endif
