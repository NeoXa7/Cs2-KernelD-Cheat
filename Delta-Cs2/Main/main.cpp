#include <Utils/Overlay.hpp>
#include <Globals/Globals.h>
#include <Utils/Process.hpp>
#include <Utils/Console.hpp>
#include <Menu/Menu.h>
#include <Cheats/Cheats.h>
#include <Main/Driver.h>
#include <SDK/CGameComponents.h>

using namespace std;
INT APIENTRY WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev_instance, _In_ LPSTR cmd_line, _In_ int cmd_show)
{
    console.CreateConsoleWindow(L"Delta-Cs2");
    Overlay overlay(L"Delta Cheat Overlay", L"DELTA_CS2_OVERLAY_CLASS", SCREEN_WIDTH, SCREEN_HEIGHT);
   
    console.SetConsoleTextColor(YELLOW);

    if (CS2::ProcID <= 0)
    {
        std::cout << " [+] Failed to find designated Process (cs2.exe)\n";
        ShowErrorBox(L"Failed to find designated Process (cs2.exe)\n", L"Driver Error");
        std::cin.get();
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
        }
        
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

                // This is the Main Entry Point for the Cheat;
                cheats.BeginLocalCheats(CS2::ClientDll);
                cheats.BeginPlayerEntityLoop(CS2::ClientDll, CS2::MatchMakingDll);
                cheats.BeginWorldEntitiesLoop(CS2::ClientDll, CS2::MatchMakingDll);
            
          
                menu.Render();

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
            Driver::WPM<UINT64>(game.CameraServices + Offsets::m_iFOV, 60);
        }
 
    }

    // Clean Up
    console.DestroyConsoleWindow();
    CloseHandle(Driver::Handle);
    std::cin.get();
    return 0;
}
