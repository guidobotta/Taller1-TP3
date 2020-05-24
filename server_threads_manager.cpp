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
    while (!this->ended) {
        SocketTCP peer = std::move(this->serverManager.connect());
        this->serverClients.push_back(std::thread { ServerClient(peer, this->roundList.getNext(), this->score) });
        /*
        for hilo in listadehilos
            chequear y joinear
        */
    }
}

void ThreadsManager::close() {
    this->ended = true;
    this->serverManager.closeSocket();
}
