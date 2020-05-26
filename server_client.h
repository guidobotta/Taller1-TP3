#ifndef __SERVER_CLIENT_H__
#define __SERVER_CLIENT_H__

#include "server_client_real.h"

class ServerClient {
    private:
        _ServerClient* sc;

    public:
        ServerClient(SocketTCP &&aPeer, uint16_t aNumber, ServerScore &aScore);
        ~ServerClient();
        void start();
        ServerClient(ServerClient&& other);
        ServerClient& operator=(ServerClient&& other);
        bool operator==(const ServerClient &other);
        void join();
        bool isDead();
};

#endif
