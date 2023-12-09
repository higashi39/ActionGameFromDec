#include "../../Main.h"
#include "../../Scene/Game.h"
#include "Ttpe/RockBase.h"
#include "Type/Rock01.h"
#include "Type/Rock02.h"
#include "RockManager.h"

RockManager::RockManager()
{
}

void RockManager::CreateObject(int type, Vector3 pos)
{
	switch (type)
	{
	case 1:
		rocks_.emplace_back(new Rock01(pos));
		break;
	case 2:
		rocks_.emplace_back(new Rock02(pos));
		break;
	}
}

void RockManager::Render()
{
	for (auto& obj : rocks_)
	{
		obj->Render();
	}
}