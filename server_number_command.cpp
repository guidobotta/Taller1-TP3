#include "server_number_command.h"
#include <string>
#include <arpa/inet.h>

NumberCommand::NumberCommand(SocketTCP &aPeer, bool &aWin, int &att, int aNum) :
                                                            Command(aPeer),
                                                            win(aWin),
                                                            attempts(att),
                                                            realNumber(aNum) {}

NumberCommand::~NumberCommand() {}

bool NumberCommand::digitRepeated(uint16_t n) {
    std::string s = std::to_string(n);

    if ((s[0] == s[1]) || (s[0] == s[2]) || (s[1] == s[2])) {
        return true;
    }

    return false;
}

void NumberCommand::checkNumber(uint16_t n, std::string &msg) {
    if (n == this->realNumber) {
        msg += "Ganaste";
        win = true;
    } else {
        this->attempts --;
        if (!this->attempts) {
            msg += "Perdiste";
        } else if ((n < 100) || (n > 999) || (this->digitRepeated(n))) {
            msg += "Número inválido. Debe ser de 3 cifras no repetidas";
        } else {
            std::string att = std::to_string(n);
            std::string real = std::to_string(this->realNumber);
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
}

void NumberCommand::operator()() {
    char charNum[2];
    this->peer.receiveTCP(charNum, 2, 0);
    
    uint16_t userNum = (charNum[1] << 8) + charNum[0];
    userNum = ntohs(userNum);

    std::string msg = "";
    this->checkNumber(userNum, msg);

    uint32_t len = (uint32_t) msg.size();
    len = htonl(len);
    this->peer.sendTCP((char *) &len, 4, 0);
    this->peer.sendTCP(msg.c_str(), msg.size(), 0);
}
