#include <Utils/Overlay.h>
#include <Menu/Menu.h>
#include <thread>
#include <Main/Driver.h>
#include <Cheats/mainclp.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Overlay::Overlay(LPCWSTR window_name, LPCWSTR window_class_name, INT screen_width, INT screen_height)
{
    this->WindowName = window_name;
    this->ClassName = window_class_name;
    this->WIDTH = screen_width;
    this->HEIGHT = screen_height;
}

Overlay::~Overlay()
{
}

LRESULT Overlay::Window_Procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
    if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param))
    {
        return 0L;
    }

    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0L;
    }

    return DefWindowProc(window, message, w_param, l_param);
}

HWND Overlay::InitializeWindow(HINSTANCE instance, int cmd_show)
{
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = this->Window_Procedure;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = this->ClassName;
    wc.hIconSm = 0;

    RegisterClassExW(&wc);

    HWND window = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_LAYERED,
        wc.lpszClassName,
        this->WindowName,
        WS_POPUP,
        0, 0,
        this->WIDTH,
        this->HEIGHT,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr
    );

    SetLayeredWindowAttributes(window, RGB(0, 0, 0), BYTE(255), LWA_COLORKEY);

    RECT client_area{}, window_area{};
    GetClientRect(window, &client_area);
    GetWindowRect(window, &window_area);
    POINT diff{};
    ClientToScreen(window, &diff);

    const MARGINS margins{
        window_area.left + (diff.x - window_area.left),
        window_area.top + (diff.y - window_area.top),
        client_area.right,
        client_area.bottom
    };

    DwmExtendFrameIntoClientArea(window, &margins);
    ShowWindow(window, cmd_show);
    UpdateWindow(window);
    return window;
}

BOOL Overlay::InitializeDirectX(HWND window, ID3D11Device** device, ID3D11DeviceContext** device_context, IDXGISwapChain** swap_chain, ID3D11RenderTargetView** render_target_view)
{
    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferDesc.RefreshRate.Numerator = 60U;
    sd.BufferDesc.RefreshRate.Denominator = 1U;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.SampleDesc.Count = 1U;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 3U;
    sd.OutputWindow = window;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
    D3D_FEATURE_LEVEL level;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0U,
        levels,
        2U,
        D3D11_SDK_VERSION,
        &sd,
        swap_chain,
        device,
        &level,
        device_context
    );

    if (FAILED(hr)) return false;

    ID3D11Texture2D* back_buffer = nullptr;
    (*swap_chain)->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
    if (back_buffer)
    {
        (*device)->CreateRenderTargetView(back_buffer, nullptr, render_target_view);
        back_buffer->Release();
    }
    else return false;

    return true;
}

VOID Overlay::InitializeImGui(HWND window, ID3D11Device* device, ID3D11DeviceContext* device_context)
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(device, device_context);
    Resources::LoadFonts();
    Resources::InitializeImages(device);
}

VOID Overlay::CleanUp(IDXGISwapChain* swap_chain, ID3D11Device* device, ID3D11DeviceContext* device_context, ID3D11RenderTargetView* render_target_view, HWND window, WNDCLASSEXW wc)
{
    Resources::CleanupFonts();
    Resources::CleanupImages();
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (render_target_view) render_target_view->Release();
    if (swap_chain) swap_chain->Release();
    if (device_context) device_context->Release();
    if (device) device->Release();

    DestroyWindow(window);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
}