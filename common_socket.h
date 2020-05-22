#ifndef __SOCKET_TCP_H__
#define __SOCKET_TCP_H__

#include <unistd.h>
#include <sys/socket.h>
#include "common_app_error.h"

typedef int socket_t;

class SocketTCP {
    private:
        socket_t socketTCP;
        SocketTCP(socket_t &socket);

    public:
        SocketTCP();
        SocketTCP(const SocketTCP &other) = delete;
        ~SocketTCP();
        void bindTCP(const struct sockaddr *address, socklen_t &address_len);
        void listenTCP(int backlog);
        SocketTCP acceptTCP(struct sockaddr *address, socklen_t *address_len);
        void connectTCP(const struct sockaddr *address, socklen_t &address_len);
        size_t sendTCP(const char *buffer, size_t &length, int flags);
        size_t receiveTCP(char *buffer, size_t &length, int flags);
        void shutdownTCP(int how);
};

#endif
