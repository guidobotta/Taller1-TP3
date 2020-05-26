#include "server_help_command.h"
#include <string>
#include <arpa/inet.h>

HelpCommand::HelpCommand(SocketTCP &aPeer) : Command(aPeer) {}

HelpCommand::~HelpCommand() {}

void HelpCommand::operator()() {
    std::string msg = "Comandos válidos:\n\t"; 
    msg += "AYUDA: despliega la lista de comandos válidos\n\t";
    msg += "RENDIRSE: pierde el juego automáticamente\n\t";
    msg += "XXX: Número de 3 cifras a ser enviado al servidor para ";
    msg += "adivinar el número secreto";

    uint32_t len = (uint32_t) msg.size();
    len = htonl(len);
    this->peer.sendTCP((char *) &len, 4, 0);
    this->peer.sendTCP(msg.c_str(), msg.size(), 0);
}
