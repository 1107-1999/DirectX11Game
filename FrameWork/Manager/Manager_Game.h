//=============================================================================
//
//  �Q�[���}�l�[�W���[ [Manager_Game.h]
//  Date   : 2021/11/02
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <vector>
#include "../System/Singleton.h"
#include "../Level/Base/Level.h"
#include "../PlayerController/Base/PlayerController.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Manager_Game : public Singleton<Manager_Game>
{
private: 
	friend class Singleton<Manager_Game>;//�V���O���g��

	class Level*             m_Level;    //���݂̃��x��
	class Level*             m_NextLevel;//���̃��x��

	class PlayerController*  m_PlayerController;//�v���C���[�R���g���[���[

public:

	//�������E�X�V�E�I��
	void Init();  
	void Update();
	void Uninit();

	//�`��
	void Draw(); 

	inline class Level*            GetLevel()            const { return m_Level;}            //���݂̃��x���擾
	inline class PlayerController* GetPlayerController() const { return m_PlayerController; }//���݂̃v���C���[�R���g���[���[�擾


	//���x���ύX�֐�(�t�F�[�h����)
	template <typename T>
	void LoadLevelByClass(float _time)
	{
		m_NextLevel = new T();//���x���쐬

		//���݂̃��x��������ꍇ�t�F�[�h�J�n
		if (m_Level != nullptr)
		{
			m_Level->SetFade(_time);
		}
		else if (m_NextLevel != nullptr)
		{//���݂̃��x���Ȃ��ꍇ

			//���x���ǂݍ���	
			m_Level = m_NextLevel;//�ǂݍ���
			m_Level->Init();//������

		}
	}

	//���̃��x���ɕύX
	void OpenLevel()
	{
		//���݂̃��x��������ꍇ�I��
		if (m_Level != nullptr)
		{
			m_Level->Uninit();//�I��
			delete m_Level;//�폜
			m_Level = nullptr;//nullptr���
		}

		//�V�������x���ǂݍ���	
		if (m_NextLevel != nullptr)
		{
			m_Level = m_NextLevel;
			m_Level->Init();//������
		}
	}

	//�v���C���[�R���g���[���[�ύX�֐�
	template <typename T>
	void SetPlayerController()
	{
		if (m_PlayerController != nullptr)
		{//���݂̃v���C���[�R���g���[���[�I��
			delete m_PlayerController;//�폜
			m_PlayerController = nullptr;//nullptr���
		}
		m_PlayerController = new T();//�쐬
		m_PlayerController->Init();//������
	}

};