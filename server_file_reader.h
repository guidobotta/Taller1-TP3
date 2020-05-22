#ifndef __READING_FILE_H__
#define __READING_FILE_H__

#include <fstream>
#include <string>

class FileReader {
    private:
        std::ifstream file;

    public:
        explicit FileReader(const std::string &path);
        FileReader(const FileReader &other) = delete;
        ~FileReader();
        void getLine(std::string &str);
        void getCompleteFile(std::string &str);
        bool eof() const;
        bool isOpen() const;
};

#endif
