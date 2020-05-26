#include "server_command.h"

Command::Command(SocketTCP &aPeer) : peer(aPeer) {}

Command::~Command() {}
