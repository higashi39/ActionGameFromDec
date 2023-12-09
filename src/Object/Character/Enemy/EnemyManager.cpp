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

void EnemyManager::SpawnEnemy(int type, Vector3 pos)
{
	// ��~�^
	if (type == EnemyType::TypeStop)
	{
		enemies_.emplace_back(new EnemySword(pos, set_id_num_));
		++set_id_num_;
	}
	// ����^
	else if (type == EnemyType::TypePatrol)
	{
		enemies_.emplace_back(new EnemyPatrol(pos, set_id_num_));
		++set_id_num_;
	}
}

void EnemyManager::Update(const Vector3& p_pos, const std::vector<Villager*>& v_objs)
{
	// �S�G���ʂ̓G���m�̓����蔻��
	HitOtherEnemies();

	// �e�G�̍X�V����
	for (auto& e_obj : enemies_)
	{
		if (e_obj != NULL)
		{
			e_obj->FetchPlayerPosition(p_pos);
			e_obj->FetchVillagersPosition(v_objs);
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
		// ���̓G�Ƃ̓����蔻�菈��
		for (auto& e_obj2 : enemies_)
		{
			// �������g�������̎��ʔԍ������������G�͌��Ȃ�(�d���h�~)
			if (e_obj1->GetterMyID() <= e_obj2->GetterMyID())
			{
				continue;
			}

			// �x�N�g���Ƃ��̒����̎Z�o
			Vector3 vec;
			vec = CalculateTwoVector(e_obj1->GetterMyPosition(), e_obj2->GetterMyPosition());
			float len = CalculateVectorToLength(vec);

			// ���݂��̋����������Z���Ȃ�̂ł����
			if (len < 5.0f)
			{
				// �������Œ肷��
				Vector3 dir = vec * -1.0f;
				dir.SetLength(5.0f);

				e_obj2->SetterMyPosition(e_obj1->GetterMyPosition() + dir);
			}
		}
	}
}

std::vector<EnemyBase*> EnemyManager::GetterEnemies() const
{
	return enemies_;
}
