//=============================================================================
//
//  OBBコンポーネント [Component_OBB.h]
//  Author : Ryosuke Kotera
//  Date   : 2021/10/18
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "Base/Component.h"
#include "../Manager/Manager_Drawer/Manager_OBB.h"

//=============================================================================
// クラス定義
//=============================================================================
class Component_OBB : public Component
{
public:

	Component_OBB(class Actor* _owner, int _updatePriority) : Component(_owner, _updatePriority) {}

	//初期化・更新・終了
	void Init()   override;
	void Update() override;
	void Uninit() override {};
	
	//描画
	void Draw();

	//視認性設定
	inline void SetVisibility(bool _visibility) { m_Visibility = _visibility; }

	//スケール設定
	inline void SetScale(Vector3 _scale) { m_Scale = _scale; }

	//スケール取得
	inline Vector3 GetScale() const { return m_Scale; };

	// 座標取得
	inline Vector3 GetPosition() const { return m_Position; };

	//回転取得
	inline Vector3 GetRotation() const { return m_Rotation; }

	//視認性取得
	inline bool GetVisibility()  const { return  m_Visibility; }

	//色設定
	inline void SetColor(Color _color) { m_Color = _color; }

	//回転セット
	inline void SetRotation(Vector3 _rot) { m_Rotation = _rot; }

	//座標オフセット設定
	inline void SetPositionOffset(Vector3 _offset) { m_PositionOffset = _offset; }

	//レイに反応するかを取得・設定
	inline void SetIsReactRay(bool _set) { m_isReactRay = _set; }
	inline bool GetIsReactRay()const { return m_isReactRay; }

	//物理マテリアル取得・設定
	inline int GetPhysicsMaterial() const{ return m_PhysicsMaterial; }
	inline void SetPhysicsMaterial(int _physicsMaterial)  { m_PhysicsMaterial = _physicsMaterial; }

	//OBB
	inline Vector3 GetNormaDirectionX() const { return m_NormaDirectionX; };// 指定軸番号のX方向ベクトルを取得
	inline Vector3 GetNormaDirectionY() const { return m_NormaDirectionY; };// 指定軸番号のY方向ベクトルを取得
	inline Vector3 GetNormaDirectionZ() const { return m_NormaDirectionZ; };// 指定軸番号のZ方向ベクトルを取得

	inline float   GetLengthX()        const { return m_LengthX; }// X軸方向の長さを取得
	inline float   GetLengthY()        const { return m_LengthY; }// Y軸方向の長さを取得
	inline float   GetLengthZ()        const { return m_LengthZ; }// Z軸方向の長さを取得

	//重なっているか判定
	inline bool GetOverlap() const{ return m_isOverlap; }
	inline void SetOverlap(bool _flag) { m_isOverlap = _flag; }

	//オーナー座標設定
	void SetOwnerPosition(Vector3 _position);

	
	//レイキャスト
	//_ignoreMySelfは無視したい自分自身のActor*。_ignoreListは無視したいアクタータイプ。list。
	s_HIT_Result Raycast(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 10.0f, int _drawRayLife = 60 * 3);

	//高精度レイキャスト(重め)
	s_HIT_Result RaycastHighAccuracy(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 10.0f, int _drawRayLife = 60 * 3);

	//レイキャスト(HITしたオブジェクト全てを配列にして返す)
	std::vector<s_HIT_Result> RaycastGetHit(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 0.025f, int _drawRayLife = 60 * 3);


private:

	//OBBマネージャーキャッシュ用
	class Manager_OBB* m_Manager_OBB;

	//X方向ベクトル
	Vector3 m_NormaDirectionX;

	//Y方向ベクトル
	Vector3 m_NormaDirectionY;

	//Z方向ベクトル
	Vector3 m_NormaDirectionZ;

	//X軸方向の長さ
	float   m_LengthX;

	//Y軸方向の長さ
	float   m_LengthY;

	//Z軸方向の長さ
	float   m_LengthZ;

	//座標
	Vector3 m_Position;

	//回転
	Vector3 m_Rotation;

	//スケール
	Vector3 m_Scale;   

	//座標オフセット
	Vector3 m_PositionOffset;

	//色
	Color   m_Color;

	//重なっているか？
	bool m_isOverlap;

	//使用するシェーダーの種類
	int  m_ShaderType;

	//視認性
	bool m_Visibility;

	//レイに反応するか
	bool m_isReactRay;

	//物理マテリアル
	int  m_PhysicsMaterial;

};


