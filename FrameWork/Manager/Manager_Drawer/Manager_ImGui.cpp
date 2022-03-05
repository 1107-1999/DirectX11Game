//=============================================================================
//
//  ImGUIマネージャー [Manager_ImGui.cpp]
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
// 関数定義
//=============================================================================
//=============================================================================
// 初期化
//=============================================================================
void Manager_ImGui::Init()
{
	m_MainDebugWindow = nullptr;
	GetMainDebugWindow();//メインデバッグウィンドウ作成

	//GUIスタイル初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	//キャッシュ用変数をセット
	ID3D11Device* pDev = Renderer_DirectX11::Instance()->GetDevice();
	ID3D11DeviceContext* pDevContext = Renderer_DirectX11::Instance()->GetDeviceContext();

	//GUI描画用の初期化
	ImGui_ImplWin32_Init(MainWindow::Instance()->GetWindow());
	ImGui_ImplDX11_Init(pDev, pDevContext);
}

//=============================================================================
// 更新
//=============================================================================
void Manager_ImGui::Update()
{
	//登録されているGUIを全て更新
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
// 描画
//=============================================================================
void Manager_ImGui::Draw()
{
	//GUIフレーム更新
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//GUIまとめて更新
	auto itr = m_WindowList.begin();
	for (; itr != m_WindowList.end(); itr++)
	{
		if (Window_ImGui* temp = itr->second)
		{
			temp->SetDrawData();//描画するデータをセット
		}
	}

	//GUI描画
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

//=============================================================================
// 終了処理
//=============================================================================
void Manager_ImGui::Uninit()
{
	//全てのウィンドウを削除
	DestroyAllWindow();
}

//=============================================================================
// ImGuiWindow作成
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
// 登録されているImGuiWindowを取得
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
// 登録されている全てのWindowを削除
//=============================================================================
void Manager_ImGui::DestroyAllWindow()
{
	//全てのウィンドウを削除
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
// メインのImGuiWindowを取得
//=============================================================================
Window_ImGui * Manager_ImGui::GetMainDebugWindow()
{
	//メインウィンドウがなければ作成
	if (m_MainDebugWindow == nullptr)
	{
		m_MainDebugWindow = CreateGuiWindow("mainDebugWindow");
	}

	return m_MainDebugWindow;
}
