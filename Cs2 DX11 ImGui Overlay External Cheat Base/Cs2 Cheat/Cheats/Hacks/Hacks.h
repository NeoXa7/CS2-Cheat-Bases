#pragma once
#include <Memory/hMemory.h>
#include <Inputs/Events.h>
#include <Readers/Game.h>
#include <Readers/Player.h>
#include "Esp.h"
#include <Maths/WorldToScreen.h>

namespace CHEATS
{
	void PlayerEsp();
}

void CHEATS::PlayerEsp() // Main Loop
{
	for (int i = 1; i < 64; i++)
	{		
		uintptr_t listEntry = Memory::ReadMemory<uintptr_t>(game.EntityList + (8 * (i & 0x7FFF) >> 9) + 16);
		if (!listEntry)
			continue;

		uintptr_t currentController = Memory::ReadMemory<uintptr_t>(listEntry + 120 * (i & 0x1FF));
		if (!currentController)
			continue;

		uint32_t pawnHandle = Memory::ReadMemory<uint32_t>(currentController + Offsets::m_hPlayerPawn);
		if (!pawnHandle)
			continue;

		uintptr_t listEntry2 = Memory::ReadMemory<uintptr_t>(game.EntityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 16);
		if (!listEntry2)
			continue;

		uintptr_t currentPawn = Memory::ReadMemory<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
		if (!currentPawn)
			continue;

		if (currentPawn == player.localPlayerPawn)
			continue;

		entities->UpdateEntities(currentPawn, currentController); // Updating Entities Vars After looping through all entities;
		game.UpdateGameVars(); // Updatng Game Vars;

		if (entities->Health <= 0 || entities->Health > 100)
			continue;

		Vector3 HeadPosition = entities->Position + Vector3{ 0.0f, 0.0f, 72.0f }; // Box Height 72 Units;

		Vector2 screenPos, headScreenPos;
		Vector2 screenTop(Screen_WIDTH / 2.0f, 0.0f);
		Vector2 screenCenter(Screen_WIDTH / 2.0f, Screen_HEIGHT / 2.0f);
		Vector2 screenBottom(Screen_WIDTH / 2.0f, Screen_HEIGHT);

		if (WorldToScreen(entities->Position, screenPos, game.ViewMatrix) &&  // Entities W2S Position;
			WorldToScreen(HeadPosition, headScreenPos, game.ViewMatrix)) // Entities W2S Head Position;
		{
			float boxHeight = std::fabs(headScreenPos.y - screenPos.y);
			float boxWidth = boxHeight * 0.6f;

			Vector2 topLeft(screenPos.x - boxWidth / 2, headScreenPos.y);
			Vector2 topRight(screenPos.x + boxWidth / 2 + 12.0f, headScreenPos.y);
			Vector2 bottomRight(screenPos.x + boxWidth / 2, screenPos.y);

			ESP::DrawBox
			(
				topLeft,
				bottomRight
			);


			ESP::DrawHealthBar
			(
				topLeft,
				bottomRight,
				entities->Health,
				ImColor(0, 183, 0, 255),
				2.0f,
				6.0f
			);


			ESP::DrawHealthBar
			(
				topRight,
				bottomRight,
				entities->Armor,
				C_Elements::RGBToImColor(182, 212, 238),
				2.0f,
				6.0f
			);

			// Draw the Snap Lines
			ESP::DrawLine
			(
				screenBottom,
				screenPos,
				ImColor(255, 255, 255, 255),
				1.0f,
				true
			);

			Vector2 namePos(screenPos.x - 20.0f, screenPos.y);
			ESP::DrawTextW
			(
				entities->Names,
				namePos,
				ImColor(255, 255, 255, 255),
				true
			);
			
			ESP::DrawBones(
				currentPawn
			);
			
			char DistTextArray[128];
			float distanceInUnits = (entities->Position - player.Position).Magnitude();
			float distanceInMeters = distanceInUnits / 39.37f;
			snprintf(DistTextArray, sizeof(DistTextArray), "[%.1f m]", distanceInMeters);

			ESP::DrawTextW(
				DistTextArray,
				topRight, 
				ImColor(255, 255, 255, 255)
			);
		}
	}
}