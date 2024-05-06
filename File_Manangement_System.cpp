#include <iostream>
#include <cstring>
#include <windows.h>
#include "Base_Class.cpp"
#include "File_Manager.cpp"

using namespace std;

int main() {
    FileManager fileManager;
    cDirectory* objDirectory = &fileManager;

    while (true) {
        cout << "File Manager : " << endl;
        cout << "1. Create File" << endl;
        cout << "2. Write File" << endl;
        cout << "3. Read File" << endl;
        cout << "4. Edit File" << endl;
        cout << "5. Location of File" << endl;
        cout << "6. Space taken by File(File Size)" << endl;
        cout << "7. Rename File" << endl;
        cout << "8. Delete File" << endl;
        cout << "12. Exiting Program..." << endl << endl;

        int ichoice;
        cout << "Enter the File Operation you want Perform : ";
        cin >> ichoice;
        cout << "\n";

        switch (ichoice) {
        case 1:
        {
            try {
                if (objDirectory->createFile("test.txt")) {
                    cout << "File created successfully!" << endl;
                }
            }
            catch (const exception& ex) {
                cerr << "Error occurred: " << ex.what() << endl;
            }
            cout << "\n";
            break;
        }

        case 2:
        {
            const char* data = "Hello, world!";
            size_t dataSize = strlen(data);
            try {
                if (objDirectory->writeFile("test.txt", data, dataSize)) {
                    cout << "Data written to file successfully!" << endl;
                }
            }
            catch (const exception& ex) {
                cerr << "Error occurred: " << ex.what() << endl;
            }
            cout << "\n";
            break;
        }

        case 3:
        {
            char buffer[100];
            size_t bufferSize = sizeof(buffer);
            try {
                if (objDirectory->readFile("test.txt", buffer, bufferSize)) {
                    cout << "Data read from file: " << buffer << endl;
                }
            }
            catch (const exception& ex) {
                cerr << "Error occurred: " << ex.what() << endl;
            }
            cout << "\n";
            break;
        }

        case 4:
        {
            const char* newData = "Hello Parth Sharma!";
            size_t newSize = strlen(newData);
            try {
                if (objDirectory->editFile("test.txt", newData, newSize)) {
                    cout << "Data edited in file successfully!" << endl;
                }
            }
            catch (const exception& ex) {
                cerr << "Error occurred: " << ex.what() << endl;
            }
            cout << "\n";
            break;
        }

        case 5:
        {
            string filePath;
            try {
                if (objDirectory->findLocationOfFile("test.txt", filePath)) {
                    cout << "File found at location: " << filePath << endl;
                }
            }
            catch (const exception& ex) {
                cerr << "Error occurred: " << ex.what() << endl;
            }
            cout << "\n";
            break;
        }

        case 6:
        {
            unsigned long long fileSize;
            try {
                if (objDirectory->findSpaceTakenByFile("test.txt", fileSize)) {
                    cout << "File size: " << fileSize << " bytes" << endl;
                }
            }
            catch (const exception& ex) {
                cerr << "Error occurred: " << ex.what() << endl;
            }
            cout << "\n";
            break;
        }

        case 7:
        {
            try {
                if (objDirectory->renameFile("test.txt", "test_renamed.txt")) {
                    cout << "File renamed successfully!" << endl;
                }
            }
            catch (const exception& ex) {
                cerr << "Error occurred: " << ex.what() << endl;
            }
            cout << "\n";
            break;
        }

        case 8:
        {
            try {
                if (objDirectory->deleteFile("test_renamed.txt")) {
                    cout << "File deleted successfully!" << endl;
                }
            }
            catch (const exception& ex) {
                cerr << "Error occurred: " << ex.what() << endl;
            }
            cout << "\n";
            break;
        }

        case 12:
        {
            cout << "Exiting program...\n";
            cout << "\n";
            return 0;
        }

        default:
        {
            cout << "Invalid input, please try again.\n\n";
            cout << "\n";
        }
        }
    }
}
