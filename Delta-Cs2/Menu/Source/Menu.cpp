#define IMGUI_DEFINE_MATH_OPERATORS
#include <Menu/Menu.h>
#include <Menu/Custom.h>
#include <Cheats/Data.h>

Custom custom;

// Designing Menu

VOID Menu::ApplyStyles()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 0.0f;
    style.WindowRounding = 10.0f;
    style.ScrollbarSize = 2.0f;
    style.Colors[ImGuiCol_Border] = ImColor(255, 255, 255);
    style.Colors[ImGuiCol_FrameBg] = ImColor(14, 14, 14);
}


// Menu Elements
VOID Menu::CreatePlayerEspInterfaces()
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

VOID Menu::CreateBombEspInterfaces()
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

VOID Menu::CreateWorldEspInterfaces()
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

// Memory Cheats Interface
VOID Menu::CreateMemoryInterfaces()
{
    const float xOffset = 10.0f;  // Horizontal spacing
    const float ySpacing = 10.0f; // Vertical spacing between checkboxes

    // First child frame
    ImGui::SetCursorPos(ImVec2(85, 65));
    ImGui::BeginChildFrame(ImGui::GetID("Memory-Cheats-Frame"), ImVec2(585, 386));
    ImVec2 startPos = ImGui::GetCursorPos();

    // Draw checkboxes in a vertical layout
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

// Menu Entry Point
VOID Menu::Render()
{
    if (GetAsyncKeyState(VK_INSERT) & 1) {
        Flags::m_bIsVisible = !Flags::m_bIsVisible; // Hide/Unhide Menu;
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
            draw->AddCircleFilled(pos + ImVec2(35, 433), 16.f, ImColor(0, 0, 0, 50), 60.f);
            draw->AddCircle(pos + ImVec2(35, 433), 17.f, ImColor(255, 255, 255, 15), 60.f);
        }

        // Main Logo
        {
            ImGui::SetCursorPos(ImVec2(10, 3));
            ImGui::Image((ImTextureID)resources::cheat_logo2, ImVec2(50, 50));
        }

        // Left Vertical Tab-Bar;
        {
            ImGui::SetCursorPos(ImVec2(10, 63));
            ImGui::BeginGroup();

            if (custom.Selection("Visuals", (ImTextureID)resources::visuals_image, 0 == tab_selection_count))
            {
                tab_selection_count = 0;
            }

            if (custom.Selection("Legit", (ImTextureID)resources::legit_image, 1 == tab_selection_count))
            {
                tab_selection_count = 1;
            }

            if (custom.Selection("Rage", (ImTextureID)resources::rage_image, 2 == tab_selection_count))
            {
                tab_selection_count = 2;
            }

            if (custom.Selection("Movements", (ImTextureID)resources::players_image, 3 == tab_selection_count))
            {
                tab_selection_count = 3;
            }

            if (custom.Selection("Miscs", (ImTextureID)resources::misc_image, 4 == tab_selection_count))
            {
                tab_selection_count = 4;
            }

            if (custom.Selection("Settings", (ImTextureID)resources::settings_image, 5 == tab_selection_count))
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
                    this->CreatePlayerEspInterfaces();
                }
                else if (visuals_group_count == Groups::BOMB) // Bomb Visuals Menu
                {
                    this->CreateBombEspInterfaces();
                }
                else if (visuals_group_count == Groups::WORLD) // World Visuals Menu
                {
                    this->CreateWorldEspInterfaces();
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
                ImGui::SameLine();
                if (custom.Group("Misc", Groups::MISC == legit_group_count))
                    legit_group_count = Groups::MISC;

                ImGui::SetCursorPos(ImVec2(85, 70));
                if (legit_group_count == Groups::AIMBOT)
                {

                }
                else if (legit_group_count == Groups::TRIGGERBOT)
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

                    ImGui::EndChildFrame();
                }
                else if (legit_group_count == Groups::MISC)
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

                    ImGui::EndChildFrame();
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
                    this->CreateMemoryInterfaces();
            }

            // Settings
            if (tab_selection_count == 5)
            {
                if (custom.Group("Menu", Groups::SETTINGS == settings_group_count))
                    settings_group_count = Groups::SETTINGS;

                if (settings_group_count == Groups::SETTINGS)
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

                    ImGui::EndChildFrame();
                }            
            }


            ImGui::EndGroup();
        }


        ImGui::End();
    }


}