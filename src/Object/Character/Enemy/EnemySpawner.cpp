#include <ctime>

#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "EnemyManager.h"
#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(Vector3& m_pos)
{
	enemy_manage = nullptr;
	enemy_spawner_position_.set(m_pos.x, m_pos.y, m_pos.z);
	//CreateEnemyManager();
}

//void EnemySpawner::CreateEnemyManager()
//{
//	enemy_manage = new EnemyManager(enemy_spawner_position_);
//}

void EnemySpawner::Update()
{
#if SHOW_DEBUG
	//printfDx("Enemy::CreateSpawner\n");
	//printfDx("spawner_pos : %f, %f, %f\n", enemy_spawner_position_.x, enemy_spawner_position_.y, enemy_spawner_position_.z);
#endif
}

void EnemySpawner::Render()
{
#if SHOW_DEBUG
	DrawSphere3D(enemy_spawner_position_.VGet(), 3.0f, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);
#endif
}