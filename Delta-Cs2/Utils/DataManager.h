#pragma once
#include <fstream>
#include <Libs/Json.hpp>
#include <Cheats/Data.h>
#include <Globals/Globals.h>
#include <filesystem>
#include <Libs/ImGui/imgui.h>
#include <Menu/Custom.h>

using json = nlohmann::json;
namespace fs = std::filesystem;
inline std::vector<String> jsonFiles;

class DataManager {
public:
    ImVec4 LoadColorFromJson(const json& colorJson, const ImVec4& defaultColor = ImVec4(1.0, 1.0, 1.0, 1.0));
    Float LoadFloatFromJson(const json& jsonValue, float defaultValue = 0.0f);
    VOID ScanDirectoryForJsonFiles(const String& path);

    template<typename T>
    VOID SaveField(json& jsonConfig, const std::string& fieldName, const T& fieldValue)
    {
        jsonConfig[fieldName] = fieldValue;
    }

public:
    Bool FileExists(const String& name);
    String GetExecutablePath();
    String GetConfigPath(const String& folderName, const String& filename);

}; inline DataManager dataManager;

// This function Saves all the Cheat Data from Data.h Header File
inline VOID SaveCheatData()
{
    fs::path dirPath = Data::folderName;
    if (!fs::exists(dirPath)) {
        fs::create_directory(dirPath);
    }

    String fullPath = dataManager.GetConfigPath(Data::folderName, Data::fileName);
    json jsonConfig;

    // Save Player Esp Data
    {
        jsonConfig["Esp"]["Player"]["Enable"] = Data::Esp::m_bPlayerEsp;
        jsonConfig["Esp"]["Player"]["EnableBox"] = Data::Esp::Player::m_bEnableBox;
        jsonConfig["Esp"]["Player"]["EnableBoxFilled"] = Data::Esp::Player::m_bBoxFilled;
        jsonConfig["Esp"]["Player"]["EnableLines"] = Data::Esp::Player::m_bEnableLines;
        jsonConfig["Esp"]["Player"]["EnableNames"] = Data::Esp::Player::m_bEnableNames;
        jsonConfig["Esp"]["Player"]["EnableDistance"] = Data::Esp::Player::m_bEnableDistance;
        jsonConfig["Esp"]["Player"]["EnableHealthBar"] = Data::Esp::Player::m_bEnableHealthBar;
        jsonConfig["Esp"]["Player"]["EnableHealthText"] = Data::Esp::Player::m_bEnableHealthText;
        jsonConfig["Esp"]["Player"]["EnableArmorBar"] = Data::Esp::Player::m_bEnableArmorBar;
        jsonConfig["Esp"]["Player"]["EnableBones"] = Data::Esp::Player::m_bEnableBones;
        jsonConfig["Esp"]["Player"]["EnableBonesJoints"] = Data::Esp::Player::m_bEnableBonesJoints;
        jsonConfig["Esp"]["Player"]["EnableBoneHeadFilled"] = Data::Esp::Player::m_bBoneHeadFilled;
        jsonConfig["Esp"]["Player"]["EnableTeamCheck"] = Data::Esp::Player::m_bTeamCheck;
        jsonConfig["Esp"]["Player"]["EnableBonesOnDeadEntity"] = Data::Esp::Player::m_bBonesOnDeadEntity;
        jsonConfig["Esp"]["Player"]["EnableDormantCheck"] = Data::Esp::Player::m_bDormantCheck;


        jsonConfig["Esp"]["Player"]["BoxFilledColor"] = { Data::Esp::Player::m_clBoxFilledColor.x, Data::Esp::Player::m_clBoxFilledColor.y, Data::Esp::Player::m_clBoxFilledColor.z, Data::Esp::Player::m_clBoxFilledColor.w };
        jsonConfig["Esp"]["Player"]["BoxUnfilledColor"] = { Data::Esp::Player::m_clBoxUnfilledColor.x, Data::Esp::Player::m_clBoxUnfilledColor.y, Data::Esp::Player::m_clBoxUnfilledColor.z, Data::Esp::Player::m_clBoxUnfilledColor.w };
        jsonConfig["Esp"]["Player"]["LineColor"] = { Data::Esp::Player::m_clLineColor.x, Data::Esp::Player::m_clLineColor.y, Data::Esp::Player::m_clLineColor.z, Data::Esp::Player::m_clLineColor.w };
        jsonConfig["Esp"]["Player"]["NameColor"] = { Data::Esp::Player::m_clNameColor.x, Data::Esp::Player::m_clNameColor.y, Data::Esp::Player::m_clNameColor.z, Data::Esp::Player::m_clNameColor.w };
        jsonConfig["Esp"]["Player"]["ArmorBarColor"] = { Data::Esp::Player::m_clArmorBarColor.x, Data::Esp::Player::m_clArmorBarColor.y, Data::Esp::Player::m_clArmorBarColor.z, Data::Esp::Player::m_clArmorBarColor.w };
        jsonConfig["Esp"]["Player"]["DistanceTextColor"] = { Data::Esp::Player::m_clDistanceTextColor.x, Data::Esp::Player::m_clDistanceTextColor.y, Data::Esp::Player::m_clDistanceTextColor.z, Data::Esp::Player::m_clDistanceTextColor.w };
        jsonConfig["Esp"]["Player"]["BoneColor"] = { Data::Esp::Player::m_clBoneColor.x, Data::Esp::Player::m_clBoneColor.y, Data::Esp::Player::m_clBoneColor.z, Data::Esp::Player::m_clBoneColor.w };
        jsonConfig["Esp"]["Player"]["BoneJointsColor"] = { Data::Esp::Player::m_clBoneJointsColor.x, Data::Esp::Player::m_clBoneJointsColor.y, Data::Esp::Player::m_clBoneJointsColor.z, Data::Esp::Player::m_clBoneJointsColor.w };
        
        jsonConfig["Esp"]["Player"]["BoxThickness"] = Data::Esp::Player::m_flBoxUnfilledThickness;
        jsonConfig["Esp"]["Player"]["LineThickness"] = Data::Esp::Player::m_flLinesThickness;
        jsonConfig["Esp"]["Player"]["BoneThickness"] = Data::Esp::Player::m_flBonesThickness;
        jsonConfig["Esp"]["Player"]["JointRadius"] = Data::Esp::Player::m_flJointRadius;
        jsonConfig["Esp"]["Player"]["CurrentLinePosIndex"] = Data::Esp::Player::m_iCurrentLinePosIndex;
    }


    // Save Bomb Esp Data
    {
        jsonConfig["Esp"]["Bomb"]["BombEsp"] = Data::Esp::m_bBombEsp;
        jsonConfig["Esp"]["Bomb"]["EnableBox"] = Data::Esp::Bomb::m_bEnableC4Box;
        jsonConfig["Esp"]["Bomb"]["EnableDistance"] = Data::Esp::Bomb::m_bEnableC4DistanceText;
        jsonConfig["Esp"]["Bomb"]["EnableLines"] = Data::Esp::Bomb::m_bEnableC4Lines;
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

    }

    // Save World Esp Data
    {
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
    }


    // Save Aimbot Data
    {
        // Bools
        jsonConfig["Aimbot"]["Enable"] = Data::Aimbot::m_bAimbot;
        jsonConfig["Aimbot"]["EnableHotKey"] = Data::Aimbot::m_bEnableHotKey;
        jsonConfig["Aimbot"]["TeamCheck"] = Data::Aimbot::m_bTeamCheck;
        jsonConfig["Aimbot"]["FovBased"] = Data::Aimbot::m_bFovBased;
        jsonConfig["Aimbot"]["ShowFovCircle"] = Data::Aimbot::m_bShowFovCircle;

        // Floats and ints
        jsonConfig["Aimbot"]["FovRange"] = Data::Aimbot::m_flFov;
        jsonConfig["Aimbot"]["FovCircleThickness"] = Data::Aimbot::m_flFovCircleThickness;
        jsonConfig["Aimbot"]["HotkeyCode"] = Data::Aimbot::m_iCurrentKey;
        jsonConfig["Aimbot"]["AimPositionIndex"] = Data::Aimbot::m_iCurrentAimPosIndex;

        // Colors
        jsonConfig["Aimbot"]["FovCircleColor"] = {
           Data::Aimbot::m_clFovCircleColor.x * 255,
           Data::Aimbot::m_clFovCircleColor.y * 255,
           Data::Aimbot::m_clFovCircleColor.z * 255,
           Data::Aimbot::m_clFovCircleColor.w * 255
        };
    }


    // Save Memory Data
    {
        jsonConfig["Memory"]["EnableAntiflash"] = Data::Memory::m_bEnableAntiflash;
        jsonConfig["Memory"]["EnableNoSky"] = Data::Memory::m_bEnableNoSky;
        jsonConfig["Memory"]["EnableNoSpread"] = Data::Memory::m_bEnableNoSpread;
        jsonConfig["Memory"]["EnableTPV"] = Data::Memory::m_bEnableTPV;
        jsonConfig["Memory"]["EnableMapView"] = Data::Memory::m_bEnableMapView;
        jsonConfig["Memory"]["EnableBhop"] = Data::Memory::m_bEnableBhop;
        jsonConfig["Memory"]["EnableFovChanger"] = Data::Memory::m_bEnableFovChanger;
        jsonConfig["Memory"]["EnableSensiChanger"] = Data::Memory::m_bEnableSensiChanger;
        jsonConfig["Memory"]["FlashAlpha"] = Data::Memory::m_flFlashAlpha;
    }

    // Save Misc Datas
    {
        // Save RCS Data
        jsonConfig["Misc"]["EnableRecoilControlSystem"] = Data::Rcs::m_bRcs;
        // Save JumpShot Data
        jsonConfig["Misc"]["EnableAutoJumpshot"] = Data::JumpShot::m_bJumpShot;

        // Save FOV Data
        jsonConfig["Misc"]["DesiredFov"] = Data::Fov::m_iDesiredFov;
        jsonConfig["Misc"]["DefaultFov"] = Data::Fov::m_iDefaultFov;
    }
    
    // Save TriggerBot Data
    {
        jsonConfig["TriggerBot"]["Enable"] = Data::TriggerBot::m_bEnableTriggerBot;
        jsonConfig["TriggerBot"]["EnableHotKey"] = Data::TriggerBot::m_bEnableHotKey;
        jsonConfig["TriggerBot"]["EnableTeamCheck"] = Data::TriggerBot::m_bEnableTeamCheck;
        jsonConfig["TriggerBot"]["HotkeyCode"] = Data::TriggerBot::m_iCurrentKey;
    }

    // Comments
    {
        jsonConfig["null_values"] = "No Null Values Stored";
        jsonConfig["_comment"] = "This configuration file for Delta Cheat for CS2 manages the data and settings system for the user's cheat preferences.";
        jsonConfig["_comment2"] = "This Data Management System took more than 1000 Fucking lines of code to implement.";
    }

    // Saving the JSON to file
    std::ofstream file(fullPath);
    if (file.is_open()) {
        file << jsonConfig.dump(4); // Save with 4-space indentation
        file.close();
    }
    else {
        std::cout << " [+] Data Manager\n";
        std::cout << std::endl;
        console.SetConsoleTextColor(RED);
        std::cout << "Error: Unable to save config to " << fullPath << std::endl;
    }
}

