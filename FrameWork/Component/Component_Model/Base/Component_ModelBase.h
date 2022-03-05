//=============================================================================
//
//  ���f���֘A�R���|�[�l���g��� [Componet_ModelBase.h]
//  Date   : 2021/12/08
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <unordered_map>
#include "../../Base/Component.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Component_ModelBase : public Component
{
protected:

	//�V�F�[�_�[�^�C�v
	int m_ShaderType;

	//�`��X�P�[���䗦
	float m_ScaleRate;

	//���W�I�t�Z�b�g�l
	Vector3 m_PositionOffset;

	//��]�I�t�Z�b�g�l
	Vector3	m_RotationOffset;

	//���_&�C���f�b�N�X�o�b�t�@�[
	ID3D11Buffer** m_VertexBuffer;
	ID3D11Buffer** m_IndexBuffer;

	//���f���J���[
	Vector4 m_ModelColor;

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture;

public:

	Component_ModelBase(class Actor* _owner, int _updatePriority) :
		Component(_owner, _updatePriority) {}

	//�`��֐�
	virtual void Draw() = 0;

	//���W�I�t�Z�b�g�l�ݒ�
	inline void SetPositionOffset(Vector3 _set) { m_PositionOffset = _set; }

	//��]�I�t�Z�b�g�l�ݒ�
	inline void SetRotationOffset(Vector3 _set) { m_RotationOffset = _set; }

	//�V�F�[�_�[�擾�E�ݒ�
	inline int  GetShaderType() { return m_ShaderType; }
	inline void SetShaderType(int _type) { m_ShaderType = _type; }


	//�T�C�Y�䗦�ݒ�
	inline void SetScaleRate(float _scaleRate) { m_ScaleRate = _scaleRate; }

	//�F�擾�E�ݒ�
	inline Vector4 GetColor() { return m_ModelColor; }
	virtual inline void SetColor(Vector4 _color) { m_ModelColor; }

};