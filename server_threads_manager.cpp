#include "server_threads_manager.h"
#include <utility>

ThreadsManager::ThreadsManager(ServerManager &aServerManager, 
                                ServerScore &aScore, RoundList &aRoundList) : 
                                serverManager(aServerManager), score(aScore),
                                roundList(aRoundList), ended(false) {}

ThreadsManager::~ThreadsManager() {
    while (!this->serverClients.empty()) {
        this->serverClients.back().join();
        this->serverClients.pop_back();
    }
}

void ThreadsManager::run() {
    try {
        while (!this->ended) {
            this->serverClients.push_back(std::move(ServerClient(
                                    SocketTCP(this->serverManager.accept()), 
                                    this->roundList.getNext(), this->score)));
            this->serverClients.back().start();
            for (size_t i = 0; i < this->serverClients.size(); i++) {
                if (this->serverClients.back().isDead()) {
                    this->serverClients.back().join();
                    this->serverClients.pop_back();
                    i--;
                }
            }
        }
    } catch(const std::exception& e) {
        while (!this->serverClients.empty()) {
            this->serverClients.back().join();
            this->serverClients.pop_back();
        }
    }
}

void ThreadsManager::close() {
    this->ended = true;
    this->serverManager.closeSocket();
}
