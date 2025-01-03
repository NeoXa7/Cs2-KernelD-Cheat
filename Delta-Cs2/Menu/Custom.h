#pragma once
#include "Menu.h"

class Custom
{
public:

	INT accent_color[4] = { 34, 151, 255, 255 };
	INT accent_color_hovered[4] = { accent_color[0] - 10, accent_color[1] - 10, accent_color[2] - 10, accent_color[3]};

	struct Selections_Anims
	{
		INT HOVERED;
		INT ACTIVE;
	};

	struct Group_Anims
	{
		INT hovered_text_anim;
		INT active_text_anim;
		INT active_outline_anim;
		INT active_rect_alpha;
	};

	IMGUI_API Bool Selection(const char* label, ImTextureID user_texture_id, bool selected);
	IMGUI_API Bool Group(const char* label, bool selected);

	VOID LeaveLine(int count = 1);
	VOID Checkbox(const char* format, bool* value);
	VOID CenterText(const char* format, const float y_padding = 0.0f, ImColor color = ImColor(255, 255, 255));
	VOID ColorEditor(const char* label, ImVec4* color, float width = 200.0f, float roundness = 2.0f);
	VOID RadioButtonGroup(int* current_index, const char* const items[], int items_size);
	VOID SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.1f", float width = 200.0f);
	VOID SliderInt(const char* label, int* v, int v_min, float v_max, const char* format = "%d", float width = 200.0f);
	VOID Hotkey(int* k, const ImVec2& size_arg = ImVec2(100, 30));
	Bool ComboBox(const char* label, const char* combo_items, int* current_index, const char* const items[], int items_size, float roundness = 2.0f, float width = 150.0f);
}; inline Custom custom;

