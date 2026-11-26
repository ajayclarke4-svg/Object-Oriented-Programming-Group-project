#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdexcept>
#include <string>
#include <vector>

#include "Storable.h"

class FileException : public std::runtime_error {
public:
    FileException(const std::string& message) : std::runtime_error(message) {}
};

class FileManager {
private:
    std::string folder;

public:
    FileManager(const std::string& dataFolder = "Data");

    std::string getPath(const std::string& fileName) const;
    bool fileExists(const std::string& fileName) const;

    void saveRecords(const std::string& fileName, const std::vector<std::string>& records) const;
    std::vector<std::string> loadRecords(const std::string& fileName) const;

    static std::string joinFields(const std::vector<std::string>& fields);
    static std::vector<std::string> splitFields(const std::string& record);

    static std::string toText(int value);
    static std::string toText(double value);
    static int toInt(const std::string& text);
    static double toDouble(const std::string& text);
};

#endif
