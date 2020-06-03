#include "server_client_real.h"
#include "server_help_command.h"
#include "server_surrender_command.h"
#include "server_number_command.h"
#include <arpa/inet.h>
#include <sstream>
#include <utility>
#include <string>
#include <iostream>
#include <exception>

#define ATTEMPTS 10

_ServerClient::_ServerClient(ServerProtocol aSp, uint16_t aNumber, 
                            ServerScore &aScore) : sp(std::move(aSp)), 
                                                    number(aNumber),
                                                    score(aScore),
                                                    dead(false),
                                                    attempts(ATTEMPTS),
                                                    win(false) {}

_ServerClient::~_ServerClient() {}

#include "server_command_maker.h"

void _ServerClient::run() {
    try {
        while (!this->dead) {
            char op = this->sp.rcvCommand();

            CommandMaker cmMaker(op, this->sp, this->win, 
                                 this->attempts, this->number);
            Command *cm = cmMaker.getCommand();
            cm->run();

            if (win) {
                this->dead = true;
                this->score.addWinner();
            } else if (!this->attempts) {
                this->dead = true;
                this->score.addLooser();
            }
        }
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

bool _ServerClient::isDead() {
    return this->dead;
}
