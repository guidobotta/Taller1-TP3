#include "server_surrender_command.h"
#include <string>

SurrenderCommand::SurrenderCommand(ServerProtocol &sp, int &att) : Command(sp),
                                                                 attemps(att) {}

SurrenderCommand::~SurrenderCommand() {}

void SurrenderCommand::run() {
    this->attemps = 0;
    std::string msg = "Perdiste";

    sp.sendMsg(msg);
}
