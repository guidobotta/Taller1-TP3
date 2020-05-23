#include "client_controller.h"
#include "client_connector.h"
#include "common_app_error.h"

#define ERROR 1
#define SUCCESS 0

/*
 * Se debe ejecutar como
 * $./client <hostname> <servicename>
*/
int main(int argc, char const *argv[]) {
    try {
        if (argc != 3) {
            throw AppError("Error: argumentos invalidos");
        }

        ClientConnector connector(argv[1], argv[2]);

        ClientController controller(connector);

        while ((!std::cin.eof()) && (!controller.end())) {
            controller.run();
        }

        return SUCCESS;
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        return ERROR;
    } catch(...) {
        std::cout << "Error: Unknown" << '\n';
        return ERROR;
    }
}
