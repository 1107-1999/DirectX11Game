//=============================================================================
//
//  �L�����N�^�[���N���X [Character.cpp]
//  Date   : 2021/11/4
//
//=============================================================================

//=============================================================================
//  �C���N���[�h
//=============================================================================
#include "Character.h"
#include "StateMachine/StateMachine_Character.h"
#include "../../../../../Component/Component_Model/Component_SkeletalMesh.h"
#include "../../../../../Manager/Manager_Shader.h"
#include "../../../../../System/MainWindow.h"
#include "../../../../../Sound/FootStep.h"
#include "../../../../../Sound/Cloth.h"

//=============================================================================
//  �萔�錾
//=============================================================================
constexpr int   PLAYER_MASS             = 100;      //�v���C���[�̎���
constexpr float LERP_ROTATION_SPEED     = 0.2f;     //��]�p�̕�ԑ��x
constexpr float ONEFRAME_MAX_MOMENTUM   = 1.5f;     //1�t���[���̍ő�^����
constexpr float EFFECTIVE_VALUE         = 0.1f;     //�L������ɗp����l
constexpr float DIADONAL_MOVEMENT_VALUE = 0.71428f; //45�x�΂߈ړ��ɗp����l
constexpr float INERTIA                 = 0.98f;    //����

//=============================================================================
//  ���\�[�X�ǂݍ��݁E�폜�֐�
//=============================================================================
void  Character::Load()
{
	//�����ǂݍ���
	FootStep::Load();

	//�����ǂݍ���
	Cloth::Load();
}
void  Character::Unload()
{
	//�����폜
	FootStep::Unload();

	//�����폜
	Cloth::Unload();
}

