#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class FileManager
{
private:
	fs::path currentDir;

    std::string normalizeTxtName(const std::string& name) const;
public:
    FileManager();

    bool createFile(const std::string& fileName);

    bool createFolder(const std::string& folderName);

    bool deleteFolder(const std::string& folderName);

    bool changeDirectory(const std::string& newPath);

    bool readFile(const std::string& fileName, std::string& outText);

    bool rewrite(const std::string& fileName, const std::string& text);

    bool appendToFile(const std::string& fileName, const std::string& text);

    bool deleteFile(const std::string& name);

    bool copyFile(const std::string& from, const std::string& to);

    bool cutFile(const std::string& from, const std::string& to);

    bool goUp();

    std::vector<fs::directory_entry> listDirectory() const;

    fs::path getCur() const;

};
