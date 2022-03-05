//=============================================================================
//
//  キャラクター基底クラス [Character.cpp]
//  Date   : 2021/11/4
//
//=============================================================================

//=============================================================================
//  インクルード
//=============================================================================
#include "Character.h"
#include "StateMachine/StateMachine_Character.h"
#include "../../../../../Component/Component_Model/Component_SkeletalMesh.h"
#include "../../../../../Manager/Manager_Shader.h"
#include "../../../../../System/MainWindow.h"
#include "../../../../../Sound/FootStep.h"
#include "../../../../../Sound/Cloth.h"

//=============================================================================
//  定数宣言
//=============================================================================
constexpr int   PLAYER_MASS             = 100;      //プレイヤーの質量
constexpr float LERP_ROTATION_SPEED     = 0.2f;     //回転角の補間速度
constexpr float ONEFRAME_MAX_MOMENTUM   = 1.5f;     //1フレームの最大運動量
constexpr float EFFECTIVE_VALUE         = 0.1f;     //有効判定に用いる値
constexpr float DIADONAL_MOVEMENT_VALUE = 0.71428f; //45度斜め移動に用いる値
constexpr float INERTIA                 = 0.98f;    //慣性

//=============================================================================
//  リソース読み込み・削除関数
//=============================================================================
void  Character::Load()
{
	//足音読み込み
	FootStep::Load();

	//服音読み込み
	Cloth::Load();
}
void  Character::Unload()
{
	//足音削除
	FootStep::Unload();

	//服音削除
	Cloth::Unload();
}

//=============================================================================
// 初期化関数
//=============================================================================
void  Character::Init()
{
	//親クラス初期化
	ActorRB::Init();

	//移動速度初期化
	m_PlayerVelocity = 0.0f;

#pragma region ModelConfig

	//スケルタルメッシュコンポーネント追加
	m_Component_SkeletalMesh = AddComponent<Component_SkeletalMesh>(0);

	//スケルタルメッシュコンポーネントnullチェック
	if (m_Component_SkeletalMesh != nullptr)
	{

		//スケルタルメッシュ読み込み
		m_Component_SkeletalMesh->LoadSkeletalMesh("ROM\\3D\\Character\\Hutao\\SK_Hutao.fbx");

		//アニメーション読み込み
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_Idle.fbx",         "Idle");       //棒立ちアニメ
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_Running.fbx",      "Walk");       //歩きアニメ
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_Sprint.fbx",       "Run");        //走りアニメ
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_Jump_Start.fbx",   "Jump_Start"); //ジャンプ開始アニメ
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_Jump_Loop.fbx",    "Jump_Loop");  //ジャンプ中アニメ
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_falling_idle.fbx", "Fall");       //落下アニメ

		//シェーダー設定
		m_Component_SkeletalMesh->SetShaderType(Manager_Shader::SHADER_TYPE::SHADER_UNLIT);

		//初期ステート
		m_Component_SkeletalMesh->SetCurrentAnimationName("Idle");

		//描画サイズ比率変更
		m_Component_SkeletalMesh->SetScaleRate(0.0005f);//モデルデータの0.0005倍

		//座標オフセット調整
		m_Component_SkeletalMesh->SetPositionOffset(Vector3(0.0f, -0.525f, 0.0f));

		//回転オフセット調整
		m_Component_SkeletalMesh->SetRotationOffset(Vector3{ DegToRad(0.0f),DegToRad(180.0f),DegToRad(0.0f) });

	}

#pragma endregion

	//半径0.5,高さ1.0のカプセル型剛体追加
	AddCapsuleRB(0.5f, 1.0f, m_Position, m_Rotation, PLAYER_MASS);
	

	//ステートマシン初期化
	if (m_StateMachine = new StateMachine_Character)
	{
		m_StateMachine->Init(this);
		m_StateMachine->Jump();
	}


	//足音クラス生成
	m_FootStep = new FootStep;

	//足音クラスnullチェック
	if (m_FootStep != nullptr)
	{
		//足音クラス初期化
		m_FootStep->Init();
	}

	//服音クラス生成
    m_ClothSounds = new Cloth;

	//服の音クラスnullチェック
	if (m_ClothSounds != nullptr)
	{
		//服音クラス初期化
		m_ClothSounds->Init();
	}

}

//=============================================================================
// 更新関数
//=============================================================================
void Character::Update()
{
	//ステートマシン更新
	if (m_StateMachine != nullptr)
	{
		m_StateMachine->Update();
	}

	//移動速度に慣性加算
	m_PlayerVelocity *= INERTIA;

	//親クラス更新
	ActorRB::Update();

}

//=============================================================================
// 終了関数
//=============================================================================
void Character::Uninit()
{
	//ステートマシン終了
	if (m_StateMachine != nullptr)
	{
		m_StateMachine->Uninit();
		delete m_StateMachine;
		m_StateMachine = nullptr;
	}

	//足音クラス終了
	if (m_FootStep != nullptr)
	{
		m_FootStep->Uninit();
		delete m_FootStep;
		m_FootStep = nullptr;
	}

	//服の音クラス終了
	if (m_ClothSounds != nullptr)
	{
		m_ClothSounds->Uninit();
		delete m_ClothSounds;
		m_ClothSounds = nullptr;
	}

	//親クラス終了
	ActorRB::Uninit();
}

//=============================================================================
// 回転関数
//=============================================================================
void Character::MoveRotation(float _mouseX)
{
	m_Rotation.y += _mouseX;
}


//=============================================================================
// 軸移動関数
//=============================================================================
void Character::MoveAxis(float _forward_value, float _right_value)
{
	//ステートマシンからステートに軸移動命令
	if (m_StateMachine != nullptr)
	{
		m_StateMachine->MoveAxis(_forward_value, _right_value);
	}
}

//=============================================================================
// スプリント関数
//=============================================================================
void Character::Sprint(bool _input)
{
	//ステートマシンからステートにスプリント命令
	if (m_StateMachine != nullptr)
	{
		m_StateMachine->Sprint(_input);
	}
}

//=============================================================================
// ジャンプ関数
//=============================================================================
void Character::Jump()
{
	//ステートマシンからステートにジャンプ命令
	if (m_StateMachine != nullptr)
	{
		m_StateMachine->Jump();
	}
}

//=============================================================================
// 足音再生関数
//=============================================================================
void Character::PlayFootStep(int _physicsMaterial)
{
	//足音クラスnullチェック
	if (m_FootStep != nullptr)
	{
		//再生
		m_FootStep->Play(_physicsMaterial);
	}
}

//=============================================================================
// 服の音再生関数
//=============================================================================
void Character::PlayClothSound()
{
	//服の音クラスnullチェック
	if (m_ClothSounds != nullptr)
	{
		//再生
		m_ClothSounds->PlayClothSound();
	}
}

//アクセサリ音再生
void Character::PlayClothSoundMetal()
{
	//服の音クラスnullチェック
	if (m_ClothSounds != nullptr)
	{
		//再生
		m_ClothSounds->PlaySoundsMetal();
	}
}