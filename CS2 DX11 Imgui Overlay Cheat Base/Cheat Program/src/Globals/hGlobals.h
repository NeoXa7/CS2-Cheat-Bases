#pragma once
#include <Memory/hProcess.h>

namespace Flags
{
    // menu flags;
    inline bool isRunning = true;

    // cheats flags;
    inline bool checkBox1 = false;
    inline bool checkBox2 = false;
}

namespace CS2
{
    Process processName = L"cs2.exe";
    Module moduleName = L"client.dll";

    inline DWORD procID = ProcessManager::GetProcessID(processName);
    inline uintptr_t clientAddress = ProcessManager::GetModuleBaseAddress(procID, moduleName);
}

namespace Offsets
{
    namespace buttons // buttons (last updated 31 August 2024);
    {
        inline int dwForceAttack = 0x17C7ED0;
        inline int dwForceAttack2 = 0x17C7F60;
        inline int dwForceJump = 0x17C83E0;
    }

    namespace client_dll // client_dll (last updated 31 August 2024);
    {
        // entity
        inline int m_iTeamNum = 0x3C3; // uint8
        inline int m_iHealth = 0x324; // int32
        inline int m_hPlayerPawn = 0x7EC; // CHandle<C_CSPlayerPawn>

        // antiflash
        inline int m_flFlashBangTime = 0x1348; // float32

        // trigger bot
        inline int m_iIDEntIndex = 0x13A8; // CEntityIndex
        inline int m_iShotsFired = 0x22B4; // int32

        // aimbot
        inline int m_aimPunchAngle = 0x14CC; // QAngle
        inline int m_vOldOrigin = 0x1274; // Vector
        inline int m_vecViewOffset = 0xC50; // CNetworkViewOffsetVector

        // glow
        inline int m_Glow = 0xBA0; // CGlowProperty
        inline int m_glowColorOverride = 0x40; // Color
        inline int m_bGlowing = 0x51; // bool

        // radar
        int m_entitySpottedState = 0x2288;
        int m_bSpotted = 0x8; // bool
    }

    namespace offsets // offsets (last updated 31 August 2024);
    {
        inline int dwEntityList = 0x19684F8;
        inline int dwLocalPlayerPawn = 0x17D37F0;
        inline int dwViewAngles = 0x19D98E8;
        inline int dwViewMatrix = 0x19CA480;
        inline int dwSensitivity = 0x19C6AC8;
        inline int dwSensitivity_sensitivity = 0x40;
    }
}