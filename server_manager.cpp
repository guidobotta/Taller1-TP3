#include "server_manager.h"
#include "common_app_error.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <iostream>

ServerManager::ServerManager(const char *aServicename) : 
                                                    servicename(aServicename) {
    int status;
    struct addrinfo *addr_ptr;

    memset(&this->hints, 0, sizeof(struct addrinfo));
    this->hints.ai_family = AF_INET;       // IPv4
    this->hints.ai_socktype = SOCK_STREAM; // TCP
    this->hints.ai_flags = AI_PASSIVE;     // For bind

    status = getaddrinfo(0, this->servicename, &this->hints, &this->results);

    if (status != 0) {
        throw AppError("Error: fallo al levantar servidor en getaddrinfo");
    }

    // Recorro resultados de getaddrinfo
    for (addr_ptr = this->results; addr_ptr != NULL; 
        addr_ptr = addr_ptr->ai_next) {
        try {
            SocketTCP aBlSocket;
            aBlSocket.bindTCP(addr_ptr->ai_addr, addr_ptr->ai_addrlen);
            aBlSocket.listenTCP(LISTEN_SOCKETS);
            this->blSocket = std::move(aBlSocket);
            break;
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    
    if (addr_ptr == NULL){
        freeaddrinfo(this->results);
        throw AppError("Error: fallo al levantar servidor en bind");
    }
}

ServerManager::~ServerManager() {
    freeaddrinfo(results);
    this->blSocket.shutdownTCP(SHUT_RDWR);
}
