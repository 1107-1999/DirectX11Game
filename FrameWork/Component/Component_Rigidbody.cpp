//=============================================================================
//
//  ���̃R���|�[�l���g [Component_Rigidbody.cpp]
//  Date   : 2021/11/22
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Component_Rigidbody.h"
#include "../Manager/Manager_Game.h"
#include "../Actor/3D/Base/Actor3D.h"

//=============================================================================
// �萔��`
//=============================================================================
constexpr int   JUMP_UP_TIME      = 6;     //�W�����v�㏸����
constexpr int   HIGH_JUMP_UP_TIME = 8;     //�n�C�W�����v�㏸����
constexpr float JUMP_POWER        = 500.0f;//�W�����v��

//=============================================================================
// �������֐�
//=============================================================================
void Component_Rigidbody::Init()
{
	//���N���X�X�V
	Component::Init();

	//nullptr���
	m_RigidBody = nullptr;

	//�W�����v���ԏ�����
	m_JumpTime = 0;
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Component_Rigidbody::Update()
{
	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//�A�N�^�[3D�ɃL���X�g���������ꍇ
		if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
		{
			//���݂̃g�����X�t�H�[���擾
			btTransform transform = m_RigidBody->body->getWorldTransform();

			//���݂̍��̂̈ʒu�擾
			btVector3 btPosition = transform.getOrigin();

			//�I�[�i�[�̉�]�擾
			Vector3 rotation = actor3D->GetRotation();

			//�I�[�i�[�̉�]�����̂ɐݒ�(y,x,z�̏�)
			btVector3 btrotation = { rotation.y, rotation.x, rotation.z };

			//�g�����X�t�H�[���ɑ��
			transform.setRotation(btQuaternion{ btrotation.x(), btrotation.y(), btrotation.z() });

			//���݂̃g�����X�t�H�[�����ɐݒ�
			m_RigidBody->body->setWorldTransform(transform);

			//���W���擾
			btPosition = transform.getOrigin();

			//�W�����v�㏸���̏ꍇ
			if (m_JumpTime > 0)
			{
				//�㏸���Ԍ���
				m_JumpTime--;

				//�W�����v�͌v�Z
				Vector3 jumpImpulse = actor3D->GetUp() * JUMP_POWER;

				//�W�����v�͂ɉ������C���p���X��^����
				m_RigidBody->body->applyImpulse(btVector3{ jumpImpulse.x,jumpImpulse.y ,jumpImpulse.z }, m_RigidBody->body->getWorldTransform().getOrigin());

			}

			//�I�[�i�[�̍��W��ݒ�
			actor3D->SetPosition(Vector3{ btPosition.x(),btPosition.y(),btPosition.z() });
		}
	}
}

//=============================================================================
// ���̍��W�擾�֐�
//=============================================================================
Vector3 Component_Rigidbody::GetPosition()
{
	//�߂�l�p�ϐ�
	Vector3 value = { 0.0f,0.0f,0.0f };

	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//���̂̍��W�擾
		btVector3 btPosition = m_RigidBody->body->getWorldTransform().getOrigin();

		//�߂�l�ɍ��̂̍��W��ݒ�
		value = Vector3{ btPosition.x(),btPosition.y(),btPosition.z() };

	}

	return value;
}

//=============================================================================
// ���̃X�P�[���ݒ�֐�
//=============================================================================
void Component_Rigidbody::SetScale(const Vector3& _scale)
{
	//��������
	m_Scale = _scale;

	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//���̂̃X�P�[�����㏑��
		m_RigidBody->body->getCollisionShape()->setLocalScaling(btVector3{ _scale.x,_scale.y,_scale.z });
	}

}

//=============================================================================
// ����XZ���ړ��֐�
//=============================================================================
void Component_Rigidbody::SetMoveXZ(const Vector3& _velocity)
{
	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//Y���ȊO�ɃC���p���X��^����
		m_RigidBody->body->applyImpulse(btVector3{_velocity.x,m_RigidBody->body->getLinearVelocity().y(),_velocity.z }, m_RigidBody->body->getWorldTransform().getOrigin());
	}
}

//=============================================================================
// ����XYZ���ړ��֐�
//=============================================================================
void Component_Rigidbody::SetMoveXYZ(const Vector3& _velocity)
{
	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//�C���p���X��^����
		m_RigidBody->body->applyImpulse(btVector3{ _velocity.x,_velocity.y,_velocity.z }, m_RigidBody->body->getWorldTransform().getOrigin());
	}
}

//=============================================================================
// ���̏d�͐ݒ�֐�
//=============================================================================
void Component_Rigidbody::SetGravity(const Vector3& _velocity)
{
	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//�d�͐ݒ�
		m_RigidBody->body->setGravity(btVector3{ _velocity.x,_velocity.y,_velocity.z });
	}
}

