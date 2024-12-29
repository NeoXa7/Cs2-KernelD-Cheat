#pragma once
#include <fstream>
#include <Libs/Json.hpp>
#include <Cheats/Data.h>
#include <Globals/Globals.h>
#include <filesystem>
#include <Libs/ImGui/imgui.h>

using json = nlohmann::json;
std::string ConfigFileName = "config";
namespace fs = std::filesystem;
std::vector<std::string> jsonFiles;

inline bool FileExists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void ScanDirectoryForJsonFiles(const std::string& path)
{
    jsonFiles.clear();

    // Check if the directory exists
    if (!fs::exists(path))
    {
        std::cerr << "Directory does not exist: " << path << std::endl; // Debug log (optional)
        return; // Exit the function if the directory does not exist
    }

    try
    {
        for (const auto& entry : fs::directory_iterator(path))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".json")
            {
                jsonFiles.push_back(entry.path().filename().string());
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error scanning directory: " << e.what() << std::endl; // Debug log for exceptions
    }
}

std::string GetExecutablePath()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

std::string GetConfigPath(const std::string& filename)
{
    return GetExecutablePath() + "\\configs\\" + filename;
}

void SaveConfig(const std::string& filename, const std::string& folder = "configs")
{
    fs::path dirPath = folder;
    if (!fs::exists(dirPath)) {
        fs::create_directory(dirPath); // Create the folder
    }

    std::string fullPath = GetConfigPath(ConfigFileName);

    json jsonConfig;

    // Save Player Esp Data
    jsonConfig["Esp"]["Player"]["EnablePlayerEsp"] = Data::Esp::m_bPlayerEsp;
    jsonConfig["Esp"]["Player"]["EnableBox"] = Data::Esp::Player::m_bEnableBox;
    jsonConfig["Esp"]["Player"]["EnableLines"] = Data::Esp::Player::m_bEnableLines;
    jsonConfig["Esp"]["Player"]["EnableNames"] = Data::Esp::Player::m_bEnableNames;
    jsonConfig["Esp"]["Player"]["EnableDistance"] = Data::Esp::Player::m_bEnableDistance;
    jsonConfig["Esp"]["Player"]["EnableHealthBar"] = Data::Esp::Player::m_bEnableHealthBar;
    jsonConfig["Esp"]["Player"]["EnableHealthText"] = Data::Esp::Player::m_bEnableHealthText;
    jsonConfig["Esp"]["Player"]["EnableArmorBar"] = Data::Esp::Player::m_bEnableArmorBar;
    jsonConfig["Esp"]["Player"]["EnableBones"] = Data::Esp::Player::m_bEnableBones;
    jsonConfig["Esp"]["Player"]["EnableBonesJoints"] = Data::Esp::Player::m_bEnableBonesJoints;
    jsonConfig["Esp"]["Player"]["BoneHeadFilled"] = Data::Esp::Player::m_bBoneHeadFilled;
    jsonConfig["Esp"]["Player"]["BoxFilledColor"] = { Data::Esp::Player::m_clBoxFilledColor.x, Data::Esp::Player::m_clBoxFilledColor.y, Data::Esp::Player::m_clBoxFilledColor.z, Data::Esp::Player::m_clBoxFilledColor.w };
    jsonConfig["Esp"]["Player"]["BoxUnfilledColor"] = { Data::Esp::Player::m_clBoxUnfilledColor.x, Data::Esp::Player::m_clBoxUnfilledColor.y, Data::Esp::Player::m_clBoxUnfilledColor.z, Data::Esp::Player::m_clBoxUnfilledColor.w };
    jsonConfig["Esp"]["Player"]["LineColor"] = { Data::Esp::Player::m_clLineColor.x, Data::Esp::Player::m_clLineColor.y, Data::Esp::Player::m_clLineColor.z, Data::Esp::Player::m_clLineColor.w };
    jsonConfig["Esp"]["Player"]["NameColor"] = { Data::Esp::Player::m_clNameColor.x, Data::Esp::Player::m_clNameColor.y, Data::Esp::Player::m_clNameColor.z, Data::Esp::Player::m_clNameColor.w };
    jsonConfig["Esp"]["Player"]["ArmorBarColor"] = { Data::Esp::Player::m_clArmorBarColor.x, Data::Esp::Player::m_clArmorBarColor.y, Data::Esp::Player::m_clArmorBarColor.z, Data::Esp::Player::m_clArmorBarColor.w };
    jsonConfig["Esp"]["Player"]["DistanceTextColor"] = { Data::Esp::Player::m_clDistanceTextColor.x, Data::Esp::Player::m_clDistanceTextColor.y, Data::Esp::Player::m_clDistanceTextColor.z, Data::Esp::Player::m_clDistanceTextColor.w };
    jsonConfig["Esp"]["Player"]["BoxThickness"] = Data::Esp::Player::m_flBoxUnfilledThickness;
    jsonConfig["Esp"]["Player"]["LineThickness"] = Data::Esp::Player::m_flLinesThickness;
    jsonConfig["Esp"]["Player"]["BoneThickness"] = Data::Esp::Player::m_flBonesThickness;
    jsonConfig["Esp"]["Player"]["JointRadius"] = Data::Esp::Player::m_flJointRadius;
    jsonConfig["Esp"]["Player"]["CurrentLinePosIndex"] = Data::Esp::Player::m_iCurrentLinePosIndex;

    // Save Bomb Esp Data
    jsonConfig["Esp"]["Bomb"]["BombEsp"] = Data::Esp::m_bBombEsp;
    jsonConfig["Esp"]["Bomb"]["EnableBox"] = Data::Esp::Bomb::m_bEnableC4Box;
    jsonConfig["Esp"]["Bomb"]["EnableDistance"] = Data::Esp::Bomb::m_bEnableC4DistanceText;
    jsonConfig["Esp"]["Bomb"]["EnableLines"] = Data::Esp::Bomb::m_bEnableC4Lines;
    jsonConfig["Esp"]["Bomb"]["BoxOpacity"] = Data::Esp::Bomb::m_iBoxOpacity;
    jsonConfig["Esp"]["Bomb"]["DistanceTextColor"] = {
        Data::Esp::Bomb::m_clDistanceTextColor.x * 255,
        Data::Esp::Bomb::m_clDistanceTextColor.y * 255,
        Data::Esp::Bomb::m_clDistanceTextColor.z * 255,
        Data::Esp::Bomb::m_clDistanceTextColor.w * 255
    };
    jsonConfig["Esp"]["Bomb"]["PlantedC4BoxColor"] = {
        Data::Esp::Bomb::m_clPlantedC4BoxColor.x * 255,
        Data::Esp::Bomb::m_clPlantedC4BoxColor.y * 255,
        Data::Esp::Bomb::m_clPlantedC4BoxColor.z * 255,
        Data::Esp::Bomb::m_clPlantedC4BoxColor.w * 255
    };
    jsonConfig["Esp"]["Bomb"]["DroppedC4BoxColor"] = {
        Data::Esp::Bomb::m_clDroppedC4BoxColor.x * 255,
        Data::Esp::Bomb::m_clDroppedC4BoxColor.y * 255,
        Data::Esp::Bomb::m_clDroppedC4BoxColor.z * 255,
        Data::Esp::Bomb::m_clDroppedC4BoxColor.w * 255
    };
    jsonConfig["Esp"]["Bomb"]["LineColor"] = {
       Data::Esp::Bomb::m_clC4LineColor.x * 255,
       Data::Esp::Bomb::m_clC4LineColor.y * 255,
       Data::Esp::Bomb::m_clC4LineColor.z * 255,
       Data::Esp::Bomb::m_clC4LineColor.w * 255
    };
    jsonConfig["Esp"]["Bomb"]["BoxThickness"] = Data::Esp::Bomb::m_flBoxThickness;
    jsonConfig["Esp"]["Bomb"]["LineThickness"] = Data::Esp::Bomb::m_flLineThickness;
    jsonConfig["Esp"]["Bomb"]["CurrentLinePosIndex"] = Data::Esp::Bomb::m_iCurrentLinePosIndex;

    // Save World Esp Data
    jsonConfig["Esp"]["World"]["WorldEsp"] = Data::Esp::m_bWorldEsp;
    jsonConfig["Esp"]["World"]["EnableDroppedWeaponEsp"] = Data::Esp::World::m_bEnableDroppedWeaponEsp;
    jsonConfig["Esp"]["World"]["EnableProjectilesEsp"] = Data::Esp::World::m_bEnableProjectilesEsp;
    jsonConfig["Esp"]["World"]["EnableChickenEsp"] = Data::Esp::World::m_bEnableChickenEsp;
    jsonConfig["Esp"]["World"]["EnableHostagesEsp"] = Data::Esp::World::m_bEnableHostagesEsp;

    jsonConfig["Esp"]["World"]["WeaponEspTextColor"] = {
        Data::Esp::World::m_clWeaponEspTextColor.x * 255,
        Data::Esp::World::m_clWeaponEspTextColor.y * 255,
        Data::Esp::World::m_clWeaponEspTextColor.z * 255,
        Data::Esp::World::m_clWeaponEspTextColor.w * 255
    };

    jsonConfig["Esp"]["World"]["WeaponEspTextStrokeColor"] = {
        Data::Esp::World::m_clWeaponEspTextStrokeColor.x * 255,
        Data::Esp::World::m_clWeaponEspTextStrokeColor.y * 255,
        Data::Esp::World::m_clWeaponEspTextStrokeColor.z * 255,
        Data::Esp::World::m_clWeaponEspTextStrokeColor.w * 255
    };

    jsonConfig["Esp"]["World"]["ProjectilesEspTextColor"] = {
        Data::Esp::World::m_clProjectilesEspTextColor.x * 255,
        Data::Esp::World::m_clProjectilesEspTextColor.y * 255,
        Data::Esp::World::m_clProjectilesEspTextColor.z * 255,
        Data::Esp::World::m_clProjectilesEspTextColor.w * 255
    };

    jsonConfig["Esp"]["World"]["ProjectilesEspTextStrokeColor"] = {
        Data::Esp::World::m_clProjectilesEspTextStrokeColor.x * 255,
        Data::Esp::World::m_clProjectilesEspTextStrokeColor.y * 255,
        Data::Esp::World::m_clProjectilesEspTextStrokeColor.z * 255,
        Data::Esp::World::m_clProjectilesEspTextStrokeColor.w * 255
    };

    jsonConfig["Esp"]["World"]["ChickenEspTextColor"] = {
        Data::Esp::World::m_clChickenEspTextColor.x * 255,
        Data::Esp::World::m_clChickenEspTextColor.y * 255,
        Data::Esp::World::m_clChickenEspTextColor.z * 255,
        Data::Esp::World::m_clChickenEspTextColor.w * 255
    };

    jsonConfig["Esp"]["World"]["ChickenEspTextStrokeColor"] = {
        Data::Esp::World::m_clChickenEspTextStrokeColor.x * 255,
        Data::Esp::World::m_clChickenEspTextStrokeColor.y * 255,
        Data::Esp::World::m_clChickenEspTextStrokeColor.z * 255,
        Data::Esp::World::m_clChickenEspTextStrokeColor.w * 255
    };

    jsonConfig["Esp"]["World"]["WorldEntitiesBoxColor"] = {
        Data::Esp::World::m_clWorldEntitiesBoxColor.x * 255,
        Data::Esp::World::m_clWorldEntitiesBoxColor.y * 255,
        Data::Esp::World::m_clWorldEntitiesBoxColor.z * 255,
        Data::Esp::World::m_clWorldEntitiesBoxColor.w * 255
    };

    // Save Aimbot Data
    jsonConfig["Aimbot"]["Enable"] = Data::Aimbot::m_bAimbot;
    jsonConfig["Aimbot"]["EnableHotKey"] = Data::Aimbot::m_bEnableHotKey;
    jsonConfig["Aimbot"]["TeamCheck"] = Data::Aimbot::m_bTeamCheck;
    jsonConfig["Aimbot"]["Hotkey"] = Data::Aimbot::m_iCurrentHotkeyIndex;
    jsonConfig["Aimbot"]["HotkeyCode"] = Data::Aimbot::m_iCurrentKey;
    jsonConfig["Aimbot"]["AimPosition"] = Data::Aimbot::m_iCurrentAimPosIndex;

    // Save Memory Data
    jsonConfig["Memory"]["EnableAntiflash"] = Data::Memory::m_bEnableAntiflash;
    jsonConfig["Memory"]["EnableNoSky"] = Data::Memory::m_bEnableNoSky;
    jsonConfig["Memory"]["EnableNoSpread"] = Data::Memory::m_bEnableNoSpread;
    jsonConfig["Memory"]["EnableTPV"] = Data::Memory::m_bEnableTPV;
    jsonConfig["Memory"]["EnableMapView"] = Data::Memory::m_bEnableMapView;
    jsonConfig["Memory"]["EnableBhop"] = Data::Memory::m_bEnableBhop;
    jsonConfig["Memory"]["EnableFovChanger"] = Data::Memory::m_bEnableFovChanger;
    jsonConfig["Memory"]["EnableSensiChanger"] = Data::Memory::m_bEnableSensiChanger;
    jsonConfig["Memory"]["FlashAlpha"] = Data::Memory::m_flFlashAlpha;

    // Save RCS Data
    jsonConfig["Rcs"]["Enable"] = Data::Rcs::m_bRcs;
    // Save JumpShot Data
    jsonConfig["JumpShot"]["Enable"] = Data::JumpShot::m_bJumpShot;

    // Save FOV Data
    jsonConfig["Fov"]["DesiredFov"] = Data::Fov::m_iDesiredFov;
    jsonConfig["Fov"]["DefaultFov"] = Data::Fov::m_iDefaultFov;

    // Save TriggerBot Data
    jsonConfig["TriggerBot"]["Enable"] = Data::TriggerBot::m_bEnableTriggerBot;
    jsonConfig["TriggerBot"]["EnableHotKey"] = Data::TriggerBot::m_bEnableHotKey;
    jsonConfig["TriggerBot"]["EnableTeamCheck"] = Data::TriggerBot::m_bEnableTeamCheck;
    jsonConfig["TriggerBot"]["HotkeyCode"] = Data::TriggerBot::m_iCurrentKey;

    jsonConfig["_comment"] = "\nThis configuration file for Delta Cheat for CS2 manages the data and settings system for the user's cheat preferences.";
    jsonConfig["_comment2"] = "This Data Management System took 497 Fucking lines of code to implement.";

    // Saving the JSON to file
    std::ofstream file(fullPath);
    if (file.is_open()) {
        file << jsonConfig.dump(4); // Save with 4-space indentation
        file.close();
    }
    else {
        std::cerr << "Error: Unable to save config to " << fullPath << std::endl;
    }
}


