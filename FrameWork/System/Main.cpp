//=============================================================================
//
//  メイン　[Main.cpp]
//  Date   : 2021/12/19
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "Main.h"
#include "../Renderer/Renderer_DirectX11.h"
#include "../Manager/Manager_Audio.h"
#include "../Manager/Manager_Game.h"
#include "../Manager/Manager_Drawer/Manager_ImGui.h"
#include "../System/MainWindow.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//=============================================================================
	// 初期化
	//=============================================================================

	//メインウィンドウ初期化
	MainWindow* mainWindow = MainWindow::Instance();
	mainWindow->Init(hInstance, nCmdShow, WndProc);
	MSG msg;


	//毎フレーム使用するシングルトンをキャッシュ
	Input*              input         = Input::Instance();             //インプットキャッシュ
	Renderer_DirectX11* renderer_DX11 = Renderer_DirectX11::Instance();//DX11描画機構キャッシュ
	Manager_Game*       manager_game  = Manager_Game::Instance();      //ゲームマネージャーキャッシュ
	Manager_Audio*      manager_audio = Manager_Audio::Instance();     //オーディオマネージャーキャッシュ
	Manager_ImGui*      manager_imgui = Manager_ImGui::Instance();     //ImGuiマネージャーキャッシュ


	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			if (mainWindow->CalculationFps())continue;

			//ゲームの処理
			{

			//=============================================================================
			// 更新処理
			//=============================================================================

				input->Update();        //インプット更新
				manager_game->Update(); //ゲームマネージャー更新
				manager_audio->Update();//サウンドマネージャーの更新
				manager_imgui->Update();//ImGuiの更新

			//=============================================================================
			// 描画処理
			//=============================================================================

				//ゲームマネージャー描画
				manager_game->Draw(); 

			}
			
			mainWindow->DebugFps();//fps表示
			mainWindow->SwapStartAndEnd();//入れ替え
		}
	}

	//=============================================================================
	// 終了処理
	//=============================================================================

	MainWindow::Instance()->Uninit();//ウィンドウ終了処理

	return (int)msg.wParam;
}

//ImGui用
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//imGUI用
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}

	// マウスメッセージ処理
	switch (uMsg)
	{
	case WM_ACTIVATEAPP:
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Input::Instance()->Mouse_ProcessMessage(uMsg, wParam, lParam);
		break;
	}

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
