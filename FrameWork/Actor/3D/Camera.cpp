//=============================================================================
//
//  カメラ制御 [Camera.cpp]
//  Date   : 2021/11/20
//
//=============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Camera.h"
#include "ActorRB/Charcter/Base/Character.h"
#include "../3D/Prop/Gun.h"
#include "../../System/MainWindow.h"
#include "../../Renderer/Renderer_DirectX11.h"
#include "../../Manager/Manager_Game.h"
#include "../../Manager/Manager_Drawer/Manager_ImGui.h"
#include "../../Component/Component_OBB.h"
#include "../../Component/Component_Rigidbody.h"
#include "../../Level/Base/Level.h"

//=============================================================================
// 定数宣言
//=============================================================================
constexpr float CAMERA_NEAR   = 0.1f;     //ニア
constexpr float CAMERA_FAR    = 1000.0f;  //ファー

//=============================================================================
// 初期化関数
//=============================================================================
void Camera::Init()
{
	//親クラス初期化
	Actor3D::Init();

	//注視点対象をnullptr化
	m_Owner = nullptr;

	//初期座標
	m_Position = Vector3(0.5f, 2.5f, 0.5f);

	//初期スケール
	m_Scale    = Vector3(0.5f, 0.5f, 0.5f);

	//初期ターゲット
	m_Target = m_Position + GetForward();

	//座標オフセット
	m_Offset_Position = Vector3_Zero;

	//OBBコンポーネント追加
	m_Component_OBB = AddComponent<Component_OBB>(0);

	//OBBコンポーネントnullチェック
	if (m_Component_OBB != nullptr)
	{
		//可視性
		m_Component_OBB->SetVisibility(true);
		//スケール設定
		m_Component_OBB->SetScale(Vector3{ 1,1,1 });
	}


	//視野
	m_FOV    = DEFAULT_FOV;

	//カメラ距離
	m_TargetArmLength = 2.0f;

	//進行方向を向くかどうか
	m_OrientRotationtoMovement = false;

	//レイ判定使用
	m_IsUseRayHit = true;

}

//=============================================================================
// 更新関数
//=============================================================================
void Camera::Update()
{
	//注視点対象nullチェック
	if (m_Owner != nullptr)
	{

		//注視点取得
		m_Target = m_Owner->GetPosition() + m_Offset_Position;

		//注視点対象の前方ベクトルをキャッシュ
		Vector3 targetForward = m_Owner->GetForward();

		if (m_OrientRotationtoMovement)
		{//Y軸固定カメラ
			m_Position.y = m_Target.y - GetForward().y  * m_TargetArmLength;
			m_Position.x = m_Target.x - targetForward.x * m_TargetArmLength;
			m_Position.z = m_Target.z - targetForward.z * m_TargetArmLength;
		}
		else
		{//サードパーソンビュー
			m_Position = m_Target - GetForward() * m_TargetArmLength;
		}
	}
	else
	{
		m_Target = m_Position + GetForward();
	}

	//親クラス更新
	Actor3D::Update();

	// カメラバッファのセット
	CAMERA camera;
	camera.Position = Vector4(m_Position, 0.0f);
	camera.Length = D3DXVec3Length(&m_Position);


	//プレイヤーからカメラまでレイでチェック
	if (Character* character = dynamic_cast<Character*>( m_Owner))
	{
			if (m_IsUseRayHit)
			{
			std::vector < s_HIT_Result> hit =
				GetComponentByClass<Component_OBB>()->RaycastGetHit(m_Owner->GetPosition(), m_Position);


			if (!hit.empty())//レイが当たった場合
			{
				s_HIT_Result* nearestObj = nullptr;
				for (auto& i : hit)
				{
					if (i.hitActor == nullptr)continue;
					if (!i.hitActor->GetComponentByClass<Component_OBB>()->GetIsReactRay())continue;//レイに反応しない

					//カメラの向いているプレイヤーは判定しない
					if (m_Owner != i.hitActor)
					{
						//nullかプレイヤーに近いオブジェクト
						if (!nearestObj || i.length < nearestObj->length)
						{
							nearestObj = &i;
						}
					}
				}

				//プレイヤーとカメラ以外のオブジェクトに当たったらプレイヤーに
				//一番近いオブジェクトにヒットした場所にカメラをセットする
				if (nearestObj)
				{
					m_Position = nearestObj->hitPos;
					Vector3 tempDir;
					D3DXVec3Normalize(&tempDir, &(m_Position - m_Owner->GetPosition()));
					m_Position -= tempDir * m_Scale.z;
				}
			}
		}
	}
	else if (m_FirstPerson)
	{//一人称視点の場合

		//スコープの位置にカメラを設定
		m_Position = m_Owner->GetPosition() + HalfSize(m_Owner->GetForward()) +  Size25(m_Owner->GetUp());

		//前方向を注視点
		m_Target = m_Position + GetForward();

		//カメラ正規化
		m_Rotation.y = Math::clamp(m_Rotation.y, -VIEW_PITCH_MAX, VIEW_PITCH_MAX);

		
	}

	//カメラ情報を設定
	Renderer_DirectX11::Instance()->SetCamera(camera);
}

