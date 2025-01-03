#include <Utils/DataManager.h>

// Helper Function: Check if file exists
Bool DataManager::FileExists(const String& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

// Helper Function: Get executable path
String DataManager::GetExecutablePath() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    String::size_type pos = String(buffer).find_last_of("\\/");
    return String(buffer).substr(0, pos);
}

// Helper Function: Get config path
String DataManager::GetConfigPath(const String& folderName, const String& filename) {
    return GetExecutablePath() + "\\" + folderName + "\\" + filename;
}

// Helper Function: Load color from JSON
ImVec4 DataManager::LoadColorFromJson(const json& colorJson, const ImVec4& defaultColor) {
    if (colorJson.is_array() && colorJson.size() == 4) {
        return ImVec4(colorJson[0], colorJson[1], colorJson[2], colorJson[3]);
    }
    return defaultColor;
}

// Helper Function: Load float from JSON
Float DataManager::LoadFloatFromJson(const json& jsonValue, float defaultValue) {
    return jsonValue.is_number() ? jsonValue.get<float>() : defaultValue;
}

// Scan directory for JSON files
VOID DataManager::ScanDirectoryForJsonFiles(const String& path) {
    jsonFiles.clear();
    if (!fs::exists(path)) {
        std::cerr << "Directory does not exist: " << path << std::endl;
        return;
    }
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file() && entry.path().extension() == ".json") {
                jsonFiles.push_back(entry.path().filename().string());
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error scanning directory: " << e.what() << std::endl;
    }
}