// This function Loads all the Saved Cheat Data
inline VOID LoadCheatData()
{
    std::string fullPath = dataManager.GetConfigPath(Data::folderName, Data::fileName);
    if (!dataManager.FileExists(fullPath)) {
        std::cerr << "Error: File does not exist: " << fullPath << std::endl;
        return;
    }

    std::ifstream inFile(fullPath);
    if (!inFile) {
        std::cerr << "Error: Failed to open file: " << fullPath << std::endl;
        return;
    }

    json Data;
    try {
        inFile >> Data;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: Failed to parse JSON: " << e.what() << std::endl;
        return;
    }

    // Load Esp Data
    if (Data.contains("Esp"))
    {
        const auto& esp = Data["Esp"];

        // Load Player Esp Data
        if (esp.contains("Player"))
        {
            const auto& playerEsp = esp["Player"];

            // Bools
            Data::Esp::m_bPlayerEsp = playerEsp.value("Enable", false);
            Data::Esp::Player::m_bEnableBox = playerEsp.value("EnableBox", false);
            Data::Esp::Player::m_bBoxFilled = playerEsp.value("EnableBoxFilled", false);
            Data::Esp::Player::m_bEnableLines = playerEsp.value("EnableLines", false);
            Data::Esp::Player::m_bEnableNames = playerEsp.value("EnableNames", false);
            Data::Esp::Player::m_bEnableDistance = playerEsp.value("EnableDistance", false);
            Data::Esp::Player::m_bEnableHealthBar = playerEsp.value("EnableHealthBar", false);
            Data::Esp::Player::m_bEnableHealthText = playerEsp.value("EnableHealthText", false);
            Data::Esp::Player::m_bEnableArmorBar = playerEsp.value("EnableArmorBar", false);
            Data::Esp::Player::m_bEnableBones = playerEsp.value("EnableBones", false);
            Data::Esp::Player::m_bEnableBonesJoints = playerEsp.value("EnableBonesJoints", false);
            Data::Esp::Player::m_bBoneHeadFilled = playerEsp.value("EnableBoneHeadFilled", false);
            Data::Esp::Player::m_bTeamCheck = playerEsp.value("EnableTeamCheck", false);
            Data::Esp::Player::m_bBonesOnDeadEntity = playerEsp.value("EnableBonesOnDeadEntity", false);
            Data::Esp::Player::m_bDormantCheck = playerEsp.value("EnableDormantCheck", false);

            // Colors
            Data::Esp::Player::m_clBoxFilledColor = dataManager.LoadColorFromJson(playerEsp["BoxFilledColor"]);
            Data::Esp::Player::m_clBoxUnfilledColor = dataManager.LoadColorFromJson(playerEsp["BoxUnfilledColor"]);
            Data::Esp::Player::m_clLineColor = dataManager.LoadColorFromJson(playerEsp["LineColor"]);
            Data::Esp::Player::m_clNameColor = dataManager.LoadColorFromJson(playerEsp["NameColor"]);
            Data::Esp::Player::m_clArmorBarColor = dataManager.LoadColorFromJson(playerEsp["ArmorBarColor"]);
            Data::Esp::Player::m_clDistanceTextColor = dataManager.LoadColorFromJson(playerEsp["DistanceTextColor"]);
            Data::Esp::Player::m_clBoneColor = dataManager.LoadColorFromJson(playerEsp["BoneColor"]);
            Data::Esp::Player::m_clBoneJointsColor = dataManager.LoadColorFromJson(playerEsp["BoneJointsColor"]);

            // Floats
            Data::Esp::Player::m_flBoxUnfilledThickness = dataManager.LoadFloatFromJson(playerEsp["BoxThickness"]);
            Data::Esp::Player::m_flLinesThickness = dataManager.LoadFloatFromJson(playerEsp["LineThickness"]);
            Data::Esp::Player::m_flBonesThickness = dataManager.LoadFloatFromJson(playerEsp["BoneThickness"]);
            Data::Esp::Player::m_flJointRadius = dataManager.LoadFloatFromJson(playerEsp["JointRadius"]);

            // Ints
            Data::Esp::Player::m_iCurrentLinePosIndex = playerEsp["CurrentLinePosIndex"];
        }

        // Load Bomb ESP Data
        if (esp.contains("Bomb"))
        {
            const auto& bombEsp = esp["Bomb"];

            // Bools
            Data::Esp::m_bBombEsp = bombEsp.value("BombEsp", false);
            Data::Esp::Bomb::m_bEnableC4Box = bombEsp.value("EnableBox", false);
            Data::Esp::Bomb::m_bEnableC4Lines = bombEsp.value("EnableLines", false);;
            Data::Esp::Bomb::m_bEnableC4DistanceText = bombEsp.value("EnableDistance", false);

            // Colors
            Data::Esp::Bomb::m_clDistanceTextColor = dataManager.LoadColorFromJson(bombEsp["DistanceTextColor"]);
            Data::Esp::Bomb::m_clPlantedC4BoxColor = dataManager.LoadColorFromJson(bombEsp["PlantedC4BoxColor"]);
            Data::Esp::Bomb::m_clDroppedC4BoxColor = dataManager.LoadColorFromJson(bombEsp["DroppedC4BoxColor"]);
            Data::Esp::Bomb::m_clC4LineColor = dataManager.LoadColorFromJson(bombEsp["LineColor"]);

            // Customizations
            Data::Esp::Bomb::m_flBoxThickness = dataManager.LoadFloatFromJson(bombEsp["BoxThickness"]);
            Data::Esp::Bomb::m_flLineThickness = dataManager.LoadFloatFromJson(bombEsp["LineThickness"]);
            Data::Esp::Bomb::m_iCurrentLinePosIndex = bombEsp["CurrentLinePosIndex"];
        }

        // Load World ESP Data
        if (esp.contains("World"))
        {
            const auto& worldEsp = esp["World"];

            // Bools
            Data::Esp::m_bWorldEsp = worldEsp.value("WorldEsp", false);
            Data::Esp::World::m_bEnableDroppedWeaponEsp = worldEsp.value("EnableDroppedWeaponEsp", false);
            Data::Esp::World::m_bEnableProjectilesEsp = worldEsp.value("EnableProjectilesEsp", false);
            Data::Esp::World::m_bEnableChickenEsp = worldEsp.value("EnableChickenEsp", false);

            // Colors
            Data::Esp::World::m_clWeaponEspTextColor = dataManager.LoadColorFromJson(worldEsp["WeaponEspTextColor"]);
            Data::Esp::World::m_clWeaponEspTextStrokeColor = dataManager.LoadColorFromJson(worldEsp["WeaponEspTextStrokeColor"]);
            Data::Esp::World::m_clProjectilesEspTextColor = dataManager.LoadColorFromJson(worldEsp["ProjectilesEspTextColor"]);
            Data::Esp::World::m_clProjectilesEspTextStrokeColor = dataManager.LoadColorFromJson(worldEsp["ProjectilesEspTextStrokeColor"]);
            Data::Esp::World::m_clChickenEspTextColor = dataManager.LoadColorFromJson(worldEsp["ChickenEspTextColor"]);
            Data::Esp::World::m_clChickenEspTextStrokeColor = dataManager.LoadColorFromJson(worldEsp["ChickenEspTextStrokeColor"]);
        }
    }

    // Load Aimbot Data
    if (Data.contains("Aimbot"))
    {
        const auto& aimbot = Data["Aimbot"];

        // Bools
        Data::Aimbot::m_bAimbot = aimbot.value("Enable", false);
        Data::Aimbot::m_bEnableHotKey = aimbot.value("EnableHotKey", false);
        Data::Aimbot::m_bTeamCheck = aimbot.value("TeamCheck", false);
        Data::Aimbot::m_bFovBased = aimbot.value("FovBased", false);
        Data::Aimbot::m_bShowFovCircle = aimbot.value("ShowFovCircle", false);

        // Floats and Ints
        Data::Aimbot::m_flFov = aimbot["FovRange"];
        Data::Aimbot::m_flFovCircleThickness = aimbot["FovCircleThickness"];
        Data::Aimbot::m_iCurrentAimPosIndex = aimbot["AimPositionIndex"];
        Data::Aimbot::m_iCurrentKey = aimbot["HotkeyCode"];

        // Colors
        Data::Aimbot::m_clFovCircleColor = dataManager.LoadColorFromJson(aimbot["FovCircleColor"]);
    }

    // Load Memory Cheats Data
    if (Data.contains("Memory"))
    {
        const auto& memory = Data["Memory"];

        // Bools
        Data::Memory::m_bEnableAntiflash = memory.value("EnableAntiflash", false);
        Data::Memory::m_bEnableNoSky = memory.value("EnableNoSky", false);
        Data::Memory::m_bEnableNoSpread = memory.value("EnableNoSpread", false);
        Data::Memory::m_bEnableMapView = memory.value("EnableMapView", false);
        Data::Memory::m_bEnableBhop = memory.value("EnableBhop", false);
        Data::Memory::m_bEnableFovChanger = memory.value("EnableFovChanger", false);
        Data::Memory::m_bEnableSensiChanger = memory.value("EnableSensiChanger", false);

        // Floats
        Data::Memory::m_flFlashAlpha = memory["FlashAlpha"];
    }

    // Load Miscs Data
    if (Data.contains("Misc"))
    {
        const auto& misc = Data["Misc"];

        // Bools
        Data::Rcs::m_bRcs = misc.value("EnableRecoilControlSystem", false);
        Data::JumpShot::m_bJumpShot = misc.value("EnableAutoJumpshot", false);

        // Ints
        Data::Fov::m_iDesiredFov = misc["DesiredFov"];
        Data::Fov::m_iDefaultFov = misc["DefaultFov"];
    }

    // Load Triggerbot Data
    if (Data.contains("Triggerbot"))
    {
        const auto& triggerbot = Data["Triggerbot"];

        // Bools
        Data::TriggerBot::m_bEnableTriggerBot = triggerbot.value("Enable", false);
        Data::TriggerBot::m_bEnableHotKey = triggerbot.value("EnableHotKey", false);
        Data::TriggerBot::m_bEnableTeamCheck = triggerbot.value("EnableTeamCheck", false);
        Data::TriggerBot::m_iCurrentKey = triggerbot.value("HotkeyCode", false);
    }
}

