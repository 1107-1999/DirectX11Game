//=============================================================================
//
//  FBXモデルコンポーネント [Component_SkeletalMesh.h]
//  Date   : 2021/11/06
//
//=============================================================================
#pragma once

//=============================================================================
// インクルード
//=============================================================================
#include <unordered_map>
#include <string>
#include "Component_StaticMesh.h"
#include "../../Project/Assimp/matrix4x4.h"

//=============================================================================
// クラス定義
//=============================================================================
class Component_SkeletalMesh : public Component_StaticMesh
{
private:

	//変形後頂点構造体
	struct s_DFEFORM_VERTEX
	{
		aiVector3D Position;
		aiVector3D Normal;
		Color Color;

		int         BoneNum;
		int			BoneIndex[4];
		float       BoneWeight[4];
	};

	//ボーン構造体
	struct s_BONE
	{
		aiMatrix4x4 Matrix;
		aiMatrix4x4 AnimationMatrix;
		aiMatrix4x4 OffsetMatrix;
	};

	//2種のアニメのブレンド比率
	float m_BlendRate;

	//ブレンド元アニメの名前
	std::string m_CurrentAnimName;

	//ブレンド先アニメの名前
	std::string m_NextAnimName;

	struct s_AnimationSet
	{
		const aiScene* animation;//アニメーション
		unsigned int frame;      //現在のフレーム数
		bool isReverse;          //逆再生フラグ
	};

	//アニメーション配列
	std::unordered_map<std::string, s_AnimationSet> m_Animation;

	//変形後頂点データ
	std::vector<s_DFEFORM_VERTEX>* m_DeformVertex;

	//ボーン
	s_BONE* m_Bone;

	//ボーン配列
	std::unordered_map<std::string, int> m_BoneTable;

	//アニメーションブレンド比率更新速度
	float m_UpdateFrameTime;

	//ボーン作成
	void CreateBone(aiNode* node);

	//ボーンマトリクス更新
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

public:

	Component_SkeletalMesh(class Actor* owner, int updatePriority) : 
		Component_StaticMesh(owner, updatePriority) {}

	//初期化・更新・終了
	virtual void Init()override;	
	virtual void Update() override;	
	virtual void Uninit()override;  

	//描画
	virtual void Draw();

	//ブレンドレート加算
	void AddBlendRate(float rate);

	//スケルタルメッシュ読み込み
	void LoadSkeletalMesh(const char *FileName);

	//アニメーション読み込み
	void LoadAnimation(const char *FileName, const char *AnimationName);

	//削除関数
	void UnloadFBX();

	//ブレンド元アニメーションを設定
	void SetCurrentAnimationName(std::string _name, unsigned int _frame = 0);

	//ブレンド先アニメーションを設定
	void SetNextAnimationName(std::string _name, unsigned int _frame = 0);

	//ブレンドアニメーション2種を設定
	void SetAnimation(std::string _start, std::string _end,
		unsigned int _startFrame = 0, unsigned int _endFrame = 0);

	//ブレンド元アニメーションのフレーム数を設定
	void SetCurrentAnimationFrame(unsigned int _frame);

	//ブレンド先アニメーションのフレーム数を設定
	void SetNextAnimationFrame(unsigned int _frame);

	//ブレンド元アニメーション名取得
	inline std::string GetCurrentAnimationName()const  { return m_CurrentAnimName; }
	
	//ブレンド先アニメーション名取得
	inline std::string GetNextAnimationName()const { return m_NextAnimName; }

	//ブレンド元アニメーションフレーム取得
	inline unsigned int GetCurrentAnimationFrame()  { return m_Animation[m_CurrentAnimName].frame; }

	//ブレンド先アニメーションフレーム取得
	inline unsigned int GetNextAnimationFrame()  { return m_Animation[m_NextAnimName].frame; }

	//ブレンド元アニメーションフレームの最大数取得
	inline unsigned int GetCurrentAnimationFrameMax()  { return  m_CurrentAnimName != "none" ? m_Animation[m_CurrentAnimName].animation->mAnimations[0]->mNumChannels : 0; }

	//ブレンド先アニメーションフレームの最大数取得
	inline unsigned int GetNextAnimationFrameMax()  { return  m_NextAnimName != "none" ? m_Animation[m_NextAnimName].animation->mAnimations[0]->mNumChannels : 0; }

	//ブレンドレート取得
	inline float GetBlendLate()const { return m_BlendRate; }

	//ブレンド元アニメーション累計再生時間取得
	unsigned int GetCurrentAnimationPlayTime();

	//ブレンド先アニメーション累計再生時間取得
	unsigned int GetNextAnimationPlayTime();

	//アニメーション更新速度設定
	inline void SetUpdateFlameTime(float _set) { m_UpdateFrameTime = _set; }

};
