//=============================================================================
//
//  OBBコンポーネントマネージャー [Manager_OBB.cpp]
//  Date   : 2021/11/10
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Manager_OBB.h"
#include "Manager_ImGui.h"
#include "../Manager_Game.h"
#include "../../Actor/Base/Actor.h"
#include "../../Component/Component_OBB.h"
#include "../../Renderer/Renderer_Polygon.h"
#include "../../System/Math.h"
#include "../../System/Exchanger.h"

//=============================================================================
// OBBコンポーネントリスト登録(第二引数はコリジョンチャンネル)
//=============================================================================
void Manager_OBB::AddComponent(class Component_OBB* _add, int _layer)
{
	m_ComponentList[_layer].push_back(_add);
}

//=============================================================================
// 更新関数
//=============================================================================
void Manager_OBB::Update()
{
	//プレイヤーの判定
	for (Component_OBB* OBB_Player : m_ComponentList[COLLISION_PLAYER])
	{

		//有効か
		if (OBB_Player->GetActive())
		{
			//プレイヤーと銃の判定
			for (Component_OBB* OBB_Gun : m_ComponentList[COLLISION_GUN])
			{
				if (OBB_Gun->GetActive())//有効か
				{
					if (OverlapJudgeOBB(OBB_Player, OBB_Gun))
					{
						OBB_Player->SetColor(Color{0.0f,0.0f,1.0f,1.0f});
						OBB_Gun->SetColor(Color{ 1.0f,0.0f,0.0f,1.0f });
						OBB_Gun->SetOverlap(true);
					}
				}
			}

			//プレイヤーとゴールの判定
			for (Component_OBB* OBB_Goal : m_ComponentList[COLLISION_GOAL])
			{
				if (OBB_Goal->GetActive())//有効か
				{
					if (OverlapJudgeOBB(OBB_Player, OBB_Goal))
					{
						OBB_Player->SetColor(Color{ 0.0f,0.0f,1.0f,1.0f });
						OBB_Goal->SetColor(Color{ 1.0f,0.0f,0.0f,1.0f });
						OBB_Goal->SetOverlap(true);
					}
				}
			}


			//プレイヤーとブロックの判定
			for (Component_OBB* OBB_Block : m_ComponentList[COLLISION_BLOCK])
			{
				if (OBB_Block->GetActive())//有効か
				{
					if (OverlapJudgeOBB(OBB_Player, OBB_Block))
					{
						OBB_Block->SetOverlap(true);
					}
				}
			}
		}


	}

	//レイの描画時間加算
	for (auto& i : m_DebugDrawRayList)
	{
		i.time++;
	}

	//レイの描画終了
	m_DebugDrawRayList.remove_if([](s_DrawData _data) {return _data.time >= _data.timeMax; });
}

//=============================================================================
// 描画関数
//=============================================================================
void Manager_OBB::Draw()
{
	//OBBコンポーネントリストの描画
	for (int i = 0; i < MAX_ACTOR_TYPE; i++)
	{
		for (Component_OBB* component_OBB : m_ComponentList[i])
		{
			component_OBB->Draw();
		}
	}

	//レイ描画
	for (auto& i : m_DebugDrawRayList)
	{
		Renderer_Polygon::Instance()->DrawLine(i.startPos, i.endPos, i.color);
	}
}

//=============================================================================
// 終了関数
//=============================================================================
void Manager_OBB::Uninit()
{
	//OBBコンポーネントリストのクリア
	for (int i = 0; i < MAX_ACTOR_TYPE; i++)
	{
		m_ComponentList[i].clear();
	}
}

