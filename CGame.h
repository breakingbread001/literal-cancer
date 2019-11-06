

#pragma once

//#include "Entity.h"

namespace Engine
{
	class CGame
	{
	public:

		static CGame* GetInstance();
		std::vector<Entity*> GetPlayers();
		Entity* GetLocalPlayer();
		std::vector<Entity*> GetObjects();
	};
}