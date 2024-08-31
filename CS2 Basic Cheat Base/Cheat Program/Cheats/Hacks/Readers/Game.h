#pragma once
#include <Memory/hMemory.h>
#include <Maths/hVector.h>
#include <Globals/hGlobals.h>

class Game
{
public:
	uintptr_t EntityList;
	Vector3 ViewAngles;

	void Initialize()
	{
		EntityList = Memory::ReadMemory<uintptr_t>(CS2::clientAddress + Offsets::offsets::dwEntityList);
		ViewAngles = Memory::ReadMemory<Vector3>(CS2::clientAddress + Offsets::offsets::dwViewAngles);
	}
}; extern Game game;