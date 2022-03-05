//=============================================================================
//
//  �r���{�[�h�R���|�[�l���g [Component_Billboard.cpp]
//  Date   : 2021/11/05
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Component_Billboard.h"
#include "../Actor/3D/Camera.h"
#include "../Manager/Manager_Shader.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Texture.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Manager/Manager_Drawer/Manager_Billboard.h"
#include "../Renderer/Renderer_DirectX11.h"
#include "../Level/Base/Level.h"

//=============================================================================
// �������֐�
//=============================================================================
void Component_Billboard::Init()
{
	//���N���X������
	Component::Init();

	//�f�t�H���g�̓A�����b�g�V�F�[�_�[
	m_ShaderType = Manager_Shader::SHADER_UNLIT;

	//���݂̃t���[����������
	m_AnimationInformation.AnimCount    = 0;     

	//���t���[���ōX�V���邩������
	m_AnimationInformation.MaxAnimCount = 0;       

	//1�R�}�ӂ�̃T�C�Y������
	m_AnimationInformation.OneFrameSize    = { 0.0f,0.0f };

	//�؂���J�n���W������
	m_AnimationInformation.CutStartPostion = { 0.0f,0.0f };

	//���[�v�����邩�t���O������
	m_AnimationInformation.Loop     = true;

	//�F�����l
	m_Color = { 1.0f,1.0f,1.0f,1.0f };

	//�r���{�[�h�}�l�[�W���[���擾�ł����ꍇ
	if (Manager_Billboard* manager_Billboard = Manager_Game::Instance()->GetLevel()->GetManager_Drawer()->GetManager_Billboard())
	{
		//���g���}�l�[�W���[�ɓo�^
		manager_Billboard->AddComponent(this);
	}

}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Component_Billboard::Update()
{
	//�L���̏ꍇ
	if (m_Active)
	{
		//���݂̃t���[�������Z
		m_AnimationInformation.AnimCount++; 
		
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
// �I���֐�
//=============================================================================
void Component_Billboard::Uninit()
{
	//�L���b�V�������e�N�X�`��������ꍇ
	if (m_Texture != nullptr)
	{
		//nullptr��
		m_Texture = nullptr;
	}
}


//=============================================================================
// �`��֐�
//=============================================================================
void Component_Billboard::Draw()
{
	//�L�����e�N�X�`����null�ł͂Ȃ��ꍇ
	if (m_Active && m_Texture != nullptr)
	{
		//Actor3D�ɃL���X�g
		if (Actor3D* actor3D = dynamic_cast<Actor3D*>(m_Owner))
		{
			//�V�F�[�_�[�ݒ�
			Manager_Shader::Instance()->SetShader(m_ShaderType);

			//�e�N�X�`���ݒ�
			Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

			//�|���S���`��@�\�ŕ`��
			Renderer_Polygon::Instance()->DrawBillboard(actor3D->GetPosition(), actor3D->GetScale(),m_Color, m_AnimationInformation.OneFrameSize, m_AnimationInformation.CutStartPostion);
		}
	}
}

//=============================================================================
// �e�N�X�`���ݒ�֐�
//=============================================================================
void Component_Billboard::SetTexture(const char* _Key)
{
	//�w��̃L�[�̃e�N�X�`�������邩�m�F
	if (ID3D11ShaderResourceView* texture = Manager_Texture::Instance()->GetTexture(_Key))
	{
		//�e�N�X�`���ݒ�
		m_Texture = texture;
	}
}

//=============================================================================
// ���v���C�֐�
//=============================================================================
void Component_Billboard::Replay()
{
	//�L����
	m_Active = true;

	//�A�j���[�V�������Z�b�g
	m_AnimationInformation.AnimCount = 0;     

	//�؂���J�n���W���Z�b�g
	m_AnimationInformation.CutStartPostion = { 0.0f,0.0f };

}