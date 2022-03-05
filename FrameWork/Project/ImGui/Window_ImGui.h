//=============================================================================
//
//  ImGui�E�B���h�E�N���X [Window_ImGui.h]
//  Date   : 2021/2/3
//
//=============================================================================

#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <string>
#include <unordered_map>
#include <list>
#include "../../System/Main.h"
#include "../ImGui/imgui.h"


//=============================================================================
// �N���X��`
//=============================================================================
class Window_ImGui
{
public:

	void SetWindowSize(Vector2 _size) { m_WindowSize = _size; }//�E�B���h�E�T�C�Y�ύX
	void SetWindowName(std::string _set) { m_WindowName = _set; }//�E�B���h�E����ς���֐�
	void SetDrawData();//�`��p�f�[�^���Z�b�g����֐�

	//�������E�X�V�E�I��
	void Init();
	void Update();
	void Uninit();

	void SendBoolData(bool* _bool, std::string _dataName);//BOOL�Z�b�g�B
	void SendIntData(int* _int, std::string _dataName, int _min, int _max);//INT�Z�b�g
	void SendFloatData(float* _float, std::string _dataName, float min, float max);//FLOAT�Z�b�g
	void SendStringData(std::string* _float, std::string _dataName);//�X�g�����O�Z�b�g
	void SendVector2Data(Vector2* _data, std::string _dataName, float min, float max);//VEC2�Z�b�g
	void SendVector3Data(Vector3* _data, std::string _dataName, float min, float max);//VEC3�Z�b�g
	void SendVector4Data(Vector4* _data, std::string _dataName, float min, float max);//VEC4�Z�b�g
	void DebugLog(std::string, std::string _logName = "none", Vector4 _color = Vector4(1, 1, 1, 1),
		int dispCnt = (int)(60 * 2), bool _isUseKeyCheck = false);//���O�ǉ�
	void DebugLogDontDestroy(std::string _data, std::string _key, Vector4 _color = Vector4(1, 1, 1, 1));//�폜���Ȃ����O��ǉ�
	void AddButton(const char* _buttonName, bool& _link, ImVec2 _buttonSize = ImVec2(128.0f, 32.0f));//�E�B���h�E�Ƀ{�^���ǉ�
	void AddColorPicker(const char* _colorPickerName, Vector4& _link);//�J���[�s�b�J�[��ǉ�

private:

	struct s_GuiIntData//GUI�pINT�f�[�^
	{
		int* data = nullptr;
		int min = -1000;
		int max = 1000;
	};

	struct s_GuiFloatData//GUI�pFLOAT�f�[�^
	{
		float* data = nullptr;
		float min = -1000.0f;
		float max = 1000.0f;
	};

	struct s_GuiVec2Data//GUI�pVEC2�f�[�^
	{
		Vector2* data = nullptr;
		float min = -1000.0f;
		float max = 1000.f;
	};

	struct s_GuiVec3Data//GUI�pVEC3�f�[�^
	{
		Vector3* data = nullptr;
		float min = -1000.0f;
		float max = 1000.0f;
	};

	struct s_GuiVec4Data//GUI�pVEC4�f�[�^
	{
		Vector4* data = nullptr;
		float min = -1000.0f;
		float max = 1000.0f;
	};

	struct s_LogData//GUI�p���O�f�[�^
	{
		std::string key = "";
		std::string data = "";
		int dispTime = 60 * 2;
		int cnt = 0;
		bool isDestroy = true;
		Vector4 color = Vector4(1, 1, 1, 1);
	};

	struct s_ButtonData//GUI�p�{�^���f�[�^
	{
		bool* link;
		ImVec2 size;
	};

	struct s_GuiColorData//Gui�J���[�s�b�J�[�p�f�[�^
	{
		float color[4] = {};
		Vector4* link;
	};

	Vector2 m_WindowSize;//�E�B���h�E�T�C�Y
	std::string m_WindowName;//�E�B���h�E��

	//�f�o�b�O����ϐ��B�̃|�C���^��ۑ����Ă���List
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
