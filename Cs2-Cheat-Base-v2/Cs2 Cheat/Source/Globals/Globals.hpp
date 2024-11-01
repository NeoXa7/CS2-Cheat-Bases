#pragma once
#include <Memory/Process.hpp>

#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)

namespace Flags
{
    // menu flags;
    inline bool IsRunning = true;

    // cheats flags;
    inline bool enableEsp = true;
}

namespace CS2
{
    inline DWORD ProcID = PM.GetProcessID(L"cs2.exe");
    inline uintptr_t ClientDll = PM.GetModuleBaseAddress(ProcID, L"client.dll");
    inline uintptr_t Engine2Dll = PM.GetModuleBaseAddress(ProcID, L"engine2.dll");
    inline uintptr_t InputsystemDll = PM.GetModuleBaseAddress(ProcID, L"inputsystem.dll");
    inline uintptr_t MatchMakingDll = PM.GetModuleBaseAddress(ProcID, L"matchmaking.dll");
    inline uintptr_t SoundsystemDll = PM.GetModuleBaseAddress(ProcID, L"soundsystem.dll");
    inline uintptr_t ServerDll = PM.GetModuleBaseAddress(ProcID, L"server.dll");
}

namespace Offsets
{
    // buttons;
    inline int dwForceAttack = 0x182F6B0;
    inline int dwForceAttack2 = 0x182F740;
    inline int dwForceJump = 0x182FBC0;

    // offsets;
    inline int dwEntityList = 0x19D1A98; // uintptr_t
    inline int dwLocalPlayerPawn = 0x1836BB8; // uintptr_t
    inline int dwLocalPlayerController = 0x1A219E0; // uintptr_t
    inline int dwViewAngles = 0x1A3DCC0; // uintptr_t
    inline int dwViewMatrix = 0x1A33E30; // uintptr_t
    inline int dwSensitivity = 0x1A30488; // uintptr_t
    inline int dwSensitivity_sensitivity = 0x40; // uintptr_t
    inline int dwGameRules = 0x1A2F768; // uintptr_t
    inline int dwGameTypes = 0x1A31B0; // uintptr_t
    inline int dwGameTypes_mapName = 0x120; // uintptr_t
    inline int dwPlantedC4 = 0x1A393A0; // uintptr_t
    inline int dwGlobalVars = 0x182ADF0; // uintptr_t
    inline int dwWeaponC4 = 0x19D4E80;  // uintptr_t


    // client_dll;   
    inline int m_iTeamNum = 0x3E3; // uint8
    inline int m_iHealth = 0x344; // int32
    inline int m_ArmorValue = 0x2404; // int32
    inline int m_hPlayerPawn = 0x80C; // CHandle<C_CSPlayerPawn>
    inline int m_flFlashBangTime = 0x13F8; // float32
    inline int m_iIDEntIndex = 0x1458; // CEntityIndex
    inline int m_iShotsFired = 0x23E4; // int32
    inline int m_aimPunchAngle = 0x1584; // QAngle
    inline int m_vOldOrigin = 0x1324; // Vector
    inline int m_vecViewOffset = 0xCB0; // CNetworkViewOffsetVector
    inline int m_pGameSceneNode = 0x328; // CGameSceneNode*
    inline int m_bBombPlanted = 0x9A5; // bool
    inline int m_bBombDropped = 0x9A4; // bool
    inline int m_nBombSite = 0xF94; // int32
    inline int m_bIsScoped = 0x23D0; // bool
    inline int m_sSanitizedPlayerName = 0x770; // CUtlString
    inline int m_fFlags = 0x3EC; // uint32
    inline int m_vecAbsVelocity = 0x3F0; // Vector
    inline int m_vecAbsOrigin = 0xD0; // Vector
    inline int m_hOwnerEntity = 0x440; // CHandle<C_BaseEntity>
    inline int m_iPing = 0x740; // uint32
    inline int m_bHasExploded = 0xFC5; // bool
    inline int m_bBeingDefused = 0xFCC; // bool
    inline int m_bWarmupPeriod = 0x41; // bool
    inline int m_bCTTimeOutActive = 0x4E; // bool
    inline int m_bTerroristTimeOutActive = 0x4D; // bool
    inline int m_pCameraServices = 0x11E0; // (CPlayer_CameraServices*)
    inline int m_iFOV = 0x210; // uint32
    inline int m_bDormant = 0xEF; // bool
}
