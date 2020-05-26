#include "server_surrender_command.h"
#include <string>
#include <arpa/inet.h>

SurrenderCommand::SurrenderCommand(SocketTCP &aPeer) : Command(aPeer) {}

SurrenderCommand::~SurrenderCommand() {}

void SurrenderCommand::operator()() {
    std::string msg = "Perdiste";

    uint32_t len = (uint32_t) msg.size();
    len = htonl(len);
    this->peer.sendTCP((char *) &len, 4, 0);
    this->peer.sendTCP(msg.c_str(), msg.size(), 0);
}
