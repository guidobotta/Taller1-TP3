#ifndef __SERVER_HELP_COMMAND_H__
#define __SERVER_HELP_COMMAND_H__

#include "server_command.h"

class HelpCommand : public Command {
    private:

    public:
        HelpCommand(SocketTCP &aPeer);
        ~HelpCommand();
        virtual void operator()() override;
};

#endif