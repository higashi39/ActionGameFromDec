#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "Type/RockBase.h"
#include "Type/Rock01.h"
#include "Type/Rock02.h"
#include "Type/Rock03.h"
#include "Type/Rock04.h"
#include "Type/Rock05.h"
#include "RockManager.h"


void RockManager::CreateObject(int type, Vector3 pos, Vector3 rot)
{
	switch (type)
	{
	case 1:
		rocks_.emplace_back(new Rock01(pos, rot));
		break;
	case 2:
		rocks_.emplace_back(new Rock02(pos, rot));
		break;
	case 3:
		rocks_.emplace_back(new Rock03(pos, rot));
		break;
	case 4:
		rocks_.emplace_back(new Rock04(pos, rot));
		break;
	case 5:
		rocks_.emplace_back(new Rock05(pos, rot));
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