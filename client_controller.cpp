#include "client_controller.h"
#include <sstream>

#define MAX_DIGITS_UINT16 5
#define MAX_NUMB_UINT16 65535
#define UINT32_SIZE 4 
#define ERROR 1
#define SUCCESS 0

int ClientController::checkLine(std::string &line) {
    char err[] = "Error: comando invalido. Escriba AYUDA para obtener ayuda";

    if ((line == "AYUDA") || (line == "RENDIRSE")) {
        return SUCCESS;
    }

    for (int i = 0; i < line.size(); i++) {
        if (!std::isdigit(line[i])) {
            return ERROR;
        }
    }

    if ((line.size() > MAX_DIGITS_UINT16) || (line.size() == 0)) {
        return ERROR;
    }

    int n = std::stoi(line);
    
    if ((n < 0) || (n > MAX_NUMB_UINT16)) {
        return ERROR;
    }

    return SUCCESS;
}

void ClientController::sendLine(std::string &line) {
    if (line == "AYUDA") {
        char msg[1] = {'h'};
        this->connector.sendMsg(msg, 1);
    } else if (line == "RENDIRSE") {
        char msg[1] = {'s'};
        this->connector.sendMsg(msg, 1);
    } else {
        char msg[3];
        msg[0] = 'n';
        uint16_t num = htons((uint16_t)std::stoi(line));
        msg[1] = ((char *) &num)[0];
        msg[2] = ((char *) &num)[1];
        this->connector.sendMsg(msg, 3);
    }
}

void ClientController::receiveResult(char** result) {
    char tamBytes[UINT32_SIZE];
    this->connector.rcvMsg(tamBytes, UINT32_SIZE);
    
    std::stringstream strTam;
    strTam << tamBytes;
    
    uint32_t tam;
    strTam >> tam;
    tam = ntohs(tam);
    
    char *msg = (char*) malloc(tam * sizeof(char));
    this->connector.rcvMsg(msg, tam);

    (*result) = msg;
    /*CAMBIAR IMPLEMENTACION DAR ORIENTACION A OBJETOS ENCAPSULAR MALLOC*/
    /*AGREGAR UN IF MSG == "PERDISTE" O "GANASTE" -> ENDED=TRUE*/
}

ClientController::ClientController(ClientConnector &aConnector) : 
                                        connector(aConnector), ended(false) {}

ClientController::~ClientController() {}

void ClientController::run() {
    std::string line;
    getline(std::cin, line);
    
    if (this->checkLine(line) == ERROR) {
        char e[] = "Error: comando invalido. Escriba AYUDA para obtener ayuda";
        std::cout << e;
        return;
    }

    this->sendLine(line);
    
    char* result;
    this->receiveResult(&result);

    std::cout << result;
    free(result);
    /*CAMBIAR IMPLEMENTACION DAR ORIENTACION A OBJETOS ENCAPSULAR FREE*/
}

bool ClientController::end() {
    return this->ended;
}