//=============================================================================
// 視点設定処理関数
//=============================================================================
void Camera::SetView()
{
	//ビューマトリクス設定
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target,
		&Vector3(0.0f, 1.0f, 0.0f));

	//ビューを設定
	Renderer_DirectX11::Instance()->SetViewMatrix(&m_ViewMatrix);

	// 画角設定
	float windowX = static_cast<float>(MainWindow::Instance()->GetWindowSize().x);
	float windowY = static_cast<float>(MainWindow::Instance()->GetWindowSize().y);

	//プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, m_FOV,
		static_cast<float>(windowX) / static_cast<float>(windowY), CAMERA_NEAR, CAMERA_FAR);

	//プロジェクションマトリクス設定
	Renderer_DirectX11::Instance()->SetProjectionMatrix(&m_ProjectionMatrix);

}

//=============================================================================
// 視錐台カリング関数
//=============================================================================
bool Camera::CheckView(Vector3 _position, Vector3 _scale)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	Vector3 vpos[4];
	Vector3 wpos[4];

	vpos[0] = Vector3(-1.0f, 1.0f, 1.0f);
	vpos[1] = Vector3(1.0f, 1.0f, 1.0f);
	vpos[2] = Vector3(-1.0f, -1.0f, 1.0f);
	vpos[3] = Vector3(1.0f, -1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	Vector3 v, v1, v2, n;

	// カメラから見たオブジェクトのベクトル
	v = _position - m_Position;

	/*=============== 左面 ==================*/
	v1 = wpos[0] - m_Position;
	v2 = wpos[2] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);

	if (D3DXVec3Dot(&n, &v) < 0.0f)
	{
		return false;
	}

	/*=============== 右面 ==================*/
	v1 = wpos[1] - m_Position;
	v2 = wpos[3] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);

	if (D3DXVec3Dot(&n, &v) > 0.0f)
	{
		return false;
	}

	/*=============== 上面 ==================*/
	v1 = wpos[0] - m_Position;
	v2 = wpos[1] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);

	if (D3DXVec3Dot(&n, &v) > 0.0f)
	{
		return false;
	}

	/*=============== 下面 ==================*/
	v1 = wpos[2] - m_Position;
	v2 = wpos[3] - m_Position;
	D3DXVec3Cross(&n, &v1, &v2);

	if (D3DXVec3Dot(&n, &v) < 0.0f)
	{
		return false;
	}

	return true;
}


//=============================================================================
// カメラ移動関数
//=============================================================================
void Camera::Move(float _forward, float _right)
{
	//入力に応じて座標加算
	m_Position = m_Position + _forward * GetForward() + _right * GetRight();
}

//=============================================================================
// カメラYaw回転関数
//=============================================================================
void Camera::AddCameraYaw(float _value) 
{
	//加算
	m_Rotation.y += _value;

	//Yaw軸正規化
	if (m_Rotation.y < DegToRad(-180.0f))
	{
		m_Rotation.y += DegToRad(360.0f);
		if (m_Owner != nullptr)
		{//オーナーをキャッシュしオーナーも正規化
			Vector3 rotation = m_Owner->GetRotation();
			m_Owner->SetRotation(Vector3{ rotation .x,rotation.y + DegToRad(360.0f),rotation.z});
		}

	}
	else if (m_Rotation.y > DegToRad(180.0f))
	{
		m_Rotation.y -= DegToRad(360.0f);
		if (m_Owner != nullptr)
		{//オーナーをキャッシュしオーナーも正規化
			Vector3 rotation = m_Owner->GetRotation();
			m_Owner->SetRotation(Vector3{ rotation.x,rotation.y - DegToRad(360.0f),rotation.z });
		}
	}

}

//=============================================================================
// カメラPitch回転関数
//=============================================================================
void Camera::AddCameraPitch(float _value)
{
	//加算後に正規化
	m_Rotation.x = Math::clamp(m_Rotation.x + _value, -VIEW_PITCH_MAX, VIEW_PITCH_MAX);
}


//=============================================================================
// ターゲット距離加算
//=============================================================================
void Camera::AddTargetLength(float _length)
{
	//1フレームで加算されるカメラオフセットY座標
	float offset_y = (MAX_OFFSET_POSITION_Y - MIN_OFFSET_POSITION_Y) / ((MAX_TARGET_ARM_LENGTH - MIN_TARGET_ARM_LENGTH) / _length);

	//加算&正規化
	m_TargetArmLength = Math::clamp(m_TargetArmLength + _length, MIN_TARGET_ARM_LENGTH, MAX_TARGET_ARM_LENGTH);

	//オフセット調整
	m_Offset_Position.y = Math::clamp(m_Offset_Position.y - offset_y, MIN_OFFSET_POSITION_Y, MAX_OFFSET_POSITION_Y);
}
