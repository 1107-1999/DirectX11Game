//=============================================================================
//
//  �`��}�l�[�W���[ [Manager_Drawer.cpp]
//  Date   : 2021/11/16
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <string>
#include "Manager_Drawer.h"
#include "../Manager_Cube.h"
#include "../Manager_Model.h"
#include "../Manager_Billboard.h"
#include "../Manager_Sprite.h"
#include "../Manager_Fade.h"
#include "../Manager_OBB.h"
#include "../Manager_Rigidbody.h"
#include "../Manager_ImGui.h"
#include "../Manager_Font2D.h"
#include "../../Manager_Game.h"
#include "../../../Level/Base/Level.h"
#include "../../../System/MainWindow.h"
#include "../../../System/Color.h"
#include "../../../System/Exchanger.h"
#include "../../../Actor/3D/Camera.h"
#include "../../../Actor/HUD/Base/HUD.h"
#include "../../../Renderer/Renderer_DirectX11.h"

//=============================================================================
// �萔��`
//=============================================================================
const Vector3 LIGHT_OFFSET = { -5.0f, 12.5f, -10.0f };//���C�g���W

//=============================================================================
// �������֐�
//=============================================================================
void Manager_Drawer::Init()
{
	//DirextX11�`��@�\�N���X���L���b�V��
	m_Renderer_DX11 = Renderer_DirectX11::Instance();

	//�e��}�l�[�W���[������
	m_Manager_Model     = nullptr;//���f���}�l�[�W���[nullptr��
	m_Manager_Billboard = nullptr;//�r���{�[�h�}�l�[�W���[nullptr��
	m_Manager_Sprite    = nullptr;//�X�v���C�g�}�l�[�W���[nullptr��
	m_Manager_OBB       = nullptr;//OBB�}�l�[�W���[nullptr��
	m_Manager_Rigidbody = nullptr;//���̃}�l�[�W���[nullptr��
	m_HUD               = nullptr;//HUD��nullptr��
	m_Manager_Font2D    = Manager_Font2D::Instance();//�L���b�V��


	m_Manager_Fade      = new Manager_Fade;//�t�F�[�h�}�l�[�W���[����
	m_Manager_Fade->Init();//�t�F�[�h�}�l�[�W���[������
	m_Manager_Fade->SetFade(Manager_Fade::FADE_IN, 3.0f);

	m_Manager_ImGui = Manager_ImGui::Instance();//ImGui�}�l�[�W���[�L���b�V��

	m_DebugDraw     = false;//�f�o�b�O�R���W������\��
	m_DebugCube     = false;//�f�o�b�O�L���[�u��\��                             

	//�����v�Z
	m_Light = new LIGHT;

	//�X�e�[�^�X
	m_Light->Enable = true;
	m_Light->Direction = Vector4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&m_Light->Direction, &m_Light->Direction);
	m_Light->Ambient   = Color(0.1f, 0.1f, 0.1f, 1.0f);
	m_Light->Diffuse   = Color(1.0f, 1.0f, 1.0f, 1.0f);

	Int2 windowSize = MainWindow::Instance()->GetWindowSize();

	//2�����T�C�Y�����l
	Vector2 Scale2D = Vector2{ static_cast<float>(windowSize.x),static_cast<float>(windowSize.y) };

	//���C�g�J�����̃r���[�s����쐬
	D3DXMatrixLookAtLH(&m_Light->ViewMatrix, &LIGHT_OFFSET,
		&Vector3(0.0f, 0.0f, 0.0f), &Vector3(0.0f, 1.0f, 0.0f));

	//���C�g�J�����̃v���W�F�N�V�����s����쐬
	D3DXMatrixPerspectiveFovLH(&m_Light->ProjectionMatrix, 1.0f,
		Scale2D.x / Scale2D.y, 5.0f, 30.0f);

	//�f�o�b�O�E�B���h�E�쐬
	Window_ImGui* debugWindow = Manager_ImGui::Instance()->CreateGuiWindow("Manager_Drawer");
	Vector4 tempColor = ColorSpace::Yellow;
	std::string tempColorString = Exchanger::VEC4_TO_STRING(tempColor);
	debugWindow->DebugLog(tempColorString, "none", tempColor);

	//�f�o�b�O�R���W����
	debugWindow->SendBoolData(&m_DebugDraw, "DebugCollision");

	//�f�o�b�O�L���[�u
	debugWindow->SendBoolData(&m_DebugCube, "DebugCube");


}

