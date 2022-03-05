//=============================================================================
//
//  キャラクターステート基底 [CharacterState.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "CharacterState.h"
#include "../../../../../../Camera.h"
#include "../../../../../../../../Manager/Manager_Game.h"
#include "../../../../../../../../Component/Component_Rigidbody.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr float LERP_ROTATION_SPEED = 0.2f;         //回転角の補間速度
constexpr float ONEFRAME_MAX_MOMENTUM = 1.5f;       //1フレームの最大運動量
constexpr float EFFECTIVE_VALUE = 0.1f;             //有効判定に用いる値
constexpr float DIADONAL_MOVEMENT_VALUE = 0.71428f; //45度斜め移動に用いる値

//=============================================================================
// 初期化関数
//=============================================================================
void CharacterState::Init(Character* _owner)
{
	//このコンポーネントのオーナーをnullチェック
	if (_owner!= nullptr)
	{
		//オーナーキャッシュ
		m_Owner = _owner;

		//剛体コンポーネント追加
		m_Component_Rigidbody = m_Owner->GetComponentByClass<Component_Rigidbody>();

	}
}

//=============================================================================
// 軸移動関数
//=============================================================================
void CharacterState::MoveAxis(float _forward_value, float _right_value)
{
	//剛体コンポーネントとオーナーをnullチェック
	if (m_Component_Rigidbody != nullptr && m_Owner != nullptr)
	{
		//斜め移動時の運動両制限処理
		if (fabsf(_forward_value) + fabsf(_right_value) >= ONEFRAME_MAX_MOMENTUM)
		{
			_forward_value = DIADONAL_MOVEMENT_VALUE * _forward_value;
			_right_value   = DIADONAL_MOVEMENT_VALUE * _right_value;
		}

		//オーナーの速度をキャッシュ
		float velocity = m_Owner->GetPlayerVelocity();

		//方向ベクトル
		Vector3 forward, right, up;

		//カメラがある存在する場合、キャッシュする
		if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
		{

			if (camera->GetOrientRotationtoMovement())
			{//プレイヤー軸移動モード

				//キャラクターの前方向ベクトルをキャッシュ
				forward = m_Owner->GetForward();

				//キャラクターの右方向ベクトルをキャッシュ
				right   = m_Owner->GetRight();  

				//前後軸移動処理
				m_Component_Rigidbody->SetMoveXZ(forward * velocity * _forward_value);

				//左右軸移動処理
				m_Component_Rigidbody->SetMoveXZ(right   * velocity * _right_value);

			}
			else
			{//カメラ軸移動モード

				//現在のキャラクターの回転をキャッシュ
				float rotationY       = m_Owner->GetRotation().y;

				//現在のカメラの回転をキャッシュ
				float cameraRotationY = camera->GetRotation().y;

				//カメラの方向ベクトルをキャッシュ

				forward = camera->GetForward();//前方向
				right   = camera->GetRight();  //右方向
				up      = camera->GetUp();     //上方向

				//アップとフォワードをPitch軸で補間して移動ベクトルに用いる
				D3DXVec3Lerp(&forward, &forward, &up, camera->GetRotation().x / VIEW_PITCH_MAX);

				//前後軸移動処理
				m_Component_Rigidbody->SetMoveXZ(forward * velocity * _forward_value);

				//左右軸処理
				m_Component_Rigidbody->SetMoveXZ(right   * velocity * _right_value);


				//キャラクター回転線形補間計算

				int   input_cnt = 0;     //キー入力数
				float degree = 0.0f;     //度数
				int   vector_pattern = 0;//方向のパターン

				if (_right_value > EFFECTIVE_VALUE)
				{//右方向補間

					//キー入力数加算
					input_cnt++;

					//180度以上回転してしまう場合逆で補正
					if (rotationY <= cameraRotationY + DegToRad(-135.0f))
					{
						rotationY = cameraRotationY + DegToRad(180.0f);
					}

					//進行のパターン
					vector_pattern = 1;

					//カメラから見て右方向指定
					degree += DegToRad(90.0f);

				}
				else if (_right_value < -EFFECTIVE_VALUE)
				{//左方向補間

					//キー入力数加算
					input_cnt++;

					//180度以上回転してしまう場合逆で補正
					if (rotationY >= cameraRotationY + DegToRad(135.0f))
					{
						rotationY = cameraRotationY + DegToRad(-180.0f);
					}

					//進行のパターン
					vector_pattern = 2;

					//カメラから見て左方向指定
					degree += DegToRad(-90.0f);
				}
				if (_forward_value > EFFECTIVE_VALUE)
				{//前方向補間

					//キー入力数加算
					input_cnt++;

				}
				else if (_forward_value < -EFFECTIVE_VALUE)
				{//後ろ方向補間

					//キー入力数加算
					input_cnt++;

					//正と負の絶対値が小さい方で補間
					if (vector_pattern == 0)
					{
						//絶対値を比較
						(fabsf(rotationY - cameraRotationY + DegToRad(180.0f)) < fabsf(rotationY - cameraRotationY + DegToRad(-180.0f))) 
							? degree += DegToRad(-180.0f) : degree += DegToRad(180.0f);
					}
					else if (vector_pattern == 1)
					{
						degree += DegToRad(180.0f);
					}
					else
					{
						degree += DegToRad(-180.0f);
					}
				
		

				}
				if (input_cnt > 0)
				{//キー入力があった場合

					//入力方向数で回転角を割る
					cameraRotationY += degree / input_cnt;

					//カメラとキャラクターの回転差分を補間し回転角代入
					rotationY = Math::lerpf(rotationY, cameraRotationY, LERP_ROTATION_SPEED);

					//回転角設定
					m_Owner->SetRotation(Vector3{ m_Owner->GetRotation().x,Math::clamp(rotationY,DegToRad(-360.0f),DegToRad(360.0f)),m_Owner->GetRotation().z});

				}
			}
		}
	}
}

//=============================================================================
// ジャンプ関数
//=============================================================================
void CharacterState::Jump()
{
	//剛体コンポーネントをnullチェック
	if (m_Component_Rigidbody != nullptr)
	{
		//剛体コンポーネントジャンプ処理
		m_Component_Rigidbody->Jump();
	}
}
