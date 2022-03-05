//==============================================================================
//
//  �Q�[���V�[���p�v���C���[�R���g���[���[ [PC_Game.cpp]
//  Date   : 2021/1/22
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "PC_Game.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../System/Main.h"
#include "../System/MainWindow.h"
#include "../Level/Base/Level.h"
#include "../Level/Level_Game.h"
#include "../Level/Level_Title.h"
#include "../Actor/3D/ActorRB/Charcter/Base/Character.h"
#include "../Actor/3D/Camera.h"
#include "../Actor/3D/Prop/Gun.h"
#include "../Actor/HUD/HUD_Game.h"
#include "../Component/Component_Model/Component_StaticMesh.h"
#include "../Component/Component_Model/Component_SkeletalMesh.h"

//=============================================================================
// �萔��`
//=============================================================================
constexpr float ONE_FRAME_LERP_RATE = 0.005f;//1�t���[���ɕ⊮����䗦

//=============================================================================
// �������֐�
//=============================================================================
void PC_Game::Init()
{
	//���N���X������
	PlayerController::Init();

	//�}�E�X���΍��W���[�h�ɕύX
	if (m_Input != nullptr)
	{
		m_Input->Mouse_SetMode(Input::MOUSE_POSITION_MODE_RELATIVE);
	}

	//�X�R�[�v�t���O������
	m_ScopeFlag = false;

	//�e���[�h�t���O������
	m_GunFlag = false;

	//�ˌ��t���O������
	m_ShotFlag = false;

	//�S�[���t���O������
	m_GoalFlag = false;  

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void PC_Game::Update()
{
	if (m_Input != nullptr)
	{
		if (InputAction_Pause())
		{//�|�[�Y����
			if (m_Input->GetMouse_PositionMode() == Input::MOUSE_POSITION_MODE_RELATIVE)
			{
				m_Input->Mouse_SetMode(Input::MOUSE_POSITION_MODE_ABSOLUTE);
			}
			else
			{
				m_Input->Mouse_SetMode(Input::MOUSE_POSITION_MODE_RELATIVE);
			}
		}

		if (m_Input->GetMouse_PositionMode() == Input::MOUSE_POSITION_MODE_RELATIVE)
		{//���΍��W���[�h�Ȃ�v���C���[����
			if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
			{
				if (!m_ScopeFlag)
				{//��X�R�[�v����

					if (Character* character = Manager_Game::Instance()->GetLevel()->GetActor<Character>())
					{//�L�����N�^�[�����x���ɑ��݂���ꍇ

						//=============================================================================
						//���ړ�
						//=============================================================================

						character->MoveAxis(MoveForward(), MoveRight());

						//=============================================================================
						//�J��������
						//=============================================================================

						//Yaw���J�����p�x
						if (camera->GetOrientRotationtoMovement())
						{//��Ƀv���C���[���J��������������
							character->MoveRotation(Turn());
						}
						else
						{//�I�[�\�h�b�N�X�ȃT�[�h�p�[�\���r���[
							camera->AddCameraYaw(Turn());
						}
						//Pitch���J�����p�x
						camera->AddCameraPitch(LookUp());

						//�J��������
						camera->AddTargetLength(Zoom());

						//=============================================================================
						//�A�N�V����
						//=============================================================================

						if (InputAction_Jump())
						{//�W�����v
							character->Jump();
						}

						//�X�v�����g
						character->Sprint(InputAction_Sprint());

						if (InputAction_Main())
						{//���C���A�N�V����

							//�S�[���t���O�`�F�b�N
							if (m_GoalFlag)
							{
								//�^�C�g���V�[���Z�b�g
								character->SetRigidbodyPosition({ 0.0f,3.0f,-3.5f });
							}
						}

						//�Z�J���h�A�N�V����
						if (InputAction_Second())
						{
							if (m_GunFlag)
							{//�e���߂��ɂ���

								//�X�R�[�v�t���O�I��
								m_ScopeFlag = true;

								if (HUD_Game* hud = dynamic_cast<HUD_Game*>(Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetHUD()))
								{
									//�X�R�[�v��UI��\��
									hud->SetScopeUI(m_ScopeFlag);

									//�v���C���[��\��
									character->GetComponentByClass<Component_SkeletalMesh>()->SetActive(false);

									//�v���C���[��~
									character->MoveAxis(0.0f, 0.0f);

									if (Gun* gun = Manager_Game::Instance()->GetLevel()->GetActor<Gun>())
									{
										//�e��\��
										gun->GetComponentByClass<Component_StaticMesh>()->SetActive(false);
										//�J��������l�̂ɐݒ�
										camera->SetFirstPerson(true);
										//�J�����̃I�[�i�[�ɏe���Z�b�g
										camera->SetOwner(gun);

									}
								}
							}
						}
					}
				}
				else
				{
			
					//Pitch���J�����p�x
					camera->AddCameraPitch(LookUp());
					//Yaw���J�����p�x
					camera->AddCameraYaw(Turn());
						
					//�X�R�[�v�Y�[��
					camera->SetFOV(camera->GetFOV() + Zoom());
				

					if (InputAction_Main())
					{//���C���A�N�V����

						m_ShotFlag = true;

					}
					else if(m_ShotFlag)
					{
						if (Gun* gun = Manager_Game::Instance()->GetLevel()->GetActor<Gun>())
						{
							gun->Shot();
							m_ShotFlag = false;
						}
					}
				
					if (!InputAction_Second())
					{//�Z�J���h�A�N�V�����������Ă��Ȃ�

						if (m_GunFlag)
						{//�e���߂��ɂ���

							//�X�R�[�v�t���O�I�t
							m_ScopeFlag = false;

							//�Q�[��HUD�擾
							if (HUD_Game* hud = dynamic_cast<HUD_Game*>(Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetHUD()))
							{

								//����p������
								camera->SetFOV(DEFAULT_FOV);

								//�X�R�[�v��UI���폜
								hud->SetScopeUI(m_ScopeFlag);

								if (Character* character = Manager_Game::Instance()->GetLevel()->GetActor<Character>())
								{
									//�v���C���[�\��
									character->GetComponentByClass<Component_SkeletalMesh>()->SetActive(true);
									//�J�������O�l�̂ɐݒ�
									camera->SetFirstPerson(false);
									//�J�����̃I�[�i�[�ɃL�����N�^�[���Z�b�g
									camera->SetOwner(character);
								}

								//��\��
								if (Gun* gun = Manager_Game::Instance()->GetLevel()->GetActor<Gun>())
								{
									gun->GetComponentByClass<Component_StaticMesh>()->SetActive(true);
								}
							}

						}		
					}
				}
			}
		}
	}
}
