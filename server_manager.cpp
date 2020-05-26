#include "server_manager.h"
#include "common_app_error.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <iostream>

ServerManager::ServerManager(const char *aServicename) : 
                                                    servicename(aServicename),
                                                    closed(false) {
    int status;

    memset(&this->hints, 0, sizeof(struct addrinfo));
    this->hints.ai_family = AF_INET;       // IPv4
    this->hints.ai_socktype = SOCK_STREAM; // TCP
    this->hints.ai_flags = AI_PASSIVE;     // For bind

    status = getaddrinfo(0, this->servicename, &this->hints, &this->results);

    if (status != 0) {
        throw AppError("Error: fallo al levantar servidor en getaddrinfo");
    }

    // Recorro resultados de getaddrinfo
    for (this->addr_ptr = this->results; this->addr_ptr != NULL; 
        this->addr_ptr = this->addr_ptr->ai_next) {
        try {
            SocketTCP aBlSocket;
            aBlSocket.bindTCP(this->addr_ptr->ai_addr, this->addr_ptr->ai_addrlen);
            aBlSocket.listenTCP(LISTEN_SOCKETS);
            this->blSocket = std::move(aBlSocket);
            break;
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    
    if (this->addr_ptr == NULL){
        freeaddrinfo(this->results);
        throw AppError("Error: fallo al levantar servidor en bind");
    }
}

ServerManager::~ServerManager() {
    freeaddrinfo(results);

    if (!this->closed) {
        this->blSocket.shutdownTCP(SHUT_RDWR);
    }
}

SocketTCP ServerManager::accept() {
    return std::move(this->blSocket.acceptTCP(this->addr_ptr->ai_addr, &this->addr_ptr->ai_addrlen));
 }

void ServerManager::closeSocket() {
    this->blSocket.shutdownTCP(SHUT_RDWR);
    this->closed = true;
}
