//=============================================================================
//
//  ImGuiウィンドウクラス [Window_ImGui.cpp]
//  Date   : 2021/2/3
//
//=============================================================================


//=============================================================================
// インクルード
//=============================================================================
#include "Window_ImGui.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"

//=============================================================================
//  描画用データをGuiにセット
//=============================================================================
void Window_ImGui::SetDrawData()
{
	//このウィンドウの描画開始
	ImGui::Begin(m_WindowName.c_str());

	//BOOL表示
	auto boolItr = m_BoolList.begin();
	for (; boolItr != m_BoolList.end(); boolItr++)
	{
		ImGui::Checkbox(boolItr->first.c_str(), boolItr->second);
	}

	//INT表示
	auto intItr = m_IntList.begin();
	for (; intItr != m_IntList.end(); intItr++)
	{
		ImGui::SliderInt(intItr->first.c_str(), intItr->second.data, intItr->second.min, intItr->second.max);
	}

	//FLOAT表示
	auto floatItr = m_FloatList.begin();
	for (; floatItr != m_FloatList.end(); floatItr++)
	{
		ImGui::SliderFloat(floatItr->first.c_str(), floatItr->second.data, floatItr->second.min, floatItr->second.max);
	}

	//VECTOR2表示
	auto vec2Itr = m_Vec2List.begin();
	for (; vec2Itr != m_Vec2List.end(); vec2Itr++)
	{
		ImGui::SliderFloat2(vec2Itr->first.c_str(), *vec2Itr->second.data, vec2Itr->second.min, vec2Itr->second.max);
	}

	//VECTOR3表示
	auto vec3Itr = m_Vec3List.begin();
	for (; vec3Itr != m_Vec3List.end(); vec3Itr++)
	{
		ImGui::DragFloat3(vec3Itr->first.c_str(), *vec3Itr->second.data, 0.1f, vec3Itr->second.min, vec3Itr->second.max);
	}

	//VECTOR4表示
	auto vec4Itr = m_Vec4List.begin();
	for (; vec4Itr != m_Vec4List.end(); vec4Itr++)
	{
		ImGui::SliderFloat4(vec4Itr->first.c_str(), *vec4Itr->second.data, vec4Itr->second.min, vec4Itr->second.max);
	}

	//STRING表示
	auto stringItr = m_StringList.begin();
	for (; stringItr != m_StringList.end(); stringItr++)
	{
		ImGui::Text(stringItr->second->c_str());
	}

	//ボタン表示
	auto buttonItr = m_ButtonList.begin();
	for (; buttonItr != m_ButtonList.end(); buttonItr++)
	{
		memset(buttonItr->second.link, false, sizeof(bool));

		//押された時に現在の状態を変える
		if (ImGui::Button(buttonItr->first.c_str(), buttonItr->second.size))
		{
			memset(buttonItr->second.link, true, sizeof(bool));
		}
	}

	auto colorItr = m_ColorList.begin();
	for (; colorItr != m_ColorList.end(); colorItr++)
	{
		if (ImGui::ColorEdit4(colorItr->first.c_str(), colorItr->second.color))
		{
			colorItr->second.link->x = colorItr->second.color[0];
			colorItr->second.link->y = colorItr->second.color[1];
			colorItr->second.link->z = colorItr->second.color[2];
			colorItr->second.link->w = colorItr->second.color[3];
		}
	}

	//デバッグログ表示
	for (auto& i : m_LogList)
	{
		ImGui::TextColored(ImVec4(i.color.x, i.color.y, i.color.z, i.color.w), i.data.c_str());
	}

	//このウィンドウの描画終了
	ImGui::End();
}

//=============================================================================
//  初期化関数
//=============================================================================
void Window_ImGui::Init()
{
	m_BoolList.clear();
	m_IntList.clear();
	m_FloatList.clear();
	m_StringList.clear();
	m_Vec2List.clear();
	m_Vec3List.clear();
	m_Vec4List.clear();
	m_ButtonList.clear();
	m_ColorList.clear();
	m_LogList.clear();
}

//=============================================================================
//  更新関数
//=============================================================================
void Window_ImGui::Update()
{
	for (auto& i : m_LogList)
	{
		i.cnt++;
	}
	m_LogList.remove_if([](s_LogData log) {return (log.cnt > log.dispTime) && log.isDestroy; });
}

//=============================================================================
//  終了関数
//=============================================================================
void Window_ImGui::Uninit()
{
	m_BoolList.clear();
	m_IntList.clear();
	m_FloatList.clear();
	m_StringList.clear();
	m_Vec2List.clear();
	m_Vec3List.clear();
	m_Vec4List.clear();
	m_ButtonList.clear();
	m_ColorList.clear();
	m_LogList.clear();
}

//=============================================================================
//  boolをGuiにセットする関数
//=============================================================================
void Window_ImGui::SendBoolData(bool* _data, std::string _dataName)
{
	if (m_BoolList.count(_dataName) == 0)
	{
		m_BoolList[_dataName] = _data;
	}
}

//=============================================================================
//  intをGuiにセットする関数
//=============================================================================
void Window_ImGui::SendIntData(int* _data, std::string _dataName, int min, int max)
{
	if (m_IntList.count(_dataName) == 0)
	{
		s_GuiIntData temp;
		temp.data = _data;
		temp.min = min;
		temp.max = max;
		m_IntList[_dataName] = temp;
	}
}

