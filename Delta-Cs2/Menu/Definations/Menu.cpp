#define IMGUI_DEFINE_MATH_OPERATORS
#include <Menu/Menu.h>
#include <Menu/Custom.h>
#include <Cheats/Data.h>
#include <Utils/KeyArrays.h>
#include <SDK/CPlayer.h>
#include <SDK/CGame.h>
#include <SDK/CC4.h>
#include <Utils/DataManager.h>
#include <Menu/Resources.h>
#include <Utils/Updater.h>

VOID Menu::ApplyStyles()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 0.0f;
    style.WindowRounding = 10.0f;
    style.ScrollbarSize = 2.0f;
    style.FrameRounding = 5.0f;
    style.Colors[ImGuiCol_Border] = ImColor(255, 255, 255);
    style.Colors[ImGuiCol_FrameBg] = ImColor(14, 14, 14);
    style.Colors[ImGuiCol_HeaderHovered] = ImColor(custom.accent_color[0], custom.accent_color[1], custom.accent_color[2], custom.accent_color[3]);
    style.Colors[ImGuiCol_HeaderActive] = ImColor(custom.accent_color[0] - 10, custom.accent_color[1] - 10, custom.accent_color[2] - 10, custom.accent_color[3]);
    style.Colors[ImGuiCol_Button] = ImColor(custom.accent_color[0], custom.accent_color[1], custom.accent_color[2], custom.accent_color[3]);
    style.Colors[ImGuiCol_ButtonHovered] = ImColor(custom.accent_color[0] - 10, custom.accent_color[1] - 10, custom.accent_color[2] - 10, custom.accent_color[3]);
    style.Colors[ImGuiCol_ButtonActive] = ImColor(custom.accent_color[0] - 5, custom.accent_color[1] - 5, custom.accent_color[2] - 5, custom.accent_color[3]);
}

VOID Menu::CreatePlayerEspInterface()
{
    const float xOffset = 10.0f;
    const float ySpacing = 29.0f;

    // First child frame
    {
        ImGui::BeginChildFrame(ImGui::GetID("Players-Visuals-Frame"), ImVec2(200, 386));
        ImVec2 startPos = ImGui::GetCursorPos();

        std::vector<std::pair<const char*, bool*>> checkboxes = {
            {"Enable Esp", &Data::Esp::m_bPlayerEsp},
            {"Box", &Data::Esp::Player::m_bEnableBox},
            {"Box Filled", &Data::Esp::Player::m_bBoxFilled},
            {"Snap Lines", &Data::Esp::Player::m_bEnableLines},
            {"Distance", &Data::Esp::Player::m_bEnableDistance},
            {"Bone", &Data::Esp::Player::m_bEnableBones},
            {"Head Filled", &Data::Esp::Player::m_bBoneHeadFilled},
            {"Bone Joints", &Data::Esp::Player::m_bEnableBonesJoints},
            {"Names", &Data::Esp::Player::m_bEnableNames},
            {"Health Bar", &Data::Esp::Player::m_bEnableHealthBar},
            {"Armor Bar", &Data::Esp::Player::m_bEnableArmorBar},
            {"Health Text", &Data::Esp::Player::m_bEnableHealthText},
            {"Team Check", &Data::Esp::Player::m_bTeamCheck},
        };

        for (size_t i = 0; i < checkboxes.size(); ++i) {
            ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + i * ySpacing });
            custom.Checkbox(checkboxes[i].first, checkboxes[i].second);
        }

        ImGui::EndChildFrame();
    }


    ImGui::SameLine();

    // Second child frame
    {
        ImGui::BeginChildFrame(ImGui::GetID("Players-Visuals-Frame2"), ImVec2(375, 386));
        ImVec2 startPos = ImGui::GetCursorPos();

        const float columnWidth = 180.0f;
        const float spacing = 70.0f;

        std::vector<std::pair<const char*, ImVec4*>> esp_colors = {
            {"Box Color", &Data::Esp::Player::m_clBoxUnfilledColor},
            {"Box Fill Color", &Data::Esp::Player::m_clBoxFilledColor},
            {"Snap Lines Color", &Data::Esp::Player::m_clLineColor},
            {"Distance text Color", &Data::Esp::Player::m_clDistanceTextColor},
            {"Bone Color", &Data::Esp::Player::m_clBoneColor},
            {"Head Color", &Data::Esp::Player::m_clBoneHeadColor},
            {"Joints Color", &Data::Esp::Player::m_clBoneJointsColor},
            {"Name Color", &Data::Esp::Player::m_clNameColor}
        };

        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, columnWidth);

        for (size_t i = 0; i < esp_colors.size(); ++i) {
            custom.ColorEditor(esp_colors[i].first, esp_colors[i].second);

            if (i == esp_colors.size() / 2 - 1) {
                ImGui::NextColumn();
            }
        }

        ImGui::Columns(1);

        ImGui::Spacing();
        ImGui::Separator();

        custom.LeaveLine(2);
        ImGui::Text(" Line Position");

        custom.RadioButtonGroup(
            &Data::Esp::Player::m_iCurrentLinePosIndex,
            Data::Esp::Player::m_AvailableSnapLinesPos,
            IM_ARRAYSIZE(Data::Esp::Player::m_AvailableSnapLinesPos)
        );

        custom.LeaveLine(2);

        custom.SliderFloat("    Box Thickness", &Data::Esp::Player::m_flBoxUnfilledThickness, 1.0f, 10.0f);
        custom.LeaveLine(1);

        custom.SliderFloat("    Line Thickness", &Data::Esp::Player::m_flLinesThickness, 1.0f, 10.0f);
        custom.LeaveLine(1);

        custom.SliderFloat("    Bone Thickness", &Data::Esp::Player::m_flBonesThickness, 1.0f, 10.0f);
        custom.LeaveLine(1);

        custom.SliderFloat("    Joint Radius", &Data::Esp::Player::m_flJointRadius, 1.0f, 10.0f);
        custom.LeaveLine(1);

        ImGui::SetCursorPos({ startPos.x + 5.0f, 285 });
        custom.Checkbox("Bone Check", &Data::Esp::Player::m_bBonesOnDeadEntity);

        ImGui::SetCursorPos({ startPos.x + 5.0f, 310 });
        custom.Checkbox("Dormant Check", &Data::Esp::Player::m_bDormantCheck);


        ImGui::EndChildFrame();
    }

}

