//=============================================================================
//
//  �r���{�[�h�R���|�[�l���g [Component_Billboard.cpp]
//  Date   : 2021/11/05
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Base/Component.h"
#include "../Renderer/Renderer_Polygon.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Component_Billboard : public Component
{
private:

	//�e�N�X�`���[
	ID3D11ShaderResourceView*  m_Texture;

	//�X�v���C�g�A�j���[�V�����\����
	s_SpriteAnimation m_AnimationInformation;

	//�g�p����V�F�[�_�[�̎��
	int   m_ShaderType; 

	//�F 
	Color m_Color;


public:

	Component_Billboard(class Actor* _owner, int _updatePriority) : Component(_owner, _updatePriority) {}

	//�������E�X�V�E�I��
	virtual void Init()override;   
	virtual void Update() override;
	virtual void Uninit()override; 

	//�`��
	virtual void Draw();

	//���v���C
	void Replay();

	//�e�N�X�`���Z�b�g
	void SetTexture(const char* _Key);

	//�F�ݒ�
	inline void SetColor(Color _color) { m_Color = _color;}

	//1�R�}�ӂ�̃T�C�Y����o��
	inline void CalculationOneFrameSize(int _W_frame, int _H_frame)
	{
		m_AnimationInformation.OneFrameSize.x = static_cast<float>(1.0f / _W_frame);
		m_AnimationInformation.OneFrameSize.y = static_cast<float>(1.0f / _H_frame);
	}

	//���[�v�����邩�ݒ�
	inline void SetLoop(bool _loop) { m_AnimationInformation.Loop = _loop; }

	//���t���[���ōX�V���邩�ݒ�
	inline void SetMaxAnimCount(int _max_count) { m_AnimationInformation.MaxAnimCount = _max_count; }

};
