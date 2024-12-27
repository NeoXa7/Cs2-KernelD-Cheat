#pragma once
#include <Libs/imgui/imgui.h>
#include <Libs/imgui/imstb_rectpack.h>
#include "Readers.h"
#include <Menu/Resources.hpp>

namespace Draw
{
    inline VOID Box(const Vector2& topLeft, const Vector2& bottomRight, ImColor color = ImColor(255, 255, 255, 255), float thickness = 2.0f) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color, 0.0f, ImDrawFlags_None, thickness);
    }

    inline VOID FilledBox(const Vector2& topLeft, const Vector2& bottomRight, ImColor fillColor = ImColor(255, 0, 0, 128), float borderThickness = 2.0f, ImColor borderColor = ImColor(255, 255, 255, 255)) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), fillColor, 0.0f, ImDrawFlags_None);
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), borderColor, 0.0f, ImDrawFlags_None, borderThickness);
    }

    inline VOID Line(const Vector2& from, const Vector2& to, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, bool drawEndPoint = false, float endPointRadius = 3.0f, ImColor endPointColor = ImColor(255, 255, 255, 255)) {
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), color, thickness);

        if (drawEndPoint) {
            ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(to.x, to.y), endPointRadius, endPointColor);
        }
    }

    inline VOID HealthBar(const Vector2& topLeft, const Vector2& bottomRight, int health, ImColor fillColor = ImColor(0, 255, 0, 255), float barWidth = 2.0f, float offset = 6.0f) {
        float boxHeight = bottomRight.y - topLeft.y;
        float healthHeight = (health / 100.0f) * boxHeight;
        float BGRectThickness = 1.0f;

        ImVec2 borderTopLeft(topLeft.x - barWidth - offset - BGRectThickness, topLeft.y - BGRectThickness);
        ImVec2 borderBottomRight(topLeft.x - offset + BGRectThickness, bottomRight.y + BGRectThickness);
        ImColor BGColor = ImColor(10, 10, 10, 255);
        ImGui::GetBackgroundDrawList()->AddRectFilled(borderTopLeft, borderBottomRight, BGColor, 0.0f, ImDrawFlags_None);

        // Draw the actual health bar
        ImVec2 healthTopLeft(topLeft.x - barWidth - offset, bottomRight.y - healthHeight);
        ImVec2 healthBottomRight(topLeft.x - offset, bottomRight.y);
        ImGui::GetBackgroundDrawList()->AddRectFilled(healthTopLeft, healthBottomRight, fillColor, 0.0f, ImDrawFlags_None);
    }

    inline VOID TextW(std::string Text, Vector2 Pos, ImColor Color = ImColor(255, 255, 255, 255), float FontSize = 15.0f, bool KeepCenter = true)
    {
        if (!KeepCenter)
        {
            ImGui::PushFont(resources::Roboto);
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos.ToImVec2(), Color, Text.c_str());
            ImGui::PopFont();
        }
        else
        {
            ImGui::PushFont(resources::Roboto);
            float TextWidth = ImGui::GetFont()->CalcTextSizeA(FontSize, FLT_MAX, 0.f, Text.c_str()).x;
            ImVec2 Pos_ = { Pos.x - TextWidth / 2,Pos.y };
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos_, Color, Text.c_str());
            ImGui::PopFont();
        }
    }

    inline VOID TextWithStroke(const std::string& text, Vector2 position, ImColor textColor = ImColor(255, 255, 255, 255), ImColor strokeColor = ImColor(0, 0, 0, 255), float fontSize = 15.0f, float strokeThickness = 1.0f)
    {
        ImVec2 pos = ImVec2(position.x, position.y);

        ImGui::PushFont(resources::Roboto);
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - strokeThickness, pos.y), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + strokeThickness, pos.y), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y - strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y + strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - strokeThickness, pos.y - strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + strokeThickness, pos.y - strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - strokeThickness, pos.y + strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x + strokeThickness, pos.y + strokeThickness), strokeColor, text.c_str());
        ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x, pos.y), textColor, text.c_str());
        ImGui::PopFont();
    }

    inline VOID Circle(float x, float y, float radius, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, int segments = 0) {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x, y), radius, color, segments, thickness);
    }

    inline VOID CircleFilled(float x, float y, float radius, ImColor color = ImColor(255, 255, 255, 255)) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, color, 0);
    }

    inline VOID Bones
    (
        Pointer BoneMatrix,
        ImColor BoneColor = ImColor(255, 255, 255, 255),
        ImColor HeadColor = ImColor(255, 255, 255, 255),
        float BoneThickness = 3.0f,
        bool ShowBoneJoints = false,
        bool HeadFilled = false,
        float JointRadius = 2.0f,
        ImColor BoneJointsColor = ImColor(255, 255, 255, 255)
    ) {
       // Pointer BoneMatrix = bone.GetMatrix(CCSPlayerPawn);
        Vector3 head = Driver::RPM<Vector3>(BoneMatrix + bone.Index::HEAD * 32);

        Vector2 headScreenPos;
        Vector2 screenPos;

        for (int i = 0; i < sizeof(bone.Connections) / sizeof(bone.Connections[0]); i++)
        {
            int bone1 = bone.Connections[i].bone1;
            int bone2 = bone.Connections[i].bone2;

            Vector3 VectorBone1 = Driver::RPM<Vector3>(BoneMatrix + bone1 * 32);
            Vector3 VectorBone2 = Driver::RPM<Vector3>(BoneMatrix + bone2 * 32);

            if (Project3DWorldTo2D(entities->Position, screenPos, game.ViewMatrix) &&
                Project3DWorldTo2D(head, headScreenPos, game.ViewMatrix))
            {
                Vector2 b1, b2;
                if (Project3DWorldTo2D(VectorBone1, b1, game.ViewMatrix) &&
                    Project3DWorldTo2D(VectorBone2, b2, game.ViewMatrix))
                {
                    float headHeight = entities->GetHeadHeight(screenPos, headScreenPos);

                    if (!ShowBoneJoints)
                    {
                        Draw::Line(b1, b2, BoneColor, BoneThickness);
                    }
                    else
                    {
                        Draw::Line(
                            b1,
                            b2,
                            BoneColor,
                            BoneThickness,
                            true,
                            JointRadius,
                            BoneJointsColor
                        );
                    }

                    if (!HeadFilled)
                    {
                        if(entities->Health != 0)
                            Draw::Circle(headScreenPos.x, headScreenPos.y, headHeight, HeadColor, BoneThickness);
                    }
                    else
                    {
                        if (entities->Health != 0)
                            Draw::CircleFilled(headScreenPos.x, headScreenPos.y, headHeight, HeadColor);
                    }

                }
            }
        }
    }


}