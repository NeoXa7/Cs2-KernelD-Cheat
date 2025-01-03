#define IMGUI_DEFINE_MATH_OPERATORS
#include <Menu/Custom.h>
#include <Utils/KeyArrays.h>

IMGUI_API bool Custom::Selection(const char* label, ImTextureID user_texture_id, bool selected)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    ImVec2 pos = window->DC.CursorPos;

    const ImRect rect(pos, pos + ImVec2(50, 50));
    ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y + 5), style.FramePadding.y);
    if (!ImGui::ItemAdd(rect, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

    static std::map <ImGuiID, Selections_Anims> anim;
    auto it_anim = anim.find(id);
    if (it_anim == anim.end())
    {
        anim.insert({ id, {0, 0} });
        it_anim = anim.find(id);
    }

    if (hovered)
        it_anim->second.HOVERED += 8 * (1.f - ImGui::GetIO().DeltaTime);
    else
        it_anim->second.HOVERED -= 8 * (1.f - ImGui::GetIO().DeltaTime);

    if (it_anim->second.HOVERED > 50)
        it_anim->second.HOVERED = 50;
    else if (it_anim->second.HOVERED < 0)
        it_anim->second.HOVERED = 0;

    if (selected)
        it_anim->second.ACTIVE += 16 * (1.f - ImGui::GetIO().DeltaTime);
    else
        it_anim->second.ACTIVE -= 16 * (1.f - ImGui::GetIO().DeltaTime);

    if (it_anim->second.ACTIVE > 155)
        it_anim->second.ACTIVE = 155;
    else if (it_anim->second.ACTIVE < 0)
        it_anim->second.ACTIVE = 0;

    //int hovered_anim = animate(label, "hovered_anim", hovered, 50, 8, STATIC);

    //int active_anim = animate(label, "active_anim", selected, 155, 16, STATIC);

    window->DrawList->AddImage(user_texture_id, rect.Min + ImVec2(15, 15), rect.Max - ImVec2(15, 15), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 100 + it_anim->second.HOVERED + it_anim->second.ACTIVE));

    return pressed;
}

