#include "../../../Main.h"
//#include "../../Scene/Game.h"
#include "Type/EnemyBase.h"
#include "Type/EnemySword.h"
#include "Type/EnemyPatrol.h"
#include "EnemyManager.h"
#include "../Friend/VillagerManager.h"
#include "../Friend/Villager.h"
#include "../Friend/Player.h"

#include "../../../System/Hit.h"
#include "../../../Other/StatusData.h"

#define ENEMY_MOV_SPEED	0.1f

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	for (auto& e_obj : enemies_)
	{
		delete e_obj;
	}
	enemies_.clear();
}

void EnemyManager::SpawnEnemy(int handle, int type, Vector3 pos, Vector3 rot, Vector3 patrol_pos1, Vector3 patrol_pos2)
{
	// 停止型
	if (type == EnemyType::TypeStop)
	{
		enemies_.emplace_back(new EnemySword(handle, pos, rot, set_id_num_));
		++set_id_num_;
	}
	// 巡回型
	else if (type == EnemyType::TypePatrol)
	{
		enemies_.emplace_back(new EnemyPatrol(handle, pos, rot, set_id_num_, patrol_pos1, patrol_pos2));
		++set_id_num_;
	}
}

void EnemyManager::Update(const Vector3& p_pos, const std::vector<Villager*>& v_objs)
{
	// 全敵共通の敵同士の当たり判定
	HitOtherEnemies();

	// 各敵の更新処理
	for (auto& e_obj : enemies_)
	{
		if (e_obj != NULL)
		{
			e_obj->FetchPlayerPosition(p_pos);
			e_obj->FetchVillagers(v_objs);
			e_obj->Update();
		}
	}
}

void EnemyManager::Render()
{
	for (auto& e_obj : enemies_)
	{
		if (e_obj != NULL)
		{
			e_obj->Render();
			e_obj->RenderFor2D();
		}
	}
}

void EnemyManager::RenderFor2D()
{
	for (auto& e_obj : enemies_)
	{
		if (e_obj != NULL)
		{
			e_obj->RenderFor2D();
		}
	}
}

void EnemyManager::HitOtherEnemies()
{
	for (auto& e_obj1 : enemies_)
	{
		// 他の敵との当たり判定処理
		for (auto& e_obj2 : enemies_)
		{
			// 自分自身か自分の識別番号よりも小さい敵は見ない(重複防止)
			if (e_obj1->GetterMyID() <= e_obj2->GetterMyID())
			{
				continue;
			}

			// ベクトルとその長さの算出
			Vector3 vec;
			vec = CalculateTwoVector(e_obj1->GetterMyPosition(), e_obj2->GetterMyPosition());
			float len = CalculateVectorToLength(vec);

			// お互いの距離が一定より短くなるのであれば
			if (len < 14.0f)
			{
				// 距離を固定する
				Vector3 dir = vec * -1.0f;
				dir.SetLength(14.0f);

				e_obj2->SetterMyPosition(e_obj1->GetterMyPosition() + dir);
			}
		}
	}
}

std::vector<EnemyBase*> EnemyManager::GetterEnemies() const
{
	return enemies_;
}
