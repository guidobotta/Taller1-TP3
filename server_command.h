#ifndef __SERVER_COMMAND_H__
#define __SERVER_COMMAND_H__

#include "server_protocol.h"

class Command {
    protected:
        ServerProtocol &sp;

    public:
        explicit Command(ServerProtocol &asp);
        virtual ~Command();
        virtual void run() = 0;
};

#endif