IMGUI_API bool Custom::Group(const char* label, bool selected)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true) - ImVec2(0.f, 2.f);
    ImVec2 pos = window->DC.CursorPos;

    const ImRect rect(pos, pos + ImVec2(label_size.x + 60.f, 25.f));
    ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x + 2.f, rect.Max.y), style.FramePadding.y);
    if (!ImGui::ItemAdd(rect, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

    static std::map < ImGuiID, Group_Anims> anim;
    auto it_anim = anim.find(id);
    if (it_anim == anim.end())
    {
        anim.insert({ id, {0, 0, 0, 0} });
        it_anim = anim.find(id);
    }

    if (hovered)
        it_anim->second.hovered_text_anim += 8 * (1.f - ImGui::GetIO().DeltaTime);
    else
        it_anim->second.hovered_text_anim -= 8 * (1.f - ImGui::GetIO().DeltaTime);

    if (it_anim->second.hovered_text_anim > 50)
        it_anim->second.hovered_text_anim = 50;
    else if (it_anim->second.hovered_text_anim < 0)
        it_anim->second.hovered_text_anim = 0;

    if (selected)
        it_anim->second.active_text_anim += 16 * (1.f - ImGui::GetIO().DeltaTime);
    else
        it_anim->second.active_text_anim -= 16 * (1.f - ImGui::GetIO().DeltaTime);

    if (it_anim->second.active_text_anim > 155)
        it_anim->second.active_text_anim = 155;
    else if (it_anim->second.active_text_anim < 0)
        it_anim->second.active_text_anim = 0;

    if (selected)
        it_anim->second.active_outline_anim += 3 * (1.f - ImGui::GetIO().DeltaTime);
    else
        it_anim->second.active_outline_anim -= 3 * (1.f - ImGui::GetIO().DeltaTime);

    if (it_anim->second.active_outline_anim > 15)
        it_anim->second.active_outline_anim = 15;
    else if (it_anim->second.active_outline_anim < 0)
        it_anim->second.active_outline_anim = 0;

    if (selected)
        it_anim->second.active_rect_alpha += 20 * (1.f - ImGui::GetIO().DeltaTime);
    else
        it_anim->second.active_rect_alpha -= 20 * (1.f - ImGui::GetIO().DeltaTime);

    if (it_anim->second.active_rect_alpha > 255)
        it_anim->second.active_rect_alpha = 255;
    else if (it_anim->second.active_rect_alpha < 0)
        it_anim->second.active_rect_alpha = 0;

    //int hovered_text_anim = animate(label, "hovered_text_anim", hovered, 50, 8, STATIC);

    //int active_text_anim = animate(label, "active_text_anim", selected, 155, 16, STATIC);

    //int active_outline_anim = animate(label, "active_outline_anim", selected, 15, 3, STATIC);

    //int active_rect_alpha = animate(label, "active_rect_alpha", selected, 255, 20, STATIC);

    window->DrawList->AddRectFilled(rect.Min, rect.Max, ImColor(11, 11, 11, 255), 12.f);

    window->DrawList->AddRectFilled(rect.Min, rect.Max, ImColor(accent_color[0], accent_color[1], accent_color[2], it_anim->second.active_rect_alpha), 12.f);

    window->DrawList->AddRect(rect.Min, rect.Max, ImColor(255, 255, 255, (15 + it_anim->second.active_outline_anim)), 12.f);

    window->DrawList->AddText(ImVec2((rect.Min.x + rect.Max.x) / 2.f - (label_size.x / 2.f), (rect.Min.y + rect.Max.y) / 2.f - (label_size.y / 2.f)), ImColor(255, 255, 255, (100 + it_anim->second.hovered_text_anim + it_anim->second.active_text_anim)), label);


    return pressed;
}

VOID Custom::LeaveLine(int count) {
    for (int i = 0; i < count; i++)
    {
        ImGui::Dummy(ImVec2());
    }
}

VOID Custom::Checkbox(const char* format, bool* value)
{
    static std::map<const char*, float> stateProgress;
    const float animationSpeed = 5.0f;

    ImVec4 UncheckedBGColor = ImVec4(30 / 255.0f, 30 / 255.0f, 30 / 255.0f, 1.0f);
    ImVec4 CheckedBGColor = ImVec4(accent_color[0] / 255.0f, accent_color[1] / 255.0f, accent_color[2] / 255.0f, 1.0f);
    ImVec4 HoveredAndActiveBGColor = ImVec4(accent_color_hovered[0] / 255.0f, accent_color_hovered[1] / 255.0f, accent_color_hovered[2] / 255.0f, 1.0f);
    ImVec4 CheckMarkColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    float& stateProg = stateProgress[format];
    stateProg += (*value ? 1.0f : -1.0f) * ImGui::GetIO().DeltaTime * animationSpeed;
    stateProg = std::clamp(stateProg, 0.0f, 1.0f);

    auto LerpColor = [](const ImVec4& a, const ImVec4& b, float t) {
        return ImVec4(
            a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t,
            a.z + (b.z - a.z) * t,
            a.w + (b.w - a.w) * t
        );
        };

    ImVec4 CurrentBGColor = LerpColor(UncheckedBGColor, CheckedBGColor, stateProg);

    ImGui::PushStyleColor(ImGuiCol_FrameBg, CurrentBGColor);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, CurrentBGColor);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, CurrentBGColor);
    ImGui::PushStyleColor(ImGuiCol_CheckMark, CheckMarkColor);

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3.5f, 3.5f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);

    ImGui::Checkbox(format, value);

    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar(2);
}

VOID Custom::CenterText(const char* format, const float y_padding, ImColor color)
{
    const ImVec2 text_size = ImGui::CalcTextSize(format);
    ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (text_size.x / 2));


    if (y_padding > 0.0f)
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + y_padding);
    ImGui::TextColored(color, format);
}

VOID Custom::ColorEditor(const char* label, ImVec4* color, float width, float roundness)
{
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(accent_color[0], accent_color[1], accent_color[2], accent_color[3]).Value);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(accent_color[0] - 10, accent_color[1] - 10, accent_color[2] - 4, accent_color[3]).Value);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImColor(accent_color[0] - 10, accent_color[1] - 10, accent_color[2] - 4, accent_color[3]).Value);
    ImGui::PushStyleColor(ImGuiCol_Border, ImColor(10, 10, 10, 255).Value);

    ImGui::SetNextItemWidth(width);
    ImGui::ColorEdit4(label, (float*)color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder);

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(4);
}

