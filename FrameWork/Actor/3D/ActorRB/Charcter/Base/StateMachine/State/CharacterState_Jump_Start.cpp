//=============================================================================
//
//  キャラクタージャンプ開始状態 [CharacterState_Jump_Start.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "CharacterState_Jump_Loop.h"
#include "CharacterState_Jump_Start.h"
#include "../StateMachine_Character.h"
#include "../../Character.h"
#include "../../../../../../../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// 初期化関数
//=============================================================================
void CharacterState_Jump_Start::Init(Character* _owner)
{

	//基底クラス初期化
	CharacterState::Init(_owner);

	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{
		//ブレンド先のアニメをジャンプ開始アニメに設定
		component_SkeletalMesh->SetNextAnimationName("Jump_Start");

		//0フレーム目からアニメをブレンド
		component_SkeletalMesh->SetNextAnimationFrame(0);

	}

	//オーナーをnullチェック
	if (m_Owner != nullptr)
	{
		//服の音を再生
		m_Owner->PlayClothSound();

		//アクセサリの音を再生
		m_Owner->PlayClothSoundMetal();

	}
}

//=============================================================================
// 更新関数
//=============================================================================
void CharacterState_Jump_Start::Update()
{
	//オーナーをnullチェック
	if (m_Owner != nullptr)
	{
		//スケルタルメッシュコンポーネントが存在する場合
		if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
		{
			//ブレンドレートが0.1以上の場合
			if (component_SkeletalMesh->GetBlendLate() > 0.1f)
			{
				//ジャンプ中に遷移
				m_Owner->GetStateMachine()->SetState<CharacterState_Jump_Loop>();

			}
		}
	}
}

//=============================================================================
// 終了関数
//=============================================================================
void CharacterState_Jump_Start::Uninit()
{
	//スケルタルメッシュコンポーネントが存在する場合
	if (Component_SkeletalMesh* component_SkeletalMesh = m_Owner->GetComponentByClass<Component_SkeletalMesh>())
	{	
		//ブレンド元のアニメをジャンプ開始アニメに設定
		component_SkeletalMesh->SetCurrentAnimationName("Jump_Start");

	}
}