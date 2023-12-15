#include "../../Main.h"
//#include "../../Scene/Game.h"
#include "FenceBase.h"
#include "Fence.h"
#include "FenceManager.h"

FenceManager::~FenceManager()
{
	for (auto& f_obj : fences_)
	{
		delete f_obj;
	}
	fences_.clear();
}

//void FenceManager::ObjectInitializeSetting()
//{
//	for (auto& f_pos : infomation_.GetterFencePositions())
//	{
//		// 村人(保護対象)を生成
//		CreateObject(f_pos);
//	}
//}

void FenceManager::SpawnFence(int handle, int id, Vector3 pos, Vector3 rot)
{
	// 指定したモデルを指定した位置、向きに生成
	switch (id)
	{
	case 1:
		fences_.emplace_back(new Fence(handle, pos, rot));
		break;
	}
}

void FenceManager::Update()
{
	for (auto& f_obj : fences_)
	{
		if (f_obj != NULL)
		{
			f_obj->Update();
		}
	}
}

void FenceManager::Render()
{
	for (auto& f_obj : fences_)
	{
		if (f_obj != NULL)
		{
			f_obj->Render();
		}
	}
}

std::vector<FenceBase*> FenceManager::GetterFenceInfos() const
{
	return fences_;
}