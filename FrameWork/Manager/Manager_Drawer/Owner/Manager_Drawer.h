//=============================================================================
//
//  �`��}�l�[�W���[ [Manager_Drawer.h]
//  Date   : 2021/11/03
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <unordered_map>

//=============================================================================
// �N���X��`
//=============================================================================
class Manager_Drawer
{
private:

	//DirextX11�`��@�\�N���X�L���b�V��
	class Renderer_DirectX11*           m_Renderer_DX11;        

	//�e��`��@�\�����N���X�}�l�[�W���[
	class Manager_Cube*            m_Manager_Cube;         //�L���[�u�}�l�[�W���[
	class Manager_Model*           m_Manager_Model;        //���f���}�l�[�W���[
	class Manager_Billboard*       m_Manager_Billboard;    //�r���{�[�h�}�l�[�W���[
	class Manager_Sprite*          m_Manager_Sprite;       //�X�v���C�g�}�l�[�W���[
	class Manager_Fade*            m_Manager_Fade;         //�t�F�[�h�}�l�[�W���[
	class Manager_OBB*             m_Manager_OBB;          //OBB�}�l�[�W���[
	class Manager_Rigidbody*       m_Manager_Rigidbody;    //���̃}�l�[�W���[
	class HUD3D*                   m_HUD3D;				   //�g�pHUD3D
	class HUD*                     m_HUD;                  //�g�pHUD
	class Manager_Font2D*		   m_Manager_Font2D;       //�t�H���g�}�l�[�W���[�L���b�V���p
	class Manager_Font3D*		   m_Manager_Font3D;       //3D�t�H���g�}�l�[�W���[
	class Manager_ImGui*           m_Manager_ImGui;        //ImGui�}�l�[�W���[

    //�R���W�����f�o�b�O�\���t���O
	bool m_DebugDraw;             

	//�L���[�u�f�o�b�O�\���t���O
	bool m_DebugCube;                                     

	//����
	struct LIGHT*  m_Light;              

public:

	//�������E�I��
	void Init();      
	void Uninit(); 

	//�A�N�^�[�X�V�O�̍X�V
	void UpdateBefore();

	//�A�N�^�[�X�V��̍X�V
	void UpdateAfter(); 

	//�`��
	void Draw();      

	//3D�I�u�W�F�N�g�̂ݕ`��֐�
	void Draw3D();

	//�e��`��@�\�����N���X�}�l�[�W���[�ǉ��֐�

	void AddManager_Cube();         //�L���[�u�}�l�[�W���[�ǉ�
	void AddManager_Model();        //���f���}�l�[�W���[�ǉ�
	void AddManager_Billboard();    //�r���{�[�h�}�l�[�W���[�ǉ�
	void AddManager_Sprite();       //�X�v���C�g�}�l�[�W���[�ǉ�
	void AddManager_OBB();          //OBB�}�l�[�W���[�ǉ�
	void AddManager_Rigidbody();    //���̃}�l�[�W���[�ǉ�


	//�e��`��@�\�����N���X�}�l�[�W���[�擾�֐�
	inline class Manager_Cube*          GetManager_Cube()          const { return m_Manager_Cube; }         //�L���[�u�}�l�[�W���[�擾
	inline class Manager_Model*         GetManager_Model()         const { return m_Manager_Model; }        //���f���}�l�[�W���[�擾
	inline class Manager_Billboard*     GetManager_Billboard()     const { return m_Manager_Billboard; }    //�r���{�[�h�}�l�[�W���[�擾
	inline class Manager_Sprite*        GetManager_Sprite()        const { return m_Manager_Sprite; }       //�X�v���C�g�}�l�[�W���[�擾
	inline class Manager_Fade*          GetManager_Fade()          const { return m_Manager_Fade; }         //�t�F�[�h�}�l�[�W���[�擾
	inline class Manager_OBB*           GetManager_OBB()           const { return m_Manager_OBB; }          //OBB�}�l�[�W���[�擾
	inline class Manager_Rigidbody*     GetManager_Rigidbody()     const { return m_Manager_Rigidbody; }    //���̃}�l�[�W���[�擾
	inline class Manager_Font3D*        GetManager_Font3D()        const { return m_Manager_Font3D; }       //3D�t�H���g�}�l�[�W���[�擾

	//HUD�擾
	inline class HUD* GetHUD()const { return m_HUD; }                 

	//�f�o�b�O�L���[�u�̃t���O�擾
	inline bool GetDebugCube() const{ return m_DebugCube; }

	//HUD�ݒ�֐�
	template <typename T>
	void SetHUD()
	{
		//���݂�HUD������ꍇ
		if (m_HUD != nullptr)
		{
			m_HUD->Uninit();//�I��
			delete m_HUD;//�폜
			m_HUD = nullptr;//nullptr���
		}

		//HUD�ǂݍ���	
		if (m_HUD == nullptr)
		{
			m_HUD = new T();//HUD�쐬;
			m_HUD->Init();//������
		}
	}

};
