#pragma once
#include <Globals/Globals.hpp>
#include <Driver/UM_Driver.hpp>
#include <Maths/Vector.hpp>
#include <Readers/Game.hpp>
#include <Readers/Player.hpp>

class C4
{
public:
	Vector3 GetPlantedC4Position()
	{
		uintptr_t Planted_C4_Node = Driver::read_memory<uintptr_t>(game.Planted_C4 + Offsets::m_pGameSceneNode);
		return Driver::read_memory<Vector3>(Planted_C4_Node + Offsets::m_vecAbsOrigin);// C4 Position
	}

	Vector3 GetDroppedC4Position()
	{
		uintptr_t Dropped_C4_Node = Driver::read_memory<uintptr_t>(game.Weapon_C4 + Offsets::m_pGameSceneNode);
		return Driver::read_memory<Vector3>(Dropped_C4_Node + Offsets::m_vecAbsOrigin);// C4 Position
	}

	int GetBombSite()
	{
		return Driver::read_memory<int>(game.Planted_C4 + Offsets::m_nBombSite);
	}

	float Get_Distance_From_PlantedC4_To_LocalPlayer()
	{
		return (GetPlantedC4Position() - player.Position).Magnitude(); // In Units;
	}

	float Get_Distance_From_DroppedC4_To_LocalPlayer()
	{
		return (GetDroppedC4Position() - player.Position).Magnitude(); // In Units;
	}

}; inline C4 c4;