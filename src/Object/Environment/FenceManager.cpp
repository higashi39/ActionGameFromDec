#include "../../Main.h"
//#include "../../Scene/Game.h"
#include "FenceManager.h"
#include "Fence.h"

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
//		// ���l(�ی�Ώ�)�𐶐�
//		CreateObject(f_pos);
//	}
//}

void FenceManager::SpawnFence(Vector3 pos, Vector3 rot)
{
	// �w�肵���ʒu�ɐ���
	fences_.emplace_back(new Fence(pos, rot));
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

std::vector<Fence*> FenceManager::GetterFenceInfos() const
{
	return fences_;
}