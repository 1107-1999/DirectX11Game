//=============================================================================
//
//  �t�F�[�h�}�l�[�W���[ [Manager_Fade.h]
//  Date   : 2021/11/16
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
class Manager_Fade
{
public:

	//�t�F�[�h���
	enum State
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	};

	//�������E�X�V�E�I��
	void Init();
	void Update();
	void Uninit();

	//�`��
	void Draw();

	//�t�F�[�h�ݒ�(�����̓t�F�[�h��ԂƎ���)
	void SetFade(State _fadeState, float _time);

	//���݂̃t�F�[�h��Ԏ擾
	inline State GetState()    const { return m_FadeState; }

	//���݂̃t�F�[�h���Ԏ擾
	inline float GetFadeTime() const { return m_FadeTime; }

private:

	//�V�F�[�_�[�^�C�v
	int m_ShaderType;

	//���݂̃t�F�[�h���
	State m_FadeState = FADE_NONE;

	//�t�F�[�h����
	float m_FadeTime  = 0.0f;

	//�t�F�[�h�J�n����
	float m_StartTime = 0.0f;

	//�F
	Color m_Color = Color(0.0f, 0.0f, 0.0f, 0.0f);

	//�e�N�X�`��
	ID3D11ShaderResourceView* m_Texture;

};