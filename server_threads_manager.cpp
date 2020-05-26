#include "server_threads_manager.h"

ThreadsManager::ThreadsManager(ServerManager &aServerManager, 
                                ServerScore &aScore, RoundList &aRoundList) : 
                                serverManager(aServerManager), score(aScore),
                                roundList(aRoundList), ended(false) {}

ThreadsManager::~ThreadsManager() {
    /*
    for hilo in listadehilos
        joinear
    */
}

void ThreadsManager::run() {
    try {
        SocketTCP peer;
        while (!this->ended) {
            peer = this->serverManager.accept();
            this->serverClients.push_back(std::move(ServerClient(peer, this->roundList.getNext(), this->score)));
            this->serverClients.back().start();
        }
    } catch(const std::exception& e) {
        /*
        for hilo in listadehilos
            chequear y joinear
        */
        /*std::cerr << e.what() << '\n';*/
    }
}

void ThreadsManager::close() {
    this->ended = true;
    this->serverManager.closeSocket();
}
