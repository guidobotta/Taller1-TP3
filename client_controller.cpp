#include "client_controller.h"

#define MAX_DIGITS_UINT16 5
#define MAX_NUMB_UINT16 65535

void ClientController::checkLine(std::string &line) {
    char err[] = "Error: comando invalido. Escriba AYUDA para obtener ayuda";

    if ((line == "AYUDA") || (line == "RENDIRSE")) {
        return;
    }

    for (int i = 0; i < line.size(); i++) {
        if (!std::isdigit(line[i])) {
            throw AppError(err);
        }
    }

    if ((line.size() > MAX_DIGITS_UINT16) || (line.size() == 0)) {
        throw AppError(err);
    }

    int n = std::stoi(line);
    
    if ((n < 0) || (n > MAX_NUMB_UINT16)) {
        throw AppError(err);
    }

}

ClientController::ClientController(int paramAmount, const char *aHostname, 
                                const char *aService) : hostname(aHostname), 
                                            service(aService), ended(false) {}

ClientController::~ClientController() {}

void ClientController::run() {
    try {
        std::string line;
        getline(std::cin, line);
        this->checkLine(line);
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

bool ClientController::end() {
    return this->ended;
}
