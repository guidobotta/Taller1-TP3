#ifndef __SERVER_CLIENT_H__
#define __SERVER_CLIENT_H__

#include "common_socket.h"
#include "server_score.h"

class ServerClient {
    private:
        SocketTCP &peer;
        uint16_t number;
        ServerScore &score;
        bool ended;
        int attempts;
        void checkNumber(uint16_t n, uint16_t m, std::string &msg, bool *win);
        bool digitRepeated(uint16_t n);

    public:
        ServerClient(SocketTCP &aPeer, uint16_t aNumber, ServerScore &aScore);
        ~ServerClient();
        void operator()();
};

#endif
