#ifndef __THREADS_MANAGER_H__
#define __THREADS_MANAGER_H__

#include "server_manager.h"

class ThreadsManager {
    private:
        ServerManager &serverManager;

    public:
        ThreadsManager(ServerManager &aServerManager);
        ~ThreadsManager();
        static void run(ThreadsManager a);
        void close();
};

ThreadsManager::ThreadsManager(ServerManager &aServerManager) : 
                                                serverManager(aServerManager) {
}

ThreadsManager::~ThreadsManager() {
}

void ThreadsManager::run(ThreadsManager self) {
    
}

void ThreadsManager::close() {}

#endif
