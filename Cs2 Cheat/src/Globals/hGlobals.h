#pragma once
#include <Memory/hProcess.h>

#define Screen_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define Screen_HEIGHT GetSystemMetrics(SM_CYSCREEN)

namespace Flags
{
    // menu flags;
    inline bool isRunning = true;

    // cheats flags;
    inline bool enableEsp = true;
}

namespace CS2
{
    inline DWORD procID = ProcessManager::GetProcessID(L"cs2.exe");
    inline uintptr_t ClientDll = ProcessManager::GetModuleBaseAddress(procID, L"client.dll");
    inline uintptr_t Engine2Dll = ProcessManager::GetModuleBaseAddress(procID, L"engine2.dll");
    inline uintptr_t InputsystemDll = ProcessManager::GetModuleBaseAddress(procID, L"inputsystem.dll");
    inline uintptr_t MatchMakingDll = ProcessManager::GetModuleBaseAddress(procID, L"matchmaking.dll"); 
    inline uintptr_t SoundsystemDll = ProcessManager::GetModuleBaseAddress(procID, L"soundsystem.dll");
}

namespace Offsets
{
    // buttons;
    inline int dwForceAttack = 0x17BA020;
    inline int dwForceAttack2 = 0x17BA0B0;
    inline int dwForceJump = 0x17BA530;

    // offsets;
    inline int dwEntityList = 0x1954568; // uintptr_t
    inline int dwLocalPlayerPawn = 0x17C17F0; // uintptr_t
    inline int dwLocalPlayerController = 0x19A41C8; // uintptr_t
    inline int dwViewAngles = 0x19C5958; // uintptr_t
    inline int dwViewMatrix = 0x19B64F0; // uintptr_t
    inline int dwSensitivity = 0x19B2B38; // uintptr_t
    inline int dwSensitivity_sensitivity = 0x40; // uintptr_t
    inline int dwGameRules = 0x19B1558; // uintptr_t
    inline int dwGameTypes = 0x1A41C0; // uintptr_t
    inline int dwGameTypes_mapName = 0x120; // uintptr_t
    inline int dwPlantedC4 = 0x19BAF38; // uintptr_t
    inline int dwGlobalVars = 0x17B54F8; // uintptr_t
    inline int dwWeaponC4 = 0x1958570;  // uintptr_t
    

    // client_dll;   
        // Add Offsets =>
}
