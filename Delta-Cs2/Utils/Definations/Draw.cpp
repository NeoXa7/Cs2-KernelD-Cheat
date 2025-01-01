#include <Utils/Draw.h>

VOID Draw::Box(const Vector2& topLeft, const Vector2& bottomRight, ImColor color, float thickness) 
{
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color, 0.0f, ImDrawFlags_None, thickness);
}

VOID Draw::FilledBox(const Vector2& topLeft, const Vector2& bottomRight, ImColor fillColor, float borderThickness, ImColor borderColor) 
{
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), fillColor, 0.0f, ImDrawFlags_None);
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), borderColor, 0.0f, ImDrawFlags_None, borderThickness);
}

VOID Draw::Line(const Vector2& from, const Vector2& to, ImColor color, float thickness, bool drawEndPoint, float endPointRadius, ImColor endPointColor) {
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), color, thickness);

    if (drawEndPoint) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(to.x, to.y), endPointRadius, endPointColor);
    }
}

VOID Draw::HealthBar(const Vector2& topLeft, const Vector2& bottomRight, int health, ImColor fillColor, float barWidth, float offset) 
{
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

VOID Draw::TextW(std::string Text, Vector2 Pos, ImColor Color, float FontSize, bool KeepCenter)
{
    if (!KeepCenter)
    {
        ImGui::PushFont(Resources::Roboto);
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos.ToImVec2(), Color, Text.c_str());
        ImGui::PopFont();
    }
    else
    {
        ImGui::PushFont(Resources::Roboto);
        float TextWidth = ImGui::GetFont()->CalcTextSizeA(FontSize, FLT_MAX, 0.f, Text.c_str()).x;
        ImVec2 Pos_ = { Pos.x - TextWidth / 2,Pos.y };
        ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos_, Color, Text.c_str());
        ImGui::PopFont();
    }
}

VOID Draw::TextWithStroke(const std::string& text, Vector2 position, ImColor textColor, ImColor strokeColor, float fontSize, float strokeThickness)
{
    ImVec2 pos = ImVec2(position.x, position.y);

    ImGui::PushFont(Resources::Roboto);
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

VOID Draw::Circle(float x, float y, float radius, ImColor color, float thickness, int segments) {
    ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x, y), radius, color, segments, thickness);
}

VOID Draw::CircleFilled(float x, float y, float radius, ImColor color) {
    ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, color, 0);
}

VOID Draw::Bones
(
    UINTPTR BoneMatrix,
    Vector3 Position,
    view_matrix_t ViewMatrix,
    ImColor BoneColor,
    ImColor HeadColor,
    float BoneThickness,
    bool ShowBoneJoints,
    bool HeadFilled,
    float JointRadius,
    ImColor BoneJointsColor
) 

{
    Vector3 head = Driver::RPM<Vector3>(BoneMatrix + cBone.Index::HEAD * 32);

    Vector2 headScreenPos;
    Vector2 screenPos;

    for (int i = 0; i < sizeof(cBone.Connections) / sizeof(cBone.Connections[0]); i++)
    {
        int bone1 = cBone.Connections[i].bone1;
        int bone2 = cBone.Connections[i].bone2;

        Vector3 VectorBone1 = Driver::RPM<Vector3>(BoneMatrix + bone1 * 32);
        Vector3 VectorBone2 = Driver::RPM<Vector3>(BoneMatrix + bone2 * 32);

        if (cView.Project3DWorldTo2D(Position, screenPos, ViewMatrix) &&
            cView.Project3DWorldTo2D(head, headScreenPos, ViewMatrix))
        {
            Vector2 b1, b2;
            if (cView.Project3DWorldTo2D(VectorBone1, b1, ViewMatrix) &&
                cView.Project3DWorldTo2D(VectorBone2, b2, ViewMatrix))
            {
                float headHeight = cEntities->GetHeadHeight(screenPos, headScreenPos);

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
                    if (cEntities->Health != 0)
                        Draw::Circle(headScreenPos.x, headScreenPos.y, headHeight, HeadColor, BoneThickness);
                }
                else
                {
                    if (cEntities->Health != 0)
                        Draw::CircleFilled(headScreenPos.x, headScreenPos.y, headHeight, HeadColor);
                }

            }
        }
    }
}