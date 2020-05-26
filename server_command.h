#ifndef __SERVER_COMMAND_H__
#define __SERVER_COMMAND_H__

#include "common_socket.h"

class Command {
    protected:
        SocketTCP &peer;

    public:
        explicit Command(SocketTCP &aPeer);
        ~Command();
        virtual void operator()() = 0;
};

#endif
