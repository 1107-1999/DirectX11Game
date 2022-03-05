//=============================================================================
//
//  �L���[�u�R���|�[�l���g [Component_Cube.h]
//  Author : Ryosuke Kotera
//  Date   : 2021/1/19
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Base/Component.h"
#include "../Manager/Manager_Drawer/Manager_Cube.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Component_Cube : public Component
{
public:

	Component_Cube(class Actor* _owner, int _updatePriority) : Component(_owner, _updatePriority) {}

	//�������E�X�V�E�I��
	void Init()   override;
	void Update() override {};
	void Uninit() override {};

	//�`��
	void Draw();

	//�e�N�X�`���ݒ�
	void SetTexture(const char* _Key);

	//�V�F�[�_�[�擾�E�ݒ�
	inline int GetShaderType() const { return m_ShaderType; }
	inline void SetShaderType(int _type) { m_ShaderType = _type; }

	//�F�ݒ�
	inline void SetColor(Color _color) { m_Color = _color; }

	//�e�N�X�`�����[�v�ݒ�
	inline void SetTexLoop(bool _isLoop) { m_TexLoop = _isLoop; }

private:

	//�e�N�X�`��
	ID3D11ShaderResourceView*  m_Texture;

	//�L���[�u�}�l�[�W���[�L���b�V���p
	class Manager_Cube* m_Manager_Cube;

	//�F
	Color   m_Color;

	//�g�p����V�F�[�_�[�̎��
	int  m_ShaderType;

	//�e�N�X�`�������[�v�����邩
	bool m_TexLoop;
	
};


