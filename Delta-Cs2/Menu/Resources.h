#pragma once
#include <Libs/fonts/Poppins.h>
#include <Libs/fonts/Roboto.h>
#include <Menu/Bytes.h>
#include <Libs/imgui/imgui.h>
#include <d3d11.h>
#include <D3DX11tex.h>

namespace Resources
{
	static ImFont* Poppins_17 = nullptr;
	static ImFont* Poppins_15 = nullptr;
	static ImFont* Poppins_22 = nullptr;	
	static ImFont* Roboto	  = nullptr;

	inline ID3D11ShaderResourceView* SynapseX_Logo = nullptr;
	inline ID3D11ShaderResourceView* Blue_Triangle_Logo = nullptr;
	inline ID3D11ShaderResourceView* Delta_Logo = nullptr;
	inline ID3D11ShaderResourceView* legit_image = nullptr;
	inline ID3D11ShaderResourceView* rage_image = nullptr;
	inline ID3D11ShaderResourceView* visuals_image = nullptr;
	inline ID3D11ShaderResourceView* players_image = nullptr;
	inline ID3D11ShaderResourceView* misc_image = nullptr;
	inline ID3D11ShaderResourceView* settings_image = nullptr;


	inline bool LoadFonts() {
		ImGuiIO& io = ImGui::GetIO();
		io.LogFilename = nullptr;
		io.IniFilename = nullptr;

		io.Fonts->AddFontFromMemoryTTF(fonto, sizeof(fonto), 14.f);
		Poppins_17 = io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 17);
		Poppins_15 = io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 15);
		Poppins_22 = io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 22);		
		Roboto	   = io.Fonts->AddFontFromMemoryTTF((void*)roboto_bold, sizeof(roboto_bold), 15);

		return true;
	}

	inline VOID CleanupFonts() {
		ImGuiIO& io = ImGui::GetIO();
		if (io.Fonts) {
			io.Fonts->Clear();
			if(Poppins_17)
				Poppins_17 = nullptr;

			if (Poppins_22)
				Poppins_22 = nullptr;

			if (Poppins_15)
				Poppins_15 = nullptr;

			if (Roboto)
				Roboto = nullptr;
		}
	}

	inline bool LoadImageByMemory(ID3D11Device* device, unsigned char* image, size_t image_size, ID3D11ShaderResourceView** result)
	{
		D3DX11_IMAGE_LOAD_INFO information;
		ID3DX11ThreadPump* thread = nullptr;

		auto hres = D3DX11CreateShaderResourceViewFromMemory(device, image, image_size, &information, thread, result, 0);
		return (hres == S_OK);
	}

	inline bool InitializeImages(ID3D11Device* device)
	{
		auto cheatIcon = LoadImageByMemory(device, SynapseX_Logo_Byte, sizeof(SynapseX_Logo_Byte), &SynapseX_Logo);
		if (!cheatIcon)
			return false;
		
		auto cheatIcon2 = LoadImageByMemory(device, Blue_Triangle_Cheat_Logo_Byte, sizeof(Blue_Triangle_Cheat_Logo_Byte), &Blue_Triangle_Logo);
		if (!cheatIcon2)
			return false;

		auto cheatIcon3 = LoadImageByMemory(device, D_Letter_Cheat_Logo_Byte, sizeof(D_Letter_Cheat_Logo_Byte), &Delta_Logo);
		if (!cheatIcon3)
			return false;

		auto legitIcon = LoadImageByMemory(device, legit, sizeof(legit), &legit_image);
		if (!legitIcon)
			return false;

		auto rageIcon = LoadImageByMemory(device, rage, sizeof(rage), &rage_image);
		if (!rageIcon)
			return false;

		auto visualsIcon = LoadImageByMemory(device, visuals, sizeof(visuals), &visuals_image);
		if (!visualsIcon)
			return false;

		auto playersIcon = LoadImageByMemory(device, players, sizeof(players), &players_image);
		if (!playersIcon)
			return false;

		auto miscIcon = LoadImageByMemory(device, misc, sizeof(misc), &misc_image);
		if (!miscIcon)
			return false;

		auto settingsIcon = LoadImageByMemory(device, settings, sizeof(settings), &settings_image);
		if (!settingsIcon)
			return false;

	}

	inline VOID CleanupImages() {
		if (SynapseX_Logo) { SynapseX_Logo->Release(); SynapseX_Logo = nullptr; }
		if (legit_image) { legit_image->Release(); legit_image = nullptr; }
		if (rage_image) { rage_image->Release(); rage_image = nullptr; }
		if (visuals_image) { visuals_image->Release(); visuals_image = nullptr; }
		if (players_image) { players_image->Release(); players_image = nullptr; }
		if (misc_image) { misc_image->Release(); misc_image = nullptr; }
		if (settings_image) { settings_image->Release(); settings_image = nullptr; }
	}

}
