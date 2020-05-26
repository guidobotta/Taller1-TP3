#ifndef __THREADS_MANAGER_H__
#define __THREADS_MANAGER_H__

#include "server_manager.h"
#include "server_client.h"
#include "server_round_list.h"
#include "server_score.h"
#include "server_thread.h"
#include <vector>
#include <thread>

class ThreadsManager : public ServerThread {
    private:
        ServerManager &serverManager;
        ServerScore &score;
        RoundList &roundList;
        bool ended;
        std::vector <ServerClient> serverClients;

    public:
        ThreadsManager(ServerManager &aServerManager, ServerScore &aScore,
                        RoundList &aRoundList);
        ThreadsManager(const ThreadsManager &other) = delete;
        ~ThreadsManager();
        virtual void run() override;
        void close();
};

#endif
