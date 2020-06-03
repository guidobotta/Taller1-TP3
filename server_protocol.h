#ifndef __SERVER_PROTOCOL_H__
#define __SERVER_PROTOCOL_H__

#include "common_socket.h"
#include <string>
#include <utility>

class ServerProtocol {
    private:
        SocketTCP peer;

    public:
        explicit ServerProtocol(SocketTCP &&aPeer);
        ~ServerProtocol();
        ServerProtocol(const ServerProtocol&) = delete;
        ServerProtocol& operator=(const ServerProtocol&) = delete;
        ServerProtocol(ServerProtocol&& other);
        ServerProtocol& operator=(ServerProtocol&& other);
        void sendMsg(std::string &msg);
        char rcvCommand();
        uint16_t rcvNumber();
};

#endif