//=============================================================================
// OBBとOBBのオーバーラップ判定関数
//=============================================================================
bool Manager_OBB::OverlapJudgeOBB(Component_OBB* _component_OBBA, Component_OBB* _component_OBBB)
{
	//ボックス同士の距離
	Vector3 distance = _component_OBBB->GetPosition() - _component_OBBA->GetPosition();

	//比較用の構造体
	s_OBBCompData A = {};
	s_OBBCompData B = {};

	//中心からの各軸の長さ
	A.lengthX = _component_OBBA->GetLengthX();
	A.lengthY = _component_OBBA->GetLengthY();
	A.lengthZ = _component_OBBA->GetLengthZ();
	B.lengthX = _component_OBBB->GetLengthX();
	B.lengthY = _component_OBBB->GetLengthY();
	B.lengthZ = _component_OBBB->GetLengthZ();

	//ローカル基底軸ベクトルにそれぞれの回転を反映させる
	D3DXMATRIX mtxRA;
	Vector3 tempCmpRotA = _component_OBBA->GetRotation();
	D3DXMatrixRotationYawPitchRoll(&mtxRA, tempCmpRotA.y, tempCmpRotA.x, tempCmpRotA.z);
	D3DXVec3TransformCoord(&A.axisX, &A.axisX, &mtxRA);
	D3DXVec3TransformCoord(&A.axisY, &A.axisY, &mtxRA);
	D3DXVec3TransformCoord(&A.axisZ, &A.axisZ, &mtxRA);

	D3DXMATRIX mtxRB;
	Vector3 tempCmpRotB = _component_OBBB->GetRotation();
	D3DXMatrixRotationYawPitchRoll(&mtxRB, tempCmpRotB.y, tempCmpRotB.x, tempCmpRotB.z);
	D3DXVec3TransformCoord(&B.axisX, &B.axisX, &mtxRB);
	D3DXVec3TransformCoord(&B.axisY, &B.axisY, &mtxRB);
	D3DXVec3TransformCoord(&B.axisZ, &B.axisZ, &mtxRB);

	//ボックスA基準のローカル基底軸基準の影算出
	if (!CompareLength(&A, &B, &A.axisX, &distance))return false;//Xを分離軸に
	if (!CompareLength(&A, &B, &A.axisY, &distance))return false;//Yを分離軸に
	if (!CompareLength(&A, &B, &A.axisZ, &distance))return false;//Zを分離軸に

	//ボックスB基準のローカル基底軸基準の影算出
	if (!CompareLength(&A, &B, &B.axisX, &distance))return false;//Xを分離軸に
	if (!CompareLength(&A, &B, &B.axisY, &distance))return false;//Yを分離軸に
	if (!CompareLength(&A, &B, &B.axisZ, &distance))return false;//Zを分離軸に

	Vector3 separate = {};
	//お互いの基底軸同士の外戚ベクトル基準の影算出
	{
		//ボックスAのX
		{
			//と　ボックスBのX軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisX, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのY軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisX, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのZ軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisX, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
		//ボックスAY
		{
			//と　ボックスBのX軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisY, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのY軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisY, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのZ軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisY, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
		//ボックスAZ
		{
			//と　ボックスBのX軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのY軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのZ軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
	}

	//当たった
	return true;
}

//=============================================================================
// OBBと点のオーバーラップ判定関数
//=============================================================================
bool Manager_OBB::OverlapJudgeOBBandPoint(Component_OBB * _component_OBB, Vector3 _point)
{
	//ボックス同士の距離
	Vector3 distance = _component_OBB->GetPosition() - _point;

	//比較用の構造体
	s_OBBCompData A = {};
	s_OBBCompData B = {};

	//点に長さが無いので0。
	A.lengthX = 0.0f;
	A.lengthY = 0.0f;
	A.lengthZ = 0.0f;
	B.lengthX = _component_OBB->GetLengthX();
	B.lengthY = _component_OBB->GetLengthY();
	B.lengthZ = _component_OBB->GetLengthZ();

	//ローカル基底軸ベクトルにそれぞれの回転を反映させる
	D3DXMATRIX mtxRA;
	Vector3 tempCmpRotA = Vector3(0, 0, 0);
	D3DXMatrixRotationYawPitchRoll(&mtxRA, tempCmpRotA.y, tempCmpRotA.x, tempCmpRotA.z);
	D3DXVec3TransformCoord(&A.axisX, &A.axisX, &mtxRA);
	D3DXVec3TransformCoord(&A.axisY, &A.axisY, &mtxRA);
	D3DXVec3TransformCoord(&A.axisZ, &A.axisZ, &mtxRA);

	D3DXMATRIX mtxRB;
	Vector3 tempCmpRotB = _component_OBB->GetRotation();
	D3DXMatrixRotationYawPitchRoll(&mtxRB, tempCmpRotB.y, tempCmpRotB.x, tempCmpRotB.z);
	D3DXVec3TransformCoord(&B.axisX, &B.axisX, &mtxRB);
	D3DXVec3TransformCoord(&B.axisY, &B.axisY, &mtxRB);
	D3DXVec3TransformCoord(&B.axisZ, &B.axisZ, &mtxRB);

	//ボックスA基準のローカル基底軸基準の影算出
	if (!CompareLength(&A, &B, &A.axisX, &distance))return false;//Xを分離軸に
	if (!CompareLength(&A, &B, &A.axisY, &distance))return false;//Yを分離軸に
	if (!CompareLength(&A, &B, &A.axisZ, &distance))return false;//Zを分離軸に

	//ボックスB基準のローカル基底軸基準の影算出
	if (!CompareLength(&A, &B, &B.axisX, &distance))return false;//Xを分離軸に
	if (!CompareLength(&A, &B, &B.axisY, &distance))return false;//Yを分離軸に
	if (!CompareLength(&A, &B, &B.axisZ, &distance))return false;//Zを分離軸に

	Vector3 separate = {};
	//お互いの基底軸同士の外戚ベクトル基準の影算出
	{
		//ボックスAのX
		{
			//と　ボックスBのX軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisX, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのY軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisX, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのZ軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisX, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
		//ボックスAY
		{
			//と　ボックスBのX軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisY, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのY軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisY, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのZ軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisY, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
		//ボックスAZ
		{
			//と　ボックスBのX軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisX);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのY軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisY);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
			//と　ボックスBのZ軸との外積ベクトルを分離軸とした場合
			D3DXVec3Cross(&separate, &A.axisZ, &B.axisZ);
			if (!CompareLength(&A, &B, &separate, &distance)) return false;
		}
	}

	//当たった
	return true;
}

//=============================================================================
// 引数の軸から当たっているか確認
//=============================================================================
bool Manager_OBB::CompareLength(s_OBBCompData * _A, s_OBBCompData * _B, Vector3 * _separate, Vector3 * _distance)
{
	//分離軸上でのボックスAの中心からボックスBの中心までの座標
	float distance = fabsf(D3DXVec3Dot(_distance, _separate));
	//分離軸上でボックスAの中心から最も遠いボックスAの頂点までの距離
	float shadowA = 0.0f;
	//分離軸上でボックスBの中心から最も遠いボックスBの頂点までの距離
	float shadowB = 0.0f;
	//それぞれのボックスの影を算出
	shadowA = fabsf(D3DXVec3Dot(&_A->axisX, _separate) * _A->lengthX) +
		fabsf(D3DXVec3Dot(&_A->axisY, _separate) * _A->lengthY) +
		fabsf(D3DXVec3Dot(&_A->axisZ, _separate) * _A->lengthZ);

	shadowB = fabsf(D3DXVec3Dot(&_B->axisX, _separate) * _B->lengthX) +
		fabsf(D3DXVec3Dot(&_B->axisY, _separate) * _B->lengthY) +
		fabsf(D3DXVec3Dot(&_B->axisZ, _separate) * _B->lengthZ);

	if (distance > shadowA + shadowB) return false;
	return true;
}

//=============================================================================
// レイ判定関数
//=============================================================================
s_HIT_Result Manager_OBB::Raycast(Vector3 _startPos, Vector3 _endPos,
	Actor* _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE>_ignoreList,
	Color _drawRayColor,float _accuracy, int _drawRayLife)
{
	//空のHITリザルト
	s_HIT_Result hit_result;

	//開始点から終了点までの距離
	const float length = D3DXVec3Length(&(_endPos - _startPos));

	//開始点から終了点までの距離キャッシュ
	float tempLen = length;

	//繰り返し回数初期化
	int tempRep = 0;

	//繰り返し回数計算
	while (tempLen < 1.0f)
	{
		tempLen *= 10.0f;
		tempRep++;
	}

	//繰り返し回数
	const int repeat = static_cast<int>(floor(length * (_accuracy * max(tempRep, 1))));

	//一度の更新で進む距離
	const float addLen = static_cast<float>(length / repeat);

	//現在の探索位置
	Vector3 currentPos = _startPos;

	//プレイヤーからカメラの方向
	Vector3 dir;

	D3DXVec3Normalize(&dir, &(_endPos - _startPos));

	//描画用データ入力
	if (_isDispRay)
	{
		s_DrawData temp = {};
		temp.color = _drawRayColor;
		temp.startPos = _startPos;
		temp.endPos = _endPos;
		temp.time = 0;
		temp.timeMax = _drawRayLife;
		m_DebugDrawRayList.emplace_back(temp);
	}

	float currentLen = 0.0f;
	for (int i = 0; i < repeat; i++)
	{
		//OBBのレイヤー分繰り返す
		for (int k = 0; k < ACTOR_TYPE::MAX_ACTOR_TYPE; k++)
		{
			//カメラ同士は判定しない
			if (k == ACTOR_TYPE::COLLISION_CAMERA)continue;

			bool isIgn = false;
			//無視リストと現在のレイヤーを比較
			for (auto& ign : _ignoreList)
			{
				if (k == ign)
				{
					isIgn = true;
					break;
				}
			}
			if (isIgn)continue;

			//OBBの個数分繰り返す
			std::list<Component_OBB*>::iterator itr = m_ComponentList[k].begin();
			for (; itr != m_ComponentList[k].end(); itr++)
			{
				//自身を無視する設定なら無視する
				if (_ignoreMySelf && _ignoreMySelf == (*itr)->GetOwner())continue;

				//OBBに点がヒット
				if (OverlapJudgeOBBandPoint(*itr, currentPos))
				{
					//当ったかどうか
					hit_result.isHIT = true;

					//物理マテリアル取得
					hit_result.physicsMaterial = (*itr)->GetPhysicsMaterial();

					//当ったアクター
					hit_result.hitActor = (*itr)->GetOwner();

					//HIT座標
					hit_result.hitPos = currentPos;

					//当るまでのレイの長さ
					hit_result.length = currentLen;

				}
			}
		}
		//スタート地点から探査した長さ
		currentLen += addLen;

		//現在の探索位置
		currentPos += dir * currentLen;
	}

	return hit_result;
}

//=============================================================================
// 高精度レイキャスト関数
//=============================================================================
s_HIT_Result Manager_OBB::RaycastHighAccuracy(Vector3 _startPos, Vector3 _endPos,
	Actor* _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE>_ignoreList,
	Color _drawRayColor, float _accuracy, int _drawRayLife)
{
	//空のHITリザルト
	s_HIT_Result hit_result;

	//開始点から終了点までの距離
	const float length = D3DXVec3Length(&(_endPos - _startPos));

	//開始点から終了点までの距離キャッシュ
	float tempLen = length;

	//繰り返し回数初期化
	int tempRep = 0;

	//繰り返し回数計算
	while (tempLen < 1.0f)
	{
		tempLen *= 10.0f;
		tempRep++;
	}

	//繰り返し回数
	const int repeat = static_cast<int>(floor(length * (_accuracy * max(tempRep, 1))));

	//一度の更新で進む距離
	constexpr float addLen = 0.0001f;

	//現在の探索位置
	Vector3 currentPos = _startPos;

	//プレイヤーからカメラの方向
	Vector3 dir;

	D3DXVec3Normalize(&dir, &(_endPos - _startPos));

	//描画用データ入力
	if (_isDispRay)
	{
		s_DrawData temp = {};
		temp.color = _drawRayColor;
		temp.startPos = _startPos;
		temp.endPos = _endPos;
		temp.time = 0;
		temp.timeMax = _drawRayLife;
		m_DebugDrawRayList.emplace_back(temp);
	}

	float currentLen = 0.0f;
	for (int i = 0; i < repeat; i++)
	{
		//OBBのレイヤー分繰り返す
		for (int k = 0; k < ACTOR_TYPE::MAX_ACTOR_TYPE; k++)
		{
			//カメラ同士は判定しない
			if (k == ACTOR_TYPE::COLLISION_CAMERA)continue;

			bool isIgn = false;
			//無視リストと現在のレイヤーを比較
			for (auto& ign : _ignoreList)
			{
				if (k == ign)
				{
					isIgn = true;
					break;
				}
			}
			if (isIgn)continue;

			//OBBの個数分繰り返す
			std::list<Component_OBB*>::iterator itr = m_ComponentList[k].begin();
			for (; itr != m_ComponentList[k].end(); itr++)
			{
				//自身を無視する設定なら無視する
				if (_ignoreMySelf && _ignoreMySelf == (*itr)->GetOwner())continue;

				//OBBに点がヒット
				if (OverlapJudgeOBBandPoint(*itr, currentPos))
				{
					//当ったかどうか
					hit_result.isHIT = true;

					//物理マテリアル取得
					hit_result.physicsMaterial = (*itr)->GetPhysicsMaterial();

					//当ったアクター
					hit_result.hitActor = (*itr)->GetOwner();

					//HIT座標
					hit_result.hitPos = currentPos;

					//当るまでのレイの長さ
					hit_result.length = currentLen;

				}
			}
		}
		//スタート地点から探査した長さ
		currentLen += addLen;

		//現在の探索位置
		currentPos += dir * currentLen;
	}

	return hit_result;
}

//=============================================================================
// レイが当たった物を全て配列にまとめて返す関数
//=============================================================================
std::vector<s_HIT_Result> Manager_OBB::RaycastGetHit(Vector3 _startPos, Vector3 _endPos,
	Actor* _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE>_ignoreList, Color _drawRayColor, float _accuracy, int _drawRayLife)
{
	//HITリザルト配列
	std::vector<s_HIT_Result>ret;

	//開始点から終了点までの距離
	const float length = D3DXVec3Length(&(_endPos - _startPos));

	//繰り返し回数
	const int repeat = static_cast<int>(floor(length / _accuracy));

	//現在の探索位置
	Vector3 currentPos = _startPos;

	//プレイヤーからカメラの方向
	Vector3 dir;
	D3DXVec3Normalize(&dir, &(_endPos - _startPos));

	//描画用データ入力
	if (_isDispRay)
	{
		s_DrawData temp = {};
		temp.color = _drawRayColor;
		temp.startPos = _startPos;
		temp.endPos = _endPos;
		temp.time = 0;
		temp.timeMax = _drawRayLife;
		m_DebugDrawRayList.emplace_back(temp);
	}

	float currentLen = 0.0f;
	for (int i = 0; i < repeat; i++)
	{
		//OBBのレイヤー分繰り返す
		for (int k = 0; k < ACTOR_TYPE::MAX_ACTOR_TYPE; k++)
		{
			//カメラ同士は判定しない
			if (k == ACTOR_TYPE::COLLISION_CAMERA)continue;

			bool isIgn = false;
			//無視リストと現在のレイヤーを比較
			for (auto& ign : _ignoreList)
			{
				if (k == ign)
				{
					isIgn = true;
					break;
				}
			}
			if (isIgn)continue;

			auto itr = m_ComponentList[k].begin();
			//OBBの個数分繰り返す
			for (; itr != m_ComponentList[k].end(); itr++)
			{
				//自身を無視する設定なら無視する
				if (_ignoreMySelf && _ignoreMySelf == (*itr)->GetOwner())continue;

				//OBBに点がヒット
				if (OverlapJudgeOBBandPoint(*itr, currentPos))
				{
					//同じアクターは登録しない
					bool isContinue = false;
					for (auto& hitObjList : ret)
					{
						if (hitObjList.hitActor == (*itr)->GetOwner())
						{
							isContinue = true;
							break;
						}
					}
					if (isContinue)continue;

					//新規ヒットアクター登録
					s_HIT_Result hit_result = {};

					//当ったかどうか
					hit_result.isHIT = true;

					//物理マテリアル取得
					hit_result.physicsMaterial = (*itr)->GetPhysicsMaterial();

					//当ったアクター
					hit_result.hitActor = (*itr)->GetOwner();

					//HIT座標
					hit_result.hitPos = currentPos;

					//当るまでのレイの長さ
					hit_result.length = currentLen;

					//配列にHITリザルト登録
					ret.emplace_back(hit_result);

				}
			}
		}

		//スタート地点から探査した長さ
		currentLen += _accuracy;

		//現在の探索位置
		currentPos += dir * _accuracy;
	}

	return ret;
}
