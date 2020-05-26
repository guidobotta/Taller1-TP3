#ifndef __SERVER_NUMBER_COMMAND_H__
#define __SERVER_NUMBER_COMMAND_H__

#include "server_command.h"
#include "stdint.h"
#include <string>

class NumberCommand : public Command {
    private:
        bool &win;
        int &attempts;
        int realNumber;
        void checkNumber(uint16_t n, std::string &msg);
        bool digitRepeated(uint16_t n);
        
    public:
        NumberCommand(SocketTCP &aPeer, bool &aWin, int &att, int aNum);
        ~NumberCommand();
        virtual void operator()() override;
};

#endif
