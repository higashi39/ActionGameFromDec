#include "../../../Main.h"
#include "../../../Scene/Game.h"
#include "VillagerManager.h"
#include "VillagerSpawner.h"


VillagerSpawner::VillagerSpawner(Vector3& m_pos)
{
	villager_manage = nullptr;
	villager_spawner_position_.set(m_pos.x, m_pos.y, m_pos.z);
	//CreateVillagerManager();
}

//void VillagerSpawner::CreateVillagerManager()
//{
//	villager_manage = new VillagerManager(villager_spawner_position_);
//}

void VillagerSpawner::Update()
{
#if SHOW_DEBUG
#endif
}

void VillagerSpawner::Render()
{
#if SHOW_DEBUG
	DrawSphere3D(villager_spawner_position_.VGet(), 3.0f, 16, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);
#endif
}