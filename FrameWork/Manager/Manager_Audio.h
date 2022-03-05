//=============================================================================
//
//  �I�[�f�B�I�}�l�[�W���[ [Manager_Audio.h]
//  Date   : 2021/12/19
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include "../System/WavePlayer.h"
#include "../System/Singleton.h"

//=============================================================================
// �萔�錾
//=============================================================================
constexpr int MAX_AUDIO        = 100; //�ő吔
constexpr int ALL_USE_AUDIO    = -1;  //�S�Ďg�p��

//=============================================================================
// �N���X��`
//=============================================================================
class Manager_Audio : public Singleton<Manager_Audio>
{
public:

	//�������E�X�V�E�I��
	void Init();
	void Update();
	void Uninit();

	//�T�E���h�Đ��֐�(��2�����̓��[�v�񐔁�XAUDIO2_LOOP_INFINITE�Ŗ������[�v)
	int Play(const char* _key, int loop);

	//�w��̃T�E���h�̍Đ��I��
	void End(int _num) { m_Player[_num]->Destroy(); }

	//���ʐݒ�
	inline void SetVolume(int _num, float volume) { m_Player[_num]->SetVolume(volume); }

	//�g�p���Ă��Ȃ��v�f������
	int IsUsePlayer();

	//�����̗v�f���g���Ă��邩�̊m�F
	bool IsInElement(int _num);

	//�t�F�[�h
	void Fade(int _num, float _time, float _volume);

	//���\�[�X�ǂݍ���
	void Load_Resource(const char* _key, LPCSTR _fileName);

	//�w��v�f�̃��\�[�X���
	void Unload_Resource(const char* _key);

	//�S���\�[�X���
	void Unload_Resource_All();

	//�w��v�f�̎擾
	inline LPCSTR GetResource(const char* _key) { return m_Resource[_key]; }


private:

	//XAudio2�N���X
	IXAudio2* m_XAudio2;

	//�}�X�^�[�{�C�X
	IXAudio2MasteringVoice* m_MasterVoice;

	//�T�E���h�̎��̔z��
	std::vector<WavePlayer*> m_Player;

	//���\�[�X�Ǘ��z��
	std::unordered_map<std::string, LPCSTR> m_Resource;


};