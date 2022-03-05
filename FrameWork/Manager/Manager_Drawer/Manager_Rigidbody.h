//=============================================================================
//
//  Rigidbodyマネージャー [Manager_Rigidbody.h]
//  Date   : 2021/11/22
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <unordered_map>
#include "../../Project/Bullet/src/btBulletDynamicsCommon.h"
#include "../../Renderer/Renderer_Polygon.h"
#include "../../System/Main.h"

#if defined(_DEBUG)
#pragma comment(lib, "Bullet/bin/BulletCollision_Debug.lib")
#pragma comment(lib, "Bullet/bin/BulletDynamics_Debug.lib")
#pragma comment(lib, "Bullet/bin/LinearMath_Debug.lib")
#else
#pragma comment(lib, "Bullet/bin/BulletCollision.lib")
#pragma comment(lib, "Bullet/bin/BulletDynamics.lib")
#pragma comment(lib, "Bullet/bin/LinearMath.lib")
#endif

//=============================================================================
// クラス定義
//=============================================================================
class Manager_Rigidbody
{

public:

	//剛体構造体
	typedef struct 
	{
		btMotionState* state; //状態
		btRigidBody*   body;//実体

	} s_RigidBody;


	//初期化・更新・終了
	void Init();
	void Update();
	void Uninit();

	//描画
	void Draw();

	//スフィア型剛体追加(引数はスケール・座標・質量)
	s_RigidBody* AddSphere(const Vector3& _scale, const Vector3& _position, float _mass);

	//ボックス型剛体追加(引数はスケール・座標・質量)
	s_RigidBody* AddBox(const Vector3& _scale, const Vector3& _position, float _mass);

	//カプセル型剛体追加(引数は半径・高さ・座標・質量)
	s_RigidBody* AddCapsule(float _radius, float _height, const Vector3& _position, const Vector3& _rotation, float _mass);

	//平面型剛体追加(引数は向き・座標・質量)
	s_RigidBody* AddStaticPlane(const Vector3& _up, const Vector3& _position, float _mass);

	//Bulletワールド取得
	inline btDynamicsWorld* GebtDynamicsWorld() { return m_DynamicsWorld; }

	//剛体を除去する
	void RemoveRigidBody(btRigidBody* _rigidBody);

private:

	//Bulletワールド
	btDynamicsWorld*   m_DynamicsWorld = 0;

	//デバッグ描画クラス
	class MyDebugDraw* m_MyDebugDraw;      

	//剛体追加(引数はコリジョンの型・質量・トランスフォーム)
	s_RigidBody* AddRigidBody(btCollisionShape* _shape, btScalar _mass, const btTransform& _transform);

};

// デバッグ描画クラス
class MyDebugDraw : public btIDebugDraw
{
	//デバッグモード
	int Debug_mode;

	//線描画関数
	void drawLine(const btVector3& _from, const btVector3& _to,
		const btVector3& _color);

	//複数色線描画関数
	void drawLine(const btVector3& _from, const btVector3& _to,
		const btVector3& _fromColor, const btVector3& _toColor);


	/* PointOnBに、衝突点を描画 */
	void drawContactPoint(const btVector3& _PointOnB, const btVector3& _normalOnB,
		btScalar _distance, int _lifeTime,
		const btVector3& _color){}


	/* 警告表示 */
	void reportErrorWarning(const char* _warningString){}

	/* 指定空間座標に文字列表示 */
	void draw3dText(const btVector3& _location, const char* _textString){}

public:

	/* デバッグモード指定 */
	inline void setDebugMode(int _debugMode){Debug_mode = _debugMode;}

	/* 現在のデバッグモードを返却 */
	inline int getDebugMode() const override{return Debug_mode;}


};