#include "client_connector.h"
#include <utility>

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
            this->clSocket = std::move(aClSocket);
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

ClientConnector::~ClientConnector() {}

void ClientConnector::sendMsg(char* msg, size_t n) {
    this->clSocket.sendTCP(msg, n, 0);
}

void ClientConnector::rcvMsg(char* msg, size_t n) {
    this->clSocket.receiveTCP(msg, n, 0);
}
