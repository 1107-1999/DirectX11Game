//=============================================================================
//
//  �^�C�g���V�[���p�v���C���[�R���g���[���[ [PC_Title.cpp]
//  Date   : 2021/1/08
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "PC_Title.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../System/Main.h"
#include "../System/MainWindow.h"
#include "../System/Math.h"
#include "../Level/Base/Level.h"
#include "../Actor/3D/Camera.h"
#include "../Actor/3D/ActorRB/Charcter/Base/Character.h"
#include "../Actor/HUD/HUD_Game.h"
#include "../PlayerController/PC_Game.h"

//=============================================================================
// �萔��`
//=============================================================================
constexpr float HALF_SPEED  = 0.5f;
constexpr float ACCEL_SPEED = 2.0f;

//=============================================================================
// �������֐�
//=============================================================================
void PC_Title::Init()
{
	//��ꏉ����
	PlayerController::Init();

	//�}�E�X���΍��W���[�h�ɕύX
	if (m_Input != nullptr)
	{
		m_Input->Mouse_SetMode(Input::MOUSE_POSITION_MODE_ABSOLUTE);
	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void PC_Title::Update()
{
	if (m_Input != nullptr)
	{
		//�K���ȃL�[��������
		if (InputAction_Main() || InputAction_Second() || InputAction_Jump())
		{
			//�J���������x���ɑ��݂���ꍇ
			if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
			{
				//�����J��������
				camera->AddTargetLength(300.0f);
			}

			//PlayerController�ύX
			Manager_Game::Instance()->SetPlayerController<PC_Game>();

			//HUD�ύX
			Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->SetHUD<HUD_Game>();
		}
	}

	//�L�����N�^�[�����x���ɑ��݂���ꍇ
	if (Character* character = Manager_Game::Instance()->GetLevel()->GetActor<Character>())
	{			
		//��~����
		character->MoveAxis(0.0f, 0.0f);
	}
}
