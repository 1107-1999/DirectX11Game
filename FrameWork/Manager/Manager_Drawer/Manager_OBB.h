//=============================================================================
//
//  OBB�R���|�[�l���g�}�l�[�W���[ [Manager_OBB.h]
//  Date   : 2021/11/10
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <unordered_map>
#include "../../System/Main.h"

//=============================================================================
// enum��`
//=============================================================================
//�R���W�����^�C�v
enum ACTOR_TYPE
{
	COLLISION_PLAYER,      //�v���C���[
	COLLISION_GUN,         //�e
	COLLISION_BULLET,      //�e
	COLLISION_GOAL,        //�S�[��
	COLLISION_GUN_TARGET,  //�e�̃^�[�Q�b�g
	COLLISION_BLOCK,       //�u���b�N
	COLLISION_CAMERA,      //�J����
	MAX_ACTOR_TYPE,        //�A�N�^�[�^�C�v��
};

//�����}�e���A��
enum PHYSICS_MATERIAL
{
	PM_CONCRETE,//�R���N���[�g
	PM_METAL,   //����
	PM_SAND,    //��
	PM_GLASS,   //�K���X
	PM_WOOD,    //��
	PM_IGNORE,  //��������
	MAX_PM_TYPE,//�����}�e���A���ő吔
};

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	bool         isHIT           = false;          //HIT������
	int          physicsMaterial = INVALID_ID;     //�����}�e���A��
	class Actor* hitActor        = nullptr;        //HIT�����A�N�^�[
	float        length          = 0.0f;		   //���C�̊J�n�ʒu����hitpos�܂ł̒���
	Vector3      hitPos          = Vector3_Zero;   //�q�b�g�����|�W�V����

} s_HIT_Result;//HIT���U���g�\����

//=============================================================================
// �N���X��`
//=============================================================================
class Manager_OBB
{
private:

	//�R���W�����`�����l��������OBB�R���|�[�l���g���X�g
	std::list<class Component_OBB*>m_ComponentList[ACTOR_TYPE::MAX_ACTOR_TYPE];

	//����r�p�\����
	struct s_OBBCompData
	{
		Vector3 axisX = { 1,0,0 };	//X��
		Vector3 axisY = { 0,1,0 };	//Y��
		Vector3 axisZ = { 0,0,1 };	//Z��
		float lengthX = 0.0f;		//X���̒���
		float lengthY = 0.0f;		//Y���̒���
		float lengthZ = 0.0f;		//Z���̒���
	};

	//�e���̒�����r
	bool CompareLength(s_OBBCompData* _A, s_OBBCompData* _B, Vector3* _separate, Vector3* _distance);

	//���C��`�悷�邽�߂̍\����
	struct s_DrawData
	{
		s_DrawData() :startPos(Vector3_Zero), endPos(Vector3_Zero),
			color(Color(1, 0, 0, 1)), time(0), timeMax(60 * 5) {};//������
		Vector3 startPos;	//���C�J�n�ʒu
		Vector3 endPos;		//���C�I���ʒu
		Color color;		//���C�̐F
		int time;			//���C�̐������Ԃ̃J�E���^�[
		int timeMax;		//���C�̐�������
	};

	//�`�撆�̃��C���X�g
	std::list<s_DrawData> m_DebugDrawRayList;

public:

	//OBB�R���|�[�l���g���X�g�o�^(��2�����̓R���W�����`�����l��)
	void AddComponent(class Component_OBB* _add, int _layer);

	//�X�V�E�I��
	void Update();
	void Uninit();

	//�`��
	void Draw();

	//OBB�̃I�[�o�[���b�v����
	bool OverlapJudgeOBB(Component_OBB* _component_OBBA, Component_OBB* _component_OBBB);

	//OBB�Ɠ_�̔���
	bool OverlapJudgeOBBandPoint(Component_OBB* _component_OBB, Vector3 _point);

	//���C�L���X�g
	s_HIT_Result Raycast(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 0.01f,int _drawRayLife = 60 * 3);

	//�����x���C�L���X�g
	s_HIT_Result RaycastHighAccuracy(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 0.01f, int _drawRayLife = 60 * 3);

	//�A�N�^�[�z���Ԃ����C�L���X�g
	std::vector<s_HIT_Result> RaycastGetHit(Vector3 _startPos, Vector3 _endPos,
		Actor* _ignoreMySelf = nullptr, bool _isDispRay = false, std::list<ACTOR_TYPE>_ignoreList = std::list<ACTOR_TYPE>(),
		Color _drawRayColor = Color(1, 0, 0, 1), float _accuracy = 0.01f, int _drawRayLife = 60 * 3);

};

