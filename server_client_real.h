#ifndef __SERVER_CLIENT_REAL_H__
#define __SERVER_CLIENT_REAL_H__

#include "common_socket.h"
#include "server_score.h"
#include "server_thread.h"

class _ServerClient : public ServerThread {
    private:
        SocketTCP peer;
        uint16_t number;
        ServerScore &score;
        bool dead;
        int attempts;
        void checkNumber(uint16_t n, uint16_t m, std::string &msg, bool *win);
        bool digitRepeated(uint16_t n);

    public:
        _ServerClient(SocketTCP &&aPeer, uint16_t aNumber, ServerScore &aScore);
        ~_ServerClient();
        void run();
        bool isDead();
};

#endif
