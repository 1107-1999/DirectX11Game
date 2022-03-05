//=============================================================================
//
//  OBB�R���|�[�l���g [Component_OBB.cpp]
//  Author : Ryosuke Kotera
//  Date   : 2021/10/18
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <math.h>
#include "Component_OBB.h"
#include "../Level/Base/Level.h"
#include "../Manager/Manager_Shader.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Manager/Manager_Drawer/Manager_OBB.h"
#include "../Manager/Manager_Game.h"
#include "../Renderer/Renderer_Polygon.h"
#include "../Actor/3D/Base/Actor3D.h"
#include "../Actor/3D/ActorRB/Charcter/Base/Character.h"
#include "../Actor/3D/ActorRB/Prop/Bullet.h"
#include "../Actor/3D/ActorRB/Prop/GunTarget.h"
#include "../Actor/3D/Camera.h"
#include "../Actor/3D/Prop/Gun.h"
#include "../Actor/3D/Prop/Goal.h"

//=============================================================================
// �萔��`
//=============================================================================
constexpr float HALF_SIZE = 0.5f;

//=============================================================================
// �������֐�
//=============================================================================
void Component_OBB::Init()
{
	//���N���X������
	Component::Init();

	//�f�t�H���g�̓A�����b�g�V�F�[�_�[
	m_ShaderType = Manager_Shader::SHADER_UNLIT;

	//�F�𔒂ɐݒ�
	m_Color = Color{ 1.0f,1.0f,1.0f,1.0f };

	//�f�o�b�O�R���W�����`�悵�Ȃ�
	m_Visibility = true;

	//���C�ɔ������邩
	m_isReactRay = true;

	//�����}�e���A���ݒ�(�����̓R���N���[�g)
	m_PhysicsMaterial = PM_CONCRETE;

	//�d�Ȃ��Ă��邩
	m_isOverlap = false;

	//���W�I�t�Z�b�g������
	m_PositionOffset = Vector3_Zero;

	//Actor3D�ɃL���X�g���������ꍇ
	if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
	{

		//�I�[�i�[���擾
		m_Position = actor3D->GetPosition();//���W
		m_Rotation = actor3D->GetRotation();//��]
		m_Scale    = actor3D->GetScale();   //�X�P�[��

		//OBB�}�l�[�W���[�L���b�V��
		m_Manager_OBB = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_OBB();

		///todo�F�N���X�ƃ��t�@�����X���������Ɏ����ōD���ȃ^�C�~���O�ŃR���W�����`�����l���ɓo�^�ł���悤�ɂ���///

		//OBB�}�l�[�W���[null�`�F�b�N
		if (m_Manager_OBB != nullptr)
		{
			//�I�[�i�[�̃^�C�v�ʂɃR���W�����`�����l���ɓo�^

			if (Camera* camera = dynamic_cast<Camera*>(actor3D))
			{//�J����
				m_Manager_OBB->AddComponent(this, COLLISION_CAMERA);
			}
			else if (Character* character = dynamic_cast<Character*>(actor3D))
			{//�L�����N�^�[
				m_Manager_OBB->AddComponent(this, COLLISION_PLAYER);
			}
			else if (Gun* gun = dynamic_cast<Gun*>(actor3D))
			{//�e
				m_Manager_OBB->AddComponent(this, COLLISION_GUN);
			}
			else if (Bullet* bullet = dynamic_cast<Bullet*>(actor3D))
			{//�e
				m_Manager_OBB->AddComponent(this, COLLISION_BULLET);
			}
			else if (Goal* goal = dynamic_cast<Goal*>(actor3D))
			{//�S�[��
				m_Manager_OBB->AddComponent(this, COLLISION_GOAL);
			}
			else if (GunTarget* gunTarget = dynamic_cast<GunTarget*>(actor3D))
			{//�^�[�Q�b�g
				m_Manager_OBB->AddComponent(this, COLLISION_GUN_TARGET);
			}
			else
			{//�u���b�N
				m_Manager_OBB->AddComponent(this, COLLISION_BLOCK);
			}
		}
	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Component_OBB::Update()
{

	//Actor3D�ɃL���X�g���������ꍇ
	if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
	{//�I�[�i�[���擾

		//���W�擾
		m_Position = actor3D->GetPosition() + m_PositionOffset;

		//��]�擾
		m_Rotation = actor3D->GetRotation();

		//�F�𔒂ɐݒ�
		m_Color = Color{ 1.0f,1.0f,1.0f,1.0f };

		//�I�[�o�[���b�v���胊�Z�b�g
		m_isOverlap = false;

		//�}�g���N�X�v�Z
		D3DXMATRIX rot, scale, world;

		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		world = scale * rot;

		//OBB�v�Z
		m_NormaDirectionX = Vector3{ world._11 ,world._12,world._13} *HALF_SIZE;
		m_NormaDirectionY = Vector3{ world._21 ,world._22,world._23} *HALF_SIZE;
		m_NormaDirectionZ = Vector3{ world._31 ,world._32,world._33} *HALF_SIZE;

	    //OBB�̐����̒����v�Z
		m_LengthX = D3DXVec3Length(&m_NormaDirectionX);
		m_LengthY = D3DXVec3Length(&m_NormaDirectionY);
		m_LengthZ = D3DXVec3Length(&m_NormaDirectionZ);

	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void Component_OBB::Draw()
{
	//�`�惂�[�h�I���̎�
	if (m_Visibility)
	{
		//Actor3D�ɃL���X�g�ɐ��������ꍇ
		if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
		{
			//�V�F�[�_�[�ݒ�
			Manager_Shader::Instance()->SetShader(m_ShaderType);

			//���C���[�t���[����
			Renderer_DirectX11::Instance()->SetRasterizerState(D3D11_FILL_WIREFRAME);

			//�|���S�������_���[����`��
		    Renderer_Polygon::Instance()->DrawBox(m_Position, m_Rotation, m_Scale, m_Color);

			//���C���[�t���[������
			Renderer_DirectX11::Instance()->SetRasterizerState(D3D11_FILL_SOLID);
		}
	}
}


//=============================================================================
// �I�[�i�[�̍��W�ݒ�֐�
//=============================================================================
void Component_OBB::SetOwnerPosition(Vector3 position)
{
	//Actor3D�ɃL���X�g�ɐ��������ꍇ
	if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
	{
		actor3D->SetPosition(position);
	}
}

//=============================================================================
// ���C�L���X�g�֐�
//=============================================================================
s_HIT_Result Component_OBB::Raycast(Vector3 _startPos, Vector3 _endPos,
	Actor * _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE> _ignoreList, Color _drawRayColor, float _accuracy,int _drawRayLife)
{
	//OBB�}�l�[�W���[null�`�F�b�N
	if (m_Manager_OBB != nullptr)
	{
		return m_Manager_OBB->Raycast(_startPos, _endPos, _ignoreMySelf, _isDispRay, _ignoreList, _drawRayColor, _accuracy ,_drawRayLife);
	}

	//HIT���ĂȂ��ꍇ�̒l
	s_HIT_Result nohit;

	return nohit;
}

//=============================================================================
// �����x���C�L���X�g�֐�(�d��)
//=============================================================================
s_HIT_Result Component_OBB::RaycastHighAccuracy(Vector3 _startPos, Vector3 _endPos,
	Actor * _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE> _ignoreList, Color _drawRayColor, float _accuracy, int _drawRayLife)
{
	//OBB�}�l�[�W���[null�`�F�b�N
	if (m_Manager_OBB != nullptr)
	{
		return m_Manager_OBB->RaycastHighAccuracy(_startPos, _endPos, _ignoreMySelf, _isDispRay, _ignoreList, _drawRayColor, _accuracy, _drawRayLife);
	}

	//HIT���ĂȂ��ꍇ�̒l
	s_HIT_Result nohit;

	return nohit;
}

//=============================================================================
// 	���C�L���X�g�֐�(HIT�����I�u�W�F�N�g�S�Ă�z��ɂ��ĕԂ�)
//=============================================================================
std::vector<s_HIT_Result> Component_OBB::RaycastGetHit(Vector3 _startPos,
	Vector3 _endPos, Actor * _ignoreMySelf, bool _isDispRay, std::list<ACTOR_TYPE> _ignoreList, Color _drawRayColor, float _accuracy, int _drawRayLife)
{
	//OBB�}�l�[�W���[null�`�F�b�N
	if (m_Manager_OBB != nullptr)
	{
		return m_Manager_OBB->RaycastGetHit(_startPos, _endPos, _ignoreMySelf, _isDispRay, _ignoreList, _drawRayColor, _accuracy, _drawRayLife);
	}

	return std::vector<s_HIT_Result>();
}

