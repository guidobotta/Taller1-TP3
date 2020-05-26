#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__

#include "common_socket.h"
#include <netdb.h>

#define LISTEN_SOCKETS 10

/*
 * Clase ServerManager.
 * Levanta el servidor al ser creada.
 * Maneja la información valiosa del servidor.
*/
class ServerManager {
    private:
        const char *servicename;
        bool closed;
        struct addrinfo hints;
        struct addrinfo *results;
        struct addrinfo *addr_ptr;
        SocketTCP blSocket;

    public:
        explicit ServerManager(const char *aServicename);
        ~ServerManager();
        SocketTCP accept();
        void closeSocket();
};

#endif
