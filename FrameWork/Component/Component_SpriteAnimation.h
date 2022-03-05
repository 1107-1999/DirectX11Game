//=============================================================================
//
//  �A�j���[�V�����X�v���C�g�R���|�[�l���g [Component_SpriteAnimation.h]
//  Date   : 2021/11/04
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Component_Sprite.h"
#include "../Renderer/Renderer_Polygon.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Component_SpriteAnimation : public Component_Sprite
{
private:

	//�X�v���C�g�A�j���[�V�����\����
	s_SpriteAnimation m_AnimationInformation;

public:

	Component_SpriteAnimation(class Actor* _owner, int _updatePriority) : Component_Sprite(_owner, _updatePriority) {}

	//�������E�X�V
	void Init()override;  
	void Update()override;

	//�`��
	void Draw()override;  

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
