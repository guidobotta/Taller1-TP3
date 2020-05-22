#include "common_app_error.h"

AppError::AppError(const char *msg) noexcept {
    for (int i = 0; (i < 255) && (msg[i] != '\0'); i++) {
        msg_error[i] = msg[i];
    }
}

AppError::~AppError() noexcept {}

const char* AppError::what() const noexcept {
    return msg_error;
}