// This function Saves all other datas from Globals.h Header File
inline VOID SaveSettings()
{
    fs::path dirPath = Flags::DataFolderName;
    if (!fs::exists(dirPath)) {
        fs::create_directory(dirPath);
    }

    String fullPath = dataManager.GetConfigPath(Flags::DataFolderName, Flags::DataFileName);
    json jsonConfig;

    jsonConfig["Messages"]["g_showWarningBox"] = Flags::g_showWarningBox;
    jsonConfig["Messages"]["g_showConsole"] = Flags::g_showConsole;

    jsonConfig["Flags"]["g_VisualCheats"] = Flags::VisualCheats;
    jsonConfig["Flags"]["g_MemoryCheats"] = Flags::MemoryCheats;
    jsonConfig["Flags"]["g_AimCheats"] = Flags::AimCheats;

    jsonConfig["Miscs"]["accent_color"] = { custom.accent_color[0], custom.accent_color[1], custom.accent_color[2], custom.accent_color[3] };
    jsonConfig["Miscs"]["CloseProgramHotkey"] = Panickey::CLOSEPROGRAM;
    jsonConfig["Miscs"]["HideMenuHotkey"] = Panickey::HIDEMENU;

    std::ofstream file(fullPath);
    if (file.is_open()) {
        file << jsonConfig.dump(4); 
        file.close();
    }
    else {
        std::cout << " [+] Data Manager\n";
        std::cout << std::endl;
        console.SetConsoleTextColor(RED);
        std::cout << "  => Error: Unable to save config to " << fullPath << std::endl;
    }
}

