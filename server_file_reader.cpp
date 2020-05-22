#include "server_file_reader.h"
#include "common_app_error.h"
#include <string>

FileReader::FileReader(const std::string &path) {
    this->file.open(path, std::ios::in);
    if (!this->file.is_open()) {
        throw AppError("Error: el archivo no pudo ser abierto.");
    }
}

FileReader::~FileReader() {
    this->file.close();
}

void FileReader::getLine(std::string &str) {
    str = "";

    if (this->file.is_open()) {
        getline(this->file, str);
    }
}

void FileReader::getCompleteFile(std::string &str) {
    std::string filestr;
    str = "";

    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, filestr);
            str.append(filestr);
        }
    }
}

bool FileReader::eof() const {
    return this->file.eof();
}

bool FileReader::isOpen() const {
    return this->file.is_open();
}
