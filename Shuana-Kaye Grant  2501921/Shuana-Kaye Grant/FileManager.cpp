#include "FileManager.h"

#include <fstream>
#include <sstream>

using namespace std;

FileManager::FileManager(const string& dataFolder) {
    folder = dataFolder;
}

string FileManager::getPath(const string& fileName) const {
    if (fileName.empty()) {
        throw FileException("File name cannot be empty");
    }
    if (folder.empty()) {
        return fileName;
    }
    return folder + "/" + fileName;
}

bool FileManager::fileExists(const string& fileName) const {
    ifstream file(getPath(fileName).c_str());
    return file.is_open();
}

void FileManager::saveRecords(const string& fileName, const vector<string>& records) const {
    string path = getPath(fileName);
    ofstream file(path.c_str());
    if (!file) {
        throw FileException("Could not open " + path + " for saving. Check that the folder exists.");
    }

    for (size_t i = 0; i < records.size(); i++) {
        if (records[i].find('\n') != string::npos) {
            throw FileException("A record in " + fileName + " contains a line break");
        }
        file << records[i] << "\n";
    }

    if (!file) {
        throw FileException("Error while writing to " + path);
    }
}

vector<string> FileManager::loadRecords(const string& fileName) const {
    vector<string> records;
    string path = getPath(fileName);
    ifstream file(path.c_str());
    if (!file) {
        return records;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        if (!line.empty()) {
            records.push_back(line);
        }
    }
    return records;
}

string FileManager::joinFields(const vector<string>& fields) {
    string record;
    for (size_t i = 0; i < fields.size(); i++) {
        if (fields[i].find('|') != string::npos) {
            throw FileException("The value '" + fields[i] + "' cannot contain the | character");
        }
        if (i > 0) {
            record += "|";
        }
        record += fields[i];
    }
    return record;
}

vector<string> FileManager::splitFields(const string& record) {
    vector<string> fields;
    string field;
    stringstream ss(record);
    while (getline(ss, field, '|')) {
        fields.push_back(field);
    }
    if (!record.empty() && record[record.size() - 1] == '|') {
        fields.push_back("");
    }
    return fields;
}

string FileManager::toText(int value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

string FileManager::toText(double value) {
    stringstream ss;
    ss.precision(10);
    ss << value;
    return ss.str();
}

int FileManager::toInt(const string& text) {
    stringstream ss(text);
    int value;
    char extra;
    if (!(ss >> value) || (ss >> extra)) {
        throw FileException("'" + text + "' is not a valid whole number");
    }
    return value;
}

double FileManager::toDouble(const string& text) {
    stringstream ss(text);
    double value;
    char extra;
    if (!(ss >> value) || (ss >> extra)) {
        throw FileException("'" + text + "' is not a valid number");
    }
    return value;
}
