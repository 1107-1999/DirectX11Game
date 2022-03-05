//=============================================================================
//
//  �ÓI���b�V���R���|�[�l���g [Component_StaticMesh.h]
//  Date   : 2021/12/08
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#pragma comment (lib,"Assimp/assimp.lib")
#include <unordered_map>
#include "Base/Component_ModelBase.h"
#include "../../Project/Assimp/cimport.h"
#include "../../Project/Assimp/scene.h"
#include "../../Project/Assimp/postprocess.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Component_StaticMesh : public Component_ModelBase
{
private:

	//���_�\����
	struct s_STATICMESH_VERTEX
	{
		Vector3 Position;
		Vector3 Normal;
		Color Color;
	};

protected:

	const aiScene* m_AiScene = NULL;

public:

	Component_StaticMesh(class Actor* _owner, int _updatePriority) : 
		Component_ModelBase(_owner, _updatePriority) {}

	//�������E�X�V�E�I��
	void Init() override;
	void Update()override {};
	void Uninit()override;

	//�`��
	void Draw();

	//�ÓI���b�V���ǂݍ���
	void LoadStaticMesh(const char *_fileName, std::string _texName = "none");

	//�F�ݒ�
	void SetColor(Vector4 _color) override;

};