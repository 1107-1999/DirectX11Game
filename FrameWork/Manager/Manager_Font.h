//=============================================================================
//
//  �t�H���g�}�l�[�W���[ [Manager_Font.h]
//  Date   : 2021/12/19
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <unordered_map>
#include "../System/Main.h"
#include "../Renderer/Renderer_DirectX11.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Manager_Font
{
public:

	//�t�H���g�e�N�X�`���\����
	struct s_FontTextureData
	{
		s_FontTextureData() :rv(nullptr), fontSize(Vector2(0, 0)),
			nextCenterPoint(0.0f), relativeLeftUpPosFromCenter(Vector2(0, 0)), difY(0.0f) {};//������
		ID3D11ShaderResourceView* rv;//�e�N�X�`��
		Vector2 fontSize;			//�t�H���g�T�C�Y
		float nextCenterPoint;		//���݂̃t�H���g�̎��ɕ\�����镶���̊J�n�ʒu
		Vector2 relativeLeftUpPosFromCenter;//���_���獶��܂ł̋���
		float difY = 0.0f;			//���_���C������̍�������
	};

	//������̑�����
	enum e_Aligning
	{
		center,//������
		right,//�E����
		left,//������
		MAX
	};

	virtual ~Manager_Font() {};//�p���p���z�f�X�g���N�^

	void SetFont(std::wstring _pathFontName, std::wstring _dataFontName);//�g�p����t�H���g��ݒ�
	inline void SetAilgningMode(e_Aligning _mode) { m_AligningMode = _mode; }//���������Z�b�g
	inline void SetFontSize(float _size) { m_FontSize = _size; }//�t�H���g�T�C�Y�ݒ�
	inline void SetFontColor(Color _color) { m_FontColor = _color; }//�t�H���g�J���[�ݒ�
	inline void SetCharLength(float _set) { m_CharLength = _set; }//�����Ԃ̋�����ݒ�
	inline void SetFontWeight(int _set) { m_FontWeight = _set; }//�t�H���g�̑�����ݒ�
	inline void SetIsUseItalic(bool _set) { m_IsUseItalic = _set; }//�C�^���b�N�̂ɂ��邩�ǂ���

	//��x�����Ă�Init
	void InitMaster();

	//�������E�I��
	virtual void Init();
	virtual void Uninit();

	//�`��
	virtual void Draw() = 0;

private:

	//�t�H���g�̃e�N�X�`���L���b�V��
	static std::unordered_map<std::string, s_FontTextureData*>m_FontTextures;

protected:

	//�L���b�V���ϐ�
	struct ID3D11DeviceContext* m_DeviceContext;
	class Renderer_Polygon*     m_Renderer_Polygon;
	class Manager_Shader*       m_Manager_Shader;

	//�e�L�X�g�X�^�C���ϐ�
	bool m_IsUseItalic;//�C�^���b�N�̂ɂ��邩
	int m_FontWeight;//�����̑���
	std::wstring m_PathFontName;//�t�H���g�̃p�X��̖��O
	std::wstring m_DataFontName;//�t�H���g�̃f�[�^�̖��O
	e_Aligning m_AligningMode;//�������ϐ�
	float m_FontSize;//�t�H���g�T�C�Y
	Color m_FontColor;//�t�H���g�J���[
	float m_CharLength;//�����Ԃ̋���

	//1�������e�N�X�`��������ăL���b�V������֐�
	s_FontTextureData* CreateSingleCharFontTexture(const char* _fontName,
		const char* _fontDataName, TCHAR* _c, float _fontSize);

	//���p�A�S�p�̃X�y�[�X�p�̃e�N�X�`�����쐬����֐�
	float GetSpaceFontSize(const char* _fontPathName,
		const char* _fontDataName, bool isMini);

	//�L���b�V�������e�N�X�`�����擾
	//���L���b�V������Ă��Ȃ���������̂ŁAnull�͕Ԃ��Ȃ��B
	s_FontTextureData* GetTextureData(const char* _fontName,
		const char* _fontPathName, TCHAR* _c, float _fontSize);

	//�e�L�X�g�̍��[����E�[�܂ł̋������擾
	float GetStringDif(std::string _text);

	//�ψ������珑���w��̓��e��char�ɂ���string���擾
	std::string GetStringByArg(const char* _text, va_list _argList);


};