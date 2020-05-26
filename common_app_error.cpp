#include "common_app_error.h"
#include <errno.h>
#include <string.h>

AppError::AppError(const char *msg) noexcept {
    char* _errno = strerror(errno);
    
    int i = 0;

    for (; (i < 255) && (msg[i] != '\0'); i++) {
        msg_error[i] = msg[i];
    }

    if (i < 254) {
        msg_error[i] = '\n';
        i++;
    }

    for (int j = 0; (i < 255) && (_errno[j] != '\0'); i++, j++) {
        msg_error[i] = _errno[j];
    }

    msg_error[i] = '\0';
}

AppError::~AppError() noexcept {}

const char* AppError::what() const noexcept {
    return msg_error;
}
