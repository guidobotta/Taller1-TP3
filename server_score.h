#ifndef __SERVER_SCORE_H__
#define __SERVER_SCORE_H__

#include <string>
#include <mutex>

class ServerScore {
    private:
        int winners;
        int loosers;
        std::mutex mux;

    public:
        ServerScore();
        ~ServerScore();
        void addWinner();
        void addLooser();
        std::string getResult();
};

#endif
