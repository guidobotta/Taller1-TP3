#include "server_score.h"

ServerScore::ServerScore() : winners(0), loosers(0) {}

ServerScore::~ServerScore() {}

void ServerScore::addWinner() {
    this->winners++;
}

void ServerScore::addLooser() {
    this->loosers++;
}

std::string ServerScore::getResult() {
    std::string s = "Estadísticas:\n\tGanadores:  " + this->winners;
    s += "\n\tPerdedores: " + this->loosers + '\n';

    return std::move(s);
}
