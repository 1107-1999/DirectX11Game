//=============================================================================
//
//  ���C���E�B���h�E�@[MainWindow.h]
//  Date   : 2021/12/19
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../System/Main.h"
#include "../System/Singleton.h"

//=============================================================================
// �N���X��`
//=============================================================================
class MainWindow : public Singleton<MainWindow>
{
private:

	friend class Singleton<MainWindow>;
	HWND window;
	Int2 windowSize;
	float currentFps;//���ۂ̌��݂�FPS
	float optionFps;//�ݒ���FPS
	std::string className;
	std::string windowName;
	bool isFullscreen;
	bool isFullscreenChecker;
	WNDCLASSEX windowClass;

	double elapsedTime;//���̍X�V�o�ߎ���
	LARGE_INTEGER timeFrequency;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;

	HINSTANCE* hInstance;
	int* nCmdShow;
	WNDPROC* proc;

	void CreateMyWindow(HINSTANCE _hInstance, int _nCmdShow, WNDPROC _proc);

public:

	//������
	void Init(HINSTANCE _hInstance, int _nCmdShow, WNDPROC _proc);
    
	//�I��
	void Uninit();

	//FPS�v�Z
	bool CalculationFps();

	//�f�o�b�NFPS�\��
	void DebugFps();

	//�X�V�O���ԂƍX�V�㎞�Ԃ����ւ�
	void SwapStartAndEnd();

	//�t���X�N���[�����ǂ����擾
	bool GetIsFullscreen()const { return isFullscreen; }

	//�E�B���h�E�擾
	HWND GetWindow()const { return window; }

	//�E�B���h�E�T�C�Y�擾
	Int2 GetWindowSize()const { return windowSize; }

	//���߂�FPS�擾
	float GetCurrentFPS() { return currentFps; }
	float GetOptionFPS() { return optionFps; }

	//�t���[���擾
	float GetFrame() { return (1.0f / optionFps); }

	//FPS�ݒ�
	inline void SetFps(double _set) { optionFps = static_cast<float>(_set); }

	//�t���X�N���[�����[�h�؂�ւ�
	inline void SetisFullscreen(bool _set) { isFullscreen = _set; };

	//�E�B���h�E�̖��O�ݒ�
	inline void SetWindowName(const char* _name) { windowName = _name; }

};