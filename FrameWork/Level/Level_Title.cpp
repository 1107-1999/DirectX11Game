//=============================================================================
//
//  �^�C�g�� [Level_Title.h]
//  Date   : 2021/1/09
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Level_Title.h"
#include "../PlayerController/PC_Title.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Drawer/Owner/Manager_Drawer.h"
#include "../Actor/3D/Camera.h"
#include "../Actor/2D/Atomosphere/Atomosphere.h"
#include "../Actor/HUD/HUD_Title.h"

//=============================================================================
// �������֐�
//=============================================================================
void Level_Title::Init()
{
	Level::Init();

	//�v���C���[�R���g���[���[��PC_Title�ɐݒ�
	Manager_Game::Instance()->SetPlayerController<PC_Title>();

	//���\�[�X�ǂݍ���
	Atomosphere::Load();

	//�`��}�l�[�W���[�ǉ�
	if (Manager_Drawer* manager_Drawer = GetManager_Drawer())
	{//�`��}�l�[�W���[���L���b�V��

		//�e��G���[�ԍ��ǉ�
		manager_Drawer->AddManager_Model();        //FBX�}�l�[�W���[�ǉ�
		manager_Drawer->AddManager_Billboard();    //�r���{�[�h�}�l�[�W���[�ǉ�
		manager_Drawer->AddManager_Sprite();       //�X�v���C�g�}�l�[�W���[�ǉ�
		manager_Drawer->AddManager_OBB();          //OBB�}�l�[�W���[�ǉ�
		manager_Drawer->AddManager_Rigidbody();    //Rigidbody�}�l�[�W���[�ǉ�

	
		//��C�ǉ�
		AddActor<Atomosphere>();

		//�J�����ǉ�
		Camera* gamera = AddActor<Camera>();
		gamera->SetPosition(Vector3{ 0.0f ,40.0f ,-70.0f });
		gamera->SetRotation(Vector3{ DegToRad(8.5f) ,DegToRad(0.0f) ,DegToRad(0.0f)});

		//HUD�ݒ�
		manager_Drawer->SetHUD<HUD_Title>();
	}

}
//=============================================================================
// �X�V�֐�
//=============================================================================
void Level_Title::Update()
{
	//���N���X�X�V
	Level::Update();
}

//=============================================================================
// �I���֐�
//=============================================================================
void Level_Title::Uninit()
{
	//���N���X�I��
	Level::Uninit();

	//���\�[�X���
	Atomosphere::Unload();
};