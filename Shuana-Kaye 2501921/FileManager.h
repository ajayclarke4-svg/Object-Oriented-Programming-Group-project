#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Exceptions.h"

class FileManager {
private:
    std::string folder;

public:
    explicit FileManager(const std::string& dataFolder = "Data");

    std::string getPath(const std::string& fileName) const;
    bool fileExists(const std::string& fileName) const;
    void saveRecords(const std::string& fileName, const std::vector<std::string>& records) const;
    std::vector<std::string> loadRecords(const std::string& fileName) const;

    // Static text conversion and formatting utilities
    static std::string joinFields(const std::vector<std::string>& fields);
    static std::vector<std::string> splitFields(const std::string& record);

    static std::string toText(int value);
    static std::string toText(double value);
    static int toInt(const std::string& text);
    static double toDouble(const std::string& text);
};

#endif // FILEMANAGER_H
