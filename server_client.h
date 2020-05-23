#ifndef __SERVER_CLIENT_H__
#define __SERVER_CLIENT_H__

#include "common_socket.h"

class ServerClient {
    private:
        SocketTCP &peer;
        uint16_t number;
        bool ended;

    public:
        ServerClient(SocketTCP &aPeer, uint16_t aNumber);
        ~ServerClient();
        void operator()();
};

ServerClient::ServerClient(SocketTCP &aPeer, uint16_t aNumber) : peer(aPeer),
                                                            number(aNumber),
                                                            ended(false) {}

ServerClient::~ServerClient() {
    this->peer.shutdownTCP(SHUT_RDWR);
}

void ServerClient::operator()() {
    //rcv
    char op[1] = {0};
    this->peer.receiveTCP(op, 1, 0);

    if (op[0] == 'h') {
        //AYUDA
    } else if (op[0] == 's') {
        //EL WEON SE RINDIO JAJA
    } else {
        char num[2];
        this->peer.receiveTCP(num, 2, 0);
        //logica
    }

    //send len
    //send word
}

#endif
