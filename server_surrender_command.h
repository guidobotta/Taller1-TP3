#ifndef __SERVER_SURRENDER_COMMAND_H__
#define __SERVER_SURRENDER_COMMAND_H__

#include "server_command.h"

class SurrenderCommand : public Command {
    private:
        int &attemps;

    public:
        explicit SurrenderCommand(ServerProtocol &sp, int &att);
        virtual ~SurrenderCommand();
        virtual void run() override;
};

#endif
