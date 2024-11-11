#pragma once
#include <Driver/UM_Driver.hpp>
#include <Maths/Vector.hpp>
#include <Globals/Globals.hpp>
#include <ImGui/imgui.h>
#include <Utils/Bones.hpp>

class Entities
{
public:
    int Team;
    int Health;
    int Armor;
    char Names[128] = { 0 };
    Vector3 Position;
    uintptr_t BoneMatrix;
    bool IsFiring;
    uint32_t Ping;
    Vector3 VecViewOffset;
    bool IsScoped;
    bool IsDormant;
public:
    void UpdateEntities(uintptr_t currentPawn, uintptr_t currentController)
    {
        BoneMatrix = GetBoneMatrix(currentPawn);
        Team            = Driver::read_memory<int>(currentPawn + Offsets::m_iTeamNum);
        Health          = Driver::read_memory<int>(currentPawn + Offsets::m_iHealth);
        Armor           = Driver::read_memory<int>(currentPawn + Offsets::m_ArmorValue);
        Position        = Driver::read_memory<Vector3>(currentPawn + Offsets::m_vOldOrigin);
        IsFiring        = Driver::read_memory<bool>(currentPawn + Offsets::m_iShotsFired);
        Ping            = Driver::read_memory<uint32_t>(currentController + Offsets::m_iPing);
        VecViewOffset   = Driver::read_memory<Vector3>(currentPawn + Offsets::m_vecViewOffset);
        IsScoped        = Driver::read_memory<bool>(currentPawn + Offsets::m_bIsScoped);
        IsDormant       = Driver::read_memory<bool>(currentPawn + Offsets::m_bDormant);

        // Read player name
        uintptr_t NameAddress = Driver::read_memory<uintptr_t>(currentController + Offsets::m_sSanitizedPlayerName);
        Driver::read_array<char>(NameAddress, Names, sizeof(Names));
    }

    float GetHeadHeight(Vector2 screenPos, Vector2 headScreenPos)
    {
        return (screenPos.y - headScreenPos.y) / 8;
    }

    ImColor GetColorHealth()
    {
        if (Health >= 100)
        {
            return ImColor(0, 255, 0, 255); // Green for full health
        }
        else if (Health >= 60)
        {
            return ImColor(255, 255, 0, 255); // Yellow for medium health
        }
        else if (Health >= 30)
        {
            return ImColor(255, 165, 0, 255); // Orange for low health
        }
        else
        {
            return ImColor(255, 0, 0, 255); // Red for critical health
        }
    }

}; inline Entities entities[64];