//=============================================================================
// �A�N�^�[�X�V�O�̍X�V�֐�
//=============================================================================
void Manager_Drawer::UpdateBefore()
{
	//���̍X�V
	if (m_Manager_Rigidbody != nullptr)
	{
		m_Manager_Rigidbody->Update();
	}
}

//=============================================================================
// �A�N�^�[�X�V��̍X�V�֐�
//=============================================================================
void Manager_Drawer::UpdateAfter()
{
	//���C�gnull�`�F�b�N
	if (m_Light != nullptr)
	{
		//�J����������ꍇ
		if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
		{
			//�X�e�[�^�X
			m_Light->Enable = true;
			m_Light->Direction = Vector4(1.0f, -1.0f, 1.0f, 0.0f);
			D3DXVec4Normalize(&m_Light->Direction, &m_Light->Direction);
			m_Light->Ambient = Color(0.1f, 0.1f, 0.1f, 1.0f);
			m_Light->Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);

			//�E�B���h�E�T�C�Y�擾
			Int2 windowSize = MainWindow::Instance()->GetWindowSize();

			//2�����T�C�Y�����l
			Vector2 Scale2D = Vector2{ static_cast<float>(windowSize.x),static_cast<float>(windowSize.y) };

			//�I�[�i�[���W
			Vector3 position = camera->GetOwner()->GetPosition();

			//���C�g�J�����̃r���[�s����쐬
			D3DXMatrixLookAtLH(&m_Light->ViewMatrix, &Vector3(LIGHT_OFFSET.x + position.x, LIGHT_OFFSET.y + position.y, LIGHT_OFFSET.z + position.z),
				&position, &Vector3(0.0f, 1.0f, 0.0f));

			//���C�g�J�����̃v���W�F�N�V�����s����쐬
			D3DXMatrixPerspectiveFovLH(&m_Light->ProjectionMatrix, 1.0f,
				Scale2D.x / Scale2D.y, 5.0f, 30.0f);
		}	
	}

	//HUD�X�V
	if (m_HUD != nullptr)
	{
		m_HUD->Update();
	}
	//OBB�}�l�[�W���[�X�V
	if (m_Manager_OBB != nullptr)
	{
		m_Manager_OBB->Update();
	}
	//�t�F�[�h�X�V
	if (m_Manager_Fade != nullptr)
	{
		m_Manager_Fade->Update();
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void Manager_Drawer::Draw()
{
	if (m_Renderer_DX11 != nullptr)
	{//DirextX11�`��@�\�N���X������ꍇ

	    //�����ݒ�
		m_Renderer_DX11->SetLight(*m_Light);

		//�r���[�ݒ�
		m_Renderer_DX11->SetViewMatrix(&m_Light->ViewMatrix);
		m_Renderer_DX11->SetProjectionMatrix(&m_Light->ProjectionMatrix);
		

		//�e�`��J�n
		m_Renderer_DX11->BeginDepth();

		//�e�Ή�3D���f���`��
		Draw3D();

		//�ʏ�`��J�n
		m_Renderer_DX11->Begin();

		if (Camera* camera = Manager_Game::Instance()->GetLevel()->GetActor<Camera>())
		{//�J����������ꍇ

			//�J�������_�ݒ�
			camera->SetView();

			//3D���f���`��
			Draw3D();

			//�r���{�[�h�`��
			if (m_Manager_Billboard != nullptr)
			{
				m_Manager_Billboard->Draw();
			}
			//�f�o�b�O�\���I���Ȃ�R���W�����`��
			if (m_DebugDraw)
			{
				//���̕`��
				if (m_Manager_Rigidbody != nullptr)
				{
					m_Manager_Rigidbody->Draw();
				}

				//OBB&���C�`��
				if (m_Manager_OBB != nullptr)
				{
					m_Manager_OBB->Draw();
				}
			}


		}
		//�X�v���C�g�`��
		if (m_Manager_Sprite != nullptr)
		{
			m_Manager_Sprite->Draw();
		}
		//�t�H���g2D
		{
			m_Manager_Font2D->Draw();
		}
		//HUD�`��
		if (m_HUD != nullptr)
		{
			m_HUD->Draw();
		}
	
		//�t�F�[�h�`��
		if (m_Manager_Fade != nullptr)
		{
			m_Manager_Fade->Draw();
		}
		//ImGUI�`��
		if (m_Manager_ImGui != nullptr)
		{
			m_Manager_ImGui->Draw();
		}

		//�`��I��
		m_Renderer_DX11->End();
	}
}


//=============================================================================
// �I���֐�
//=============================================================================
void Manager_Drawer::Uninit()
{

	//�����I��
	if (m_Light != nullptr)
	{
		delete m_Light;//�폜
		m_Light = nullptr;//nullptr���
	}

	//�L���[�u�}�l�[�W���[�I��
	if (m_Manager_Cube != nullptr)
	{
		m_Manager_Cube->Uninit();//�I��
		delete m_Manager_Cube;//�폜
		m_Manager_Cube = nullptr;//nullptr���
	}
	//���f���}�l�[�W���[�I��
	if (m_Manager_Model != nullptr)
	{
		m_Manager_Model->Uninit();//�I��
		delete m_Manager_Model;//�폜
		m_Manager_Model = nullptr;//nullptr���
	}
	//�r���{�[�h�}�l�[�W���[�I��
	if (m_Manager_Billboard != nullptr)
	{
		m_Manager_Billboard->Uninit();//�I��
		delete m_Manager_Billboard;//�폜
		m_Manager_Billboard = nullptr;//nullptr���
	}
	//OBB�}�l�[�W���[�I��
	if (m_Manager_OBB != nullptr)
	{
		m_Manager_OBB->Uninit();//�I��
		delete m_Manager_OBB;//�폜
		m_Manager_OBB = nullptr;//nullptr���
	}
	//���̃}�l�[�W���[�I��
	if (m_Manager_Rigidbody != nullptr)
	{
		m_Manager_Rigidbody->Uninit();//�I��
		delete m_Manager_Rigidbody;//�폜
		m_Manager_Rigidbody = nullptr;//nullptr���
	}
	//�X�v���C�g�}�l�[�W���[�I��
	if (m_Manager_Sprite != nullptr)
	{
		m_Manager_Sprite->Uninit();//�I��
		delete m_Manager_Sprite;//�폜
		m_Manager_Sprite = nullptr;//nullptr���
	}
	//HUD�I��
	if (m_HUD != nullptr)
	{
		m_HUD->Uninit();//�I��
		delete m_HUD;//�폜
		m_HUD = nullptr;//nullptr���
	}

	//�t�F�[�h�}�l�[�W���[�I��
	if (m_Manager_Fade != nullptr)
	{
		delete m_Manager_Fade;//�폜
		m_Manager_Fade = nullptr;//nullptr���
	}

	Manager_ImGui::Instance()->Uninit();//���X�g��S�ăN���A
}

//=============================================================================
// �`��֐�(3D�I�u�W�F�N�g�̂�)
//=============================================================================
void Manager_Drawer::Draw3D()
{
	//�L���[�u�`��
	if (m_Manager_Cube != nullptr)
	{
		m_Manager_Cube->Draw();
	}

	//���f���`��
	if (m_Manager_Model != nullptr)
	{
		m_Manager_Model->Draw();
	}
}


//=============================================================================
// �}�l�[�W���[�ǉ��֐�
//=============================================================================
//�L���[�u�}�l�[�W���[�ǉ�
void Manager_Drawer::AddManager_Cube()
{
	m_Manager_Cube = new Manager_Cube;
}
//���f���}�l�[�W���[�ǉ�
void Manager_Drawer::AddManager_Model()
{
	m_Manager_Model = new Manager_Model;
}
//�r���{�[�h�}�l�[�W���[�ǉ�
void Manager_Drawer::AddManager_Billboard()
{
	m_Manager_Billboard = new Manager_Billboard;
}
//�X�v���C�g�}�l�[�W���[�ǉ�
void Manager_Drawer::AddManager_Sprite()
{
	m_Manager_Sprite = new Manager_Sprite;
}
//OBB�}�l�[�W���[�ǉ�
void Manager_Drawer::AddManager_OBB()
{
	m_Manager_OBB = new Manager_OBB;
}

//���̃}�l�[�W���[�ǉ�
void Manager_Drawer::AddManager_Rigidbody()
{
	m_Manager_Rigidbody = new Manager_Rigidbody;
	m_Manager_Rigidbody->Init();//������
}

