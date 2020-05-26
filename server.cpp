#include "common_app_error.h"
#include "server_file_reader.h"
#include "server_manager.h"
#include "server_round_list.h"
#include "server_score.h"
#include "server_threads_manager.h"
#include <iostream>
#include <exception>
#include <string>
#include <thread>

#define ERROR 1
#define SUCCESS 0
#define END_KEY "q"

int main(int argc, char const *argv[]) {
    try {
        if (argc != 3) {
            throw AppError("Error: argumentos invalidos");
        }
        FileReader numberFile(argv[2]); //creo lector de file
        RoundList roundList(numberFile); //creo lista de numeros
        ServerScore score; //creo el score final

        ServerManager serverManager(argv[1]); //levanto servidor

        //pongo hilos a correr
        ThreadsManager threadsManager(serverManager, score, roundList);
        threadsManager.start();

        //espero a que me manden una 'q'
        std::string line;
        while (!std::cin.eof()) {
            getline(std::cin, line);
            if (line == END_KEY) break;
        }

        //cierro hilos
        threadsManager.close();
        threadsManager.join();

        std::cout << score.getResult();

        return SUCCESS;
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        return ERROR;
    } catch(...) {
        std::cout << "Error: Unknown" << '\n';
        return ERROR;
    }
}
