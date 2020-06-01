#include "server_score.h"
#include <utility>

ServerScore::ServerScore() : winners(0), loosers(0) {}

ServerScore::~ServerScore() {}

void ServerScore::addWinner() {
    std::unique_lock<std::mutex> lk(mux);
    this->winners++;
}

void ServerScore::addLooser() {
    std::unique_lock<std::mutex> lk(mux);
    this->loosers++;
}

std::string ServerScore::getResult() {
    std::string s = "Estadísticas:\n\tGanadores:  " +
                    std::to_string(this->winners) + 
                    "\n\tPerdedores: " +
                    std::to_string(this->loosers) + '\n';

    return std::move(s);
}
