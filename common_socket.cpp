#include "common_socket.h"
#include "iostream"
#include <utility>

#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

SocketTCP::SocketTCP() {
    this->socketTCP = socket(AF_INET, SOCK_STREAM, 0); // IPv4, TCP, ANY
    if (this->socketTCP == INVALID_SOCKET) {
        throw AppError("Error: socket fallo en create");
    }
}

SocketTCP::SocketTCP(socket_t &aSocket) {
    this->socketTCP = aSocket;
}

SocketTCP::SocketTCP(SocketTCP&& other) {
    this->socketTCP = other.socketTCP;
    other.socketTCP = INVALID_SOCKET;
}

SocketTCP& SocketTCP::operator=(SocketTCP&& other) {
    if (this == &other) {
        return *this;
    }

    if ((this->socketTCP != other.socketTCP) &&
        (this->socketTCP != INVALID_SOCKET)) {
        close(this->socketTCP);
    }

    this->socketTCP = other.socketTCP;
    other.socketTCP = INVALID_SOCKET;

    return *this;
}

SocketTCP::~SocketTCP() {
    if (this->socketTCP != INVALID_SOCKET) {
        this->closeTCP();
    }
}

void SocketTCP::bindTCP(const struct sockaddr *address, 
                        socklen_t &address_len) {
    if (bind(this->socketTCP, address, address_len) == SOCKET_ERROR) {
        throw AppError("Error: socket fallo en bind");
    }
}

void SocketTCP::listenTCP(int backlog) {
    if (listen(this->socketTCP, backlog)) {
        throw AppError("Error: socket fallo en listen");
    }
}

SocketTCP SocketTCP::acceptTCP(struct sockaddr *address, 
                                socklen_t *address_len) {
    int s;
    if ((s = accept(this->socketTCP, address, address_len)) == SOCKET_ERROR) {
        throw AppError("Error: socket fallo en accept");
    }
    SocketTCP socketTCP(s);
    return std::move(socketTCP);
}

void SocketTCP::connectTCP(const struct sockaddr *address, 
                            socklen_t &address_len) {
    if (connect(this->socketTCP, address, address_len) == SOCKET_ERROR) {
        throw AppError("Error: socket fallo en connect");
    }
}

size_t SocketTCP::sendTCP(const char *buffer, size_t length, int flags) {
    size_t bytes_sent = 0;
    ssize_t status = 1;
    
    while ((bytes_sent < length) && (status != 0)){
        status = send(this->socketTCP, &(buffer[bytes_sent]), length, flags);
        
        if (status == SOCKET_ERROR){
            throw AppError("Error: socket fallo en send");
        }

        bytes_sent += status;
    }
    
    return bytes_sent;
}

size_t SocketTCP::receiveTCP(char *buffer, size_t length, int flags) {
    size_t bytes_recv = 0;
    ssize_t status = 1;

    while ((bytes_recv < length) && (status != 0)){
        status = recv(this->socketTCP, &(buffer[bytes_recv]), length, flags);
        
        if (status == SOCKET_ERROR){
            throw AppError("Error: socket fallo en recieve");
        }

        bytes_recv += status;
    }
    
    return bytes_recv;
}

void SocketTCP::shutdownTCP(int how) {
    if (shutdown(this->socketTCP, how) == SOCKET_ERROR) {
        throw AppError("Error: socket fallo en shutdown");
    }
}

void SocketTCP::closeTCP() {
    if (this->socketTCP != INVALID_SOCKET) {
        shutdown(this->socketTCP, SHUT_RDWR);
        close(this->socketTCP);
        this->socketTCP = -1;
    }
}
