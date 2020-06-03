#ifndef __SERVER_HELP_COMMAND_H__
#define __SERVER_HELP_COMMAND_H__

#include "server_command.h"

class HelpCommand : public Command {
    public:
        explicit HelpCommand(ServerProtocol &sp);
        virtual ~HelpCommand();
        virtual void run() override;
};

#endif
