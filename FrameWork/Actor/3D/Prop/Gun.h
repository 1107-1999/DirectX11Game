//=============================================================================
//
//  �e�N���X [Gun.h]
//  Date   : 2021/1/25
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../Base/Actor3D.h"

//=============================================================================
// �N���X�錾
//=============================================================================
class Gun : public Actor3D
{
private:

	//�R���|�[�l���g
	class Component_StaticMesh* m_Component_StaticMesh;	//�ÓI���b�V���R���|�[�l���g
	class Component_OBB*        m_Component_OBB;	    //OBB�R���|�[�l���g


	//�e�Ǘ��N���X
	class Manager_Bullet* m_Manager_Bullet;

	//�e���N���X
	class GunFire* m_GunFire;

	//�v���C���[�R���g���[���[�L���b�V��
	class PC_Game*    m_PlayerConroller;

	//���R�C���J�E���g
	int m_RecoilCount;

	//���R�C���E������
	bool  m_RecoilVectorRight;

public:

	//���\�[�X�ǂݍ��݁E�폜
	static void Load();
	static void Unload();

	//�������E�X�V�E�I��
	virtual void Init()override;
	virtual void Update()override;
	virtual void Uninit()override;

	//�ˌ�
	void Shot();

};