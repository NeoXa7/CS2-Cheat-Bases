#pragma once
#include <Driver/UM_Driver.hpp>
#include <Maths/Vector.hpp>
#include <Globals/Globals.hpp>
#include <Maths/ViewMatrix.hpp>
#include <Readers/Player.hpp>
#include <Readers/Entities.hpp>

class Game
{
public:

	uintptr_t EntityList;
	uintptr_t Rules;
	uintptr_t GlobalVars;
	uintptr_t Planted_C4;
	uintptr_t Weapon_C4;
	uintptr_t CameraServices;
	uintptr_t GameModeServer;
	uintptr_t GameMode;

public:

	char MapName[128] = { 0 };
	float FlashDuration;
	float Dist_ETLP;
	int EntityIndex;
	Vector3 ViewAngles;
	view_matrix_t ViewMatrix;
public:

	bool BombPlanted;
	bool BombDropped;
	bool IsBombBeingDefused;
	bool IsWarmupPeriod;
	bool IsTerroristTimeOutActive;
	bool IsCT_TimeOutActive;

public:
	void UpdateGameVars()
	{
		uintptr_t MapNameAddress = Driver::read_memory<uintptr_t>(CS2::MatchMakingDll + Offsets::dwGameTypes + Offsets::dwGameTypes_mapName + 8);
		Driver::read_array<char>(MapNameAddress, MapName, sizeof(MapName));

		EntityList					= Driver::read_memory<uintptr_t>(CS2::ClientDll + Offsets::dwEntityList);
		Rules						= Driver::read_memory<uintptr_t>(CS2::ClientDll + Offsets::dwGameRules);
		GlobalVars					= Driver::read_memory<uintptr_t>(CS2::ClientDll + Offsets::dwGlobalVars);
		IsWarmupPeriod				= Driver::read_memory<bool>(Rules + Offsets::m_bWarmupPeriod);

		BombPlanted					= Driver::read_memory<bool>(Rules + Offsets::m_bBombPlanted);
		BombDropped					= Driver::read_memory<bool>(Rules + Offsets::m_bBombDropped);
		IsBombBeingDefused			= Driver::read_memory<bool>(Planted_C4 + Offsets::m_bBeingDefused);

		FlashDuration				= Driver::read_memory<float>(player.localPlayerPawn + Offsets::m_flFlashBangTime);
		EntityIndex					= Driver::read_memory<int>(player.localPlayerPawn + Offsets::m_iIDEntIndex);
		CameraServices				= Driver::read_memory<uintptr_t>(player.localPlayerPawn + Offsets::m_pCameraServices);

		ViewAngles					= Driver::read_memory<Vector3>(CS2::ClientDll + Offsets::dwViewAngles);
		ViewMatrix					= Driver::read_memory<view_matrix_t>(CS2::ClientDll + Offsets::dwViewMatrix);
		
		IsTerroristTimeOutActive	= Driver::read_memory<bool>(Rules + Offsets::m_bTerroristTimeOutActive);
		IsCT_TimeOutActive			= Driver::read_memory<bool>(Rules + Offsets::m_bCTTimeOutActive);
		Dist_ETLP					= (entities->Position - player.Position).Magnitude(); // In Units;


		Planted_C4 = Driver::read_memory<uintptr_t>
			(Planted_C4 = Driver::read_memory<uintptr_t>(CS2::ClientDll + Offsets::dwPlantedC4));

		Weapon_C4 = Driver::read_memory<uintptr_t>
			(Weapon_C4 = Driver::read_memory<uintptr_t>(CS2::ClientDll + Offsets::dwWeaponC4));
	}
}; inline Game game;