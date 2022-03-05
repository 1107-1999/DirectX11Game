//=============================================================================
//
//  剛体アクター基底クラス [ActorRB.h]
//  Date   : 2021/11/26
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../../Base/Actor3D.h"
#include "../../../../Component/Component_Rigidbody.h"
#include "../../../../Component/Component_OBB.h"

//=============================================================================
// クラス定義
//=============================================================================
class ActorRB : public Actor3D
{
protected:

	//コンポーネント
	class Component_Rigidbody*     m_Component_Rigidbody;    //剛体コンポーネント
	class Component_OBB*           m_Component_OBB;          //OBBコンポーネント(オーバーラップ判定用)

public:

	//初期化
	virtual void Init()override;

	//剛体座標設定
	void SetRigidbodyPosition(Vector3 _position);

	//剛体スケール設定
	void SetRigidbodyScale  (Vector3 _scale);  

	//スフィア型剛体追加(引数は大きさ・座標・質量)
	void AddSphereRB(const Vector3& _scale, const Vector3& _position, float _mass);

	//ボックス型剛体追加(引数は大きさ・座標・質量)
	void AddBoxRB(const Vector3& _scale, const Vector3& _position, float _mass);

	//カプセル型剛体追加(引数は半径・高さ・座標・回転・質量)
	void AddCapsuleRB(float _radius, float _height, const Vector3& _position, const Vector3& _rotation, float _mass);

};