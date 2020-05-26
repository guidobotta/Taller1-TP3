#ifndef __SERVER_SURRENDER_COMMAND_H__
#define __SERVER_SURRENDER_COMMAND_H__

#include "server_command.h"

class SurrenderCommand : public Command {
    private:

    public:
        SurrenderCommand(SocketTCP &aPeer);
        ~SurrenderCommand();
        virtual void operator()() override;
};

#endif
