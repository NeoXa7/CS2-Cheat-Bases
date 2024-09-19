#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>
#include <Hacks/Bones.h>

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
public:
    void UpdateEntities(uintptr_t currentPawn, uintptr_t currentController)
    {
        // Read player name
        uintptr_t NameAddress = Memory::ReadMemory<uintptr_t>(currentController + Offsets::m_sSanitizedPlayerName);
        Memory::ReadArray<char>(NameAddress, Names, sizeof(Names));

        // Read other attributes
        Team = Memory::ReadMemory<int>(currentPawn + Offsets::m_iTeamNum);
        Health = Memory::ReadMemory<int>(currentPawn + Offsets::m_iHealth);
        Armor = Memory::ReadMemory<int>(currentPawn + Offsets::m_ArmorValue);
        Position = Memory::ReadMemory<Vector3>(currentPawn + Offsets::m_vOldOrigin);
        BoneMatrix = GetBoneMatrix(currentPawn);
        IsFiring = Memory::ReadMemory<bool>(currentPawn + Offsets::m_iShotsFired);
    }

    float GetHeadHeight(Vector2 screenPos, Vector2 headScreenPos)
    {
        return (screenPos.y - headScreenPos.y) / 8;
    }
};

inline Entities entities[64];