#pragma once
#include <ImGui/imgui.h>
#include <Maths/Vector.hpp>
#include <Maths/WorldToScreen.hpp>
#include <Readers/Entities.hpp>
#include <Readers/Game.hpp>
#include <Interface/Loader.hpp>

namespace DrawUtils
{
    inline void DrawBox(const Vector2& topLeft, const Vector2& bottomRight, ImColor color = ImColor(255, 255, 255, 255), float thickness = 2.0f) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), color, 0.0f, ImDrawFlags_None, thickness);
    }

    inline void DrawFilledBox(const Vector2& topLeft, const Vector2& bottomRight, ImColor fillColor = ImColor(255, 0, 0, 128), float borderThickness = 2.0f, ImColor borderColor = ImColor(255, 255, 255, 255)) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), fillColor, 0.0f, ImDrawFlags_None);
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(topLeft.x, topLeft.y), ImVec2(bottomRight.x, bottomRight.y), borderColor, 0.0f, ImDrawFlags_None, borderThickness);
    }


    inline void DrawLine(const Vector2& from, const Vector2& to, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, bool drawEndPoint = false, float endPointRadius = 3.0f, ImColor endPointColor = ImColor(255, 255, 255, 255)) {
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(from.x, from.y), ImVec2(to.x, to.y), color, thickness);

        if (drawEndPoint) {
            ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(to.x, to.y), endPointRadius, endPointColor);
        }
    }

    inline void DrawHealthBar(const Vector2& topLeft, const Vector2& bottomRight, int health, ImColor fillColor = ImColor(0, 255, 0, 255), float barWidth = 2.0f, float offset = 6.0f) {
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


    inline void DrawTextW(std::string Text, Vector2 Pos, ImColor Color = ImColor(255, 255, 255, 255), float FontSize = 15.0f, bool KeepCenter = true)
    {
        if (!KeepCenter)
        {
            ImGui::PushFont(ImGui_Loader::Roboto);
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos.ToImVec2(), Color, Text.c_str());
            ImGui::PopFont();
        }
        else
        {
            ImGui::PushFont(ImGui_Loader::Roboto);
            float TextWidth = ImGui::GetFont()->CalcTextSizeA(FontSize, FLT_MAX, 0.f, Text.c_str()).x;
            ImVec2 Pos_ = { Pos.x - TextWidth / 2,Pos.y };
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), FontSize, Pos_, Color, Text.c_str());
            ImGui::PopFont();
        }
    }

    inline void DrawTextWithStroke(const std::string& text, Vector2 position, ImColor textColor = ImColor(255, 255, 255, 255), ImColor strokeColor = ImColor(0, 0, 0, 255), float fontSize = 15.0f, float strokeThickness = 1.0f)
    {
        ImVec2 pos = ImVec2(position.x, position.y);

        ImGui::PushFont(ImGui_Loader::Roboto);
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

    inline void DrawCircle(float x, float y, float radius, ImColor color = ImColor(255, 255, 255, 255), float thickness = 1.0f, int segments = 0) {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(x, y), radius, color, segments, thickness);
    }

    inline void DrawCircleFilled(float x, float y, float radius, ImColor color = ImColor(255, 255, 255, 255)) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, color, 0);
    }

    inline void DrawBones
    (
        uintptr_t entityPawn, 
        ImColor boneColor = ImColor(255,255,255,255),
        ImColor headColor = ImColor(255,255,255,255),
        float boneThickness = 3.0f, 
        bool showBoneJoints = false,
        bool headFilled = false,
        float jointRadius = 2.0f,
        ImColor boneJointColor = ImColor(255,255,255,255)
    ) {
        uintptr_t BoneMatrix = GetBoneMatrix(entityPawn);
        Vector3 head = Driver::read_memory<Vector3>(BoneMatrix + BoneIndex::HEAD * 32);

        Vector2 headScreenPos;
        Vector2 screenPos;

        for (int i = 0; i < sizeof(boneConnections) / sizeof(boneConnections[0]); i++)
        {
            int bone1 = boneConnections[i].bone1;
            int bone2 = boneConnections[i].bone2;

            Vector3 VectorBone1 = Driver::read_memory<Vector3>(BoneMatrix + bone1 * 32);
            Vector3 VectorBone2 = Driver::read_memory<Vector3>(BoneMatrix + bone2 * 32);

            if (WorldToScreen(entities->Position, screenPos, game.ViewMatrix) &&
                WorldToScreen(head, headScreenPos, game.ViewMatrix))
            {
                Vector2 b1, b2;
                if (WorldToScreen(VectorBone1, b1, game.ViewMatrix) &&
                    WorldToScreen(VectorBone2, b2, game.ViewMatrix))
                {
                    float headHeight = entities->GetHeadHeight(screenPos, headScreenPos);

                    if (!showBoneJoints)
                    {
                        DrawUtils::DrawLine(b1, b2, boneColor, boneThickness);
                    }
                    else
                    {
                        if (game.Dist_ETLP < 2000.0f)
                        {
                            DrawUtils::DrawLine(
                                b1,
                                b2,
                                boneColor,
                                boneThickness,
                                true,
                                jointRadius,
                                boneJointColor
                            );
                        }
                        else
                        {
                            DrawUtils::DrawLine(b1, b2, boneColor, boneColor);
                        }
                    }

                    if (!headFilled)
                    {
                        DrawUtils::DrawCircle(headScreenPos.x, headScreenPos.y, headHeight, headColor, boneThickness);
                    }
                    else
                    {
                        DrawUtils::DrawCircleFilled(headScreenPos.x, headScreenPos.y, headHeight, headColor);
                    }

                }
            }
        }
    }

}