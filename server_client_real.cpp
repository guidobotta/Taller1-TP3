#include "server_client_real.h"
#include "server_help_command.h"
#include "server_surrender_command.h"
#include "server_number_command.h"
#include <arpa/inet.h>
#include <sstream>
#include <utility>
#include <string>

#define ATTEMPTS 10

_ServerClient::_ServerClient(SocketTCP &&aPeer, uint16_t aNumber, 
                            ServerScore &aScore) : peer(std::move(aPeer)), 
                                                    number(aNumber),
                                                    score(aScore),
                                                    dead(false),
                                                    attempts(ATTEMPTS) {}

_ServerClient::~_ServerClient() {}

void _ServerClient::run() {
    while (!this->dead) {
        char op[1] = {0};
        this->peer.receiveTCP(op, 1, 0);

        if (op[0] == 'h') {
            HelpCommand hc(this->peer);
            hc();
        } else if (op[0] == 's') {
            SurrenderCommand sc(this->peer);
            sc();
            this->dead = true;
            this->score.addLooser();
        } else if (op[0] == 'n') {
            bool win = false;
            NumberCommand nc(this->peer, win, this->attempts, this->number);
            nc();

            if (win) {
                this->dead = true;
                this->score.addWinner();
            } else if (!this->attempts) {
                this->score.addLooser();
                this->dead = true;
            }
        }
    }
    this->peer.shutdownTCP(SHUT_RDWR);
}

bool _ServerClient::isDead() {
    return this->dead;
}
