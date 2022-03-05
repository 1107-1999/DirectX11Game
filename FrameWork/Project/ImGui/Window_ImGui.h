//=============================================================================
//
//  ImGuiウィンドウクラス [Window_ImGui.h]
//  Date   : 2021/2/3
//
//=============================================================================

#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <string>
#include <unordered_map>
#include <list>
#include "../../System/Main.h"
#include "../ImGui/imgui.h"


//=============================================================================
// クラス定義
//=============================================================================
class Window_ImGui
{
public:

	void SetWindowSize(Vector2 _size) { m_WindowSize = _size; }//ウィンドウサイズ変更
	void SetWindowName(std::string _set) { m_WindowName = _set; }//ウィンドウ名を変える関数
	void SetDrawData();//描画用データをセットする関数

	//初期化・更新・終了
	void Init();
	void Update();
	void Uninit();

	void SendBoolData(bool* _bool, std::string _dataName);//BOOLセット。
	void SendIntData(int* _int, std::string _dataName, int _min, int _max);//INTセット
	void SendFloatData(float* _float, std::string _dataName, float min, float max);//FLOATセット
	void SendStringData(std::string* _float, std::string _dataName);//ストリングセット
	void SendVector2Data(Vector2* _data, std::string _dataName, float min, float max);//VEC2セット
	void SendVector3Data(Vector3* _data, std::string _dataName, float min, float max);//VEC3セット
	void SendVector4Data(Vector4* _data, std::string _dataName, float min, float max);//VEC4セット
	void DebugLog(std::string, std::string _logName = "none", Vector4 _color = Vector4(1, 1, 1, 1),
		int dispCnt = (int)(60 * 2), bool _isUseKeyCheck = false);//ログ追加
	void DebugLogDontDestroy(std::string _data, std::string _key, Vector4 _color = Vector4(1, 1, 1, 1));//削除しないログを追加
	void AddButton(const char* _buttonName, bool& _link, ImVec2 _buttonSize = ImVec2(128.0f, 32.0f));//ウィンドウにボタン追加
	void AddColorPicker(const char* _colorPickerName, Vector4& _link);//カラーピッカーを追加

private:

	struct s_GuiIntData//GUI用INTデータ
	{
		int* data = nullptr;
		int min = -1000;
		int max = 1000;
	};

	struct s_GuiFloatData//GUI用FLOATデータ
	{
		float* data = nullptr;
		float min = -1000.0f;
		float max = 1000.0f;
	};

	struct s_GuiVec2Data//GUI用VEC2データ
	{
		Vector2* data = nullptr;
		float min = -1000.0f;
		float max = 1000.f;
	};

	struct s_GuiVec3Data//GUI用VEC3データ
	{
		Vector3* data = nullptr;
		float min = -1000.0f;
		float max = 1000.0f;
	};

	struct s_GuiVec4Data//GUI用VEC4データ
	{
		Vector4* data = nullptr;
		float min = -1000.0f;
		float max = 1000.0f;
	};

	struct s_LogData//GUI用ログデータ
	{
		std::string key = "";
		std::string data = "";
		int dispTime = 60 * 2;
		int cnt = 0;
		bool isDestroy = true;
		Vector4 color = Vector4(1, 1, 1, 1);
	};

	struct s_ButtonData//GUI用ボタンデータ
	{
		bool* link;
		ImVec2 size;
	};

	struct s_GuiColorData//Guiカラーピッカー用データ
	{
		float color[4] = {};
		Vector4* link;
	};

	Vector2 m_WindowSize;//ウィンドウサイズ
	std::string m_WindowName;//ウィンドウ名

	//デバッグする変数達のポインタを保存しておくList
	std::unordered_map<std::string, bool*>m_BoolList;
	std::unordered_map<std::string, s_GuiIntData>m_IntList;
	std::unordered_map<std::string, s_GuiFloatData>m_FloatList;
	std::unordered_map<std::string, std::string*>m_StringList;
	std::unordered_map<std::string, s_GuiVec2Data>m_Vec2List;
	std::unordered_map<std::string, s_GuiVec3Data>m_Vec3List;
	std::unordered_map<std::string, s_GuiVec4Data>m_Vec4List;
	std::unordered_map<std::string, s_ButtonData>m_ButtonList;
	std::unordered_map<std::string, s_GuiColorData>m_ColorList;
	std::list<s_LogData>m_LogList;
};
