#include <Utils/Overlay.h>
#include <Globals/Globals.h>
#include <Utils/Process.hpp>
#include <Utils/Console.hpp>
#include <Menu/Menu.h>
#include <Cheats/mainclp.h>
#include <Main/Driver.h>
#include <SDK/CGame.h>
#include <Utils/DataManager.h>
#include <Utils/Updater.h>

VOID CreateLogs() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    char timeBuffer[26]; 
    ctime_s(timeBuffer, sizeof(timeBuffer), &time);


    std::filesystem::path dir = "bin";
    std::filesystem::path filePath = dir / "logs.ini"; 

    if (!std::filesystem::exists(dir)) {
        std::filesystem::create_directory(dir);
    }

    std::ofstream file(filePath, std::ios::out);

    if (file.is_open()) {
        file << "Last run: " << timeBuffer;
        file << "Local Client Name: " << cPlayer.Name << '\n';
        file << "Client Build No.: " << cGame.BuildNumber << '\n';
        file.close();
    }
}


using namespace std;
INT APIENTRY WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ LPSTR cmd_line, _In_ int cmd_show)
{
    LoadSettings();
    if (Flags::g_showConsole) { console.CreateConsoleWindow(L"Delta-Cs2"); }
    Overlay overlay(L"Delta Cheat Overlay", L"DELTA_CS2_OVERLAY_CLASS", SCREEN_WIDTH, SCREEN_HEIGHT);

    console.SetConsoleTextColor(YELLOW);

    if (CS2::ProcID <= 0)
    {
        std::cout << " [+] Failed to find designated Process (cs2.exe)\n";
        ShowErrorBox(L"Failed to find designated Process (cs2.exe)\n", L"Driver Error");
        std::cin.get();
    }
    else if (CS2::ProcID > 0 && Flags::g_showWarningBox)
    {
        ShowWarningBox(L"Warning: Using cheats can lead to account bans\nWe do not recommend using cheats.\nProceed at your own risk.", L"Delta-Cs2");
    }

    // Searchs for available Driver handle (Delta or Synapse)
    Driver::SearchForHandle();

    // Attaches to the Process if HANDLE != INVALID_HANDLE_VALUE
    if (Driver::Attach(Driver::Handle, CS2::ProcID) == true)
    {
        CS2::ClientDll = cs2.GetModuleBaseAddress(CS2::ProcID, L"client.dll");
        CS2::Engine2Dll = cs2.GetModuleBaseAddress(CS2::ProcID, L"engine2.dll");
        CS2::MatchMakingDll = cs2.GetModuleBaseAddress(CS2::ProcID, L"matchmaking.dll");
        CS2::ServerDll = cs2.GetModuleBaseAddress(CS2::ProcID, L"server.dll");

        cPlayer.READ(CS2::ClientDll);
        cGame.READ(CS2::ClientDll, CS2::MatchMakingDll);
        CreateLogs();

        // Some Prints
        {
            console.SetConsoleTextColor(YELLOW);
            cout << "  => ClientDll = 0x" << hex << uppercase << CS2::ClientDll << '\n';
            cout << "  => Engine2Dll = 0x" << hex << uppercase << CS2::Engine2Dll << '\n';
            cout << "  => MatchMakingDll = 0x" << hex << uppercase << CS2::MatchMakingDll << '\n';
            cout << "  => ServerDll = 0x" << hex << uppercase << CS2::ServerDll << '\n';
            console.SetConsoleTextColor(WHITE);
            cout << endl;
        }

        HWND window = overlay.InitializeWindow(instance, cmd_show);
        ID3D11Device* device = nullptr;
        ID3D11DeviceContext* device_context = nullptr;
        IDXGISwapChain* swap_chain = nullptr;
        ID3D11RenderTargetView* render_target_view = nullptr;

        if (!overlay.InitializeDirectX(window, &device, &device_context, &swap_chain, &render_target_view))
            return 1;

        overlay.InitializeImGui(window, device, device_context);
        MSG msg{};

        // Some Prints
        {
            console.SetConsoleTextColor(DARK_CYAN);
            cout << " [+] Initialized DX11 \n";
            cout << endl;
            console.SetConsoleTextColor(YELLOW);
            cout << "  => Window Handle = 0x" << std::uppercase << std::hex << window << '\n';
            cout << "  => ID3D11Device = 0x" << std::uppercase << std::hex << device << '\n';
            console.SetConsoleTextColor(CYAN);
            cout << endl;
            cout << " [+] Developed By NeoXa7\n [+] Sub to YT : NeoXa7\n [+] Contact me on Discord (Username : NeoXa7)\n [+] Language Used : C/C++\n [+] Libraries Used : ImGui, Microsoft DirectX SDK (June 2010)\n";
            cout << endl;
            console.SetConsoleTextColor(DARK_CYAN);
        }

        updater.UpdateOffsets(); // Updating offsets before Running cheats. Do not call this function inside a loop or you have to face intense lag issue

        // Main Loop
        {
            while (Flags::m_bIsRunning)
            {
                while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                    if (msg.message == WM_QUIT) Flags::m_bIsRunning = false;
                }

                if (!Flags::m_bIsRunning) break;

                ImGui_ImplDX11_NewFrame();
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();

                if (Flags::m_bIsVisible)
                {
                    LONG_PTR exStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
                    exStyle &= ~WS_EX_TRANSPARENT; // remove WS_EX_TRANSPARENT
                    exStyle &= ~WS_EX_LAYERED; // remove WS_EX_LAYERED
                    SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
                }
                else
                {
                    LONG_PTR exStyle = GetWindowLongPtr(window, GWL_EXSTYLE);
                    exStyle |= WS_EX_TRANSPARENT; // add WS_EX_TRANSPARENT
                    exStyle |= WS_EX_LAYERED; // add WS_EX_TRANSPARENT
                    SetWindowLongPtr(window, GWL_EXSTYLE, exStyle);
                }

                menu.Render();

                // This is the Main Entry Point for the Cheat;
                cheats.BeginLocalCheats(CS2::ClientDll);
                cheats.BeginPlayerEntityLoop(CS2::ClientDll, CS2::MatchMakingDll);
                cheats.BeginWorldEntitiesLoop(CS2::ClientDll, CS2::MatchMakingDll);


                // Overlay Main Entry Point Ends Here

                ImGui::Render(); // Rendering Stops Here;
                const float color[4]{ 0.f, 0.f, 0.f, 0.f };
                device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
                device_context->ClearRenderTargetView(render_target_view, color);
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

                swap_chain->Present(0U, 0U);
            }
            // Overlay Cleanup;
            overlay.CleanUp(swap_chain, device, device_context, render_target_view, window, {});
        }

    }

    // Clean Up
    if (Flags::g_showConsole) { console.DestroyConsoleWindow(); }
    CloseHandle(Driver::Handle);
    std::cin.get();
    return 0;
}
