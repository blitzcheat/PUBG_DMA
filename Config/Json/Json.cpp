#include "json.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

bool CUtil_Config::FileExistsInDirectory(const std::string& directoryPath, const std::string& fileName)
{
    fs::directory_iterator endIterator;
    for (fs::directory_iterator iter(directoryPath); iter != endIterator; ++iter)
    {
        if (iter->path().filename() == fileName && !fs::is_directory(iter->status()))
        {
            return true;
        }
    }

    return false;
}

std::vector<const char*> CUtil_Config::GetFileNames()
{
    Filenames.clear();

    for (const auto& entry : fs::directory_iterator(U::Config.FolderPath))
    {
        if (entry.is_regular_file())
        {
            std::string filenameStr = entry.path().filename().string();
            const char* filenameChar = strdup(filenameStr.c_str());



            Filenames.push_back(filenameChar);
        }
    }
    return Filenames;
}
const wchar_t* CUtil_Config::CharToWchar(const char* FileName)
{
    size_t length = mbstowcs(nullptr, FileName, 0) + 1;

    // 分配内存存储转换后的字符串
    wchar_t* wcstr = new wchar_t[length];

    // 执行转换
    mbstowcs(wcstr, FileName, length);

    return wcstr;
}
const char* CUtil_Config::CreatConfigeFile(const std::string& FileName)
{
    std::string datapath = U::Config.FolderPath + "/" + FileName/* + ".json"*/;
    std::ofstream outputFile(datapath);
    if (outputFile.is_open()) {
        outputFile.close();
    }
    else {
       // std::cerr << "Create File Failed ：" << datapath << std::endl;
    }

    return std::string(FileName + ".json").c_str();
}

bool CUtil_Config::DirectoryExists(const std::string& path)
{

    return fs::exists(path) && fs::is_directory(path);

}

bool CUtil_Config::CreatFolder(const std::string& folderPath)
{
    //在创建文件夹前判断是否已经存在避免重复创建引发不必要错误
    if (!(fs::exists(folderPath) && fs::is_directory(folderPath)))
    {
        try {
            fs::create_directory(folderPath);
            return true;
        }
        catch (const std::exception& ex) {
            //std::cerr << "Failed to create folder: " << ex.what() << std::endl;
            return false;
        }
    }

    return true;
}

//bool generateJsonFile(const std::string& filePath, const json& data)
//{
//    try {
//        std::ofstream file(filePath);
//        if (file.is_open()) {
//            file << data.dump(4);
//            file.close();
//            return true;
//        }
//        else {
//            std::cerr << "Failed to open file for writing: " << filePath << std::endl;
//            return false;
//        }
//    }
//    catch (const std::exception& ex) {
//        std::cerr << "Failed to generate JSON file: " << ex.what() << std::endl;
//        return false;
//    }
//}