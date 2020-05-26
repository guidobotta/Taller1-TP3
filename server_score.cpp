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
    std::string s = "Estadísticas:\n\tGanadores:  " +
                    std::to_string(this->winners) + 
                    "\n\tPerdedores: " +
                    std::to_string(this->loosers) + '\n';

    return std::move(s);
}