void LoadConfig(const std::string& filename, const std::string& folder = "configs")
{
    json Data;

    std::string fullPath = folder + "/" + filename;

    if (!FileExists(fullPath)) {
        std::cerr << "Error: File does not exist: " << fullPath << std::endl;
        return;
    }

    std::ifstream inFile(fullPath);
    if (!inFile) {
        std::cerr << "Error: Failed to open file: " << fullPath << std::endl;
        return;
    }

    try {
        inFile >> Data;  // Parse the JSON file
        std::cout << "Loaded config: " << fullPath << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: Failed to parse JSON from file: " << fullPath << ". Error: " << e.what() << std::endl;
        return;
    }

    // Load Esp Data
    if (Data.contains("Esp"))
    {
        const auto& esp = Data["Esp"];
        Data::Esp::m_bPlayerEsp = esp["PlayerEsp"];
        Data::Esp::m_bWorldEsp = esp["WorldEsp"];
        Data::Esp::m_bBombEsp = esp["BombEsp"];

        const auto& playerEsp = esp["Player"];
        Data::Esp::Player::m_bEnableBox = playerEsp["EnableBox"];
        Data::Esp::Player::m_bEnableLines = playerEsp["EnableLines"];
        Data::Esp::Player::m_bEnableNames = playerEsp["EnableNames"];
        Data::Esp::Player::m_bEnableDistance = playerEsp["EnableDistance"];
        Data::Esp::Player::m_bEnableHealthBar = playerEsp["EnableHealthBar"];
        Data::Esp::Player::m_bEnableHealthText = playerEsp["EnableHealthText"];
        Data::Esp::Player::m_bEnableArmorBar = playerEsp["EnableArmorBar"];
        Data::Esp::Player::m_bEnableBones = playerEsp["EnableBones"];
        Data::Esp::Player::m_bEnableBonesJoints = playerEsp["EnableBonesJoints"];
        Data::Esp::Player::m_bBoneHeadFilled = playerEsp["BoneHeadFilled"];
        Data::Esp::Player::m_clBoxFilledColor = ImVec4(playerEsp["BoxFilledColor"][0], playerEsp["BoxFilledColor"][1], playerEsp["BoxFilledColor"][2], playerEsp["BoxFilledColor"][3]);
        Data::Esp::Player::m_clBoxUnfilledColor = ImVec4(playerEsp["BoxUnfilledColor"][0], playerEsp["BoxUnfilledColor"][1], playerEsp["BoxUnfilledColor"][2], playerEsp["BoxUnfilledColor"][3]);
        Data::Esp::Player::m_clLineColor = ImVec4(playerEsp["LineColor"][0], playerEsp["LineColor"][1], playerEsp["LineColor"][2], playerEsp["LineColor"][3]);
        Data::Esp::Player::m_clNameColor = ImVec4(playerEsp["NameColor"][0], playerEsp["NameColor"][1], playerEsp["NameColor"][2], playerEsp["NameColor"][3]);
        Data::Esp::Player::m_clArmorBarColor = ImVec4(playerEsp["ArmorBarColor"][0], playerEsp["ArmorBarColor"][1], playerEsp["ArmorBarColor"][2], playerEsp["ArmorBarColor"][3]);
        Data::Esp::Player::m_clDistanceTextColor = ImVec4(playerEsp["DistanceTextColor"][0], playerEsp["DistanceTextColor"][1], playerEsp["DistanceTextColor"][2], playerEsp["DistanceTextColor"][3]);
        Data::Esp::Player::m_flBoxUnfilledThickness = playerEsp["BoxThickness"];
        Data::Esp::Player::m_flLinesThickness = playerEsp["LineThickness"];
        Data::Esp::Player::m_flBonesThickness = playerEsp["BoneThickness"];
        Data::Esp::Player::m_flJointRadius = playerEsp["JointRadius"];
        Data::Esp::Player::m_iCurrentLinePosIndex = playerEsp["CurrentLinePosIndex"];

        // Bomb ESP
        const auto& bombEsp = esp["Bomb"];
        Data::Esp::Bomb::m_bEnableC4Box = bombEsp["EnableBox"];
        Data::Esp::Bomb::m_bEnableC4Lines = bombEsp["EnableLines"];
        Data::Esp::Bomb::m_bEnableC4DistanceText = bombEsp["EnableDistance"];
        Data::Esp::Bomb::m_iBoxOpacity = bombEsp["BoxOpacity"];
        Data::Esp::Bomb::m_clDistanceTextColor = ImVec4(bombEsp["DistanceTextColor"][0], bombEsp["DistanceTextColor"][1], bombEsp["DistanceTextColor"][2], bombEsp["DistanceTextColor"][3]);
        Data::Esp::Bomb::m_clPlantedC4BoxColor = ImVec4(bombEsp["PlantedC4BoxColor"][0], bombEsp["PlantedC4BoxColor"][1], bombEsp["PlantedC4BoxColor"][2], bombEsp["PlantedC4BoxColor"][3]);
        Data::Esp::Bomb::m_clDroppedC4BoxColor = ImVec4(bombEsp["DroppedC4BoxColor"][0], bombEsp["DroppedC4BoxColor"][1], bombEsp["DroppedC4BoxColor"][2], bombEsp["DroppedC4BoxColor"][3]);
        Data::Esp::Bomb::m_clC4LineColor = ImVec4(bombEsp["LineColor"][0], bombEsp["LineColor"][1], bombEsp["LineColor"][2], bombEsp["LineColor"][3]);
        Data::Esp::Bomb::m_flBoxThickness = bombEsp["BoxThickness"];
        Data::Esp::Bomb::m_flLineThickness = bombEsp["LineThickness"];
        Data::Esp::Bomb::m_iCurrentLinePosIndex = bombEsp["CurrentLinePosIndex"];

        // World ESP
        const auto& worldEsp = esp["World"];
        Data::Esp::World::m_bEnableDroppedWeaponEsp = worldEsp["EnableDroppedWeaponEsp"];
        Data::Esp::World::m_bEnableProjectilesEsp = worldEsp["EnableProjectilesEsp"];
        Data::Esp::World::m_bEnableChickenEsp = worldEsp["EnableChickenEsp"];
        Data::Esp::World::m_bEnableHostagesEsp = worldEsp["EnableHostagesEsp"];
        Data::Esp::World::m_clWeaponEspTextColor = ImVec4(worldEsp["WeaponEspTextColor"][0], worldEsp["WeaponEspTextColor"][1], worldEsp["WeaponEspTextColor"][2], worldEsp["WeaponEspTextColor"][3]);
        Data::Esp::World::m_clWeaponEspTextStrokeColor = ImVec4(worldEsp["WeaponEspTextStrokeColor"][0], worldEsp["WeaponEspTextStrokeColor"][1], worldEsp["WeaponEspTextStrokeColor"][2], worldEsp["WeaponEspTextStrokeColor"][3]);
        Data::Esp::World::m_clProjectilesEspTextColor = ImVec4(worldEsp["ProjectilesEspTextColor"][0], worldEsp["ProjectilesEspTextColor"][1], worldEsp["ProjectilesEspTextColor"][2], worldEsp["ProjectilesEspTextColor"][3]);
        Data::Esp::World::m_clProjectilesEspTextStrokeColor = ImVec4(worldEsp["ProjectilesEspTextStrokeColor"][0], worldEsp["ProjectilesEspTextStrokeColor"][1], worldEsp["ProjectilesEspTextStrokeColor"][2], worldEsp["ProjectilesEspTextStrokeColor"][3]);
        Data::Esp::World::m_clChickenEspTextColor = ImVec4(worldEsp["ChickenEspTextColor"][0], worldEsp["ChickenEspTextColor"][1], worldEsp["ChickenEspTextColor"][2], worldEsp["ChickenEspTextColor"][3]);
        Data::Esp::World::m_clChickenEspTextStrokeColor = ImVec4(worldEsp["ChickenEspTextStrokeColor"][0], worldEsp["ChickenEspTextStrokeColor"][1], worldEsp["ChickenEspTextStrokeColor"][2], worldEsp["ChickenEspTextStrokeColor"][3]);
        Data::Esp::World::m_clWorldEntitiesBoxColor = ImVec4(worldEsp["WorldEntitiesBoxColor"][0], worldEsp["WorldEntitiesBoxColor"][1], worldEsp["WorldEntitiesBoxColor"][2], worldEsp["WorldEntitiesBoxColor"][3]);

    }

    // Aimbot
    if (Data.contains("Aimbot"))
    {
        const auto& aimbot = Data["Aimbot"];
        Data::Aimbot::m_bAimbot = aimbot["Enable"];
        Data::Aimbot::m_bEnableHotKey = aimbot["EnableHotKey"];
        Data::Aimbot::m_bTeamCheck = aimbot["TeamCheck"];
        Data::Aimbot::m_iCurrentKey = aimbot["HotkeyCode"];
        Data::Aimbot::m_iCurrentHotkeyIndex = aimbot["HotkeyCode"];
        Data::Aimbot::m_iCurrentAimPosIndex = aimbot["AimPosition"];
    }

    // Memory
    if (Data.contains("Memory"))
    {
        const auto& memory = Data["Memory"];
        Data::Memory::m_bEnableAntiflash = memory["EnableAntiflash"];
        Data::Memory::m_bEnableNoSky = memory["EnableNoSky"];
        Data::Memory::m_bEnableNoSpread = memory["EnableNoSpread"];
        Data::Memory::m_bEnableTPV = memory["EnableTPV"];
        Data::Memory::m_bEnableMapView = memory["EnableMapView"];
        Data::Memory::m_bEnableBhop = memory["EnableBhop"];
        Data::Memory::m_bEnableFovChanger = memory["EnableFovChanger"];
    }

    // RCS
    if (Data.contains("Rcs"))
    {
        const auto& rcs = Data["Rcs"];
        Data::Rcs::m_bRcs = rcs["Enable"];
    }
    else {
        std::cerr << "Error: 'Rcs' key is missing in the config file" << std::endl;
    }

    // JumpShot
    if (Data.contains("JumpShot"))
    {
        const auto& jumpshot = Data["JumpShot"];
        Data::JumpShot::m_bJumpShot = jumpshot["Enable"];
    }

    // Fov
    if (Data.contains("Fov"))
    {
        const auto& fov = Data["Fov"];
        Data::Fov::m_iDesiredFov = fov["DesiredFov"];
        Data::Fov::m_iDefaultFov = fov["DefaultFov"];
    }

    // TriggerBot
    if (Data.contains("TriggerBot"))
    {
        const auto& triggerBot = Data["TriggerBot"];
        Data::TriggerBot::m_bEnableTriggerBot = triggerBot["Enable"];
        Data::TriggerBot::m_bEnableHotKey = triggerBot["EnableHotKey"];
        Data::TriggerBot::m_bEnableTeamCheck = triggerBot["EnableTeamCheck"];
        Data::TriggerBot::m_iCurrentKey = triggerBot["HotkeyCode"];
    }
}
