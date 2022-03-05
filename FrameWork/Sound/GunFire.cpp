//=============================================================================
//
//  �e���T�E���h�N���X [GunFire.cpp]
//  Date   : 2021/2/06
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "GunFire.h"
#include "../Manager/Manager_Audio.h"

//=============================================================================
// �萔��`
//=============================================================================
constexpr int MAX_SOUND = 4;//���

//=============================================================================
// ���\�[�X�ǂݍ��݊֐�
//=============================================================================
void GunFire::Load()
{
	//�I�[�f�B�I�}�l�[�W���[�L���b�V��
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{

		//�e��
		manager_audio->Load_Resource("GunFire1", "ROM\\Sound\\SE\\Gun\\Fire1.WAV");
		manager_audio->Load_Resource("GunFire2", "ROM\\Sound\\SE\\Gun\\Fire2.WAV");
		manager_audio->Load_Resource("GunFire3", "ROM\\Sound\\SE\\Gun\\Fire3.WAV");
		manager_audio->Load_Resource("GunFire4", "ROM\\Sound\\SE\\Gun\\Fire4.WAV");

	}
}

//=============================================================================
// ���\�[�X����֐�
//=============================================================================
void GunFire::Unload()
{
	//�I�[�f�B�I�}�l�[�W���[�L���b�V��
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{
		//�e��
		manager_audio->Unload_Resource("GunFire1");
		manager_audio->Unload_Resource("GunFire2");
		manager_audio->Unload_Resource("GunFire3");
		manager_audio->Unload_Resource("GunFire4");

	}
}

//=============================================================================
// �������֐�
//=============================================================================
void GunFire::Init()
{
	//���U�[�u
	m_GunFireSounds.reserve(MAX_SOUND);
	
	//�e��
    m_GunFireSounds.push_back("GunFire1");
    m_GunFireSounds.push_back("GunFire2");
    m_GunFireSounds.push_back("GunFire3");
    m_GunFireSounds.push_back("GunFire4");

}

//=============================================================================
// �I���֐�
//=============================================================================
void GunFire::Uninit()
{
	//�N���A
	m_GunFireSounds.clear();
}

//=============================================================================
// �e���Đ��֐�
//=============================================================================
void GunFire::Play()
{
	if (Manager_Audio* manager_audio = Manager_Audio::Instance())
	{//�L���b�V��

		//�L���[���烉���_���ɍĐ�
		int random = rand() % MAX_SOUND;
	
		manager_audio->Play(m_GunFireSounds[random], 0);

	}
}

