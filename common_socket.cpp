#include "common_socket.h"
#include "iostream"

SocketTCP::SocketTCP() {
    std::cout << "Constructor normal." << std::endl;
    this->socketTCP = socket(AF_INET, SOCK_STREAM, 0); // IPv4, TCP, ANY
    if (this->socketTCP == -1) {
        throw AppError("Error: socket fallo en create");
    }
}

SocketTCP::SocketTCP(socket_t &aSocket) {
    std::cout << "Constructor custom." << std::endl;
    this->socketTCP = aSocket;
}

SocketTCP::SocketTCP(SocketTCP&& other) {
    std::cout << "Constructor por movimiento: " << this->socketTCP << "|" << other.socketTCP << std::endl;
    this->socketTCP = other.socketTCP;
    other.socketTCP = -1;
}

SocketTCP& SocketTCP::operator=(SocketTCP&& other) {
    std::cout << "Operador =: " << this->socketTCP << "|" << other.socketTCP << std::endl;
    if (this == &other) {
        return *this;
    }

    if ((this->socketTCP != other.socketTCP) && (this->socketTCP != -1)) {
        close(this->socketTCP);
    }

    this->socketTCP = other.socketTCP;
    other.socketTCP = -1;

    return *this;
}

SocketTCP::~SocketTCP() {
    std::cout << "Destructor: " << this->socketTCP << std::endl;
    if (this->socketTCP != -1) {
        close(this->socketTCP);
    }
}

void SocketTCP::bindTCP(const struct sockaddr *address, socklen_t &address_len) {
    std::cout << "Bind: " << this->socketTCP << std::endl;
    if (bind(this->socketTCP, address, address_len) == -1) {
        throw AppError("Error: socket fallo en bind");
    }
}

void SocketTCP::listenTCP(int backlog) {
    std::cout << "Listen: " << this->socketTCP << std::endl;
    if (listen(this->socketTCP, backlog)) {
        throw AppError("Error: socket fallo en listen");
    }
}

SocketTCP SocketTCP::acceptTCP(struct sockaddr *address, socklen_t *address_len) {
    std::cout << "Accept: " << this->socketTCP << std::endl;
    int s;
    if ((s = accept(this->socketTCP, address, address_len)) == -1) {
        throw AppError("Error: socket fallo en accept");
    }
    SocketTCP socketTCP(s);
    std::cout << "Socket del accept: " << s << std::endl;
    return std::move(socketTCP);
}

void SocketTCP::connectTCP(const struct sockaddr *address, socklen_t &address_len) {
    std::cout << "Connect: " << this->socketTCP << std::endl;
    if (connect(this->socketTCP, address, address_len) == -1) {
        throw AppError("Error: socket fallo en connect");
    }
}

size_t SocketTCP::sendTCP(const char *buffer, size_t length, int flags) {
    std::cout << "Send: " << this->socketTCP << std::endl;
    size_t bytes_sent = 0;
    ssize_t status = 1;
    
    while ((bytes_sent < length) && (status != 0)){
        status = send(this->socketTCP, &(buffer[bytes_sent]), length, flags);
        
        if (status == -1){
            throw AppError("Error: socket fallo en send");
        }

        bytes_sent += status;
    }
    
    return bytes_sent;
}

size_t SocketTCP::receiveTCP(char *buffer, size_t length, int flags) {
    //std::cout << "Receive: " << this->socketTCP << std::endl;
    size_t bytes_recv = 0;
    ssize_t status = 1;
    
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
    std::cout << "Shutdown: " << this->socketTCP << std::endl;
    if (shutdown(this->socketTCP, how) == -1) {
        throw AppError("Error: socket fallo en shutdown");
    }
}