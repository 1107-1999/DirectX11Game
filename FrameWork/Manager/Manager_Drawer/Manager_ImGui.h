//=============================================================================
//
//  ImGUIマネージャー [Manager_ImGui.h]
//  Date   : 2021/11/16
//
//=============================================================================
#pragma once

#include <unordered_map>
#include <string>
#include "../../System/Singleton.h"
#include "../../Project/ImGui/Window_ImGui.h"


class Manager_ImGui : public Singleton<Manager_ImGui>
{
private:

	friend class Singleton<Manager_ImGui>;//シングルトン

	std::unordered_map<std::string, class Window_ImGui*>m_WindowList;//GUIウィンドウ配列
	class Window_ImGui* m_MainDebugWindow;//メインのdebugウィンドウ

public:

	virtual ~Manager_ImGui() {};

	//初期化・更新・終了
	void Init();
	void Update();
	void Uninit();

	//描画
	void Draw();

	//GUIウィンドウ作成。
	class Window_ImGui* CreateGuiWindow(std::string _windowName);
	class Window_ImGui* GetGuiWindow(std::string _windowName);//GUIウィンドウ取得

	void DestroyAllWindow();//全ウィンドウ削除

	class Window_ImGui* GetMainDebugWindow();//メインデバッグwindow取得

};