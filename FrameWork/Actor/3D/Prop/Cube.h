//=============================================================================
//
// �L���[�u�N���X [Cube.h]
//  Date   : 2021/1/19
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
class Cube : public Actor3D
{
protected:

	//�L���[�u�R���|�[�l���g
	class Component_Cube* m_Component_Cube;

public:

	//���\�[�X�ǂݍ��݁E�폜
	static void Load();
	static void Unload();

	//������
	void Init()override;

};