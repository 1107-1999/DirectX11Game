//=============================================================================
//
//  ImGUI�}�l�[�W���[ [Manager_ImGui.h]
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

	friend class Singleton<Manager_ImGui>;//�V���O���g��

	std::unordered_map<std::string, class Window_ImGui*>m_WindowList;//GUI�E�B���h�E�z��
	class Window_ImGui* m_MainDebugWindow;//���C����debug�E�B���h�E

public:

	virtual ~Manager_ImGui() {};

	//�������E�X�V�E�I��
	void Init();
	void Update();
	void Uninit();

	//�`��
	void Draw();

	//GUI�E�B���h�E�쐬�B
	class Window_ImGui* CreateGuiWindow(std::string _windowName);
	class Window_ImGui* GetGuiWindow(std::string _windowName);//GUI�E�B���h�E�擾

	void DestroyAllWindow();//�S�E�B���h�E�폜

	class Window_ImGui* GetMainDebugWindow();//���C���f�o�b�Owindow�擾

};