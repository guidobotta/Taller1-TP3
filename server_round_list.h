#ifndef __ROUND_LIST_H__
#define __ROUND_LIST_H__

#include <vector>
#include <string>
#include <stdint.h>
#include "common_app_error.h"
#include "server_file_reader.h"

class RoundList {
    private:
        std::vector<uint16_t> list;
        uint32_t index;
        static void checkString(std::string &line);
        
    public:
        RoundList(FileReader &numFile);
        RoundList(const RoundList &other) = delete;
        uint16_t getNext();
        ~RoundList();
};

#endif
