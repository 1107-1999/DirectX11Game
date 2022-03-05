//=============================================================================
//
//  メインウィンドウ　[MainWindow.h]
//  Date   : 2021/12/19
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include "../System/Main.h"
#include "../System/Singleton.h"

//=============================================================================
// クラス定義
//=============================================================================
class MainWindow : public Singleton<MainWindow>
{
private:

	friend class Singleton<MainWindow>;
	HWND window;
	Int2 windowSize;
	float currentFps;//実際の現在のFPS
	float optionFps;//設定上のFPS
	std::string className;
	std::string windowName;
	bool isFullscreen;
	bool isFullscreenChecker;
	WNDCLASSEX windowClass;

	double elapsedTime;//一回の更新経過時間
	LARGE_INTEGER timeFrequency;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;

	HINSTANCE* hInstance;
	int* nCmdShow;
	WNDPROC* proc;

	void CreateMyWindow(HINSTANCE _hInstance, int _nCmdShow, WNDPROC _proc);

public:

	//初期化
	void Init(HINSTANCE _hInstance, int _nCmdShow, WNDPROC _proc);
    
	//終了
	void Uninit();

	//FPS計算
	bool CalculationFps();

	//デバックFPS表示
	void DebugFps();

	//更新前時間と更新後時間を入れ替え
	void SwapStartAndEnd();

	//フルスクリーンかどうか取得
	bool GetIsFullscreen()const { return isFullscreen; }

	//ウィンドウ取得
	HWND GetWindow()const { return window; }

	//ウィンドウサイズ取得
	Int2 GetWindowSize()const { return windowSize; }

	//直近のFPS取得
	float GetCurrentFPS() { return currentFps; }
	float GetOptionFPS() { return optionFps; }

	//フレーム取得
	float GetFrame() { return (1.0f / optionFps); }

	//FPS設定
	inline void SetFps(double _set) { optionFps = static_cast<float>(_set); }

	//フルスクリーンモード切り替え
	inline void SetisFullscreen(bool _set) { isFullscreen = _set; };

	//ウィンドウの名前設定
	inline void SetWindowName(const char* _name) { windowName = _name; }

};