//=============================================================================
//
//  ImGUI�}�l�[�W���[ [Manager_ImGui.cpp]
//  Date   : 2021/11/16
//
//=============================================================================
#include "../../System/Main.h"
#include "../../System/MainWindow.h"
#include "../../Renderer/Renderer_DirectX11.h"

#include "../../Project/ImGui/imgui.h"
#include "../../Project/ImGui/imgui_impl_dx11.h"
#include "../../Project/ImGui/imgui_impl_win32.h"
#include "../../Project/ImGui/Window_ImGui.h"
#include "Manager_ImGui.h"

//=============================================================================
// �֐���`
//=============================================================================
//=============================================================================
// ������
//=============================================================================
void Manager_ImGui::Init()
{
	m_MainDebugWindow = nullptr;
	GetMainDebugWindow();//���C���f�o�b�O�E�B���h�E�쐬

	//GUI�X�^�C��������
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	//�L���b�V���p�ϐ����Z�b�g
	ID3D11Device* pDev = Renderer_DirectX11::Instance()->GetDevice();
	ID3D11DeviceContext* pDevContext = Renderer_DirectX11::Instance()->GetDeviceContext();

	//GUI�`��p�̏�����
	ImGui_ImplWin32_Init(MainWindow::Instance()->GetWindow());
	ImGui_ImplDX11_Init(pDev, pDevContext);
}

//=============================================================================
// �X�V
//=============================================================================
void Manager_ImGui::Update()
{
	//�o�^����Ă���GUI��S�čX�V
	auto itr = m_WindowList.begin();
	for (; itr != m_WindowList.end(); itr++)
	{
		if (Window_ImGui* temp = itr->second)
		{
			temp->Update();
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void Manager_ImGui::Draw()
{
	//GUI�t���[���X�V
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//GUI�܂Ƃ߂čX�V
	auto itr = m_WindowList.begin();
	for (; itr != m_WindowList.end(); itr++)
	{
		if (Window_ImGui* temp = itr->second)
		{
			temp->SetDrawData();//�`�悷��f�[�^���Z�b�g
		}
	}

	//GUI�`��
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

//=============================================================================
// �I������
//=============================================================================
void Manager_ImGui::Uninit()
{
	//�S�ẴE�B���h�E���폜
	DestroyAllWindow();
}

//=============================================================================
// ImGuiWindow�쐬
//=============================================================================
Window_ImGui* Manager_ImGui::CreateGuiWindow(std::string _windowName)
{
	if (m_WindowList.count(_windowName) == 0)
	{
		Window_ImGui* temp = new Window_ImGui();
		m_WindowList[_windowName] = temp;
		temp->SetWindowSize(Vector2(100, 100));
		temp->SetWindowName(_windowName);
	}
	return m_WindowList[_windowName];
}

//=============================================================================
// �o�^����Ă���ImGuiWindow���擾
//=============================================================================
Window_ImGui* Manager_ImGui::GetGuiWindow(std::string _windowName)
{
	if (m_WindowList.count(_windowName) > 0)
	{
		return m_WindowList[_windowName];
	}
	return nullptr;
}

//=============================================================================
// �o�^����Ă���S�Ă�Window���폜
//=============================================================================
void Manager_ImGui::DestroyAllWindow()
{
	//�S�ẴE�B���h�E���폜
	auto itr = m_WindowList.begin();
	for (; itr != m_WindowList.end();)
	{
		auto itrOld = itr;
		itr++;
		delete (*itrOld).second;
		(*itrOld).second = nullptr;
	}
	m_WindowList.erase(m_WindowList.begin(), m_WindowList.end());
}

//=============================================================================
// ���C����ImGuiWindow���擾
//=============================================================================
Window_ImGui * Manager_ImGui::GetMainDebugWindow()
{
	//���C���E�B���h�E���Ȃ���΍쐬
	if (m_MainDebugWindow == nullptr)
	{
		m_MainDebugWindow = CreateGuiWindow("mainDebugWindow");
	}

	return m_MainDebugWindow;
}
