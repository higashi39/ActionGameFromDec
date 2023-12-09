#include "../Main.h"
#include "Vector3.h"

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
//---------------------------------------------------------------------------------
//	ゼロ初期化（ＸＹＺの値を０にします）
//---------------------------------------------------------------------------------
void Vector3::clear()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
//---------------------------------------------------------------------------------
//	値のセット（ＸＹＺをそれぞれ受け取るバージョン）
//---------------------------------------------------------------------------------
void Vector3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
//---------------------------------------------------------------------------------
//	値のセット（ Vector3 を受け取るバージョン ）
//---------------------------------------------------------------------------------
void Vector3::set(Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
//---------------------------------------------------------------------------------
//	長さ取得
//---------------------------------------------------------------------------------
float Vector3::GetLength()
{
	return sqrtf(x * x + y * y + z * z);
}
//---------------------------------------------------------------------------------
//	正規化（ベクトルの長さを１にする）
//---------------------------------------------------------------------------------
void Vector3::normalize()
{
	float length = GetLength();
	if (length > 0.0f) {
		x = x / length;
		y = y / length;
		z = z / length;
	}
}
//---------------------------------------------------------------------------------
//	長さ設定
//---------------------------------------------------------------------------------
void Vector3::SetLength(float length)
{
	normalize();
	x = x * length;
	y = y * length;
	z = z * length;
}

//---------------------------------------------------------------------------------
//	= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3& Vector3::operator = (const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
//---------------------------------------------------------------------------------
//	+= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3& Vector3::operator += (const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
//---------------------------------------------------------------------------------
//	-= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3& Vector3::operator -= (const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
//---------------------------------------------------------------------------------
//	*= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3& Vector3::operator *= (const float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}
//---------------------------------------------------------------------------------
//	/= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3& Vector3::operator /= (const float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

//---------------------------------------------------------------------------------
//	+ 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3 operator + (const Vector3& v0, const Vector3& v1)
{
	Vector3 v;
	v.x = v0.x + v1.x;
	v.y = v0.y + v1.y;
	v.z = v0.z + v1.z;
	return v;
}
//---------------------------------------------------------------------------------
//	- 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3 operator - (const Vector3& v0, const Vector3& v1)
{
	Vector3 v;
	v.x = v0.x - v1.x;
	v.y = v0.y - v1.y;
	v.z = v0.z - v1.z;
	return v;
}
//---------------------------------------------------------------------------------
//	* 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3 operator * (const Vector3& v, const float f)
{
	Vector3 r;
	r.x = v.x * f;
	r.y = v.y * f;
	r.z = v.z * f;
	return r;
}
//---------------------------------------------------------------------------------
//	/ 演算子のオーバーロード
//---------------------------------------------------------------------------------
Vector3 operator / (const Vector3& v, const float f)
{
	Vector3 r;
	r.x = v.x / f;
	r.y = v.y / f;
	r.z = v.z / f;
	return r;
}

//---------------------------------------------------------------------------------
//	DXライブラリで使う VECTOR を返す
//---------------------------------------------------------------------------------
VECTOR Vector3::VGet()
{
	VECTOR v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}
//---------------------------------------------------------------------------------
//	DXライブラリで使う VECTOR の値を取得して設定
//---------------------------------------------------------------------------------
void Vector3::VSet(VECTOR v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
//---------------------------------------------------------------------------------
//	DXライブラリで使う FLOAT4 を返す
//---------------------------------------------------------------------------------
FLOAT4 Vector3::GetFLOAT4()
{
	FLOAT4 f4;
	f4.x = x;
	f4.y = y;
	f4.z = z;
	f4.w = 0.0f;
	return f4;
}

//---------------------------------------------------------------------------------
//	２つの Vector3 の距離を求める
//---------------------------------------------------------------------------------
float GetVector3Distance(Vector3& p0, Vector3& p1)
{
	Vector3 v = p0 - p1;
	return v.GetLength();
}
//---------------------------------------------------------------------------------
//	２つの Vector3 の内積を求める
//---------------------------------------------------------------------------------
float GetVector3Dot(Vector3& v0, Vector3& v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}
//---------------------------------------------------------------------------------
//	２つの Vector3 の外積を求める
//---------------------------------------------------------------------------------
Vector3 GetVector3Cross(Vector3& v0, Vector3& v1)
{
	Vector3 v;
	v.x = v0.y * v1.z - v0.z * v1.y;
	v.y = v0.z * v1.x - v0.x * v1.z;
	v.z = v0.x * v1.y - v0.y * v1.x;
	return v;
}

//----------------------------------
// 自作関数
//----------------------------------
//--------------------------------------------------------------------------------
// 目標地点まで移動する
//--------------------------------------------------------------------------------
void TrackingMove(Vector3 my_pos, Vector3 tracking_pos, float limit_length, Vector3 my_rot, int speed)
{
	// 目標の座標から自身の座標までのベクトルを求める
	Vector3 vec;
	vec.x = tracking_pos.x - my_pos.x;
	vec.y = tracking_pos.y - my_pos.y;
	vec.z = tracking_pos.z - my_pos.z;

	// ベクトルの長さを求める
	float length = VSize(vec.VGet());

	// もし目標座標に行くまでの長さに制限があり、
	// lengthがそれより長ければ
	if (limit_length != 0.0f && length > limit_length)
	{
		// 関数から抜ける
		return;
	}

	// ベクトルの正規化
	vec.VSet(VNorm(vec.VGet()));

	// 移動する方向に向ける
	my_rot.y = atan2f(vec.x, vec.z);

	// 移動する
	my_pos.x += speed * sinf(my_rot.y);
	my_pos.z += speed * cosf(my_rot.y);
}
