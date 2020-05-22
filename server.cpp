#include "server_file_reader.h"
#include "common_app_error.h"
#include "server_round_list.h"
#include <iostream>
#include <exception>
#include <string>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char const *argv[]) {
    try {
        if (argc != 3) {
            throw AppError("Error: argumentos invalidos");
        }
        FileReader numberFile(argv[2]);
        RoundList roundList(numberFile);

    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        return ERROR;
    } catch(...) {
        std::cout << "Error: Unknown" << '\n';
        return ERROR;
    }
    
    return SUCCESS;
}