VOID Menu::CreateBombEspInterface()
{
    // First child frame
    {
        ImGui::BeginChildFrame(ImGui::GetID("Bomb-Visuals-Frame"), ImVec2(200, 386));

        ImVec2 startPos = ImGui::GetCursorPos();
        const float xOffset = 10.0f;
        const float ySpacing = 29.0f;

        std::vector<std::pair<const char*, bool*>> checkboxes = {
            {"Enable C4 Esp", &Data::Esp::m_bBombEsp},
            {"Box", &Data::Esp::Bomb::m_bEnableC4Box },
            {"Snap Line", &Data::Esp::Bomb::m_bEnableC4Lines},
            {"Distance", &Data::Esp::Bomb::m_bEnableC4DistanceText}
        };

        for (size_t i = 0; i < checkboxes.size(); ++i) {
            ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + i * ySpacing });
            custom.Checkbox(checkboxes[i].first, checkboxes[i].second);
        }

        ImGui::EndChildFrame();
    }

    ImGui::SameLine();

    // Second child frame
    {
        ImGui::BeginChildFrame(ImGui::GetID("Bomb-Visuals-Frame2"), ImVec2(375, 386));

        const float columnWidth = 180.0f;
        const float spacing = 70.0f;

        std::vector<std::pair<const char*, ImVec4*>> bomb_esp_colors = {
            {"Planted Box Color", &Data::Esp::Bomb::m_clPlantedC4BoxColor},
            {"Dropped Box Color", &Data::Esp::Bomb::m_clDroppedC4BoxColor},
            {"Snap Lines Color", &Data::Esp::Bomb::m_clC4LineColor},
            {"Distance Text Color", &Data::Esp::Bomb::m_clDistanceTextColor}
        };

        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, columnWidth);

        for (size_t i = 0; i < bomb_esp_colors.size(); ++i) {
            custom.ColorEditor(bomb_esp_colors[i].first, bomb_esp_colors[i].second);

            if (i == bomb_esp_colors.size() / 2 - 1) {
                ImGui::NextColumn();
            }
        }

        ImGui::Columns(1);

        ImGui::Spacing();
        ImGui::Separator();

        custom.LeaveLine(2);
        ImGui::Text(" Line Position");

        custom.RadioButtonGroup(
            &Data::Esp::Bomb::m_iCurrentLinePosIndex,
            Data::Esp::Bomb::m_AvailableSnapLinesPos,
            IM_ARRAYSIZE(Data::Esp::Bomb::m_AvailableSnapLinesPos)
        );

        custom.LeaveLine(2);

        custom.SliderFloat("    Box Thickness", &Data::Esp::Bomb::m_flBoxThickness, 1.0f, 10.0f);
        custom.LeaveLine(1);

        custom.SliderFloat("    Line Thickness", &Data::Esp::Bomb::m_flLineThickness, 1.0f, 10.0f);
        custom.LeaveLine(1);

        ImGui::EndChildFrame();
    }
}

