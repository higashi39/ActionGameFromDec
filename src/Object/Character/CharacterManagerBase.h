#pragma once
#include <vector>
#include "../../System/Vector3.h"

//---------------------------------------------------------------------------------
//	オブジェクトマネージャベースクラス
//---------------------------------------------------------------------------------
class CharacterManagerBase
{
public:
	CharacterManagerBase();
	~CharacterManagerBase() {};

	// １スポナーに何人生成するか乱数で算出する
	// min : 最小人数
	// max : 最大人数
	void CalculateObjectNum(int min, int max);
	// 生成する村人(保護対象)の位置をそれぞれ決める
	// pos : オブジェクトの位置
	Vector3 AssignObjectPosition(const Vector3& pos);
	// 生成前の設定
	// id : オブジェクトID
	// 設定項目 - 1スポナーに生成される数
	// 　　　　 - 初期位置
	virtual void ObjectInitializeSetting(int id) = 0;
	// 村人(保護対象)を生成する
	// set_id : それぞれを識別するための値を設定
	// pos  : オブジェクトの位置
	virtual void CreateObject(int kindof, int set_id, const Vector3& pos) = 0;

protected:
	int object_create_num_;							// 生成されるオブジェクト数
	std::vector<Vector3> object_create_pos_;		// 生成されるオブジェクトの位置格納用配列
};