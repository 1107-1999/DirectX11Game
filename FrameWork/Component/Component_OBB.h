//=============================================================================
//
//  OBB�R���|�[�l���g [Component_OBB.h]
//  Author : Ryosuke Kotera
//  Date   : 2021/10/18
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Base/Component.h"
#include "../Manager/Manager_Drawer/Manager_OBB.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Component_OBB : public Component
{
public:

	Component_OBB(class Actor* _owner, int _updatePriority) : Component(_owner, _updatePriority) {}

	//�������E�X�V�E�I��
	void Init()   override;
	void Update() override;
	void Uninit() override {};
	
	//�`��
	void Draw();

	//���F���ݒ�
	inline void SetVisibility(bool _visibility) { m_Visibility = _visibility; }

	//�X�P�[���ݒ�
	inline void SetScale(Vector3 _scale) { m_Scale = _scale; }

	//�X�P�[���擾
	inline Vector3 GetScale() const { return m_Scale; };

	// ���W�擾
	inline Vector3 GetPosition() const { return m_Position; };

	//��]�擾
	inline Vector3 GetRotation() const { return m_Rotation; }

	//���F���擾
	inline bool GetVisibility()  const { return  m_Visibility; }

	//�F�ݒ�
	inline void SetColor(Color _color) { m_Color = _color; }

	//��]�Z�b�g
	inline void SetRotation(Vector3 _rot) { m_Rotation = _rot; }

	//���W�I�t�Z�b�g�ݒ�
	inline void SetPositionOffset(Vector3 _offset) { m_PositionOffset = _offset; }

	//���C�ɔ������邩���擾�E�ݒ�
	inline void SetIsReactRay(bool _set) { m_isReactRay = _set; }
	inline bool GetIsReactRay()const { return m_isReactRay; }

	//�����}�e���A���擾�E�ݒ�
	inline int GetPhysicsMaterial() const{ return m_PhysicsMaterial; }
	inline void SetPhysicsMaterial(int _physicsMaterial)  { m_PhysicsMaterial = _physicsMaterial; }

	//OBB
	inline Vector3 GetNormaDirectionX() const { return m_NormaDirectionX; };// �w�莲�ԍ���X�����x�N�g�����擾
	inline Vector3 GetNormaDirectionY() const { return m_NormaDirectionY; };// �w�莲�ԍ���Y�����x�N�g�����擾
	inline Vector3 GetNormaDirectionZ() const { return m_NormaDirectionZ; };// �w�莲�ԍ���Z�����x�N�g�����擾

	inline float   GetLengthX()        const { return m_LengthX; }// X�������̒������擾
	inline float   GetLengthY()        const { return m_LengthY; }// Y�������̒������擾
	inline float   GetLengthZ()        const { return m_LengthZ; }// Z�������̒������擾

	//�d�Ȃ��Ă��邩����
	inline bool GetOverlap() const{ return m_isOverlap; }
	inline void SetOverlap(bool _flag) { m_isOverlap = _flag; }

	//�I�[�i�[���W�ݒ�
	void SetOwnerPosition(Vector3 _position);

	
	//���C�L���X�g
	//_ignoreMySelf�͖����������������g��Actor*�B_ignoreList�͖����������A�N�^�[�^�C�v�Blist�B
	s_HIT_Result Raycast(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 10.0f, int _drawRayLife = 60 * 3);

	//�����x���C�L���X�g(�d��)
	s_HIT_Result RaycastHighAccuracy(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 10.0f, int _drawRayLife = 60 * 3);

	//���C�L���X�g(HIT�����I�u�W�F�N�g�S�Ă�z��ɂ��ĕԂ�)
	std::vector<s_HIT_Result> RaycastGetHit(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 0.025f, int _drawRayLife = 60 * 3);


private:

	//OBB�}�l�[�W���[�L���b�V���p
	class Manager_OBB* m_Manager_OBB;

	//X�����x�N�g��
	Vector3 m_NormaDirectionX;

	//Y�����x�N�g��
	Vector3 m_NormaDirectionY;

	//Z�����x�N�g��
	Vector3 m_NormaDirectionZ;

	//X�������̒���
	float   m_LengthX;

	//Y�������̒���
	float   m_LengthY;

	//Z�������̒���
	float   m_LengthZ;

	//���W
	Vector3 m_Position;

	//��]
	Vector3 m_Rotation;

	//�X�P�[��
	Vector3 m_Scale;   

	//���W�I�t�Z�b�g
	Vector3 m_PositionOffset;

	//�F
	Color   m_Color;

	//�d�Ȃ��Ă��邩�H
	bool m_isOverlap;

	//�g�p����V�F�[�_�[�̎��
	int  m_ShaderType;

	//���F��
	bool m_Visibility;

	//���C�ɔ������邩
	bool m_isReactRay;

	//�����}�e���A��
	int  m_PhysicsMaterial;

};


