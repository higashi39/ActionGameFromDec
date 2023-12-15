#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "../../Environment/FenceBase.h"
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

void VillagerManager::SpawnVillager(int handle, Vector3 pos)
{
	villagers_.emplace_back(new Villager(handle, pos, set_id_num_));
	++set_id_num_;
}

void VillagerManager::Update(const Vector3& p_pos)
{
	// ‘S‘ºl‹¤’Ê‚Ì‘ºl“¯Žm‚Ì“–‚½‚è”»’è
	HitOtherVillagers();

	int num = 0;
	for (auto& v_obj : villagers_)
	{
		if (v_obj != NULL)
		{
			v_obj->SetPlayerInfomation(p_pos);
			v_obj->SetFenceInfo(fences_);
			v_obj->Update();

			if (v_obj->GetterIsGoal())
			{
				++num;
			}
		}

	}
	villagersgoal_num = num;

#if SHOW_DEBUG
	//for (auto& v_obj : villagers_)
	//{
	//	printfDx("ID : %d\n",
	//		v_obj->GetterMyID());

	//}
	printfDx("add_time : %d\n", add_time_);
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

void VillagerManager::FetchFenceInfo(const std::vector<FenceBase*>& f_objs)
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

			//if (CheckBallHit(v_obj1->GetterMyPosition(), 2.0f,
			//	v_obj2->GetterMyPosition(), 2.0f))
			//{
			//	v_obj2->SetterMyPosition(HitCollision(v_obj2->GetterMyPosition(), v_obj2->GetterMyBeforePosition(), { 2.0f,2.0f,2.0f},
			//		v_obj1->GetterMyPosition(), { 2.0f,2.0f,2.0f }));

			//}

			Vector3 vec;
			vec = CalculateTwoVector(v_obj1->GetterMyPosition(), v_obj2->GetterMyPosition());
			float len = CalculateVectorToLength(vec);

			if (len < 3.0f)
			{
				Vector3 dir = vec * -1.0f;
				dir.SetLength(3.0f);

				v_obj2->SetterMyPosition(v_obj1->GetterMyPosition() + dir);
				//v_obj2->SetterMyPosition(HitCollision(v_obj2->GetterMyPosition(), v_obj2->GetterMyBeforePosition(), { 3.0f,3.0f,3.0f },
				//	v_obj1->GetterMyPosition(), { 3.0f,3.0f,3.0f }));

			}
		}
	}
}

std::vector<Villager*> VillagerManager::GetterVillagers() const
{
	return villagers_;
}

int VillagerManager::GetterGoalVillager() const
{
	return villagersgoal_num;
}

int VillagerManager::AddTimeLimit()
{
	int test = 0;
	for (auto& v_obj : villagers_)
	{
		test += v_obj->add_time_;
	}
	printfDx("test : %d\n", test);

	return test;
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
