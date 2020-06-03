#include "server_command_maker.h"

CommandMaker::CommandMaker(char aChar, ServerProtocol &sp, bool &aWin, int &att,
                            int aNum) {
    switch (aChar) {
        case 'h':
            this->command = new HelpCommand(sp);
            break;

        case 's':
            this->command = new SurrenderCommand(sp, att);
            break;

        case 'n':
            this->command = new NumberCommand(sp, aWin, att, aNum);
            break;
        
        default:
            break;
    }
}

CommandMaker::~CommandMaker() {
    delete(this->command);
}

Command* CommandMaker::getCommand() {
    return this->command;
}
