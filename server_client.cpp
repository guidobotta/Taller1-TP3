#include "server_client.h"
#include <utility>

ServerClient::ServerClient(ServerProtocol sp, uint16_t aNumber, 
                            ServerScore &aScore) {
    this->sc = new _ServerClient(std::move(sp), aNumber, aScore);
}

void ServerClient::start() {
    this->sc->start();
}

ServerClient::~ServerClient() {
    if (this->sc) {
        delete(this->sc);
    }
}

ServerClient::ServerClient(ServerClient&& other) {
    this->sc = other.sc;
    other.sc = nullptr;
}

ServerClient& ServerClient::operator=(ServerClient&& other) {
    if (this == &other) {
        return *this;
    }

    if ((this->sc != other.sc) && (this->sc)) {
        delete(this->sc);
    }

    this->sc = other.sc;
    other.sc = nullptr;

    return *this;
}

void ServerClient::join() {
    this->sc->join();
}

bool ServerClient::isDead() {
    return this->sc->isDead();
}

bool ServerClient::operator==(const ServerClient &other) {
    return this->sc == other.sc;
}