VOID Menu::CreateWorldEspInterface()
{
    const float xOffset = 10.0f;
    const float ySpacing = 29.0f;

    // First child frame
    {
        ImGui::BeginChildFrame(ImGui::GetID("World-Visuals-Frame"), ImVec2(200, 386));
        ImVec2 startPos = ImGui::GetCursorPos();

        std::vector<std::pair<const char*, bool*>> checkboxes = {
            {"Enable World Esp", &Data::Esp::m_bWorldEsp},
            {"Weapons", &Data::Esp::World::m_bEnableDroppedWeaponEsp},
            {"Projectiles", &Data::Esp::World::m_bEnableProjectilesEsp},
            {"Chicken", &Data::Esp::World::m_bEnableChickenEsp}
        };

        for (size_t i = 0; i < checkboxes.size(); ++i) {
            ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + i * ySpacing });
            custom.Checkbox(checkboxes[i].first, checkboxes[i].second);
        }

        ImGui::EndChildFrame();
    }

    ImGui::SameLine();

    // Second Child Frame
    {
        ImGui::BeginChildFrame(ImGui::GetID("World-Visuals-Frame2"), ImVec2(375, 386));
        const float columnWidth = 180.0f;

        std::vector<std::pair<const char*, ImVec4*>> world_esp_colors = {
            {"Weapon Text", &Data::Esp::World::m_clWeaponEspTextColor},
            {"Weapon Stroke", &Data::Esp::World::m_clWeaponEspTextStrokeColor},
            {"Projectiles Text", &Data::Esp::World::m_clProjectilesEspTextColor},
            {"Projectiles Stroke", &Data::Esp::World::m_clProjectilesEspTextStrokeColor},
            {"Chicken Text", &Data::Esp::World::m_clChickenEspTextColor},
            {"Chicken Stroke", &Data::Esp::World::m_clChickenEspTextStrokeColor},
        };

        // Create columns for the layout
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::SetColumnWidth(1, columnWidth);

        for (size_t i = 0; i < world_esp_colors.size(); i += 2) {
            custom.ColorEditor(world_esp_colors[i].first, world_esp_colors[i].second);

            ImGui::NextColumn();
            custom.ColorEditor(world_esp_colors[i + 1].first, world_esp_colors[i + 1].second);

            ImGui::NextColumn();
        }

        ImGui::Columns(1);

        ImGui::EndChildFrame();
    }
}

VOID Menu::CreateMemoryInterface()
{
    const float xOffset = 10.0f; 
    const float ySpacing = 10.0f; 

    // First child frame
    ImGui::SetCursorPos(ImVec2(85, 65));
    ImGui::BeginChildFrame(ImGui::GetID("Memory-Cheats-Frame"), ImVec2(585, 386));
    ImVec2 startPos = ImGui::GetCursorPos();

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + ySpacing });
    custom.Checkbox("Enable Antiflash", &Data::Memory::m_bEnableAntiflash);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 35.0f });
    custom.SliderFloat("Flash Alpha", &Data::Memory::m_flFlashAlpha, 0.0f, 255.0f);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 55.0f });
    custom.Checkbox("Enable Fov Changer", &Data::Memory::m_bEnableFovChanger);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 80.0f });
    custom.SliderInt("Field of View", &Data::Fov::m_iDefaultFov, 58, 140);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 100.0f });
    custom.Checkbox("Enable Bhop", &Data::Memory::m_bEnableBhop);

    ImGui::EndChildFrame();
}

VOID Menu::CreateAimbotInterface()
{
    const float xOffset = 10.0f;
    ImGui::SetCursorPos(ImVec2(85, 65));
    ImGui::BeginChildFrame(ImGui::GetID("Aimbot-Cheat-Frame"), ImVec2(585, 386));
    ImVec2 startPos = ImGui::GetCursorPos();

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 10.0f });
    custom.Checkbox("Enable Aimbot", &Data::Aimbot::m_bAimbot);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 35.0f });
    custom.Checkbox("Hotkey", &Data::Aimbot::m_bEnableHotKey);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 60.0f });
    custom.Checkbox("Team Check", &Data::Aimbot::m_bTeamCheck);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 85.0f });
    custom.Checkbox("Fov Based", &Data::Aimbot::m_bFovBased);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 110.0f });
    custom.Checkbox("Fov Circle", &Data::Aimbot::m_bShowFovCircle);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 135.0f });
    custom.SliderFloat("Fov Range", &Data::Aimbot::m_flFov, 10, 360);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 155.0f });
    custom.SliderFloat("Fov Circle Thickness", &Data::Aimbot::m_flFovCircleThickness, 1.0f, 20.0f);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 175.0f });
    custom.ColorEditor("Circle Color", &Data::Aimbot::m_clFovCircleColor);

    /*ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 205.0f });
    custom.Checkbox("Add Smoothness", &Data::Aimbot::m_bAddSmoothness);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 230.0f });
    custom.SliderFloat("Smoothness", &Data::Aimbot::m_flSmoothness, 0.1, 1.0);*/

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 205 });
    /*custom.ComboBox(
        "Target",
        Data::Aimbot::m_AimPositions[Data::Aimbot::m_iCurrentAimPosIndex],
        &Data::Aimbot::m_iCurrentAimPosIndex,
        Data::Aimbot::m_AimPositions,
        IM_ARRAYSIZE(Data::Aimbot::m_AimPositions)
    );*/

    ImGui::Text("Current Target Aim Position is Head.\nWe will be Adding More Target Aim positions in Future Updates.");

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 240.0f });
    custom.Hotkey(&Data::Aimbot::m_iCurrentKey, ImVec2(120, 30));

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 275.0f });
    ImGui::Text("  Aimbot Hotkey");


    ImGui::EndChildFrame();
}