//=============================================================================
// ���̖��C�ݒ�֐�
//=============================================================================
void Component_Rigidbody::SetFriction(const float& _friction)
{
	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//���C�ݒ�
		m_RigidBody->body->setFriction(_friction);
	}
}

//=============================================================================
// �W�����v�֐�
//=============================================================================
void Component_Rigidbody::Jump()
{
	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//�W�����v�㏸���Ԑݒ�
		m_JumpTime = JUMP_UP_TIME;
	}
}
//=============================================================================
// �n�C�W�����v�֐�
//=============================================================================
void Component_Rigidbody::HighJump()
{
	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//�W�����v�㏸���Ԑݒ�
		m_JumpTime = HIGH_JUMP_UP_TIME;
	}
}

//=============================================================================
// ���[�v�֐�
//=============================================================================
void Component_Rigidbody::SetWarp(const Vector3& _position)
{
	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//���݂̃g�����X�t�H�[���擾
		btTransform transform = m_RigidBody->body->getWorldTransform();

		//�ړ����ʂ��v�Z�����
		transform.setOrigin(btVector3{ _position.x,_position.y, _position.z });

		//�g�����X�t�H�[���̍X�V
		m_RigidBody->body->setWorldTransform(transform);
	}
}

//=============================================================================
// ���x�擾�֐�
//=============================================================================
Vector3 Component_Rigidbody::GetVelociy()
{
	//���̂�null�`�F�b�N
	if (m_RigidBody != nullptr)
	{
		//���x�擾
		btVector3 velocity = m_RigidBody->body->getLinearVelocity();
		return Vector3{ velocity.x(),velocity.y(),velocity.z() };
	}

	return Vector3 { 0.0f,0.0f,0.0f };
}

//=============================================================================
// �X�t�B�A�^���̒ǉ��֐�
//=============================================================================
void  Component_Rigidbody::AddSphere(const Vector3& _scale, const Vector3& _position, float _mass)
{
	//���̂�null�`�F�b�N
	if (m_RigidBody == nullptr)
	{
		//���̃}�l�[�W���[���擾�o�����ꍇ
		if (Manager_Rigidbody* manager_Rigidbody = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Rigidbody())
		{
			//�X�P�[���ݒ�
			m_Scale = _scale;

			//�X�t�B�A�^���̒ǉ�
			m_RigidBody = manager_Rigidbody->AddSphere(_scale, _position, _mass);
		}
	}
}

//=============================================================================
// �{�b�N�X�^���̒ǉ��֐�
//=============================================================================
void  Component_Rigidbody::AddBox(const Vector3& _scale, const Vector3& _position, float _mass)
{
	//���̂�null�`�F�b�N
	if (m_RigidBody == nullptr)
	{
		//���̃}�l�[�W���[���擾�o�����ꍇ
		if (Manager_Rigidbody* manager_Rigidbody = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Rigidbody())
		{
			//�X�P�[���ݒ�
			m_Scale = _scale;

			//�{�b�N�X�^���̒ǉ�
			m_RigidBody = manager_Rigidbody->AddBox(_scale, _position, _mass);
		}
	}
}

//=============================================================================
// �J�v�Z���^���̒ǉ��֐�
//=============================================================================
void  Component_Rigidbody::AddCapsule(float _radius, float _height, const Vector3& _position, const Vector3& _rotation, float _mass)
{
	//���̂�null�`�F�b�N
	if (m_RigidBody == nullptr)
	{
		//���̃}�l�[�W���[���擾�o�����ꍇ
		if (Manager_Rigidbody* manager_Rigidbody = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Rigidbody())
		{
			//�X�P�[���ݒ�
			m_Scale = Vector3{ _radius,_height,_radius };

			//�J�v�Z���^���̒ǉ�
			m_RigidBody = manager_Rigidbody->AddCapsule(_radius, _height, _position, _rotation, _mass);
		}
	}
}

//=============================================================================
// ���ʌ^���̒ǉ��֐�
//=============================================================================
void Component_Rigidbody::AddStaticPlane(const Vector3& _up, const Vector3& _position, float _mass)
{
	//���̂�null�`�F�b�N
	if (m_RigidBody == nullptr)
	{
		//���̃}�l�[�W���[���擾�o�����ꍇ
		if (Manager_Rigidbody* manager_Rigidbody = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Rigidbody())
		{
			//���ʌ^���̒ǉ�
			m_RigidBody = manager_Rigidbody->AddStaticPlane(_up, _position, _mass);
		}
	}
}