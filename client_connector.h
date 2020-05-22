#ifndef __CLIENT_CONNECTOR_H__
#define __CLIENT_CONNECTOR_H__

#include "common_socket.h"
#include "common_app_error.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <iostream>

/*
 * Clase ClientConnector.
 * Conecta cliente al servidor al ser creada.
 * Maneja la información valiosa del cliente.
*/
class ClientConnector {
    private:
        const char *hostname;
        const char *servicename;
        SocketTCP &clSocket;

    public:
        ClientConnector(const char *aHostname, const char *aServicename);
        ~ClientConnector();
};

ClientConnector::ClientConnector(const char *aHostname, 
                                const char *aServicename) : hostname(aHostname),
                                                    servicename(aServicename) {
    int status;
    struct addrinfo hints;
    struct addrinfo *results;
    struct addrinfo *addr_ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP
    hints.ai_flags = 0;              // None

    status = getaddrinfo(this->hostname, this->servicename, &hints, &results);

    if (status != 0) {
        throw AppError("Error: fallo al conectar cliente en getaddrinfo");
    }

    // Recorro resultados de getaddrinfo
    for (addr_ptr = results; addr_ptr != NULL; addr_ptr = addr_ptr->ai_next) {
        try {
            SocketTCP aClSocket;
            aClSocket.connectTCP(addr_ptr->ai_addr, addr_ptr->ai_addrlen);
            this->clSocket = aClSocket;
            break;
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    
    if (addr_ptr == NULL){
        freeaddrinfo(results);
        throw AppError("Error: fallo al conectar cliente en connect");
    }

    freeaddrinfo(results);
}

ClientConnector::~ClientConnector() {
    //CERRAR SOCKET
}

#endif
