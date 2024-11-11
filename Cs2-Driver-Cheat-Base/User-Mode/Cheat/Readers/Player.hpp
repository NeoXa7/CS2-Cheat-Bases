#pragma once
#include <Driver/UM_Driver.hpp>
#include <Maths/Vector.hpp>
#include <Globals/Globals.hpp>

class LocalPlayer
{
public:
	uintptr_t localPlayerPawn;
	uintptr_t LocalPlayerController;
private:
	uintptr_t DW_Sensitivity;
	uintptr_t NameAddress;
public:
	int Team;
	int Health;
	int Armor;
	char Name[128] = { 0 };
	uint32_t Ping;
public:
	float Sensitivity;
	Vector3 Velocity;
	bool IsScoped;
	uint32_t IsFiring;
	bool IsCrouched;
public:
	Vector3 Position;
	float AimPunchAngle;
	Vector3 VecViewOffset;
public:

	void UpdateLocalPlayer() {
		localPlayerPawn				= Driver::read_memory<uintptr_t>(CS2::ClientDll + Offsets::dwLocalPlayerPawn);
		LocalPlayerController		= Driver::read_memory<uintptr_t>(CS2::ClientDll + Offsets::dwLocalPlayerController);
		DW_Sensitivity				= Driver::read_memory<uintptr_t>(CS2::ClientDll + Offsets::dwSensitivity); // private
		NameAddress					= Driver::read_memory<uintptr_t>(LocalPlayerController + Offsets::m_sSanitizedPlayerName); // private
		Team						= Driver::read_memory<int>(localPlayerPawn + Offsets::m_iTeamNum);
		Health						= Driver::read_memory<int>(localPlayerPawn + Offsets::m_iHealth);
		Armor						= Driver::read_memory<int>(localPlayerPawn + Offsets::m_ArmorValue);		
		Ping						= Driver::read_memory<uint32_t>(LocalPlayerController + Offsets::m_iPing);
		Sensitivity					= Driver::read_memory<float>(DW_Sensitivity + Offsets::dwSensitivity_sensitivity);
		Velocity					= Driver::read_memory<Vector3>(localPlayerPawn + Offsets::m_vecAbsVelocity);
		IsScoped					= Driver::read_memory<bool>(localPlayerPawn + Offsets::m_bIsScoped);
		IsFiring					= Driver::read_memory<uint32_t>(localPlayerPawn + Offsets::m_iShotsFired);
		Position					= Driver::read_memory<Vector3>(localPlayerPawn + Offsets::m_vOldOrigin);
		AimPunchAngle				= Driver::read_memory<float>(localPlayerPawn + Offsets::m_aimPunchAngle);
		VecViewOffset				= Driver::read_memory<Vector3>(localPlayerPawn + Offsets::m_vecViewOffset);
		Driver::read_array<char>(NameAddress, Name, sizeof(Name)); // Name
	}

}; inline LocalPlayer player;