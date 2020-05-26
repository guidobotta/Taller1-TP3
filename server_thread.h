#ifndef __SERVER_THREAD_H__
#define __SERVER_THREAD_H__

#include <thread>

class ServerThread {
    private:
        std::thread thread;
 
    public:
        ServerThread();
        void start();
        void join();
        virtual void run() = 0; 
        virtual ~ServerThread();
        ServerThread(const ServerThread&) = delete;
        ServerThread& operator=(const ServerThread&) = delete;
        ServerThread(ServerThread&& other);
        ServerThread& operator=(ServerThread&& other);
};

#endif
