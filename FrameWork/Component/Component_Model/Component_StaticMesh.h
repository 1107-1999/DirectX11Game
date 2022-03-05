//=============================================================================
//
//  静的メッシュコンポーネント [Component_StaticMesh.h]
//  Date   : 2021/12/08
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#pragma comment (lib,"Assimp/assimp.lib")
#include <unordered_map>
#include "Base/Component_ModelBase.h"
#include "../../Project/Assimp/cimport.h"
#include "../../Project/Assimp/scene.h"
#include "../../Project/Assimp/postprocess.h"

//=============================================================================
// クラス定義
//=============================================================================
class Component_StaticMesh : public Component_ModelBase
{
private:

	//頂点構造体
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

	//初期化・更新・終了
	void Init() override;
	void Update()override {};
	void Uninit()override;

	//描画
	void Draw();

	//静的メッシユ読み込み
	void LoadStaticMesh(const char *_fileName, std::string _texName = "none");

	//色設定
	void SetColor(Vector4 _color) override;

};