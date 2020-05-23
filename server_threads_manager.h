#ifndef __THREADS_MANAGER_H__
#define __THREADS_MANAGER_H__

#include "server_manager.h"
#include "server_client.h"
#include "server_round_list.h"
#include "server_score.h"
#include <vector>
#include <thread>

class ThreadsManager {
    private:
        ServerManager &serverManager;
        RoundList &roundList;
        ServerScore &score;
        bool ended;
        std::vector <std::thread> serverClients;

    public:
        ThreadsManager(ServerManager &aServerManager, RoundList &aRoundList,
                        ServerScore &aScore);
        ThreadsManager(const ThreadsManager &other) = delete;
        ~ThreadsManager();
        static void run(ThreadsManager a);
        void close();
};

#endif