VOID Menu::CreateTriggerbotInterface()
{
    const float xOffset = 10.0f;

    // First child frame
    ImGui::SetCursorPos(ImVec2(85, 65));
    ImGui::BeginChildFrame(ImGui::GetID("Triggerbot-Cheat-Frame"), ImVec2(585, 386));
    ImVec2 startPos = ImGui::GetCursorPos();

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 10.0f });
    custom.Checkbox("Enable Triggerbot", &Data::TriggerBot::m_bEnableTriggerBot);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 35.0f });
    custom.Checkbox("Enable Hotkey", &Data::TriggerBot::m_bEnableHotKey);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 60.0f });
    custom.Checkbox("Team Check", &Data::TriggerBot::m_bEnableTeamCheck);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 90.0f });
    custom.Hotkey(&Data::TriggerBot::m_iCurrentKey);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 125.0f });
    ImGui::Text("I'm not sure why, but the hotkey system isn't working as expected.");

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 140.0f });
    ImGui::Text("Default Key for Triggerbot is Left Shift.");


    ImGui::EndChildFrame();
}

VOID Menu::CreateMiscInterface()
{
    const float xOffset = 10.0f;

    // First child frame
    ImGui::SetCursorPos(ImVec2(85, 65));
    ImGui::BeginChildFrame(ImGui::GetID("Misc-Cheats-Frame"), ImVec2(585, 386));
    ImVec2 startPos = ImGui::GetCursorPos();

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 10.0f });
    custom.Checkbox("Enable Rcs", &Data::Rcs::m_bRcs);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 35.0f });
    custom.Checkbox("Enable Jumpshot", &Data::JumpShot::m_bJumpShot);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 60.0f });
    custom.Checkbox("Enable Anti-Afk", &Data::AntiAfk::m_bEnableAntiAfk);


    ImGui::EndChildFrame();
}

VOID Menu::CreateLocalClientInfoInterface()
{
    const float xOffset = 10.0f;
    ImGui::SetCursorPos(ImVec2(85, 65));
    ImGui::BeginChildFrame(ImGui::GetID("Localplayer-Frame"), ImVec2(585, 386));

    if (ImGui::BeginTable("LocalInfoTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        // Column headers (optional)
        ImGui::TableSetupColumn("Local Player");
        ImGui::TableSetupColumn("Value");
        ImGui::TableHeadersRow();

        // Username
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Username");
        ImGui::TableNextColumn(); ImGui::Text("%s", cPlayer.Name);

        // Health
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Health");
        ImGui::TableNextColumn(); ImGui::Text("%d", cPlayer.Health);

        // Ping
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Ping");
        ImGui::TableNextColumn(); ImGui::Text("%i", cPlayer.Ping);

        // Sensitivity
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Sensitivity");
        ImGui::TableNextColumn(); ImGui::Text("%.2f", cPlayer.Sensitivity);

        // Map Name
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Mapname");
        ImGui::TableNextColumn(); ImGui::Text("%s", cGame.MapName);

        // Team
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Team");
        ImGui::TableNextColumn();
        switch (cPlayer.Team)
        {
        case 1: ImGui::TextColored(Data::Game::m_clSpectatorColor, "Spectator"); break;
        case 2: ImGui::TextColored(Data::Game::m_clTerroristColor, "Terrorist"); break;
        case 3: ImGui::TextColored(Data::Game::m_clCounterTerroristColor, "Counter-Terrorist"); break;
        default: ImGui::Text("~Unknown");
        }

        // Status
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Status");
        ImGui::TableNextColumn();
        if (cPlayer.IsAlive)
            ImGui::Text("Alive");
        else if (cPlayer.IsDead)
            ImGui::Text("Dead");
        else
            ImGui::Text("In Lobby");

        // Armor
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Armor");
        ImGui::TableNextColumn();
        ImGui::TextColored(Data::Game::m_clCounterTerroristColor, "%i", cPlayer.Armor);

        // Position
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Position (x, y, z)");
        ImGui::TableNextColumn();
        ImGui::Text("%.2f, %.2f, %.2f", cPlayer.Position.x, cPlayer.Position.y, cPlayer.Position.z);

        // Player State
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Player State");
        ImGui::TableNextColumn();
        if (cPlayer.IsCrouched)
            ImGui::TextColored(ImColor(34, 151, 255, 255), "Crouched");
        else if (cPlayer.IsStanding)
            ImGui::TextColored(ImColor(251, 206, 112, 255), "Standing");
        else if (cPlayer.IsInAir)
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Jumping");
        else if (cPlayer.IsNoCliped)
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "No Clip");
        else
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Neutral");

        // Gun State
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Gun State");
        ImGui::TableNextColumn();
        if (cPlayer.IsScoped && !cPlayer.IsFiring)
            ImGui::TextColored(ImColor(34, 151, 255, 255), "Scoped");
        else if (cPlayer.IsFiring && !cPlayer.IsScoped)
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Firing");
        else if (cPlayer.IsScoped && cPlayer.IsFiring)
        {
            ImGui::TextColored(ImColor(34, 151, 255, 255), "Scoped");
            ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "and");
            ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Firing");
        }
        else
            ImGui::Text("Neutral");

        // Bomb Status
        ImGui::TableNextRow();
        ImGui::TableNextColumn(); ImGui::Text("Bomb Status");
        ImGui::TableNextColumn();
        if (cGame.IsBombPlanted)
        {
            const char* label = "Planted";
            ImVec4 color = ImVec4(1, 0, 0, 1);

            if (cGame.IsBombBeingDefused)
            {
                label = "Defusing";
                color = RgbToImVec4(34, 151, 255, 255);
            }

            ImGui::TextColored(color, label);

            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::Text("Bomb Site");
            ImGui::TableNextColumn();
            if (cC4.GetBombSite() == 0)
                ImGui::Text("A");
            else if (cC4.GetBombSite() == 1)
                ImGui::Text("B");
        }
        else
        {
            if (cGame.IsBombDropped)
                ImGui::TextColored(ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f), "Dropped");
            else
                ImGui::TextColored(ImVec4(0, 183, 0, 255), "Not-Planted");
        }

        ImGui::EndTable();
    }

    ImGui::EndChildFrame();
}

