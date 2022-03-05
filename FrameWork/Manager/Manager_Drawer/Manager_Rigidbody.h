//=============================================================================
//
//  Rigidbody�}�l�[�W���[ [Manager_Rigidbody.h]
//  Date   : 2021/11/22
//
//=============================================================================
#pragma once

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <unordered_map>
#include "../../Project/Bullet/src/btBulletDynamicsCommon.h"
#include "../../Renderer/Renderer_Polygon.h"
#include "../../System/Main.h"

#if defined(_DEBUG)
#pragma comment(lib, "Bullet/bin/BulletCollision_Debug.lib")
#pragma comment(lib, "Bullet/bin/BulletDynamics_Debug.lib")
#pragma comment(lib, "Bullet/bin/LinearMath_Debug.lib")
#else
#pragma comment(lib, "Bullet/bin/BulletCollision.lib")
#pragma comment(lib, "Bullet/bin/BulletDynamics.lib")
#pragma comment(lib, "Bullet/bin/LinearMath.lib")
#endif

//=============================================================================
// �N���X��`
//=============================================================================
class Manager_Rigidbody
{

public:

	//���̍\����
	typedef struct 
	{
		btMotionState* state; //���
		btRigidBody*   body;//����

	} s_RigidBody;


	//�������E�X�V�E�I��
	void Init();
	void Update();
	void Uninit();

	//�`��
	void Draw();

	//�X�t�B�A�^���̒ǉ�(�����̓X�P�[���E���W�E����)
	s_RigidBody* AddSphere(const Vector3& _scale, const Vector3& _position, float _mass);

	//�{�b�N�X�^���̒ǉ�(�����̓X�P�[���E���W�E����)
	s_RigidBody* AddBox(const Vector3& _scale, const Vector3& _position, float _mass);

	//�J�v�Z���^���̒ǉ�(�����͔��a�E�����E���W�E����)
	s_RigidBody* AddCapsule(float _radius, float _height, const Vector3& _position, const Vector3& _rotation, float _mass);

	//���ʌ^���̒ǉ�(�����͌����E���W�E����)
	s_RigidBody* AddStaticPlane(const Vector3& _up, const Vector3& _position, float _mass);

	//Bullet���[���h�擾
	inline btDynamicsWorld* GebtDynamicsWorld() { return m_DynamicsWorld; }

	//���̂���������
	void RemoveRigidBody(btRigidBody* _rigidBody);

private:

	//Bullet���[���h
	btDynamicsWorld*   m_DynamicsWorld = 0;

	//�f�o�b�O�`��N���X
	class MyDebugDraw* m_MyDebugDraw;      

	//���̒ǉ�(�����̓R���W�����̌^�E���ʁE�g�����X�t�H�[��)
	s_RigidBody* AddRigidBody(btCollisionShape* _shape, btScalar _mass, const btTransform& _transform);

};

// �f�o�b�O�`��N���X
class MyDebugDraw : public btIDebugDraw
{
	//�f�o�b�O���[�h
	int Debug_mode;

	//���`��֐�
	void drawLine(const btVector3& _from, const btVector3& _to,
		const btVector3& _color);

	//�����F���`��֐�
	void drawLine(const btVector3& _from, const btVector3& _to,
		const btVector3& _fromColor, const btVector3& _toColor);


	/* PointOnB�ɁA�Փ˓_��`�� */
	void drawContactPoint(const btVector3& _PointOnB, const btVector3& _normalOnB,
		btScalar _distance, int _lifeTime,
		const btVector3& _color){}


	/* �x���\�� */
	void reportErrorWarning(const char* _warningString){}

	/* �w���ԍ��W�ɕ�����\�� */
	void draw3dText(const btVector3& _location, const char* _textString){}

public:

	/* �f�o�b�O���[�h�w�� */
	inline void setDebugMode(int _debugMode){Debug_mode = _debugMode;}

	/* ���݂̃f�o�b�O���[�h��ԋp */
	inline int getDebugMode() const override{return Debug_mode;}


};