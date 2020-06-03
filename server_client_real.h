#ifndef __SERVER_CLIENT_REAL_H__
#define __SERVER_CLIENT_REAL_H__

#include "server_protocol.h"
#include "server_score.h"
#include "server_thread.h"
#include <string>

class _ServerClient : public ServerThread {
    private:
        ServerProtocol sp;
        uint16_t number;
        ServerScore &score;
        bool dead;
        int attempts;
        bool win;
        void checkNumber(uint16_t n, uint16_t m, std::string &msg, bool *win);
        bool digitRepeated(uint16_t n);

    public:
        _ServerClient(ServerProtocol aSp, uint16_t aNumber, 
                      ServerScore &aScore);
        ~_ServerClient();
        void run();
        bool isDead();
};

#endif
