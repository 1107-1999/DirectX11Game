//=============================================================================
//
//  �t�F�[�h�}�l�[�W���[ [Manager_Fade.cpp]
//  Date   : 2021/11/16
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <time.h>
#include "Manager_Fade.h"
#include "../Manager_Game.h"
#include "../Manager_Shader.h"
#include "../Manager_Texture.h"
#include "../../Renderer/Renderer_Polygon.h"
#include "../../System/MainWindow.h"

//=============================================================================
// �萔��`
//=============================================================================
constexpr float MAX_FADE_OPACITY = 1.0f;//�t�F�[�h�ő�I�p�V�e�B
constexpr float MIN_FADE_OPACITY = 0.0f;//�t�F�[�h�ŏ��I�p�V�e�B

//=============================================================================
// ������
//=============================================================================
void Manager_Fade::Init()
{
	//�A�����b�g�V�F�[�_�[
	m_ShaderType = Manager_Shader::SHADER_UNLIT;

	//�t�F�[�h���Ă��Ȃ���Ԃŏ�����
	m_FadeState = FADE_NONE;

	//�t�F�[�h���ԏ�����
	m_FadeTime  = 0.0f;

	//�t�F�[�h�J�n���ԏ�����
	m_StartTime = 0.0f;

	//���F�ŏ�����
	m_Color = Color(0.0f,0.0f,0.0f, MAX_FADE_OPACITY);

	//�e�N�X�`���}�l�[�W���[�L���b�V��
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//�e�N�X�`�����[�h
		manager_Texture->LoadTexture("Fade", "../ROM/2D/Test/FadeTexture.png");

		//�e�N�X�`���ݒ�
		m_Texture = manager_Texture->GetTexture("Fade");
	}
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void Manager_Fade::Update()
{
	//�t�F�[�h���̏ꍇ
	if (m_FadeState != FADE_NONE)
	{

		float Time = clock() - m_StartTime;
		Time /= 1000.0f;

		switch (m_FadeState)
		{
		case FADE_IN:

			m_Color.a = MAX_FADE_OPACITY - Time / m_FadeTime;

			//�t�F�[�h�C���I��
			if (Time > m_FadeTime)
			{
				m_Color.a = MIN_FADE_OPACITY;
				m_FadeState = FADE_NONE;
			}
			break;

		case FADE_OUT:

			m_Color.a = Time / m_FadeTime;

			//�t�F�[�h�A�E�g�I��
			if (Time > m_FadeTime)
			{
				m_Color.a = MAX_FADE_OPACITY;

				m_FadeState = FADE_NONE;

				//���x���ύX
				Manager_Game::Instance()->OpenLevel();
			}
			break;
		}
	}
}
//=============================================================================
// �I���֐�
//=============================================================================
void Manager_Fade::Uninit()
{
	//�e�N�X�`���}�l�[�W���[�L���b�V��
	if (Manager_Texture* manager_Texture = Manager_Texture::Instance())
	{
		//�e�N�X�`���A�����[�h
		manager_Texture->UnloadTexture("Fade");
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void Manager_Fade::Draw()
{
	if (m_FadeState != FADE_NONE)
	{
		if (m_Texture != nullptr)
		{
			//�V�F�[�_�[�ݒ�
			Manager_Shader::Instance()->SetShader(m_ShaderType);

			// �e�N�X�`���ݒ�
			Renderer_DirectX11::Instance()->GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

			Int2 windowSize = MainWindow::Instance()->GetWindowSize();

			//�v���[�������_���[����`��
			Renderer_Polygon::Instance()->Draw2D(Vector2_Zero, Vector2{ static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) }, m_Color, false);
		}
	}
}

//=============================================================================
// �t�F�[�h�ݒ�֐�(�����̓t�F�[�h��ԂƎ���)
//=============================================================================
void Manager_Fade::SetFade(State _fadeState, float _time)
{
	m_FadeState = _fadeState;
	m_FadeTime  = _time;
	m_StartTime = static_cast<float>(clock());

	if (_fadeState == FADE_IN)
	{
		m_Color.a = MAX_FADE_OPACITY;
	}
	else if (_fadeState == FADE_OUT)
	{
		m_Color.a = MIN_FADE_OPACITY;
	}
}