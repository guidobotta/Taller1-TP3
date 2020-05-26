#include "server_round_list.h"

void RoundList::checkString(std::string &line) {
    int n = std::stoi(line);
    
    if ((n < 100) || (n > 999)) {
        throw AppError("Error: archivo con números fuera de rango");
    }

    if ((line[0] == line[1]) || (line[0] == line[2]) || (line[1] == line[2])) {
        throw AppError("Error: formato de los números inválidos");
    }
}

RoundList::RoundList(FileReader &numFile) : index(0) {
    std::string line;
    
    while (!numFile.eof()) {
        numFile.getLine(line);
        this->checkString(line);
        this->list.emplace_back((uint16_t) std::stoi(line));
    }
}

uint16_t RoundList::getNext() {
    uint16_t n = list[index];
    index = (index + 1) % (this->list.size());

    return n;
}

RoundList::~RoundList() {}
