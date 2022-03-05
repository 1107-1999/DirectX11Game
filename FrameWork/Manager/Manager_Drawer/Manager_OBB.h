//=============================================================================
//
//  OBBコンポーネントマネージャー [Manager_OBB.h]
//  Date   : 2021/11/10
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <unordered_map>
#include "../../System/Main.h"

//=============================================================================
// enum定義
//=============================================================================
//コリジョンタイプ
enum ACTOR_TYPE
{
	COLLISION_PLAYER,      //プレイヤー
	COLLISION_GUN,         //銃
	COLLISION_BULLET,      //弾
	COLLISION_GOAL,        //ゴール
	COLLISION_GUN_TARGET,  //銃のターゲット
	COLLISION_BLOCK,       //ブロック
	COLLISION_CAMERA,      //カメラ
	MAX_ACTOR_TYPE,        //アクタータイプ数
};

//物理マテリアル
enum PHYSICS_MATERIAL
{
	PM_CONCRETE,//コンクリート
	PM_METAL,   //金属
	PM_SAND,    //砂
	PM_GLASS,   //ガラス
	PM_WOOD,    //木
	PM_IGNORE,  //無視判定
	MAX_PM_TYPE,//物理マテリアル最大数
};

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	bool         isHIT           = false;          //HITしたか
	int          physicsMaterial = INVALID_ID;     //物理マテリアル
	class Actor* hitActor        = nullptr;        //HITしたアクター
	float        length          = 0.0f;		   //レイの開始位置からhitposまでの長さ
	Vector3      hitPos          = Vector3_Zero;   //ヒットしたポジション

} s_HIT_Result;//HITリザルト構造体

//=============================================================================
// クラス定義
//=============================================================================
class Manager_OBB
{
private:

	//コリジョンチャンネル数分のOBBコンポーネントリスト
	std::list<class Component_OBB*>m_ComponentList[ACTOR_TYPE::MAX_ACTOR_TYPE];

	//軸比較用構造体
	struct s_OBBCompData
	{
		Vector3 axisX = { 1,0,0 };	//X軸
		Vector3 axisY = { 0,1,0 };	//Y軸
		Vector3 axisZ = { 0,0,1 };	//Z軸
		float lengthX = 0.0f;		//X軸の長さ
		float lengthY = 0.0f;		//Y軸の長さ
		float lengthZ = 0.0f;		//Z軸の長さ
	};

	//各軸の長さ比較
	bool CompareLength(s_OBBCompData* _A, s_OBBCompData* _B, Vector3* _separate, Vector3* _distance);

	//レイを描画するための構造体
	struct s_DrawData
	{
		s_DrawData() :startPos(Vector3_Zero), endPos(Vector3_Zero),
			color(Color(1, 0, 0, 1)), time(0), timeMax(60 * 5) {};//初期化
		Vector3 startPos;	//レイ開始位置
		Vector3 endPos;		//レイ終了位置
		Color color;		//レイの色
		int time;			//レイの生命時間のカウンター
		int timeMax;		//レイの生命時間
	};

	//描画中のレイリスト
	std::list<s_DrawData> m_DebugDrawRayList;

public:

	//OBBコンポーネントリスト登録(第2引数はコリジョンチャンネル)
	void AddComponent(class Component_OBB* _add, int _layer);

	//更新・終了
	void Update();
	void Uninit();

	//描画
	void Draw();

	//OBBのオーバーラップ判定
	bool OverlapJudgeOBB(Component_OBB* _component_OBBA, Component_OBB* _component_OBBB);

	//OBBと点の判定
	bool OverlapJudgeOBBandPoint(Component_OBB* _component_OBB, Vector3 _point);

	//レイキャスト
	s_HIT_Result Raycast(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 0.01f,int _drawRayLife = 60 * 3);

	//高精度レイキャスト
	s_HIT_Result RaycastHighAccuracy(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 0.01f, int _drawRayLife = 60 * 3);

	//アクター配列を返すレイキャスト
	std::vector<s_HIT_Result> RaycastGetHit(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 0.01f, int _drawRayLife = 60 * 3);

};

