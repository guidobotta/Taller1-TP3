#include "server_thread.h"

ServerThread::ServerThread () {}

void ServerThread::start() {
    thread = std::thread(&ServerThread::run, this);
}

void ServerThread::join() {
    thread.join();
}

ServerThread::~ServerThread() {} 

ServerThread::ServerThread(ServerThread&& other) {
    this->thread = std::move(other.thread);
}


ServerThread& ServerThread::operator=(ServerThread&& other) {
    this->thread = std::move(other.thread);
    return *this;
}
