//=============================================================================
//
//  FBX���f���R���|�[�l���g [Component_SkeletalMesh.h]
//  Date   : 2021/11/06
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <unordered_map>
#include <string>
#include "Component_StaticMesh.h"
#include "../../Project/Assimp/matrix4x4.h"

//=============================================================================
// �N���X��`
//=============================================================================
class Component_SkeletalMesh : public Component_StaticMesh
{
private:

	//�ό`�㒸�_�\����
	struct s_DFEFORM_VERTEX
	{
		aiVector3D Position;
		aiVector3D Normal;
		Color Color;

		int         BoneNum;
		int			BoneIndex[4];
		float       BoneWeight[4];
	};

	//�{�[���\����
	struct s_BONE
	{
		aiMatrix4x4 Matrix;
		aiMatrix4x4 AnimationMatrix;
		aiMatrix4x4 OffsetMatrix;
	};

	//2��̃A�j���̃u�����h�䗦
	float m_BlendRate;

	//�u�����h���A�j���̖��O
	std::string m_CurrentAnimName;

	//�u�����h��A�j���̖��O
	std::string m_NextAnimName;

	struct s_AnimationSet
	{
		const aiScene* animation;//�A�j���[�V����
		unsigned int frame;      //���݂̃t���[����
		bool isReverse;          //�t�Đ��t���O
	};

	//�A�j���[�V�����z��
	std::unordered_map<std::string, s_AnimationSet> m_Animation;

	//�ό`�㒸�_�f�[�^
	std::vector<s_DFEFORM_VERTEX>* m_DeformVertex;

	//�{�[��
	s_BONE* m_Bone;

	//�{�[���z��
	std::unordered_map<std::string, int> m_BoneTable;

	//�A�j���[�V�����u�����h�䗦�X�V���x
	float m_UpdateFrameTime;

	//�{�[���쐬
	void CreateBone(aiNode* node);

	//�{�[���}�g���N�X�X�V
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

public:

	Component_SkeletalMesh(class Actor* owner, int updatePriority) : 
		Component_StaticMesh(owner, updatePriority) {}

	//�������E�X�V�E�I��
	virtual void Init()override;	
	virtual void Update() override;	
	virtual void Uninit()override;  

	//�`��
	virtual void Draw();

	//�u�����h���[�g���Z
	void AddBlendRate(float rate);

	//�X�P���^�����b�V���ǂݍ���
	void LoadSkeletalMesh(const char *FileName);

	//�A�j���[�V�����ǂݍ���
	void LoadAnimation(const char *FileName, const char *AnimationName);

	//�폜�֐�
	void UnloadFBX();

	//�u�����h���A�j���[�V������ݒ�
	void SetCurrentAnimationName(std::string _name, unsigned int _frame = 0);

	//�u�����h��A�j���[�V������ݒ�
	void SetNextAnimationName(std::string _name, unsigned int _frame = 0);

	//�u�����h�A�j���[�V����2���ݒ�
	void SetAnimation(std::string _start, std::string _end,
		unsigned int _startFrame = 0, unsigned int _endFrame = 0);

	//�u�����h���A�j���[�V�����̃t���[������ݒ�
	void SetCurrentAnimationFrame(unsigned int _frame);

	//�u�����h��A�j���[�V�����̃t���[������ݒ�
	void SetNextAnimationFrame(unsigned int _frame);

	//�u�����h���A�j���[�V�������擾
	inline std::string GetCurrentAnimationName()const  { return m_CurrentAnimName; }
	
	//�u�����h��A�j���[�V�������擾
	inline std::string GetNextAnimationName()const { return m_NextAnimName; }

	//�u�����h���A�j���[�V�����t���[���擾
	inline unsigned int GetCurrentAnimationFrame()  { return m_Animation[m_CurrentAnimName].frame; }

	//�u�����h��A�j���[�V�����t���[���擾
	inline unsigned int GetNextAnimationFrame()  { return m_Animation[m_NextAnimName].frame; }

	//�u�����h���A�j���[�V�����t���[���̍ő吔�擾
	inline unsigned int GetCurrentAnimationFrameMax()  { return  m_CurrentAnimName != "none" ? m_Animation[m_CurrentAnimName].animation->mAnimations[0]->mNumChannels : 0; }

	//�u�����h��A�j���[�V�����t���[���̍ő吔�擾
	inline unsigned int GetNextAnimationFrameMax()  { return  m_NextAnimName != "none" ? m_Animation[m_NextAnimName].animation->mAnimations[0]->mNumChannels : 0; }

	//�u�����h���[�g�擾
	inline float GetBlendLate()const { return m_BlendRate; }

	//�u�����h���A�j���[�V�����݌v�Đ����Ԏ擾
	unsigned int GetCurrentAnimationPlayTime();

	//�u�����h��A�j���[�V�����݌v�Đ����Ԏ擾
	unsigned int GetNextAnimationPlayTime();

	//�A�j���[�V�����X�V���x�ݒ�
	inline void SetUpdateFlameTime(float _set) { m_UpdateFrameTime = _set; }

};