//=============================================================================
// �������֐�
//=============================================================================
void  Character::Init()
{
	//�e�N���X������
	ActorRB::Init();

	//�ړ����x������
	m_PlayerVelocity = 0.0f;

#pragma region ModelConfig

	//�X�P���^�����b�V���R���|�[�l���g�ǉ�
	m_Component_SkeletalMesh = AddComponent<Component_SkeletalMesh>(0);

	//�X�P���^�����b�V���R���|�[�l���gnull�`�F�b�N
	if (m_Component_SkeletalMesh != nullptr)
	{

		//�X�P���^�����b�V���ǂݍ���
		m_Component_SkeletalMesh->LoadSkeletalMesh("ROM\\3D\\Character\\Hutao\\SK_Hutao.fbx");

		//�A�j���[�V�����ǂݍ���
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_Idle.fbx",         "Idle");       //�_�����A�j��
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_Running.fbx",      "Walk");       //�����A�j��
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_Sprint.fbx",       "Run");        //����A�j��
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_Jump_Start.fbx",   "Jump_Start"); //�W�����v�J�n�A�j��
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_Jump_Loop.fbx",    "Jump_Loop");  //�W�����v���A�j��
		m_Component_SkeletalMesh->LoadAnimation("ROM\\3D\\Character\\Hutao\\A_falling_idle.fbx", "Fall");       //�����A�j��

		//�V�F�[�_�[�ݒ�
		m_Component_SkeletalMesh->SetShaderType(Manager_Shader::SHADER_TYPE::SHADER_UNLIT);

		//�����X�e�[�g
		m_Component_SkeletalMesh->SetCurrentAnimationName("Idle");

		//�`��T�C�Y�䗦�ύX
		m_Component_SkeletalMesh->SetScaleRate(0.0005f);//���f���f�[�^��0.0005�{

		//���W�I�t�Z�b�g����
		m_Component_SkeletalMesh->SetPositionOffset(Vector3(0.0f, -0.525f, 0.0f));

		//��]�I�t�Z�b�g����
		m_Component_SkeletalMesh->SetRotationOffset(Vector3{ DegToRad(0.0f),DegToRad(180.0f),DegToRad(0.0f) });

	}

#pragma endregion

	//���a0.5,����1.0�̃J�v�Z���^���̒ǉ�
	AddCapsuleRB(0.5f, 1.0f, m_Position, m_Rotation, PLAYER_MASS);
	

	//�X�e�[�g�}�V��������
	if (m_StateMachine = new StateMachine_Character)
	{
		m_StateMachine->Init(this);
		m_StateMachine->Jump();
	}


	//�����N���X����
	m_FootStep = new FootStep;

	//�����N���Xnull�`�F�b�N
	if (m_FootStep != nullptr)
	{
		//�����N���X������
		m_FootStep->Init();
	}

	//�����N���X����
    m_ClothSounds = new Cloth;

	//���̉��N���Xnull�`�F�b�N
	if (m_ClothSounds != nullptr)
	{
		//�����N���X������
		m_ClothSounds->Init();
	}

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Character::Update()
{
	//�X�e�[�g�}�V���X�V
	if (m_StateMachine != nullptr)
	{
		m_StateMachine->Update();
	}

	//�ړ����x�Ɋ������Z
	m_PlayerVelocity *= INERTIA;

	//�e�N���X�X�V
	ActorRB::Update();

}

//=============================================================================
// �I���֐�
//=============================================================================
void Character::Uninit()
{
	//�X�e�[�g�}�V���I��
	if (m_StateMachine != nullptr)
	{
		m_StateMachine->Uninit();
		delete m_StateMachine;
		m_StateMachine = nullptr;
	}

	//�����N���X�I��
	if (m_FootStep != nullptr)
	{
		m_FootStep->Uninit();
		delete m_FootStep;
		m_FootStep = nullptr;
	}

	//���̉��N���X�I��
	if (m_ClothSounds != nullptr)
	{
		m_ClothSounds->Uninit();
		delete m_ClothSounds;
		m_ClothSounds = nullptr;
	}

	//�e�N���X�I��
	ActorRB::Uninit();
}

//=============================================================================
// ��]�֐�
//=============================================================================
void Character::MoveRotation(float _mouseX)
{
	m_Rotation.y += _mouseX;
}


//=============================================================================
// ���ړ��֐�
//=============================================================================
void Character::MoveAxis(float _forward_value, float _right_value)
{
	//�X�e�[�g�}�V������X�e�[�g�Ɏ��ړ�����
	if (m_StateMachine != nullptr)
	{
		m_StateMachine->MoveAxis(_forward_value, _right_value);
	}
}

//=============================================================================
// �X�v�����g�֐�
//=============================================================================
void Character::Sprint(bool _input)
{
	//�X�e�[�g�}�V������X�e�[�g�ɃX�v�����g����
	if (m_StateMachine != nullptr)
	{
		m_StateMachine->Sprint(_input);
	}
}

//=============================================================================
// �W�����v�֐�
//=============================================================================
void Character::Jump()
{
	//�X�e�[�g�}�V������X�e�[�g�ɃW�����v����
	if (m_StateMachine != nullptr)
	{
		m_StateMachine->Jump();
	}
}

//=============================================================================
// �����Đ��֐�
//=============================================================================
void Character::PlayFootStep(int _physicsMaterial)
{
	//�����N���Xnull�`�F�b�N
	if (m_FootStep != nullptr)
	{
		//�Đ�
		m_FootStep->Play(_physicsMaterial);
	}
}

//=============================================================================
// ���̉��Đ��֐�
//=============================================================================
void Character::PlayClothSound()
{
	//���̉��N���Xnull�`�F�b�N
	if (m_ClothSounds != nullptr)
	{
		//�Đ�
		m_ClothSounds->PlayClothSound();
	}
}

//�A�N�Z�T�����Đ�
void Character::PlayClothSoundMetal()
{
	//���̉��N���Xnull�`�F�b�N
	if (m_ClothSounds != nullptr)
	{
		//�Đ�
		m_ClothSounds->PlaySoundsMetal();
	}
}