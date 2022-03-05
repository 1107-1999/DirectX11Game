//=============================================================================
//
//  �V�F�[�_�[�}�l�[�W���[ [Manager_Shader.h]
//  Date   : 2021/11/05
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <unordered_map>
#include"../System/Singleton.h"
#include "../System/Main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Manager_Shader : public Singleton<Manager_Shader>
{
private:

	friend class Singleton<Manager_Shader>;//�V���O���g��

	struct s_Shader
	{
		ID3D11InputLayout*    VertexLayout;//IL
		ID3D11VertexShader*   VertexShader;//VS
		ID3D11PixelShader*    PixelShader; //PS
	};//�V�F�[�_�[���

	//�V�F�[�_�[�z��
	std::unordered_map < int, s_Shader > m_Shaders;

public:

	//�������E�I��
	void Init(void);
	void Uninit(void);

	//�K�p�V�F�[�_�[�ݒ�
	void SetShader(int _key);

	enum SHADER_TYPE//�V�F�[�_�[�^�C�v
	{
		SHADER_NONE = 0,
		SHADER_UNLIT,
		SHADER_VERTEX_LIGHTING,
		SHADER_PIXEL_LIGHTING,
		SHADER_ATOMOSPHERE,
		SHADER_TOON,
		SHADER_NORMALMAP,
		SHADER_ENVMAP,
		SHADER_DEPTHSHADOW
	};
};
