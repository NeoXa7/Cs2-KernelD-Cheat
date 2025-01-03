#pragma once
#include <Libs/imGui/imgui.h>
#include <Libs/imGui/imgui_impl_dx11.h>
#include <Libs/imGui/imgui_impl_win32.h>
#include <d3d11.h>
#include <dwmapi.h>
#include <string>
#include <Globals/Globals.h>

class Overlay
{
public:
	Overlay(LPCWSTR window_name, LPCWSTR window_class_name, INT screen_width, INT screen_height);
	~Overlay();

private:
	LPCWSTR WindowName;
	LPCWSTR ClassName;
	INT	WIDTH;
	INT	HEIGHT;

public:
	static LRESULT CALLBACK		
		Window_Procedure(
			HWND window, 
			UINT message, 
			WPARAM w_param, 
			LPARAM l_param
	);

	HWND InitializeWindow(
			HINSTANCE instance, 
			int cmd_show
	);

	BOOL InitializeDirectX(
		HWND window, ID3D11Device** device, 
		ID3D11DeviceContext** device_context, 
		IDXGISwapChain** swap_chain, 
		ID3D11RenderTargetView** render_target_view
	);

	VOID InitializeImGui(
		HWND window, 
		ID3D11Device* device,
		ID3D11DeviceContext* 
		device_context
	);

	VOID CleanUp(
		IDXGISwapChain* swap_chain,
		ID3D11Device* device, 
		ID3D11DeviceContext* device_context,
		ID3D11RenderTargetView* render_target_view,
		HWND window,
		WNDCLASSEXW wc
	);


};

inline VOID ShowErrorBox(const std::wstring& errorMessage, const std::wstring& errorTitle = L"Error")
{
	MessageBoxW(nullptr, errorMessage.c_str(), errorTitle.c_str(), MB_ICONERROR | MB_OK);
}

inline INT ShowWarningBox(const std::wstring& warningMessage, const std::wstring& warningTitle = L"Warning")
{
	int result = MessageBoxW(nullptr, warningMessage.c_str(), warningTitle.c_str(), MB_ICONWARNING | MB_OK);
	return result;
}

inline VOID ShowMessage(const std::wstring& message, const std::wstring& messageTitle)
{
	std::thread([message, messageTitle]() {
		MessageBoxW(nullptr, message.c_str(), messageTitle.c_str(), MB_ICONWARNING | MB_OK);
		}).detach();
}