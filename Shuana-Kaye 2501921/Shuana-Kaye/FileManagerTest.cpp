#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "FileManager.h"

using namespace std;

class TestStadium : public Storable {
public:
    int id;
    string name;
    int capacity;
    double ticketPrice;

    TestStadium() {
        id = 0;
        name = "";
        capacity = 0;
        ticketPrice = 0.0;
    }

    TestStadium(int newId, string newName, int newCapacity, double newPrice) {
        id = newId;
        name = newName;
        capacity = newCapacity;
        ticketPrice = newPrice;
    }

    string toRecord() const {
        vector<string> fields;
        fields.push_back(FileManager::toText(id));
        fields.push_back(name);
        fields.push_back(FileManager::toText(capacity));
        fields.push_back(FileManager::toText(ticketPrice));
        return FileManager::joinFields(fields);
    }

    void fromRecord(const string& record) {
        vector<string> fields = FileManager::splitFields(record);
        if (fields.size() != 4) {
            throw FileException("Stadium record should have 4 fields: " + record);
        }
        id = FileManager::toInt(fields[0]);
        name = fields[1];
        capacity = FileManager::toInt(fields[2]);
        ticketPrice = FileManager::toDouble(fields[3]);
    }
};

void saveStadiums(FileManager& fm, const vector<TestStadium>& stadiums) {
    vector<string> records;
    for (size_t i = 0; i < stadiums.size(); i++) {
        records.push_back(stadiums[i].toRecord());
    }
    fm.saveRecords("stadiums.txt", records);
}

vector<TestStadium> loadStadiums(FileManager& fm) {
    vector<TestStadium> stadiums;
    vector<string> records = fm.loadRecords("stadiums.txt");
    for (size_t i = 0; i < records.size(); i++) {
        TestStadium s;
        s.fromRecord(records[i]);
        stadiums.push_back(s);
    }
    return stadiums;
}

int passed = 0;
int failed = 0;

void check(bool result, string testName) {
    if (result) {
        passed++;
        cout << "PASS: " << testName << endl;
    } else {
        failed++;
        cout << "FAIL: " << testName << endl;
    }
}

void writeFile(string path, string text) {
    ofstream file(path.c_str());
    file << text;
}

int main() {
    FileManager fm(".");

    cout << "--- Normal ---" << endl;
    vector<TestStadium> stadiums;
    stadiums.push_back(TestStadium(1, "Sabina Park", 15000, 2500.0));
    stadiums.push_back(TestStadium(2, "National Stadium", 35000, 3000.5));
    saveStadiums(fm, stadiums);
    vector<TestStadium> loaded = loadStadiums(fm);
    check(loaded.size() == 2, "save and load 2 stadiums");
    check(loaded.size() == 2 && loaded[1].name == "National Stadium" && loaded[1].capacity == 35000
          && loaded[1].ticketPrice == 3000.5, "loaded values match saved values");
    check(fm.fileExists("stadiums.txt"), "file exists after saving");

    cout << "--- Boundary ---" << endl;
    saveStadiums(fm, vector<TestStadium>());
    check(loadStadiums(fm).empty(), "empty list saves and loads as empty");
    check(fm.loadRecords("missing_file.txt").empty(), "missing file loads as empty list");

    vector<TestStadium> edge;
    edge.push_back(TestStadium(3, "", 0, 0.0));
    edge.push_back(TestStadium(4, "Big Park", 2147483647, 0.01));
    saveStadiums(fm, edge);
    loaded = loadStadiums(fm);
    check(loaded.size() == 2 && loaded[0].name == "" && loaded[0].capacity == 0, "empty name and zero capacity");
    check(loaded.size() == 2 && loaded[1].capacity == 2147483647 && loaded[1].ticketPrice == 0.01, "largest int and small price");

    vector<string> trailing = FileManager::splitFields("5|Park|");
    check(trailing.size() == 3 && trailing[2] == "", "empty last field is kept");

    writeFile("stadiums.txt", "5|Windows Park|500|1000\r\n\r\n");
    loaded = loadStadiums(fm);
    check(loaded.size() == 1 && loaded[0].name == "Windows Park", "Windows line endings and blank lines");

    cout << "--- Invalid ---" << endl;
    bool thrown = false;
    try {
        writeFile("stadiums.txt", "6|Bad Park|lots|1000\n");
        loadStadiums(fm);
    } catch (FileException& e) {
        thrown = true;
        cout << "  message: " << e.what() << endl;
    }
    check(thrown, "text in a number field throws FileException");

    thrown = false;
    try {
        writeFile("stadiums.txt", "7|Short Park\n");
        loadStadiums(fm);
    } catch (FileException& e) {
        thrown = true;
    }
    check(thrown, "missing fields throws FileException");

    thrown = false;
    try {
        FileManager::toInt("12abc");
    } catch (FileException& e) {
        thrown = true;
    }
    check(thrown, "number followed by letters throws FileException");

    thrown = false;
    try {
        vector<TestStadium> bad;
        bad.push_back(TestStadium(8, "Park | Annex", 100, 50));
        saveStadiums(fm, bad);
    } catch (FileException& e) {
        thrown = true;
    }
    check(thrown, "name containing | throws FileException");

    thrown = false;
    try {
        FileManager noFolder("Folder_That_Does_Not_Exist");
        noFolder.saveRecords("stadiums.txt", vector<string>());
    } catch (FileException& e) {
        thrown = true;
    }
    check(thrown, "saving to a missing folder throws FileException");

    thrown = false;
    try {
        fm.getPath("");
    } catch (FileException& e) {
        thrown = true;
    }
    check(thrown, "empty file name throws FileException");

    remove("stadiums.txt");
    cout << endl << passed << " passed, " << failed << " failed" << endl;
    return 0;
}