// This function Loads all other datas from saved settings file
inline VOID LoadSettings()
{
    std::string fullPath = dataManager.GetConfigPath(Flags::DataFolderName, Flags::DataFileName);
    if (!dataManager.FileExists(fullPath)) {
        std::cerr << "Error: File does not exist: " << fullPath << std::endl;
        return;
    }

    std::ifstream inFile(fullPath);
    if (!inFile) {
        std::cerr << "Error: Failed to open file: " << fullPath << std::endl;
        return;
    }

    json Data;
    try {
        inFile >> Data;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: Failed to parse JSON: " << e.what() << std::endl;
        return;
    }

    if (Data.contains("Messages"))
    {
        const auto& message = Data["Messages"];

        Flags::g_showWarningBox = message.value("g_showWarningBox", false);
        Flags::g_showConsole = message.value("g_showConsole", false);
    }

    if (Data.contains("Flags"))
    {
        const auto& flag = Data["Flags"];

        Flags::VisualCheats = flag.value("g_VisualCheats", false);
        Flags::MemoryCheats = flag.value("g_MemoryCheats", false);
        Flags::AimCheats = flag.value("g_AimCheats", false);
    }

    if (Data.contains("Miscs"))
    {
        const auto& miscs = Data["Miscs"];

        custom.accent_color[0] = miscs["accent_color"][0];
        custom.accent_color[1] = miscs["accent_color"][1];
        custom.accent_color[2] = miscs["accent_color"][2];
        custom.accent_color[3] = miscs["accent_color"][3];

        Panickey::CLOSEPROGRAM = miscs["CloseProgramHotkey"];
        Panickey::HIDEMENU = miscs["HideMenuHotkey"];
    }

}