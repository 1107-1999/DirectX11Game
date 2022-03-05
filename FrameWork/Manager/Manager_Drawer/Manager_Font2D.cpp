//=============================================================================
//
//  �t�H���g2D�}�l�[�W���[ [Manager_Font2D.cpp]
//  Date   : 2021/11/28
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "../../System/Main.h"
#include "../../System/Exchanger.h"
#include "../../Renderer/Renderer_Polygon.h"
#include "../Manager_Shader.h"
#include "Manager_Font2D.h"


//=============================================================================
// �������֐�
//=============================================================================
void Manager_Font2D::Init()
{
	//�e�N���X������
	Manager_Font::Init();


}

//=============================================================================
// �I���֐�
//=============================================================================
void Manager_Font2D::Uninit()
{
	//�e�N���X�I������
	Manager_Font::Uninit();

	//���X�g�N���A
	cacheList.clear();
}

//=============================================================================
// �`��֐�
//=============================================================================
void Manager_Font2D::Draw()
{
	auto itr = cacheList.begin();

	for (; itr != cacheList.end(); itr++)
	{
		PrintfStatic2D(*itr->second.pPos, itr->second.pText->c_str());
	}
}

//=============================================================================
// 	�����w��q����̕����`��֐�
//=============================================================================
void Manager_Font2D::Printf2D(Vector2 _pos, const char * _text, ...)
{
	float allStringLength = 0.0f;
	std::string tempText = "";
	va_list list;
	va_start(list, _text);//�ψ����̏����w��q�̕�����string�ő�������������擾
	tempText = GetStringByArg(_text, list);
	va_end(list);

	//�|���S���`��
	m_Manager_Shader->SetShader(Manager_Shader::SHADER_TYPE::SHADER_UNLIT);

	float offsetX = _pos.x;//�������o�͂���ꏊ��1�����ڂ����offset
	int lengthOffset = 0;
	int start = 0;

	const float textLenHalfSize = Manager_Font::GetStringDif(tempText);

	//1�������e�N�X�`�����擾	- char++
	for (unsigned int byte = 0; byte < tempText.length();)
	{
		lengthOffset = 0;
		start = 0;

		//�����̃o�C�g������
		if (IsDBCSLeadByte(tempText[byte]))//2byte
		{
			start = byte;
			byte += 2;
			lengthOffset = 2;
		}
		else//1byte
		{
			start = byte;
			byte++;
			lengthOffset = 1;
		}

		std::string temp = tempText.substr(start, lengthOffset);

		//�������X�y�[�X�Ȃ�e�N�X�`���͍�炸�ɁA�e�N�X�`���T�C�Y���Ԋu���󂯂�
		if (temp == " " || temp == "�@")
		{
			offsetX += Manager_Font::GetSpaceFontSize(Exchanger::WSTRING_TO_STRING(m_PathFontName).c_str(),
				Exchanger::WSTRING_TO_STRING(m_DataFontName).c_str(), temp == " ");

			continue;
		}

		TCHAR buf[3] = {};
		strcpy(buf, temp.c_str());
		s_FontTextureData* tempTexture = Manager_Font::GetTextureData(Exchanger::WSTRING_TO_STRING(m_DataFontName).c_str(),
			Exchanger::WSTRING_TO_STRING(m_PathFontName).c_str(), buf, m_FontSize);
		m_DeviceContext->PSSetShaderResources(0, 1, &tempTexture->rv);

		m_Renderer_Polygon->Draw2D(
			Vector2{ _pos.x + offsetX + tempTexture->fontSize.x * 0.5f + tempTexture->relativeLeftUpPosFromCenter.x - textLenHalfSize,
			_pos.y + tempTexture->fontSize.y * 0.5f + tempTexture->difY },
			{ tempTexture->fontSize.x,tempTexture->fontSize.y}, m_FontColor);

		offsetX += tempTexture->nextCenterPoint * m_CharLength;
	}
}

//=============================================================================
// �@�����w��q�̂Ȃ������`��
//=============================================================================
void Manager_Font2D::PrintfStatic2D(Vector2 _pos, const char * _text)
{
	std::string tempText = _text;
	const float textLenHalfSize = GetStringDif(tempText);

	//�|���S���`��
	m_Manager_Shader->SetShader(Manager_Shader::SHADER_TYPE::SHADER_UNLIT);

	float offsetX = _pos.x;//�������o�͂���ꏊ��1�����ڂ����offset
	//1�������e�N�X�`�����擾	- char++
	for (unsigned int byte = 0, charNum = 0; byte < tempText.length(); charNum++)
	{
		int length = 0;
		int start = 0;

		//�����̃o�C�g������
		if (IsDBCSLeadByte(tempText[byte]))//2byte
		{
			start = byte;
			byte += 2;
			length = 2;
		}
		else//1byte
		{
			start = byte;
			byte++;
			length = 1;
		}

		TCHAR buf[3] = {};
		std::string temp = tempText.substr(start, length);
		strcpy(buf, temp.c_str());

		//�������X�y�[�X�Ȃ�e�N�X�`���͍�炸�ɁA�e�N�X�`���T�C�Y���Ԋu���󂯂�
		if (temp == " " || temp == "�@")
		{
			offsetX += GetSpaceFontSize(Exchanger::WSTRING_TO_STRING(m_PathFontName).c_str(),
				Exchanger::WSTRING_TO_STRING(m_DataFontName).c_str(), temp == " ");

			continue;
		}

		s_FontTextureData* tempTexture = GetTextureData(Exchanger::WSTRING_TO_STRING(m_DataFontName).c_str(),
			Exchanger::WSTRING_TO_STRING(m_PathFontName).c_str(), buf, m_FontSize);

		m_DeviceContext->PSSetShaderResources(0, 1, &tempTexture->rv);

		m_Renderer_Polygon->Draw2D(Vector2{ _pos.x + offsetX + tempTexture->fontSize.x * 0.5f + tempTexture->relativeLeftUpPosFromCenter.x - textLenHalfSize,
			_pos.y + tempTexture->fontSize.y * 0.5f + tempTexture->difY},
			{ tempTexture->fontSize.x,tempTexture->fontSize.y }, m_FontColor);

		offsetX += tempTexture->nextCenterPoint * m_CharLength;
	}
}

//=============================================================================
// �@������̃|�C���^��o�^���ĊO���當����𑀍�
//=============================================================================
void Manager_Font2D::AddPrintData(Vector2 & _pos, std::string & _text, const char * _key)
{
	if (cacheList.count(_key) == 0)
	{
		s_CachePrint2DData temp;
		temp.pPos = &_pos;
		temp.pText = &_text;
		cacheList[_key] = temp;
	}
}
