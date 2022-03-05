//=============================================================================
//
//  �e�N���X [Gun.cpp]
//  Date   : 2021/1/25
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Gun.h"
#include "../Camera.h"
#include "../ActorRB/Prop/GunTarget.h"
#include "../../../Component/Component_Model/Component_StaticMesh.h"
#include "../../../Component/Component_OBB.h"
#include "../../../Manager/Manager_Game.h"
#include "../../../Manager/Manager_Actor/Manager_Bullet.h"
#include "../../../Level/Base/Level.h"
#include "../../../Sound/GunFire.h"
#include "../../../PlayerController/PC_Game.h"

//=============================================================================
// �萔�錾
//=============================================================================
constexpr float BULLET_SPEED       = 12.0f;//�e��
constexpr float RECOIL_POWER_YAW   = 0.005f;  //YAW���R�C��
constexpr float RECOIL_POWER_PITCH = -0.025f; //Pitch���R�C��
constexpr int   RECOIL_COUNT       = 12;      //���R�C�������ɂ�����t���[����
constexpr int   RECOIL_PATTERN     = 2;       //���R�C���̎��

//=============================================================================
// ���\�[�X�ǂݍ��݁E�폜�֐�
//=============================================================================
void  Gun::Load()
{
	//�e���ǂݍ���
	GunFire::Load();
}
void  Gun::Unload()
{
	//�e���폜
	GunFire::Unload();
}

