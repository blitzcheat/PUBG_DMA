#include <iostream>
#include <fstream>
#include <filesystem>
#include "json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

class CUtil_Config 
{
public:
	bool CreatFolder(const std::string& folderPath);
	bool DirectoryExists(const std::string& path);
	bool FileExistsInDirectory(const std::string& directoryPath, const std::string& fileName);
	std::vector<const char*> GetFileNames();
	const char* CreatConfigeFile(const std::string& fileName);

	const wchar_t* CharToWchar(const char* FileName);

public:
	std::string FolderPath = "Config";
	std::vector<const char*> Filenames;
};

namespace U { inline CUtil_Config Config; }