VOID Menu::CreateEntitiesInterface()
{
    const float xOffset = 10.0f;
    ImGui::SetCursorPos(ImVec2(85, 65));
    ImGui::BeginChildFrame(ImGui::GetID("Entities-Info-Frame"), ImVec2(585, 386));
    ImVec2 startPos = ImGui::GetCursorPos();

    if (ImGui::BeginTable("EntityTable", 8, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("SN", ImGuiTableColumnFlags_WidthFixed, 20.0f);
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::TableSetupColumn("Health", ImGuiTableColumnFlags_WidthFixed, 50.0f);
        ImGui::TableSetupColumn("Armor", ImGuiTableColumnFlags_WidthFixed, 50.0f);
        ImGui::TableSetupColumn("Team", ImGuiTableColumnFlags_WidthFixed, 50.0f);
        ImGui::TableSetupColumn("Status", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("Ping", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("Gun State", ImGuiTableColumnFlags_WidthFixed, 120.0f);
        ImGui::TableHeadersRow();

        for (int i = 1; i < 64; i++)
        {
            UINTPTR ListEntry = Driver::RPM<UINTPTR>(cGame.EntityList + (8 * (i & 0x7FFF) >> 9) + 16);
            if (!ListEntry)
                continue;

            UINTPTR CCSPlayerController = Driver::RPM<UINTPTR>(ListEntry + 120 * (i & 0x1FF));
            if (!CCSPlayerController)
                continue;

            UINTPTR PawnHandle = Driver::RPM<UINTPTR>(CCSPlayerController + Offsets::m_hPlayerPawn);
            if (!PawnHandle)
                continue;

            UINTPTR ListEntry2 = Driver::RPM<UINTPTR>(cGame.EntityList + 0x8 * ((PawnHandle & 0x7FFF) >> 9) + 16);
            if (!ListEntry2)
                continue;

            UINTPTR CCSPlayerPawn = Driver::RPM<UINTPTR>(ListEntry2 + 120 * (PawnHandle & 0x1FF));
            if (!CCSPlayerPawn)
                continue;

            cEntities->READ(CCSPlayerPawn, CCSPlayerController);

            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::Text("%d", i); // Entity Index              
            ImGui::TableNextColumn(); ImGui::Text("%s", cEntities->Names); // Entity Name
            ImGui::TableNextColumn(); ImGui::Text("%d", cEntities->Health); // Entity Health
            ImGui::TableNextColumn(); ImGui::Text("%d", cEntities->Armor); // Entity Armor

            switch (cEntities->Team)
            {
            case TEAM_SPECTATOR: if (cEntities->Team)ImGui::TableNextColumn(); ImGui::Text("%s", "Spectator"); break;
            case TEAM_TERRORIST: if (cEntities->Team)ImGui::TableNextColumn(); ImGui::Text("%s", "T"); break;
            case TEAM_COUNTERTERRORIST: if (cEntities->Team)ImGui::TableNextColumn(); ImGui::Text("%s", "CT"); break;
            }


            // Entity Status 
            if (cEntities->Alive) { ImGui::TableNextColumn(); ImGui::Text("%s", "Alive"); }
            else if (cEntities->Dead) { ImGui::TableNextColumn(); ImGui::Text("%s", "Dead"); }

            ImGui::TableNextColumn(); ImGui::Text("%d", cEntities->Ping); // Entity ping

            // Entity Owner Gun State 
            if (cEntities->IsFiring && !cEntities->IsScoped) { ImGui::TableNextColumn(); ImGui::Text("%s", "Firing"); }
            else if (!cEntities->IsFiring && cEntities->IsScoped) { ImGui::TableNextColumn(); ImGui::Text("%s", "Scoped"); }
            else if (cEntities->IsFiring && cEntities->IsScoped) { ImGui::TableNextColumn(); ImGui::Text("%s", "Scoped and Firing"); }
            else { ImGui::TableNextColumn(); ImGui::Text("%s", "Neutral"); }

        }

        ImGui::EndTable();
    }

    ImGui::EndChildFrame();
}

VOID Menu::CreateConfigManagerInterface()
{
    DataManager cheatConfig;
    cheatConfig.ScanDirectoryForJsonFiles(Data::folderName);
    const float xOffset = 10.0f;

    ImGui::SetCursorPos(ImVec2(85, 65));
    ImGui::BeginChildFrame(ImGui::GetID("1-Frame"), ImVec2(585, 386));
    ImVec2 startPos = ImGui::GetCursorPos();

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 10.0f });
    ImGui::Text("Config/Data Manager");

    static char configFileNameBuffer[128] = "config";

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 30.0f });
    if (ImGui::Button("Reload JSON Files", ImVec2(130, 30)))
    {
        cheatConfig.ScanDirectoryForJsonFiles(Data::folderName);
    }

    if (!jsonFiles.empty())
    {
        static int selectedFileIndex = 0;
        std::vector<const char*> items;
        for (size_t i = 0; i < jsonFiles.size(); ++i)
        {
            items.push_back(jsonFiles[i].c_str());
        }

        const char* selectedFileName = items[selectedFileIndex];
        ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 70.0f });
        if (custom.ComboBox("Available Config Files", selectedFileName, &selectedFileIndex, items.data(), items.size()))
        {
            Data::fileName = jsonFiles[selectedFileIndex];
        }
    }
    else
    {
        ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 70.0f });
        ImGui::Text("No JSON files found.");
    }

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(50, 50, 50).Value);
    ImGui::PushStyleColor(ImGuiCol_Border, ImColor(10, 10, 10).Value);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);

ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 100.0f });
if (ImGui::InputText("Config File Name", configFileNameBuffer, sizeof(configFileNameBuffer)))
{
    Data::fileName = std::string(configFileNameBuffer);

    if (!Data::fileName.ends_with(".json"))
    {
        Data::fileName += ".json";
    }
}