//=============================================================================
// �������֐�
//=============================================================================
void  Gun::Init()
{
	//�e�N���X������
	Actor3D::Init();

	//�ÓI���b�V���R���|�[�l���g�ǉ�
	m_Component_StaticMesh = AddComponent<Component_StaticMesh>(0);

	//�ÓI���b�V���R���|�[�l���gnull�`�F�b�N
	if (m_Component_StaticMesh != nullptr)
	{
		//���f�����[�h
		m_Component_StaticMesh->LoadStaticMesh("ROM\\3D\\Prop\\SM_Sniper.fbx");

		//��]�I�t�Z�b�g����
		m_Component_StaticMesh->SetRotationOffset(Vector3{ DegToRad(90.0f),DegToRad(-95.0f),DegToRad(0.0f) });

		//�X�P�[���I�t�Z�b�g����
		m_Component_StaticMesh->SetScaleRate(0.01f);
	}

	//OBB�R���|�[�l���g�ǉ�
	m_Component_OBB = AddComponent<Component_OBB>(0);

	//OBB�R���|�[�l���gnull�`�F�b�N
	if (m_Component_OBB != nullptr)
	{
		//���W�b�h�{�f�B�Ɠ��X�P�[���ɒ���
		m_Component_OBB->SetScale(Vector3{ 2.0f,0.25f,2.0f });

		//���W�I�t�Z�b�g����
		m_Component_OBB->SetPositionOffset(Vector3{ 0.0f,0.0f,-0.6f });

		//���C�R���W�����𖳎�
		m_Component_OBB->SetIsReactRay(false);

		//�����}�e���A���𖳌�
		m_Component_OBB->SetPhysicsMaterial(PM_IGNORE);
	}

	//�v���C���[�R���g���[���[���擾&�L���X�g���ăL���b�V��
	m_PlayerConroller = dynamic_cast<PC_Game*>(Manager_Game::Instance()->GetPlayerController());

	//�e�Ǘ��N���X�����x���ɒǉ����ăL���b�V��
	m_Manager_Bullet = Manager_Game::Instance()->GetLevel()->AddManager_Actor<Manager_Bullet>();

	//�e���N���X����
	m_GunFire = new GunFire;

	//�e���N���Xnull�`�F�b�N
	if (m_GunFire != nullptr)
	{
		//�e���N���X������
		m_GunFire->Init();
	}

	//���R�C���J�E���g������
	m_RecoilCount = 0;

	//���R�C���E����
	m_RecoilVectorRight = true;

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Gun::Update()
{
	//�v���C���[�R���g���[���[null�`�F�b�N
	if (m_PlayerConroller != nullptr)
	{
	    //�v���C���[�ƐڐG���Ă���ꍇ
		if (m_Component_OBB->GetOverlap())
		{
			//�v���C���[�R���g���[���[�ɏe�Ƃ̃I�[�o�[���b�v�����n��
			m_PlayerConroller->SetGunFlag(true);

		}
		//�v���C���[�ƐڐG���Ă��Ȃ��ꍇ
		else
		{
			//�v���C���[�R���g���[���[�̏e�Ƃ̃I�[�o�[���b�v���������
			m_PlayerConroller->SetGunFlag(false);

		}
	}
	else//null�̏ꍇ�L���b�V��
	{
		//�v���C���[�R���g���[���[���擾&�L���X�g���ăL���b�V��
		m_PlayerConroller = dynamic_cast<PC_Game*>(Manager_Game::Instance()->GetPlayerController());
	}

	if (m_RecoilCount > 0)
	{
		if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
		{
			//Yaw���R�C�������ŕ���
			if (m_RecoilVectorRight)
			{
				//�E�Ƀ��R�C��
				camera->AddCameraYaw(RECOIL_POWER_YAW);
			}
			else
			{
				//���Ƀ��R�C��
				camera->AddCameraYaw(-RECOIL_POWER_YAW);
			}

			//Pitch���R�C��
			camera->AddCameraPitch(RECOIL_POWER_PITCH);

			//���R�C�����Ԍ���
			m_RecoilCount--;
		}
	}

	//�e�N���X�X�V
	Actor3D::Update();
}

//=============================================================================
// �I���֐�
//=============================================================================
void Gun::Uninit()
{
	//�e���N���X�I��
	if (m_GunFire != nullptr)
	{
		m_GunFire->Uninit();
		delete m_GunFire;
		m_GunFire = nullptr;
	}

	//�e�N���X�X�V
	Actor3D::Uninit();
}

//=============================================================================
// �ˌ��֐�
//=============================================================================
void Gun::Shot()
{
	//OBB�R���|�[�l���gnull�`�F�b�N
	if (m_Component_OBB != nullptr && m_RecoilCount == 0)
	{

		//���R�C������
		m_RecoilCount = RECOIL_COUNT;

		//Yaw���R�C�������ŕ���
		int random = rand() % RECOIL_PATTERN;

		switch (random)
		{
		case 0:
			//���R�C���E����
			m_RecoilVectorRight = true;
			break;

		case 1:
			//���R�C��������
			m_RecoilVectorRight = false;
			break;

		}

		//�J�������W�L���b�V��
		Vector3 cameraPosition = Manager_Game::Instance()->GetLevel()->GetActor<Camera>()->GetPosition();

		//�J�����O�����x�N�g���L���b�V��
		Vector3 cameraForward = Manager_Game::Instance()->GetLevel()->GetActor<Camera>()->GetForward();

		//���C�̖������C���[�̃��X�g
		std::list<ACTOR_TYPE>rocalIgnoreList;
		rocalIgnoreList.push_back(ACTOR_TYPE::COLLISION_PLAYER);
		rocalIgnoreList.push_back(ACTOR_TYPE::COLLISION_GUN);
		rocalIgnoreList.push_back(ACTOR_TYPE::COLLISION_BULLET);
		rocalIgnoreList.push_back(ACTOR_TYPE::COLLISION_BLOCK);
		rocalIgnoreList.push_back(ACTOR_TYPE::COLLISION_CAMERA);
		rocalIgnoreList.push_back(ACTOR_TYPE::MAX_ACTOR_TYPE);

	    //���C�ŃA�N�^�[���擾
		s_HIT_Result hit_result = m_Component_OBB->RaycastHighAccuracy(cameraPosition, cameraPosition + cameraForward * 100.0f, this, true,
			rocalIgnoreList,
			Color(1, 0, 1, 1));

		if (GunTarget* target = dynamic_cast<GunTarget*>(hit_result.hitActor))
		{
			//OBB�擾
			if (Component_OBB* target_OBB = target->GetComponentByClass<Component_OBB>())
			{
				target_OBB->SetOverlap(true);

			}
		}

		//�e�}�l�[�W���[
		if (m_Manager_Bullet != nullptr)
		{
			//�e����
			m_Manager_Bullet->SpawnBullet(cameraPosition, cameraForward, Manager_Game::Instance()->GetLevel()->GetActor<Camera>()->GetRotation());
		}


		//�e���N���Xnull�`�F�b�N
		if (m_GunFire != nullptr)
		{
			//�e���Đ�
			m_GunFire->Play();
		}

	}

}