VOID Custom::RadioButtonGroup(int* current_index, const char* const items[], int items_size)
{
    static float transition_progress[32] = { 0.0f }; // Static array for animation progress (max 32 buttons)
    for (int i = 0; i < items_size; ++i)
    {
        bool is_selected = (*current_index == i);
        transition_progress[i] += (is_selected ? 1.0f : -1.0f) * ImGui::GetIO().DeltaTime * 5.0f; // Adjust speed
        transition_progress[i] = std::clamp(transition_progress[i], 0.0f, 1.0f); 

        float t = 0.5f - 0.5f * std::cos(transition_progress[i] * 3.14159f); 
        ImVec4 base_color(30 / 255.0f, 30 / 255.0f, 30 / 255.0f, 1.0f);
        ImVec4 target_color(accent_color[0] / 255.0f, accent_color[1] / 255.0f, accent_color[2] / 255.0f, 1.0f);

        ImVec4 current_color = ImVec4(
            base_color.x + t * (target_color.x - base_color.x),
            base_color.y + t * (target_color.y - base_color.y),
            base_color.z + t * (target_color.z - base_color.z),
            base_color.w + t * (target_color.w - base_color.w)
        );

        ImGui::PushStyleColor(ImGuiCol_FrameBg, current_color);
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, current_color);
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, current_color);
        if (is_selected) ImGui::PushStyleColor(ImGuiCol_CheckMark, current_color);

        if (ImGui::RadioButton(items[i], is_selected)) *current_index = i;

        ImGui::PopStyleColor(is_selected ? 4 : 3);

        if (i < items_size - 1) ImGui::SameLine();
    }
}

VOID Custom::SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, float width)
{
    ImColor SliderBGColor = ImColor(30, 30, 30, 255);
    ImColor SliderGrabColor = ImColor(accent_color[0], accent_color[1], accent_color[2], accent_color[3]);
    ImColor SliderGrabActiveColor = ImColor(accent_color[0] - 10, accent_color[1] - 10, accent_color[2] - 4, accent_color[3]);

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f); 
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.1, 0.1)); 
    ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 15.0f); 

    ImGui::PushStyleColor(ImGuiCol_FrameBg, SliderBGColor.Value); 
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(34, 34, 34, 255).Value);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, SliderBGColor.Value); 
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, SliderGrabColor.Value);
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, SliderGrabActiveColor.Value);

    ImGui::SetNextItemWidth(width);
    ImGui::SliderFloat(label, v, v_min, v_max, format);

    ImGui::PopStyleColor(5); 
    ImGui::PopStyleVar(3);  
}

VOID Custom::SliderInt(const char* label, int* v, int v_min, float v_max, const char* format, float width)
{
    ImColor SliderBGColor = ImColor(30, 30, 30, 255);
    ImColor SliderGrabColor = ImColor(accent_color[0], accent_color[1], accent_color[2], accent_color[3]);
    ImColor SliderGrabActiveColor = ImColor(accent_color[0] - 10, accent_color[1] - 10, accent_color[2] - 4, accent_color[3]);

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f); 
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.1, 0.1));
    ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 15.0f); 

    ImGui::PushStyleColor(ImGuiCol_FrameBg, SliderBGColor.Value); 
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(34, 34, 34, 255).Value); 
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, SliderBGColor.Value); 
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, SliderGrabColor.Value);
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, SliderGrabActiveColor.Value);

    ImGui::SetNextItemWidth(width);
    ImGui::SliderInt(label, v, v_min, v_max, format);

    ImGui::PopStyleColor(5); 
    ImGui::PopStyleVar(3);  
}

VOID Custom::Hotkey(int* k, const ImVec2& size_arg) {
    static std::unordered_map<int*, bool> keyStates;

    if (!keyStates[k]) {
        if (ImGui::Button((std::string(KeyNames[*k]) + "##" + std::to_string(reinterpret_cast<uintptr_t>(k))).c_str(), size_arg)) {
            keyStates[k] = true;
        }
    }
    else {
        ImGui::Text("Waiting for Key...");
        Sleep(20);

        for (auto& Key : KeyCodes) {
            if (GetAsyncKeyState(Key) & 0x8000) {
                *k = Key;
                keyStates[k] = false;
                break;
            }
        }
    }
}

bool Custom::ComboBox(const char* label, const char* combo_items, int* current_index, const char* const items[], int items_size, float roundness, float width )
{
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImColor(109, 104, 160, 155).Value);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImColor(109, 104, 160, 155).Value);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImColor(100, 100, 150, 155).Value);

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);

    ImGui::SetNextItemWidth(width);
    bool is_open = ImGui::BeginCombo(label, combo_items);

    if (is_open)
    {
        for (int i = 0; i < items_size; ++i)
        {
            bool is_selected = (i == *current_index);
            if (is_selected)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 215, 0).Value);
            }

            if (ImGui::Selectable(items[i], is_selected))
            {
                *current_index = i;
            }

            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }

            if (is_selected)
            {
                ImGui::PopStyleColor();
            }
        }
        ImGui::EndCombo();
    }

    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor(3);

    return is_open;
}