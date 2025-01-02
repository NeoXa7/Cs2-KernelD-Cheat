#pragma once
#include <Libs/imgui/imgui.h>
#include <Libs/imgui/imstb_rectpack.h>
#include <SDK/CBone.h>
#include <Menu/Resources.h>
#include <SDK/CEntity.h>
#include <SDK/CGame.h>

namespace Draw
{
    // Draw Border Box
    VOID Box(
        const Vector2& topLeft, 
        const Vector2& bottomRight,
        ImColor color = ImColor(255, 255, 255, 255),
        float thickness = 2.0f
    );

    // Draw Filled Box
    VOID FilledBox(
        const Vector2& topLeft, 
        const Vector2& bottomRight, 
        ImColor fillColor = ImColor(255, 0, 0, 128), 
        float borderThickness = 2.0f, 
        ImColor borderColor = ImColor(255, 255, 255, 255)
    );

    // Draw Line
    VOID Line(
        const Vector2& from,
        const Vector2& to,
        ImColor color = ImColor(255, 255, 255, 255),
        float thickness = 1.0f,
        bool drawEndPoint = false,
        float endPointRadius = 3.0f,
        ImColor endPointColor = ImColor(255, 255, 255, 255)
    );

    // Draw Healthbar
    VOID HealthBar(
        const Vector2& topLeft,
        const Vector2& bottomRight,
        int health, 
        ImColor fillColor = ImColor(0, 255, 0, 255),
        float barWidth = 2.0f, float offset = 6.0f
    );

    // Draw Text
    VOID TextW(
        std::string Text, 
        Vector2 Pos,
        ImColor Color = ImColor(255, 255, 255, 255), 
        float FontSize = 15.0f,
        bool KeepCenter = true
    );

    // Draw Text with Stroke
    VOID TextWithStroke(
        const std::string& text,
        Vector2 position,
        ImColor textColor = ImColor(255, 255, 255, 255), 
        ImColor strokeColor = ImColor(0, 0, 0, 255), 
        float fontSize = 15.0f, 
        float strokeThickness = 1.0f
    );

    // Draw Circle
    VOID Circle(
        float x, 
        float y, 
        float radius, 
        ImColor color = ImColor(255, 255, 255, 255),
        float thickness = 1.0f, 
        int segments = 0
    );

    // Draw filled Circle
    VOID CircleFilled(
        float x, 
        float y, 
        float radius,
        ImColor color = ImColor(255, 255, 255, 255)
    );

    // Draw Bones with Lines and Circles for CS2
    VOID Bones
    (
        UINTPTR BoneMatrix,
        Vector3 Position,
        view_matrix_t ViewMatrix,
        ImColor BoneColor = ImColor(255, 255, 255, 255), /*Default Color White*/
        ImColor HeadColor = ImColor(255, 255, 255, 255), /*Default Color White*/
        float BoneThickness = 3.0f, /*Default Thickness 3*/
        bool ShowBoneJoints = false,
        bool HeadFilled = false,
        float JointRadius = 2.0f, /*Default Thickness 2*/
        ImColor BoneJointsColor = ImColor(255, 255, 255, 255) /*Default Color White*/
    );

}