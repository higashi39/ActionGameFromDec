#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "../../Environment/Fence.h"
#include "Villager.h"
#include "Player.h"
#include "VillagerManager.h"

#include "../../../System/Hit.h"

VillagerManager::VillagerManager()
{
}

VillagerManager::~VillagerManager()
{
	for (Villager* v_obj : villagers_)
	{
		delete v_obj;
	}
	villagers_.clear();
}

void VillagerManager::SpawnVillager(Vector3 pos)
{
	villagers_.emplace_back(new Villager(pos, set_id_num_));
	++set_id_num_;
}

void VillagerManager::Update(const Vector3& p_pos)
{
	// ‘S‘ºl‹¤’Ê‚Ì‘ºl“¯Žm‚Ì“–‚½‚è”»’è
	HitOtherVillagers();

	for (auto& v_obj : villagers_)
	{
		if (v_obj != NULL)
		{
			v_obj->SetPlayerInfomation(p_pos);
			v_obj->SetFenceInfo(fences_);
			v_obj->Update();
		}
	}

#if SHOW_DEBUG
	for (auto& v_obj : villagers_)
	{
		printfDx("ID : %d\n",
			v_obj->GetterMyID());

	}
#endif
}

void VillagerManager::Render()
{
	for (Villager* v_obj : villagers_)
	{
		if (v_obj != NULL)
		{
			v_obj->Render();
		}
	}
}

void VillagerManager::FetchFenceInfo(const std::vector<Fence*>& f_objs)
{
	fences_ = f_objs;
}

//std::vector<int> VillagerManager::GetterVillagersID() const
//{
//	return villager_IDs_;
//}
//
//std::vector<Vector3> VillagerManager::GetterVillagersPosition()
//{
//	return villager_positions_;
//}

void VillagerManager::HitOtherVillagers()
{
	for (auto& v_obj1 : villagers_)
	{
		for (auto& v_obj2 : villagers_)
		{
			if (v_obj1->GetterMyID() <= v_obj2->GetterMyID()) {
				continue;
			}

			Vector3 vec;
			vec = CalculateTwoVector(v_obj1->GetterMyPosition(), v_obj2->GetterMyPosition());
			float len = CalculateVectorToLength(vec);

			if (len < 5.0f)
			{
				Vector3 dir = vec * -1.0f;
				dir.SetLength(5.0f);

				v_obj2->SetterMyPosition(v_obj1->GetterMyPosition() + dir);
			}
		}
	}
}

std::vector<Villager*> VillagerManager::GetterVillagers() const
{
	return villagers_;
}

//std::vector<Villager*> VillagerManager::GetterVillagers() const
//{
//	return villagers_;
//}

//void VillagerManager::GetPlayerInfomation(Vector3 p_pos, Vector3 p_rot)
//{
//	player_position = p_pos;
//	player_rotate = p_rot;
//}
