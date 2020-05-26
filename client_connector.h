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
        SocketTCP clSocket;

    public:
        explicit ClientConnector(const char *aHostname, 
                                const char *aServicename);
        ~ClientConnector();
        void sendMsg(char* msg, size_t n);
        void rcvMsg(char* msg, size_t n);
};

#endif
