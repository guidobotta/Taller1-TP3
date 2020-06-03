#include "server_help_command.h"
#include <string>

HelpCommand::HelpCommand(ServerProtocol &sp) : Command(sp) {}

HelpCommand::~HelpCommand() {}

void HelpCommand::run() {
    std::string msg = "Comandos válidos:\n\t"; 
    msg += "AYUDA: despliega la lista de comandos válidos\n\t";
    msg += "RENDIRSE: pierde el juego automáticamente\n\t";
    msg += "XXX: Número de 3 cifras a ser enviado al servidor para ";
    msg += "adivinar el número secreto";

    this->sp.sendMsg(msg);
}
