//=============================================================================
//
//  �J�������� [Camera.h]
//  Date   : 2021/11/20
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Base/Actor3D.h"

constexpr float DEFAULT_FOV = 1.25f;//�f�t�H���g�̎���p

constexpr float VIEW_PITCH_MAX = DegToRad(89.9f);//�ő�s�b�`

constexpr float MAX_TARGET_ARM_LENGTH = 2.0f;//�ő�J��������
constexpr float MIN_TARGET_ARM_LENGTH = 0.5f;//�ŏ��J��������

constexpr float MAX_OFFSET_POSITION_Y = 0.3f;//�ő�J�����I�t�Z�b�gY���W
constexpr float MIN_OFFSET_POSITION_Y = 0.0f;//�ŏ��J�����I�t�Z�b�gY���W


//******************************************************************************
// �N���X��`
//******************************************************************************
class Camera : public Actor3D
{
private:

	//�����_�Ώ�3D�A�N�^�[
	class Actor3D* m_Owner;

	//OBB�R���|�[�l���g
	class Component_OBB* m_Component_OBB;

	//���W�I�t�Z�b�g
	Vector3 m_Offset_Position;

	//�����_
	Vector3     m_Target;

	//�r���[�}�g���N�X
	D3DXMATRIX  m_ViewMatrix;
	//�v���W�F�N�V�����}�g���N�X
	D3DXMATRIX  m_ProjectionMatrix;

	//����
	float       m_FOV;

	//�J��������
	float       m_TargetArmLength;

	//�i�s�������������ǂ���
	bool        m_OrientRotationtoMovement;

	//1�l�̃t���O
	bool        m_FirstPerson = false;

	//�v���C���[�Ƃ̓����蔻�����邩
	bool m_IsUseRayHit;

public:

	//�������E�X�V
	void Init()override;
	void Update()override;

	//�����_�Ώ�3D�A�N�^�[�ݒ�
	inline void SetOwner(Actor3D* _owner) { m_Owner = _owner; }
	inline Actor3D* GetOwner() {return  m_Owner; }

	inline D3DXMATRIX GetViewMatrix() const { return m_ViewMatrix; }
	inline D3DXMATRIX GetProjectionMatrix() const { return m_ProjectionMatrix; }

	//���_�ݒ�֐�
	void SetView();

	//�^�[�Q�b�g�܂ł̋����擾�E�ݒ�
	inline float GetTargetLength()const { return m_TargetArmLength; }
	inline void  SetTargetLength(float _length) { m_TargetArmLength = _length;}

	//�^�[�Q�b�g�������Z�֐�
	void AddTargetLength(float _length);

	// ������J�����O����֐�
	bool CheckView(Vector3 _position, Vector3 _scale);

	//��l�̃t���O�擾�E�ݒ�
	inline bool GetFirstPerson() const{ return m_FirstPerson; }
	inline void SetFirstPerson(bool _FirstPerson) { m_FirstPerson =  _FirstPerson; }

	//�i�s�������������ǂ����擾
	inline bool  GetOrientRotationtoMovement()const { return m_OrientRotationtoMovement;}

	//�i�s�������������ǂ����ύX
	inline void  SetOrientRotationtoMovement(bool _flag) { m_OrientRotationtoMovement = _flag;}

	//�J�����ړ�
	void Move(float _forward, float _right);

	//�J������]���Z
	void AddCameraYaw  (float _value); //Yaw���Z
	void AddCameraPitch(float _value); //Pitch���Z

	//����擾�E�ݒ�
	inline float GetFOV()const {return m_FOV; }
	inline void  SetFOV(float _value) { m_FOV = Math::clamp(_value, 0.1f, DEFAULT_FOV); }

	//���C�q�b�g�؂�ւ�
	inline void SetIsUseRayHit(bool _set) { m_IsUseRayHit = _set; }
	inline bool GetIsUseRayhit()const { return m_IsUseRayHit; }

};