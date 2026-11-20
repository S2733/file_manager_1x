#include "FileManager.h"

std::string FileManager::normalizeTxtName(const std::string& name) const
{
    if (name.size() >= 4 && name.substr(name.size() - 4) == ".txt")
        return name;

    return name + ".txt";
}

FileManager::FileManager()
{
	currentDir = fs::current_path();
}

bool FileManager::createFile(const std::string& fileName)
{
	std::string name = normalizeTxtName(fileName);
	std::ofstream file(currentDir / name);
	return file.good();
}

bool FileManager::createFolder(const std::string& folderName)
{
	fs::path folderPath = currentDir / folderName;
	return fs::create_directory(folderPath);
}

bool FileManager::deleteFolder(const std::string& folderName)
{
    fs::path folderPath = currentDir / folderName;

    if (fs::equivalent(folderPath, currentDir))
        return false;

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath))
        return false;

    try
    {
        fs::remove_all(folderPath);
        return true;
    }
    catch (const fs::filesystem_error&)
    {
        return false;
    }
}

bool FileManager::changeDirectory(const std::string& newPath)
{
    fs::path pathObj = newPath;

    if (!fs::exists(pathObj) || !fs::is_directory(pathObj))
        return false;

    currentDir = pathObj;
    return true;
}

bool FileManager::readFile(const std::string& fileName, std::string& outText)
{
    fs::path filePath = currentDir / normalizeTxtName(fileName);

    if (!fs::exists(filePath) || !fs::is_regular_file(filePath))
        return false;

    std::ifstream file(filePath);
    if (!file)
        return false;

    outText.clear();
    std::string line;

    while (std::getline(file, line))
        outText += line + "\n";

    return true;
}

bool FileManager::rewrite(const std::string& fileName, const std::string& text)
{
    fs::path filePath = currentDir / normalizeTxtName(fileName);

    if (!fs::exists(filePath) || !fs::is_regular_file(filePath))
        return false;

    std::ofstream file(filePath);
    if (!file)
        return false;

    file << text;
    return true;
}

bool FileManager::appendToFile(const std::string& fileName, const std::string& text)
{
    fs::path filePath = currentDir / normalizeTxtName(fileName);

    if (!fs::exists(filePath) || !fs::is_regular_file(filePath))
        return false;

    std::ofstream file(filePath, std::ios::app);
    if (!file)
        return false;

    file << text;
    return true;
}

bool FileManager::deleteFile(const std::string& name)
{
    fs::path p = currentDir / normalizeTxtName(name);

    if (!fs::exists(p) || !fs::is_regular_file(p))
        return false;

    return fs::remove(p);
}

bool FileManager::copyFile(const std::string& from, const std::string& to)
{
    fs::path src = currentDir / normalizeTxtName(from);
    fs::path dst = currentDir / normalizeTxtName(to);

    if (!fs::exists(src))
        return false;

    fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
    return true;
}

bool FileManager::cutFile(const std::string& from, const std::string& to)
{
    fs::path src = currentDir / normalizeTxtName(from);
    fs::path dstDir = currentDir / to;

    if (!fs::exists(src))
        return false;

    if (!fs::exists(dstDir) || !fs::is_directory(dstDir))
        return false;

    fs::path dst = dstDir / src.filename();

    fs::rename(src, dst);
    return true;
}

bool FileManager::goUp()
{
    if (!currentDir.has_parent_path())
        return false;

    currentDir = currentDir.parent_path();
    return true;
}

std::vector<fs::directory_entry> FileManager::listDirectory() const
{
    std::vector<fs::directory_entry> entries;

    for (const auto& entry : fs::directory_iterator(currentDir))
        entries.push_back(entry);

    return entries;
}

fs::path FileManager::getCur() const
{
    return currentDir;
}
