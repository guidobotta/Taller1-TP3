#ifndef __CLIENT_CONTROLLER_H__
#define __CLIENT_CONTROLLER_H__

#include <string>
#include <iostream>
#include "common_app_error.h"
#include "client_connector.h"

class ClientController {
    private:
        ClientConnector &connector;
        bool ended;
        int checkLine(std::string &line);
        void sendLine(std::string &line);
        void receiveResult(char** result);

    public:
        explicit ClientController(ClientConnector &aConnector);
        ClientController(const ClientController &other) = delete;
        ~ClientController() noexcept;
        void run();
        bool end();
};

#endif
