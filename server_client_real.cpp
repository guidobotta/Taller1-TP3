#include "server_client_real.h"
#include <arpa/inet.h>
#include <sstream>

#define ATTEMPTS 10

_ServerClient::_ServerClient(SocketTCP &&aPeer, uint16_t aNumber, 
                            ServerScore &aScore) : peer(std::move(aPeer)), 
                                                    number(aNumber),
                                                    score(aScore),
                                                    dead(false),
                                                    attempts(ATTEMPTS) {}

_ServerClient::~_ServerClient() {}

bool _ServerClient::digitRepeated(uint16_t n) {
    std::string s = std::to_string(n);

    if ((s[0] == s[1]) || (s[0] == s[2]) || (s[1] == s[2])) {
        return true;
    }

    return false;
}

void _ServerClient::checkNumber(uint16_t n, uint16_t m, std::string &msg, bool *win) {
    if (n == m) {
        msg += "Ganaste";
        *win = true;
    } else if ((n < 100) || (n > 999) || (this->digitRepeated(n))) {
        msg += "Número inválido. Debe ser de 3 cifras no repetidas";
    } else {
        std::string att = std::to_string(n);
        std::string real = std::to_string(m);
        char good = 0;
        char reg = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (att[i] == real[j]) {
                    if (i == j) {
                        good++;
                    } else {
                        reg++;
                    }
                    break;
                }
            }
        }

        if ((!good) && (!reg)) {
            msg += "3 mal";
        } else {
            if (good) {
                msg += std::to_string(good);
                msg += " bien";
                if (reg) {
                    msg += ", ";
                }
            }
            if (reg) {
                msg += std::to_string(reg);
                msg += " regular";
            }
        }
    }
}

void _ServerClient::run() {
    while (!this->dead) {
        std::string msg = "";
        char op[1] = {0};
        this->peer.receiveTCP(op, 1, 0);

        if (op[0] == 'h') {
            msg += "Comandos válidos:\n\t";
            msg += "AYUDA: despliega la lista de comando válidos\n\t";
            msg += "RENDIRSE: pierde el juego automáticamente\n\t";
            msg += "XXX: Número de 3 cifras a ser enviado al servidor para"; 
            msg += "adivinar el número secreto.";
        } else if (op[0] == 's') {
            this->dead = true;
            this->score.addLooser();
            msg += "Perdiste";
        } else if (op[0] == 'n') {
            char charNum[2];
            this->peer.receiveTCP(charNum, 2, 0);
            
            uint16_t userNum = (charNum[1] << 8) + charNum[0];

            userNum = ntohs(userNum);

            bool win = false;
            this->checkNumber(userNum, this->number, msg, &win);

            if (win) {
                this->dead = true;
                this->score.addWinner();
            } else {
                this->attempts--;
                if (!this->attempts) {
                    msg = "Perdiste";
                    this->score.addLooser();
                    this->dead = true;
                }
            }
        } else { //cambiar
            continue;
        }
        uint32_t len = (uint32_t) msg.size();
        len = htonl(len);
        this->peer.sendTCP((char *) &len, 4, 0);
        this->peer.sendTCP(msg.c_str(), msg.size(), 0);
    }
    this->peer.shutdownTCP(SHUT_RDWR);
}

bool _ServerClient::isDead() {
    return this->dead;
}
