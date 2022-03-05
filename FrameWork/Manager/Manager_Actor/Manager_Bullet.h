//=============================================================================
//
//  �e�N���X�}�l�[�W���[ [Manager_Bullet.h]
//  Date   : 2022/1/19
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <unordered_map>
#include "Base/Manager_Actor.h"
#include "../../System/Main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Manager_Bullet : public Manager_Actor
{
private:

	//�I�u�W�F�N�g�v�[��
	std::vector<class Bullet*>m_Bullets;

public:

	//�������E�I���E�X�V
	void Init() override;
	void Uninit()override;
	void Update()override {};

	//����
	void SpawnBullet(Vector3 _poition, Vector3 _velocity, Vector3 _rotation);

};