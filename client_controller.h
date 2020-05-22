#ifndef __CLIENT_CONTROLLER_H__
#define __CLIENT_CONTROLLER_H__

#include <string>
#include <iostream>
#include "common_app_error.h"

class ClientController
{
private:
    const char *hostname;
    const char *service;
    bool ended;
    static void checkLine(std::string &line);

public:
    ClientController(int paramAmount, const char *aHostname, 
                    const char *aService);
    ClientController(const ClientController &other) = delete;
    ~ClientController() noexcept;
    void run();
    bool end();
};

#endif