ImGui::PopStyleColor(2);
ImGui::PopStyleVar(1);


if (!Data::fileName.ends_with(".json"))
{
    Data::fileName += ".json";
}

ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 130.0f });
if (ImGui::Button("Save Config", ImVec2(100, 30)))
{
    std::cout << " [+] Data Manager\n";
    std::cout << std::endl;
    console.SetConsoleTextColor(CYAN);

    std::cout << "  => Saved Config: " << Data::fileName.substr(0, Data::fileName.size() - 5) << std::endl;
    std::cout << std::endl;

    SaveCheatData();
}

ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 170.0f });
if (ImGui::Button("Load Config", ImVec2(100, 30)))
{
    console.SetConsoleTextColor(DARK_CYAN);
    std::cout << std::endl;
    std::cout << " [+] Data Manager\n";
    std::cout << std::endl;
    console.SetConsoleTextColor(CYAN);

    std::cout << "  => Loaded Config: " << Data::fileName.substr(0, Data::fileName.size() - 5) << std::endl;
    std::cout << std::endl;

    LoadCheatData();
}

ImGui::EndChildFrame();
}

VOID Menu::CreateMenuSettingsInterface()
{
    const float xOffset = 10.0f;

    ImGui::SetCursorPos(ImVec2(85, 65));
    ImGui::BeginChildFrame(ImGui::GetID("Settings-Frame"), ImVec2(585, 386));
    ImVec2 startPos = ImGui::GetCursorPos();

    float color[4] = {
        custom.accent_color[0] / 255.0f,
        custom.accent_color[1] / 255.0f,
        custom.accent_color[2] / 255.0f,
        custom.accent_color[3] / 255.0f
    };

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 10.0f });
    custom.ColorEditor("Accent Color", (ImVec4*)color);

    for (int i = 0; i < 4; i++)
    {
        custom.accent_color[i] = static_cast<int>(color[i] * 255.0f);
    }

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 35.0f });
    custom.Checkbox("Show Console", &Flags::g_showConsole);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 60.0f });
    custom.Checkbox("Show Warning", &Flags::g_showWarningBox);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 85.0f });
    custom.Hotkey(&Panickey::CLOSEPROGRAM);
    ImGui::SameLine();
    ImGui::SetCursorPos({ startPos.x + 120.0f, startPos.y + 90.0f });
    ImGui::Text("Close/End");

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 120.0f });
    custom.Hotkey(&Panickey::HIDEMENU);
    ImGui::SameLine();
    ImGui::SetCursorPos({ startPos.x + 120.0f, startPos.y + 125.0f });
    ImGui::Text("Hide Menu");

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 160.0f });
    if (ImGui::Button("Save Settings", ImVec2(130, 30)))
    {
        SaveSettings();
    }

    ImGui::EndChildFrame();
}

VOID Menu::CreateOffsetsUpdaterInterface()
{
    const float xOffset = 10.0f;

    ImGui::SetCursorPos(ImVec2(85, 65));
    ImGui::BeginChildFrame(ImGui::GetID("Offsets-Frame"), ImVec2(585, 386));
    ImVec2 startPos = ImGui::GetCursorPos();

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 10.0f });
    if(ImGui::Button("Download/Update Latest Offsets", ImVec2(250, 40)))
    {
        if (updater.CheckAndDownload())
        {
            ShowMessage(L"Offsets successfully fetched and downloaded", L"Offsets Manager");
        }
        else
        {
            ShowMessage(L"Failed to fetch and download offsets", L"Offsets Manager");
        }
    }

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 55.0f });
    ImGui::Text("If you're unable to download offsets using the button above, try downloading them");
    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 70.0f });
    ImGui::Text("manually from the provided links.");

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 90.0f });
    ImGui::TextLinkOpenURL("Offsets.json", OffsetsJson);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 115.0f });
    ImGui::TextLinkOpenURL("Client_Dll.json", ClientDllJson);

    ImGui::SetCursorPos({ startPos.x + xOffset, startPos.y + 140.0f });
    ImGui::TextLinkOpenURL("Buttons.json", ButtonsJson);

    ImGui::EndChildFrame();
}

