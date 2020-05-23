#ifndef __SERVER_SCORE_H__
#define __SERVER_SCORE_H__

#include <string>

class ServerScore {
    private:
        int winners;
        int loosers;

    public:
        ServerScore();
        ~ServerScore();
        void addWinner();
        void addLooser();
        std::string getResult();
};

#endif
