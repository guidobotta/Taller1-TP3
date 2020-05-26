#ifndef __APP_ERROR_H__
#define __APP_ERROR_H__

#include <exception>
#define BUFF_LEN 256

class AppError : public std::exception {
    private:
        char msg_error[BUFF_LEN];

    public:
        explicit AppError(const char *msg) noexcept;
        virtual const char* what() const noexcept;
        virtual ~AppError() noexcept;
};

#endif