// Menu Entry Point
VOID Menu::Render()
{
    // KEYS
    {
        if (GetAsyncKeyState(Panickey::HIDEMENU) & 1) {
            Flags::m_bIsVisible = !Flags::m_bIsVisible; // Hide/Unhide Menu;
        }

        if (GetAsyncKeyState(Panickey::CLOSEPROGRAM) & 1) {
            ExitProcess(0);
        }

        if (GetAsyncKeyState(Panickey::VISUAL_CHEATS) & 1) {
            Flags::VisualCheats = !Flags::VisualCheats;
        }

        if (GetAsyncKeyState(Panickey::MEMORY_CHEATS) & 1) {
            Flags::MemoryCheats = !Flags::MemoryCheats;
        }

        if (GetAsyncKeyState(Panickey::AIM_CHEATS) & 1) {
            Flags::AimCheats = !Flags::AimCheats;
        }
    }

    if (Flags::m_bIsVisible)
    {
        // Start the ImGui window
        this->ApplyStyles();
        ImGui::SetNextWindowSize(ImVec2(MIN_MENU_WIDTH, MIN_MENU_HEIGHT));
        ImGui::Begin("Menu", &Flags::m_bIsRunning, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);

        const ImVec2 pos = ImGui::GetWindowPos();
        ImDrawList* draw = ImGui::GetWindowDrawList();

        float leftMargin = pos.x + 20.0f;
        float rightMargin = pos.x + 50.0f;

        // Shapes
        {
            // Top Horizontal Lines;
            draw->AddLine(pos + ImVec2(71, 55), pos + ImVec2(680, 55), ImColor(35, 35, 35, 255), 0.1f);
            draw->AddLine(pos + ImVec2(71, 55), pos + ImVec2(0, 55), ImColor(35, 35, 35, 255), 0.1f);

            // Main Menu Shapes and Line;
            draw->AddRectFilled(ImVec2(pos.x + 71, pos.y + 56), ImVec2(pos.x + 680, pos.y + 470), ImColor(10, 10, 10, 255), 2.f, ImDrawFlags_RoundCornersBottomRight);
            draw->AddRectFilled(pos, ImVec2(pos.x + 70, pos.y + 470), ImColor(14, 14, 14, 255), 5.0f, ImDrawFlags_RoundCornersLeft);
            draw->AddLine(ImVec2(pos.x + 70, pos.y), ImVec2(pos.x + 70, pos.y + 470), ImColor(35, 35, 35, 255), 0.1f);
            draw->AddRectFilled(pos + ImVec2(71, 0), pos + ImVec2(680, 55), ImColor(14, 14, 14, 255), 5.0f, ImDrawFlags_RoundCornersTopRight);

            // Left Tab-Bar Vertical Lines; 
            draw->AddLine(ImVec2(leftMargin, pos.y + 115), ImVec2(rightMargin, pos.y + 115), ImColor(255, 255, 255, 70), 2.f);
            draw->AddLine(ImVec2(leftMargin, pos.y + 175), ImVec2(rightMargin, pos.y + 175), ImColor(255, 255, 255, 70), 2.f);
            draw->AddLine(ImVec2(leftMargin, pos.y + 235), ImVec2(rightMargin, pos.y + 235), ImColor(255, 255, 255, 70), 2.f);
            draw->AddLine(ImVec2(leftMargin, pos.y + 295), ImVec2(rightMargin, pos.y + 295), ImColor(255, 255, 255, 70), 2.f);
            draw->AddLine(ImVec2(leftMargin, pos.y + 355), ImVec2(rightMargin, pos.y + 355), ImColor(255, 255, 255, 70), 2.f);

            // Left Tab-Bar Vertical Shapes; 
            ImColor CircleColor(custom.accent_color[0], custom.accent_color[1], custom.accent_color[2], custom.accent_color[3]);
            draw->AddCircleFilled(pos + ImVec2(35, 433), 16.f, CircleColor, 60.f);
           // draw->AddCircle(pos + ImVec2(35, 433), 17.0f, ImColor(10, 10, 10, 225), 60.f);
        }

        // Main Logo
        {
            ImGui::SetCursorPos(ImVec2(10, 13));
            ImGui::Image((ImTextureID)Resources::Delta_Logo, ImVec2(50, 50));
        }

        // Left Vertical Tab-Bar;
        {
            ImGui::SetCursorPos(ImVec2(10, 63));
            ImGui::BeginGroup();

            if (custom.Selection("Visuals", (ImTextureID)Resources::visuals_image, 0 == tab_selection_count))
            {
                tab_selection_count = 0;
            }

            if (custom.Selection("Legit", (ImTextureID)Resources::legit_image, 1 == tab_selection_count))
            {
                tab_selection_count = 1;
            }

            if (custom.Selection("Rage", (ImTextureID)Resources::rage_image, 2 == tab_selection_count))
            {
                tab_selection_count = 2;
            }

            if (custom.Selection("CPlayerInfo", (ImTextureID)Resources::players_image, 3 == tab_selection_count))
            {
                tab_selection_count = 3;
            }

            if (custom.Selection("Miscs", (ImTextureID)Resources::misc_image, 4 == tab_selection_count))
            {
                tab_selection_count = 4;
            }

            if (custom.Selection("Settings", (ImTextureID)Resources::settings_image, 5 == tab_selection_count))
            {
                tab_selection_count = 5;
            }

            ImGui::EndGroup();
        }

        // Main Content
        {

            ImGui::SetCursorPos(ImVec2(85, 15));
            ImGui::BeginGroup();

            // Visuals
            if (tab_selection_count == 0)
            {
                // Group Selection Logic
                if (custom.Group("Player", Groups::PLAYER == visuals_group_count))
                    visuals_group_count = Groups::PLAYER;
                ImGui::SameLine();
                if (custom.Group("Bomb", Groups::BOMB == visuals_group_count))
                    visuals_group_count = Groups::BOMB;
                ImGui::SameLine();
                if (custom.Group("World", Groups::WORLD == visuals_group_count))
                    visuals_group_count = Groups::WORLD;

                // Group Content Rendering
                ImGui::SetCursorPos(ImVec2(85, 70));
                if (visuals_group_count == Groups::PLAYER) // Player Visuals Menu
                {
                    this->CreatePlayerEspInterface();
                }
                else if (visuals_group_count == Groups::BOMB) // Bomb Visuals Menu
                {
                    this->CreateBombEspInterface();
                }
                else if (visuals_group_count == Groups::WORLD) // World Visuals Menu
                {
                    this->CreateWorldEspInterface();
                }
            }

            // Legit
            if (tab_selection_count == 1)
            {
                // Group Selection Logic
                if (custom.Group("Aimbot", Groups::AIMBOT == legit_group_count))
                    legit_group_count = Groups::AIMBOT;
                ImGui::SameLine();
                if (custom.Group("Triggerbot", Groups::TRIGGERBOT == legit_group_count))
                    legit_group_count = Groups::TRIGGERBOT;

                ImGui::SetCursorPos(ImVec2(85, 70));
                if (legit_group_count == Groups::AIMBOT)
                {
                    this->CreateAimbotInterface();
                }
                else if (legit_group_count == Groups::TRIGGERBOT)
                {
                    this->CreateTriggerbotInterface();
                }
            }

            // Rage/Memory
            if (tab_selection_count == 2)
            {
                // Group Selection Logic
                if (custom.Group("Memory", Groups::MEMORY == rage_group_count))
                    rage_group_count = Groups::MEMORY;;

                ImGui::SetCursorPos(ImVec2(85, 70));
                if (rage_group_count == Groups::MEMORY)
                    this->CreateMemoryInterface();
            }

            // Local player and Game
            if (tab_selection_count == 3)
            {
                if (custom.Group("Player", Groups::LOCALPLAYER == cplayerinfo_group_count))
                    cplayerinfo_group_count = Groups::LOCALPLAYER;
                ImGui::SameLine();
                if (custom.Group("Entities", Groups::ENTITYLIST == cplayerinfo_group_count))
                    cplayerinfo_group_count = Groups::ENTITYLIST;


                if (cplayerinfo_group_count == Groups::LOCALPLAYER)
                    this->CreateLocalClientInfoInterface();

                if (cplayerinfo_group_count == Groups::ENTITYLIST)
                    this->CreateEntitiesInterface();
            }

            // Miscs Tab
            if (tab_selection_count == 4)
            {
                if (custom.Group("Misc", Groups::MISCS == misc_group_count))
                    misc_group_count = Groups::MISCS;

                ImGui::SetCursorPos(ImVec2(85, 70));
                if (misc_group_count == Groups::MISCS)
                {
                    this->CreateMiscInterface();
                }
            }

            // Settings
            if (tab_selection_count == 5)
            {
                if (custom.Group("Config", Groups::CONFIG == settings_group_count))
                    settings_group_count = Groups::CONFIG;
                ImGui::SameLine();
                if (custom.Group("Offsets", Groups::OFFSETS == settings_group_count))
                    settings_group_count = Groups::OFFSETS;
                ImGui::SameLine();
                if (custom.Group("Others", Groups::OTHER_SETTINGS == settings_group_count))
                    settings_group_count = Groups::OTHER_SETTINGS;

                if (settings_group_count == Groups::CONFIG)
                {
                    this->CreateConfigManagerInterface();
                }

                if (settings_group_count == Groups::OFFSETS)
                {
                    this->CreateOffsetsUpdaterInterface();
                }

                if (settings_group_count == Groups::OTHER_SETTINGS)
                {
                    this->CreateMenuSettingsInterface();
                }
            }


            ImGui::EndGroup();
        }


        ImGui::End();
    }


}
