//=============================================================================
//
//  �R���|�[�l���g[Component.h]
//  Date   : 2021/11/1
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../../System/Main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Component
{
public:

	Component(class Actor* _owner, int _updatePriority) : m_Owner(_owner), m_UpdatePriority(_updatePriority) {}

	//�������E�X�V�E�I���������z�֐�
	virtual void Init()   = 0;
	virtual void Update() = 0;
	virtual void Uninit() = 0;

	//�D�揇�擾
	int GetPriority()const  { return m_UpdatePriority; }

	//�L���t���O���擾�E�ݒ�
	inline bool GetActive() { return m_Active; }
	inline void SetActive(bool _flag) { m_Active = _flag; }

	//���̃R���|�[�l���g���������Ă���A�N�^�[�擾
	inline class Actor* GetOwner() { return m_Owner; }

protected:

	//���̃R���|�[�l���g���������Ă���A�N�^�[
	class Actor* m_Owner;

	//�X�V�D�揇
	int m_UpdatePriority;

	//�L����
	bool m_Active;
};