//=============================================================================
//  FloatをGuiにセットする関数
//=============================================================================
void Window_ImGui::SendFloatData(float* _data, std::string _dataName, float min, float max)
{
	if (m_FloatList.count(_dataName) == 0)
	{
		s_GuiFloatData temp;
		temp.data = _data;
		temp.min = min;
		temp.max = max;
		m_FloatList[_dataName] = temp;
	}
}

//=============================================================================
//  StringをGuiにセットする関数
//=============================================================================
void Window_ImGui::SendStringData(std::string* _data, std::string _dataName)
{
	if (m_StringList.count(_dataName) == 0)
	{
		m_StringList[_dataName] = _data;
	}
}

//=============================================================================
//  Vector2をGuiにセットする関数
//=============================================================================
void Window_ImGui::SendVector2Data(Vector2* _data, std::string _dataName, float min, float max)
{
	if (m_Vec2List.count(_dataName) == 0)
	{
		s_GuiVec2Data temp;
		temp.data = _data;
		temp.min = min;
		temp.max = max;
		m_Vec2List[_dataName] = temp;
	}
}

//=============================================================================
//  Vector3をGuiにセットする関数
//=============================================================================
void Window_ImGui::SendVector3Data(Vector3* _data, std::string _dataName, float min, float max)
{
	if (m_Vec3List.count(_dataName) == 0)
	{
		s_GuiVec3Data temp;
		temp.data = _data;
		temp.min = min;
		temp.max = max;
		m_Vec3List[_dataName] = temp;
	}
}

//=============================================================================
//  Vector4をGuiにセットする関数
//=============================================================================
void Window_ImGui::SendVector4Data(Vector4* _data, std::string _dataName, float min, float max)
{
	if (m_Vec4List.count(_dataName) == 0)
	{
		s_GuiVec4Data temp;
		temp.data = _data;
		temp.min = min;
		temp.max = max;
		m_Vec4List[_dataName] = temp;
	}
}

//=============================================================================
//  boolをGuiにセットする関数
//=============================================================================
void Window_ImGui::AddButton(const char* _buttonName, bool & _link, ImVec2 _buttonSize)
{
	if (m_ButtonList.count(_buttonName) == 0)
	{
		s_ButtonData temp;
		temp.link = &_link;
		temp.size = _buttonSize;
		m_ButtonList[_buttonName] = temp;
	}
}

//=============================================================================
//  色用のvector4をGuiにセットする関数
//=============================================================================
void Window_ImGui::AddColorPicker(const char * _colorPickerName, Vector4& _link)
{
	if (m_ColorList.count(_colorPickerName) == 0 && _link)
	{
		s_GuiColorData temp;
		temp.link = &_link;
		temp.color[0] = _link.x;
		temp.color[1] = _link.y;
		temp.color[2] = _link.z;
		temp.color[3] = _link.w;
		m_ColorList[_colorPickerName] = temp;
	}
}

//=============================================================================
//  StringをGuiにセットする関数
//=============================================================================
void Window_ImGui::DebugLog(std::string _data, std::string _logName, Vector4 _color, int _dispCnt, bool _isUseKeyCheck)
{
	//配列のサイズを超える前にLOG全削除
	if (m_LogList.max_size() <= m_LogList.size())
	{
		m_LogList.clear();
	}

	//一回のみの追加
	if (_isUseKeyCheck)
	{
		//同じキーを持つログがあったら登録しない
		for (auto& i : m_LogList)
		{
			if (i.key == _logName)
			{
				i.data = _data;
				i.color = _color;
				return;
			}
		}

		//ログデータ登録
		s_LogData temp;
		temp.data = _data;
		temp.dispTime = _dispCnt;
		temp.key = _logName;
		temp.cnt = 0;
		temp.isDestroy = true;
		temp.color = _color;

		m_LogList.push_back(temp);
	}
	else//Updateで毎フレーム追加
	{
		//ログデータ登録
		s_LogData temp;
		temp.data = _data;
		temp.dispTime = _dispCnt;
		temp.key = _logName;
		temp.cnt = 0;
		temp.isDestroy = true;
		temp.color = _color;

		//既にログが登録されていたら追加しない
		char tempName[256] = {};
		sprintf(tempName, "%s", _logName.c_str());
		if (_isUseKeyCheck)
		{
			sprintf(tempName, "%s_%d", _logName.c_str(), m_LogList.size());
		}
		temp.key = tempName;

		m_LogList.push_back(temp);
	}
}

//=============================================================================
//  削除しないstringをGuiにセットする関数
//=============================================================================
void Window_ImGui::DebugLogDontDestroy(std::string _data, std::string _key, Vector4 _color)
{
	//配列のサイズを超える前にLOG全削除
	if (m_LogList.max_size() <= m_LogList.size())
	{
		m_LogList.clear();
	}

	//同じキーを持つログがあったら登録しない
	for (auto& i : m_LogList)
	{
		if (i.key == _key)
		{
			i.data = _data;
			i.color = _color;
			return;
		}
	}

	//ログデータ登録
	s_LogData temp;
	temp.data = _data;
	temp.dispTime = -1;
	temp.key = _key;
	temp.cnt = 0;
	temp.isDestroy = false;
	temp.color = _color;

	m_LogList.push_back(temp);
}
