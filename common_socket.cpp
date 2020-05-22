#include "common_socket.h"

SocketTCP::SocketTCP() {
    this->socketTCP = socket(AF_INET, SOCK_STREAM, 0); // IPv4, TCP, ANY
    if (this->socketTCP == -1) {
        throw AppError("Error: socket fallo en create");
    }
}

SocketTCP::SocketTCP(socket_t &aSocket) {
    this->socketTCP = aSocket;
}

SocketTCP::~SocketTCP() {
    if (close(this->socketTCP) == -1) {
        throw AppError("Error: socket fallo en close");
    }
}

void SocketTCP::bindTCP(const struct sockaddr *address, socklen_t &address_len) {
    if (bind(this->socketTCP, address, address_len) == -1) {
        throw AppError("Error: socket fallo en bind");
    }
}

void SocketTCP::listenTCP(int backlog) {
    if (listen(this->socketTCP, backlog)) {
        throw AppError("Error: socket fallo en listen");
    }
}

SocketTCP SocketTCP::acceptTCP(struct sockaddr *address, socklen_t *address_len) {
    if (accept(this->socketTCP, address, address_len) == -1) {
        throw AppError("Error: socket fallo en accept");
    }
}

void SocketTCP::connectTCP(const struct sockaddr *address, socklen_t &address_len) {
    if (connect(this->socketTCP, address, address_len) == -1) {
        throw AppError("Error: socket fallo en connect");
    }
}

size_t SocketTCP::sendTCP(const char *buffer, size_t &length, int flags) {
    size_t bytes_sent = 0;
    size_t status = 1;
    
    while ((bytes_sent < length) && (status != 0)){
        status = send(this->socketTCP, &(buffer[bytes_sent]), length, flags);
        
        if (status == -1){
            throw AppError("Error: socket fallo en send");
        }

        bytes_sent += status;
    }
    
    return bytes_sent;
}

size_t SocketTCP::receiveTCP(char *buffer, size_t &length, int flags) {
    size_t bytes_recv = 0;
    size_t status = 1;
    
    while ((bytes_recv < length) && (status != 0)){
        status = recv(this->socketTCP, &(buffer[bytes_recv]), length, flags);
        
        if (status == -1){
            throw AppError("Error: socket fallo en recieve");
        }

        bytes_recv += status;
    }
    
    return bytes_recv;
}

void SocketTCP::shutdownTCP(int how) {
    if (shutdown(this->socketTCP, how) == -1) {
        throw AppError("Error: socket fallo en shutdown");
    }
}