#include "server_threads_manager.h"

ThreadsManager::ThreadsManager(ServerManager &aServerManager, 
                                RoundList &aRoundList, ServerScore &aScore) : 
                                serverManager(aServerManager), score(aScore),
                                roundList(aRoundList), ended(false) {}

ThreadsManager::~ThreadsManager() {
    /*
    for hilo in listadehilos
        joinear
    */
}

void ThreadsManager::run(ThreadsManager self) {
    while (!self.ended) {
        SocketTCP peer = std::move(self.serverManager.connect());
        self.serverClients.push_back(std::thread { ServerClient(peer, self.roundList.getNext()) });
        /*for hilo in listadehilos
            chequear y joinear*/
    }
}

void ThreadsManager::close() {
    this->ended = true;
    this->serverManager.closeSocket();
}
