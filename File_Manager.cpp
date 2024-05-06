#include "pch.h"

#include <iostream>
#include <cstring>
#include <windows.h>
#include "Base_Class.cpp"

using namespace std;

const string FILE_PATH = "D:\\OS Project\\";

class FileManager : virtual public cDirectory {
public:
    bool createFile(const char* fileName) override {
        string filePath = FILE_PATH + string(fileName);
        HANDLE fileHandle = CreateFile(filePath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (fileHandle == INVALID_HANDLE_VALUE) {
            cout << "Failed to create file: " << fileName << endl;
            return false;
        }

        CloseHandle(fileHandle);
        cout << "File created successfully: " << fileName << endl;
        return true;
    }

    bool readFile(const char* fileName, char* buffer, int bufferSize) override {
        string filePath = FILE_PATH + string(fileName);
        HANDLE fileHandle = CreateFile(filePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (fileHandle == INVALID_HANDLE_VALUE) {
            cout << "Failed to read file: " << fileName << endl;
            return false;
        }

        DWORD bytesRead;
        if (!ReadFile(fileHandle, buffer, static_cast<DWORD>(bufferSize), &bytesRead, NULL)) {
            cout << "Failed to read file: " << fileName << endl;
            CloseHandle(fileHandle);
            return false;
        }

        CloseHandle(fileHandle);
        cout << "Read " << bytesRead << " bytes from file: " << fileName << endl;
        return true;
    }

    bool editFile(const char* fileName, const char* newData, int newSize) override {
        string filePath = FILE_PATH + string(fileName);
        HANDLE fileHandle = CreateFile(filePath.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (fileHandle == INVALID_HANDLE_VALUE) {
            cout << "Failed to edit file: " << fileName << endl;
            return false;
        }

        DWORD bytesWritten;
        if (!WriteFile(fileHandle, newData, static_cast<DWORD>(newSize), &bytesWritten, NULL)) {
            cout << "Failed to edit file: " << fileName << endl;
            CloseHandle(fileHandle);
            return false;
        }

        CloseHandle(fileHandle);
        cout << "Edited " << bytesWritten << " bytes in file: " << fileName << endl;
        return true;
    }

    bool deleteFile(const char* fileName) override {
        string filePath = FILE_PATH + string(fileName);
        if (!DeleteFile(filePath.c_str())) {
            cout << "Failed to delete file: " << fileName << endl;
            return false;
        }

        cout << "File deleted successfully: " << fileName << endl;
        return true;
    }

    bool writeFile(const char* fileName, const char* data, int dataSize) override {
        string filePath = FILE_PATH + string(fileName);
        HANDLE fileHandle = CreateFile(filePath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (fileHandle == INVALID_HANDLE_VALUE) {
            cout << "Failed to write to file: " << fileName << endl;
            return false;
        }

        DWORD bytesWritten;
        if (!WriteFile(fileHandle, data, static_cast<DWORD>(dataSize), &bytesWritten, NULL)) {
            cout << "Failed to write to file: " << fileName << endl;
            CloseHandle(fileHandle);
            return false;
        }

        CloseHandle(fileHandle);
        cout << "Wrote " << bytesWritten << " bytes to file: " << fileName << endl;
        return true;
    }

    bool renameFile(const char* oldFileName, const char* newFileName) override {
        string oldFilePath = FILE_PATH + string(oldFileName);
        string newFilePath = FILE_PATH + string(newFileName);
        if (!MoveFile(oldFilePath.c_str(), newFilePath.c_str())) {
            cout << "Failed to rename file: " << oldFileName << " to " << newFileName << endl;
            return false;
        }

        cout << "Renamed file: " << oldFileName << " to " << newFileName << endl;
        return true;
    }

    bool findLocationOfFile(const char* fileName, string& filePath) override {
        WIN32_FIND_DATAA fileData;
        HANDLE hFind;

        string searchPattern = FILE_PATH + fileName;


        hFind = FindFirstFileA(searchPattern.c_str(), &fileData);
        if (hFind == INVALID_HANDLE_VALUE) {
            cout << "File not found: " << fileName << endl;
            return false;
        }

        filePath = fileData.cFileName;
        FindClose(hFind);

        cout << "File found: " << fileName << " at location: " << filePath << endl;
        return true;
    }

    bool findSpaceTakenByFile(const char* fileName, unsigned long long& fileSize) override {
        string filePath;
        if (!findLocationOfFile(fileName, filePath)) {
            return false;
        }

        string fullPath = FILE_PATH + filePath;
        HANDLE hFile = CreateFileA(fullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            cout << "Failed to get file size: " << fileName << endl;
            return false;
        }

        LARGE_INTEGER liFileSize;
        if (!GetFileSizeEx(hFile, &liFileSize)) {
            cout << "Failed to get file size: " << fileName << endl;
            CloseHandle(hFile);
            return false;
        }

        fileSize = liFileSize.QuadPart;
        CloseHandle(hFile);

        cout << "File size of " << fileName << ": " << fileSize << " bytes" << endl;
        return true;
    }
};