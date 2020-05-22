#include "client_controller.h"
#include "common_app_error.h"

#define ERROR 1
#define SUCCESS 0

int main(int argc, char const *argv[]) {
    try {
        if (argc != 3) {
            throw AppError("Error: argumentos invalidos");
        }
        ClientController clientController(argc, argv[1], argv[2]);

        while ((!std::cin.eof()) && (!clientController.end())) {
            clientController.run();
        }
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        return ERROR;
    } catch(...) {
        std::cout << "Error: Unknown" << '\n';
        return ERROR;
    }

    return SUCCESS;
}
