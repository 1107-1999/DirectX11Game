//=============================================================================
//
//  �A�j���[�V�����X�v���C�g�R���|�[�l���g [Component_SpriteAnimation.cpp]
//  Date   : 2021/11/04
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Component_SpriteAnimation.h"
#include "../Actor/2D/Base/Actor2D.h"
#include "../Manager/Manager_Shader.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Texture.h"
#include "../Manager/Manager_Drawer/Manager_Sprite.h"
#include "../Renderer/Renderer_DirectX11.h"
#include "../Level/Base/Level.h"

//=============================================================================
// �������֐�
//=============================================================================
void Component_SpriteAnimation::Init()
{
	//�e�N���X������
	Component_Sprite::Init();

	//���݂̃t���[����������
	m_AnimationInformation.AnimCount       = 0;

	//���t���[���ōX�V���邩������
	m_AnimationInformation.MaxAnimCount    = 0;

	//1�R�}�ӂ�̃T�C�Y������
	m_AnimationInformation.OneFrameSize    = {0.0f,0.0f};

	//�؂���J�n���W������
	m_AnimationInformation.CutStartPostion = {0.0f,0.0f};

	//���[�v�����邩�t���O
	m_AnimationInformation.Loop = true;

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Component_SpriteAnimation::Update()
{
	//�L���̏ꍇ
	if (m_Active)
	{
		//�X�V�t���[�����B���ɃA�j���[�V�����X�V
		if (m_AnimationInformation.AnimCount == m_AnimationInformation.MaxAnimCount)
		{
			//���݂̃t���[�������Z�b�g
			m_AnimationInformation.AnimCount = 0;

			//X�����ɃA�j���[�V�����X�V�\�̏ꍇ
			if (m_AnimationInformation.CutStartPostion.x + m_AnimationInformation.OneFrameSize.x < MAX_CUT_START_POSTION)
			{
				//X�؂�����W��1�R�}�����炷
				m_AnimationInformation.CutStartPostion.x += m_AnimationInformation.OneFrameSize.x;
			}
			//X�����ɃA�j���[�V�����X�V�s�̏ꍇ
			else
			{
				//X�؂�����W������
				m_AnimationInformation.CutStartPostion.x = 0.0f;

				//Y�����ɃA�j���[�V�����X�V�\�̏ꍇ
				if (m_AnimationInformation.CutStartPostion.y + m_AnimationInformation.OneFrameSize.y < MAX_CUT_START_POSTION)
				{
					//Y�؂�����W��1�R�}�����炷
					m_AnimationInformation.CutStartPostion.y += m_AnimationInformation.OneFrameSize.y;
				}
				//X��Y���ɍX�V�s�̏ꍇ
				else
				{
					//Y�؂�����W������
					m_AnimationInformation.CutStartPostion.y = 0.0f;

					//���[�v���Ȃ��A�j���[�V�����̏ꍇ
					if (!m_AnimationInformation.Loop)
					{
						//��A�N�e�B�u��
						m_Active = false;
					}
				}
			}
		}
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void Component_SpriteAnimation::Draw()
{
	//�L�����e�N�X�`����null�ł͂Ȃ��ꍇ
	if (m_Active && m_Texture != nullptr)
	{
		//�V�F�[�_�[�ݒ�
		Manager_Shader::Instance()->SetShader(m_ShaderType);

		//�e�N�X�`���ݒ�
		Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

		//�|���S���`��@�\�ŕ`��
		Renderer_Polygon::Instance()->Draw2DAnimation(m_Position2D, m_Scale2D, m_Color,
			m_AnimationInformation.OneFrameSize, m_AnimationInformation.CutStartPostion, m_Reverse);
	}
}

