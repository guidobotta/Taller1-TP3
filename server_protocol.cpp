#include "server_protocol.h"
#include <arpa/inet.h>
#include <utility>

ServerProtocol::ServerProtocol(SocketTCP &&aPeer) : peer(std::move(aPeer)) {}

ServerProtocol::~ServerProtocol() {}

ServerProtocol::ServerProtocol(ServerProtocol&& other) {
    this->peer = std::move(other.peer);
}

ServerProtocol& ServerProtocol::operator=(ServerProtocol&& other) {
    if (this == &other) {
        return *this;
    }

    this->peer = std::move(other.peer);
    return *this;
}


void ServerProtocol::sendMsg(std::string &msg) {
    uint32_t len = (uint32_t) msg.size();
    len = htonl(len);
    this->peer.sendTCP((char *) &len, 4, 0);
    this->peer.sendTCP(msg.c_str(), msg.size(), 0);
}

char ServerProtocol::rcvCommand() {
    char op = 0;
    this->peer.receiveTCP(&op, 1, 0);
    return op;
}

uint16_t ServerProtocol::rcvNumber() {
    char charNum[2];
    this->peer.receiveTCP(charNum, 2, 0);
    
    uint16_t userNum = (charNum[1] << 8) + charNum[0];
    userNum = ntohs(userNum);

    return userNum;
}
